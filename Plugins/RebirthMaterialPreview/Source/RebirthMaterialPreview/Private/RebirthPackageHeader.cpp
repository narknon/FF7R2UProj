#include "RebirthPackageHeader.h"

#include "HAL/FileManager.h"
#include "Serialization/ArchiveProxy.h"
#include "UObject/ObjectResource.h"
#include "UObject/PackageFileSummary.h"
#include "UObject/UObjectGlobals.h"

namespace RebirthPackageHeaderDetail
{
	/** Reads FNames as indices into the package's name map. */
	class FNameMapReader final : public FArchiveProxy
	{
	public:
		FNameMapReader(FArchive& InInner, const TArray<FName>& InNames)
			: FArchiveProxy(InInner)
			, Names(InNames)
		{
			// The import and export tables of cooked packages depend on the editor-only filter (cooked imports have no
			// PackageName field), and they read it from this archive. Copying an archive's state clears the flag and
			// FArchiveProxy::SetFilterEditorOnly only forwards to the inner archive, so take it over here (the engine's
			// FPropertyProxyArchive does the same).
			ArIsFilterEditorOnly = InInner.IsFilterEditorOnly();
		}

		virtual FArchive& operator<<(FName& Name) override
		{
			int32 Index = 0;
			int32 Number = 0;
			InnerArchive << Index << Number;
			Name = Names.IsValidIndex(Index) ? FName(Names[Index], Number) : NAME_None;
			return *this;
		}

	private:
		const TArray<FName>& Names;
	};
}

namespace RebirthPackageHeader
{
	using namespace RebirthPackageHeaderDetail;

	bool FHeader::IsCooked() const
	{
		return (PackageFlags & (PKG_Cooked | PKG_FilterEditorOnly)) != 0;
	}

	FName FHeader::GetExportClassName(int32 ExportIndex) const
	{
		if (!Exports.IsValidIndex(ExportIndex))
		{
			return NAME_None;
		}
		const int32 Class = Exports[ExportIndex].ClassIndex;
		if (Class < 0 && Imports.IsValidIndex(-Class - 1))
		{
			return Imports[-Class - 1].ObjectName;
		}
		if (Class > 0 && Exports.IsValidIndex(Class - 1))
		{
			return Exports[Class - 1].ObjectName;
		}
		return NAME_Class;
	}

	FName FHeader::GetExportClassPackage(int32 ExportIndex) const
	{
		if (!Exports.IsValidIndex(ExportIndex))
		{
			return NAME_None;
		}
		const int32 Class = Exports[ExportIndex].ClassIndex;
		if (Class < 0 && Imports.IsValidIndex(-Class - 1))
		{
			const int32 Package = GetImportPackage(-Class - 1);
			return Imports.IsValidIndex(Package) ? Imports[Package].ObjectName : NAME_None;
		}
		return NAME_None;
	}

	FString FHeader::GetImportPath(int32 ImportIndex) const
	{
		TArray<FName> Chain;
		int32 Current = ImportIndex;
		for (int32 Guard = 0; Imports.IsValidIndex(Current) && Guard < 64; ++Guard)
		{
			Chain.Insert(Imports[Current].ObjectName, 0);
			const int32 Outer = Imports[Current].OuterIndex;
			if (Outer >= 0)
			{
				break;
			}
			Current = -Outer - 1;
		}
		FString Path;
		for (int32 Index = 0; Index < Chain.Num(); ++Index)
		{
			if (Index > 0)
			{
				Path += Index == 1 ? TEXT(".") : (Index == 2 ? TEXT(":") : TEXT("."));
			}
			Path += Chain[Index].ToString();
		}
		return Path;
	}

	int32 FHeader::GetImportPackage(int32 ImportIndex) const
	{
		int32 Current = ImportIndex;
		for (int32 Guard = 0; Imports.IsValidIndex(Current) && Guard < 64; ++Guard)
		{
			const int32 Outer = Imports[Current].OuterIndex;
			if (Outer == 0)
			{
				return Current;
			}
			if (Outer > 0)
			{
				return INDEX_NONE;
			}
			Current = -Outer - 1;
		}
		return INDEX_NONE;
	}

