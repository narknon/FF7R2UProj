#include "RebirthCookedCopies.h"

#include "RebirthAssetConversion.h"
#include "RebirthPackageHeader.h"

#include "HAL/FileManager.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "Settings/ProjectPackagingSettings.h"
#include "UObject/Class.h"
#include "UObject/Package.h"
#include "UObject/UObjectGlobals.h"

namespace RebirthCookedCopiesDetail
{
	bool IsBlueprintClassType(FName ClassName)
	{
		static const FName Types[] = { FName(TEXT("BlueprintGeneratedClass")), FName(TEXT("AnimBlueprintGeneratedClass")), FName(TEXT("WidgetBlueprintGeneratedClass")) };
		for (const FName& Type : Types)
		{
			if (ClassName == Type)
			{
				return true;
			}
		}
		return false;
	}

	/** A top-level export is a blueprint class, or an object of a plain-data class. */
	bool HoldsBlueprintOrPlainData(const RebirthPackageHeader::FHeader& Header)
	{
		for (int32 Index = 0; Index < Header.Exports.Num(); ++Index)
		{
			if (Header.Exports[Index].OuterIndex != 0)
			{
				continue;
			}
			const FName ClassName = Header.GetExportClassName(Index);
			if (IsBlueprintClassType(ClassName))
			{
				return true;
			}
			const FName ClassPackage = Header.GetExportClassPackage(Index);
			if (ClassPackage.IsNone() || !FPackageName::IsScriptPackage(ClassPackage.ToString()))
			{
				continue;
			}
			UPackage* ScriptPackage = FindObjectFast<UPackage>(nullptr, ClassPackage);
			const UClass* Class = ScriptPackage ? FindObjectFast<UClass>(ScriptPackage, ClassName) : nullptr;
			if (Class && RebirthAssetConversion::IsPlainDataClass(Class))
			{
				return true;
			}
		}
		return false;
	}
}

namespace RebirthCookedCopies
{
	using namespace RebirthCookedCopiesDetail;

	TArray<FName> FindPackages()
	{
		TArray<FString> NeverCookRoots;
		for (const FDirectoryPath& Directory : GetDefault<UProjectPackagingSettings>()->DirectoriesToNeverCook)
		{
			FString Root = Directory.Path;
			if (!Root.StartsWith(TEXT("/")))
			{
				Root = TEXT("/Game/") + Root;
			}
			Root.RemoveFromEnd(TEXT("/"));
			NeverCookRoots.Add(Root + TEXT("/"));
		}

		TArray<FString> Files;
		IFileManager::Get().FindFilesRecursive(Files, *FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir()), TEXT("*.uasset"), true, false);
		TArray<FName> Packages;
		for (const FString& File : Files)
		{
			FString PackageName;
			if (!FPackageName::TryConvertFilenameToLongPackageName(File, PackageName) || !PackageName.StartsWith(TEXT("/Game/")))
			{
				continue;
			}
			bool bNeverCooked = false;
			for (const FString& Root : NeverCookRoots)
			{
				bNeverCooked |= PackageName.StartsWith(Root);
			}
			if (bNeverCooked)
			{
				continue;
			}
			RebirthPackageHeader::FHeader Header;
			FString Error;
			if (RebirthPackageHeader::Read(File, Header, true, Error) && Header.IsCooked() && HoldsBlueprintOrPlainData(Header))
			{
				Packages.Add(FName(*PackageName));
			}
		}
		Packages.Sort(FNameLexicalLess());
		return Packages;
	}

	TArray<FName> FindSelfTestPackages()
	{
		TArray<FName> Packages;
		FString Directory;
		if (!FPackageName::TryConvertLongPackageNameToFilename(TEXT("/Game/RebirthDataObjectTests/"), Directory))
		{
			return Packages;
		}
		TArray<FString> Files;
		IFileManager::Get().FindFilesRecursive(Files, *FPaths::ConvertRelativePathToFull(Directory), TEXT("*.uasset"), true, false);
		for (const FString& File : Files)
		{
			FString PackageName;
			if (FPackageName::TryConvertFilenameToLongPackageName(File, PackageName))
			{
				Packages.Add(FName(*PackageName));
			}
		}
		Packages.Sort(FNameLexicalLess());
		return Packages;
	}
}