	bool Read(const FString& Filename, FHeader& Out, bool bReadExports, FString& OutError)
	{
		TUniquePtr<FArchive> Reader(IFileManager::Get().CreateFileReader(*Filename, FILEREAD_Silent));
		if (!Reader)
		{
			OutError = TEXT("the file could not be opened");
			return false;
		}
		const int64 FileSize = Reader->TotalSize();
		FPackageFileSummary Summary;
		*Reader << Summary;
		if (Reader->IsError() || Summary.Tag != PACKAGE_FILE_TAG || Summary.NameCount < 0 || Summary.ImportCount < 0 || Summary.ExportCount < 0)
		{
			OutError = TEXT("the file is not a package");
			return false;
		}
		if (Summary.GetFileVersionUE4() == 0)
		{
			// The summary stops early for versions it cannot read (and for unversioned files when the editor refuses them).
			OutError = TEXT("the package version cannot be read by this editor");
			return false;
		}
		auto TableFits = [FileSize](int32 Offset, int32 Count, int64 MinEntrySize)
		{
			return Count == 0 || (Offset > 0 && int64(Offset) + int64(Count) * MinEntrySize <= FileSize);
		};
		if (!TableFits(Summary.NameOffset, Summary.NameCount, 6) || !TableFits(Summary.ImportOffset, Summary.ImportCount, 28)
			|| (bReadExports && !TableFits(Summary.ExportOffset, Summary.ExportCount, 64)))
		{
			OutError = TEXT("the package header is truncated");
			return false;
		}
		Reader->SetUE4Ver(Summary.GetFileVersionUE4());
		Reader->SetLicenseeUE4Ver(Summary.GetFileVersionLicenseeUE4());
		Reader->SetEngineVer(Summary.SavedByEngineVersion);
		Reader->SetCustomVersions(Summary.GetCustomVersionContainer());
		Reader->SetFilterEditorOnly((Summary.PackageFlags & PKG_FilterEditorOnly) != 0);
		Out.PackageFlags = Summary.PackageFlags;

		TArray<FName> Names;
		Names.Reserve(Summary.NameCount);
		Reader->Seek(Summary.NameOffset);
		for (int32 Index = 0; Index < Summary.NameCount && !Reader->IsError(); ++Index)
		{
			FNameEntrySerialized Entry(ENAME_LinkerConstructor);
			*Reader << Entry;
			Names.Add(FName(Entry));
		}
		Out.Names = Names;
		FNameMapReader Proxy(*Reader, Names);
		Proxy.Seek(Summary.ImportOffset);
		Out.Imports.Reset(Summary.ImportCount);
		for (int32 Index = 0; Index < Summary.ImportCount && !Reader->IsError(); ++Index)
		{
			FObjectImport Import;
			Proxy << Import;
			FImport& Entry = Out.Imports.AddDefaulted_GetRef();
			Entry.ClassPackage = Import.ClassPackage;
			Entry.ClassName = Import.ClassName;
			Entry.OuterIndex = Import.OuterIndex.ForDebugging();
			Entry.ObjectName = Import.ObjectName;
		}
		Out.Exports.Reset();
		if (bReadExports)
		{
			Proxy.Seek(Summary.ExportOffset);
			Out.Exports.Reserve(Summary.ExportCount);
			for (int32 Index = 0; Index < Summary.ExportCount && !Reader->IsError(); ++Index)
			{
				FObjectExport Export;
				Proxy << Export;
				FExport& Entry = Out.Exports.AddDefaulted_GetRef();
				Entry.ClassIndex = Export.ClassIndex.ForDebugging();
				Entry.SuperIndex = Export.SuperIndex.ForDebugging();
				Entry.OuterIndex = Export.OuterIndex.ForDebugging();
				Entry.ObjectName = Export.ObjectName;
				Entry.ObjectFlags = uint32(Export.ObjectFlags);
				Entry.bIsAsset = Export.bIsAsset;
			}
		}
		if (Reader->IsError())
		{
			OutError = TEXT("the package header could not be read");
			return false;
		}
		return true;
	}
}
