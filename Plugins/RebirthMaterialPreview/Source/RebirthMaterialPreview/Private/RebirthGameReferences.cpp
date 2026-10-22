#include "RebirthGameReferences.h"

#include "RebirthGameAssets.h"
#include "RebirthPackageHeader.h"

#include "Animation/AnimBlueprintGeneratedClass.h"
#include "Animation/AnimInstance.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "HAL/FileManager.h"
#include "Logging/LogMacros.h"
#include "Misc/CoreDelegates.h"
#include "Misc/PackageName.h"
#include "UObject/LinkerLoad.h"
#include "UObject/Package.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/UObjectHash.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthGameReferences, Log, All);

namespace RebirthGameReferencesDetail
{
	using RebirthPackageHeader::FImport;

	TSet<FName> GStandInPackages;
	TSet<FName> GScanned;
	TSet<FName> GForced;
	TSet<FName> GScanning;
	TSet<FString> GReported;
	FDelegateHandle GSyncLoadHandle;
	FCoreUObjectDelegates::FIsPackageOKToSaveDelegate GPreviousIsOKToSave;
	bool GInstalled = false;

	bool IsScriptPackageName(FName PackageName)
	{
		return FPackageName::IsScriptPackage(PackageName.ToString());
	}

	void ReportOnce(ELogVerbosity::Type Verbosity, const FString& Message)
	{
		if (GReported.Contains(Message))
		{
			return;
		}
		GReported.Add(Message);
		if (Verbosity == ELogVerbosity::Warning)
		{
			UE_LOG(LogRebirthGameReferences, Warning, TEXT("%s"), *Message);
		}
		else
		{
			UE_LOG(LogRebirthGameReferences, Display, TEXT("%s"), *Message);
		}
	}

	bool HasObjects(UPackage* Package)
	{
		bool bHasObjects = false;
		ForEachObjectWithOuter(Package, [&bHasObjects](UObject*) { bHasObjects = true; }, false);
		return bHasObjects;
	}

	/** The package really exists: on disk, or as a real (not stand-in) package in memory, such as a new unsaved asset. */
	bool ExistsReally(FName PackageName)
	{
		if (GStandInPackages.Contains(PackageName))
		{
			return false;
		}
		if (FPackageName::DoesPackageExist(PackageName.ToString()))
		{
			return true;
		}
		// In memory only: a new asset holds objects; an empty package is what a failed load of the missing file leaves.
		UPackage* Existing = FindObjectFast<UPackage>(nullptr, PackageName);
		return Existing && (FLinkerLoad::FindExistingLinkerForPackage(Existing) != nullptr || Existing->IsDirty() || HasObjects(Existing));
	}

	/** A missing package gets stand-ins when the game has it (or when the game cannot be read: the reference is kept either way). */
	bool ShouldStandIn(FName PackageName)
	{
		if (PackageName.IsNone() || IsScriptPackageName(PackageName))
		{
			return false;
		}
		const FString Name = PackageName.ToString();
		if (!Name.StartsWith(TEXT("/Game/")) && !Name.StartsWith(TEXT("/Engine/")))
		{
			return false;
		}
		if (GStandInPackages.Contains(PackageName))
		{
			return true;
		}
		if (ExistsReally(PackageName))
		{
			return false;
		}
		// Kept even when the game's paks do not have it either (another mod's pak, for example): an editable copy keeps
		// exactly what the file referenced.
		RebirthGameAssets::FGameIndex& Index = RebirthGameAssets::FGameIndex::Get();
		FString Error;
		if (Index.Initialize(Error) && !Index.Contains(PackageName))
		{
			ReportOnce(ELogVerbosity::Display, FString::Printf(TEXT("%s is neither in this project nor in the game's paks; references to it are kept as they are."), *Name));
		}
		return true;
	}

	UPackage* GetOrCreateStandInPackage(FName PackageName)
	{
		UPackage* Package = FindObjectFast<UPackage>(nullptr, PackageName);
		if (Package && !GStandInPackages.Contains(PackageName))
		{
			// An empty package left behind by a failed load of the missing file is adopted; anything else is real.
			if (FLinkerLoad::FindExistingLinkerForPackage(Package) != nullptr || Package->IsDirty() || HasObjects(Package))
			{
				return nullptr;
			}
		}
		if (!Package)
		{
			Package = CreatePackage(*PackageName.ToString());
		}
		if (!Package)
		{
			return nullptr;
		}
		// In-memory only: imports resolve to the objects inside it, and it never has a file.
		Package->SetPackageFlags(PKG_NewlyCreated);
		Package->AddToRoot();
		GStandInPackages.Add(PackageName);
		return Package;
	}

	UObject* LoadRealObject(const FString& ObjectPath)
	{
		return StaticLoadObject(UObject::StaticClass(), nullptr, *ObjectPath, nullptr, LOAD_NoWarn | LOAD_Quiet);
	}

	UClass* CreateStandInClass(UPackage* Package, FName Name, UClass* MetaClass, int32 Depth);

	/** The game's super class of a blueprint class that is not in the project. */
	UClass* FindSuperClass(FName PackageName, FName ClassName, UClass* MetaClass, int32 Depth)
	{
		RebirthGameAssets::FGameIndex& Index = RebirthGameAssets::FGameIndex::Get();
		FString Error;
		RebirthGameAssets::FZenPackage Zen;
		if (Depth < 8 && Index.Initialize(Error) && Index.Contains(PackageName) && Index.ReadZenPackage(PackageName, Zen, Error))
		{
			for (const RebirthGameAssets::FZenExport& Export : Zen.Exports)
			{
				if (Export.ObjectName != ClassName)
				{
					continue;
				}
				if (RebirthGameAssets::IsScriptImport(Export.SuperIndex))
				{
					if (UClass* Super = Cast<UClass>(RebirthGameAssets::FindScriptObject(Export.SuperIndex)))
					{
						return Super;
					}
				}
				else if (RebirthGameAssets::IsPackageImport(Export.SuperIndex))
				{
					FName SuperPackage;
					FString SuperPath;
					int32 SuperExport = INDEX_NONE;
					if (Index.ResolvePackageImport(Zen, Export.SuperIndex, SuperPackage, SuperPath, SuperExport))
					{
						if (ExistsReally(SuperPackage))
						{
							if (UClass* Real = Cast<UClass>(LoadRealObject(SuperPath)))
							{
								return Real;
							}
						}
						else if (UPackage* SuperStandIn = GetOrCreateStandInPackage(SuperPackage))
						{
							FString SuperName = SuperPath;
							SuperName.Split(TEXT("."), nullptr, &SuperName, ESearchCase::CaseSensitive, ESearchDir::FromEnd);
							if (UClass* Super = CreateStandInClass(SuperStandIn, FName(*SuperName), MetaClass, Depth + 1))
							{
								return Super;
							}
						}
					}
				}
				break;
			}
		}
		if (MetaClass->IsChildOf(UAnimBlueprintGeneratedClass::StaticClass()))
		{
			return UAnimInstance::StaticClass();
		}
		return UObject::StaticClass();
	}

	UClass* CreateStandInClass(UPackage* Package, FName Name, UClass* MetaClass, int32 Depth)
	{
		if (UClass* Existing = FindObjectFast<UClass>(Package, Name))
		{
			return Existing;
		}
		if (!MetaClass || !MetaClass->IsChildOf(UClass::StaticClass()) || MetaClass->HasAnyClassFlags(CLASS_Abstract))
		{
			return nullptr;
		}
		UClass* Super = FindSuperClass(Package->GetFName(), Name, MetaClass, Depth);
		if (!Super)
		{
			return nullptr;
		}
		if (UClass* Existing = FindObjectFast<UClass>(Package, Name))
		{
			return Existing;
		}
		UClass* Class = NewObject<UClass>(Package, MetaClass, Name, RF_Public | RF_Standalone);
		Class->SetSuperStruct(Super);
		Class->ClassWithin = Super->ClassWithin ? Super->ClassWithin : UObject::StaticClass();
		Class->ClassConfigName = Super->ClassConfigName;
		Class->ClassFlags |= (Super->ClassFlags & CLASS_Inherit);
		Class->ClassCastFlags |= Super->ClassCastFlags;
		if (MetaClass->IsChildOf(UBlueprintGeneratedClass::StaticClass()))
		{
			Class->ClassFlags |= CLASS_CompiledFromBlueprint;
		}
		Class->Bind();
		Class->StaticLink(true);
		Class->AssembleReferenceTokenStream(true);
		Class->AddToRoot();
		if (UObject* Defaults = Class->GetDefaultObject(true))
		{
			Defaults->AddToRoot();
		}
		if (UBlueprintGeneratedClass* Generated = Cast<UBlueprintGeneratedClass>(Class))
		{
			// Instances of the class initialize from this list; it must exist even when it is empty.
			Generated->UpdateCustomPropertyListForPostConstruction();
		}
		UE_LOG(LogRebirthGameReferences, Verbose, TEXT("Stand-in class %s (super %s)."), *Class->GetPathName(), *Super->GetPathName());
		return Class;
	}

	class FStandInBuilder
	{
	public:
		explicit FStandInBuilder(const TArray<FImport>& InImports)
			: Imports(InImports)
		{
			Created.SetNumZeroed(Imports.Num());
		}

		int32 NumCreated = 0;
		TSet<FName> MissingPackages;

		/** The top package import of an import chain (INDEX_NONE when the chain leads into the referencing package). */
		int32 TopPackageOf(int32 Index) const
		{
			int32 Current = Index;
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

		UObject* Build(int32 Index)
		{
			if (!Imports.IsValidIndex(Index))
			{
				return nullptr;
			}
			if (Created[Index])
			{
				return Created[Index];
			}
			const FImport& Import = Imports[Index];
			UObject* Result = nullptr;
			if (Import.OuterIndex == 0)
			{
				if (ShouldStandIn(Import.ObjectName))
				{
					Result = GetOrCreateStandInPackage(Import.ObjectName);
					MissingPackages.Add(Import.ObjectName);
				}
			}
			else if (Import.OuterIndex < 0)
			{
				UObject* Outer = Build(-Import.OuterIndex - 1);
				if (Outer && GStandInPackages.Contains(Outer->GetOutermost()->GetFName()))
				{
					Result = StaticFindObjectFast(UObject::StaticClass(), Outer, Import.ObjectName);
					if (!Result)
					{
						Result = CreateObject(Import, Outer);
						if (Result)
						{
							++NumCreated;
						}
					}
				}
			}
			Created[Index] = Result;
			return Result;
		}

	private:
		const TArray<FImport>& Imports;
		TArray<UObject*> Created;

		void Report(const FString& Message)
		{
			ReportOnce(ELogVerbosity::Warning, Message);
		}

		UClass* ResolveClass(const FImport& Import)
		{
			if (IsScriptPackageName(Import.ClassPackage))
			{
				UPackage* ScriptPackage = FindObjectFast<UPackage>(nullptr, Import.ClassPackage);
				return ScriptPackage ? FindObjectFast<UClass>(ScriptPackage, Import.ClassName) : nullptr;
			}
			// A blueprint class: an import of this table, a real class, or a new stand-in.
			for (int32 Index = 0; Index < Imports.Num(); ++Index)
			{
				const FImport& Candidate = Imports[Index];
				if (Candidate.ObjectName == Import.ClassName && Candidate.OuterIndex < 0)
				{
					const FImport& Outer = Imports[-Candidate.OuterIndex - 1];
					if (Outer.OuterIndex == 0 && Outer.ObjectName == Import.ClassPackage)
					{
						return Cast<UClass>(Build(Index));
					}
				}
			}
			if (ExistsReally(Import.ClassPackage))
			{
				return Cast<UClass>(LoadRealObject(Import.ClassPackage.ToString() + TEXT(".") + Import.ClassName.ToString()));
			}
			if (ShouldStandIn(Import.ClassPackage))
			{
				if (UPackage* Package = GetOrCreateStandInPackage(Import.ClassPackage))
				{
					MissingPackages.Add(Import.ClassPackage);
					return CreateStandInClass(Package, Import.ClassName, UBlueprintGeneratedClass::StaticClass(), 0);
				}
			}
			return nullptr;
		}

		UObject* CreateObject(const FImport& Import, UObject* Outer)
		{
			UClass* Class = ResolveClass(Import);
			const FString Path = Outer->GetPathName() + (Outer->IsA<UPackage>() ? TEXT(".") : TEXT(":")) + Import.ObjectName.ToString();
			if (!Class)
			{
				Report(FString::Printf(TEXT("No stand-in for %s: its class %s.%s is not in this project; the reference cannot be kept."),
					*Path, *Import.ClassPackage.ToString(), *Import.ClassName.ToString()));
				return nullptr;
			}
			if (Class->IsChildOf(UClass::StaticClass()))
			{
				UPackage* Package = Cast<UPackage>(Outer);
				return Package ? CreateStandInClass(Package, Import.ObjectName, Class, 0) : nullptr;
			}
			const FString Name = Import.ObjectName.ToString();
			if (Name.StartsWith(TEXT("Default__")) && GStandInPackages.Contains(Class->GetOutermost()->GetFName()) && Class->GetOuter() == Outer)
			{
				return Class->GetDefaultObject(true);
			}
			if (Class->HasAnyClassFlags(CLASS_Abstract | CLASS_Deprecated | CLASS_NewerVersionExists))
			{
				Report(FString::Printf(TEXT("No stand-in for %s: its class %s cannot be instanced."), *Path, *Class->GetPathName()));
				return nullptr;
			}
			EObjectFlags Flags = RF_Public | RF_Standalone;
			if (Outer->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
			{
				Flags |= RF_ArchetypeObject | RF_DefaultSubObject;
			}
			UObject* Object = NewObject<UObject>(Outer, Class, Import.ObjectName, Flags);
			if (Object)
			{
				Object->AddToRoot();
			}
			return Object;
		}
	};

	int32 EnsureForImports(const TArray<FImport>& Imports, const FString& Referencer, TArray<FString>* OutMissing)
	{
		FStandInBuilder Builder(Imports);
		for (int32 Index = 0; Index < Imports.Num(); ++Index)
		{
			const int32 Top = Builder.TopPackageOf(Index);
			if (Top != INDEX_NONE && ShouldStandIn(Imports[Top].ObjectName))
			{
				Builder.Build(Index);
			}
		}
		if (OutMissing)
		{
			for (const FName& Missing : Builder.MissingPackages)
			{
				OutMissing->AddUnique(Missing.ToString());
			}
		}
		if (Builder.NumCreated > 0)
		{
			UE_LOG(LogRebirthGameReferences, Display, TEXT("%s: kept %d reference(s) to game assets that are not in this project (%d package(s))."),
				*Referencer, Builder.NumCreated, Builder.MissingPackages.Num());
		}
		return Builder.NumCreated;
	}

	FName PackageNameOf(const FString& PackageOrFile)
	{
		FString PackageName = PackageOrFile;
		if (!FPackageName::IsValidLongPackageName(PackageName, true))
		{
			if (!FPackageName::TryConvertFilenameToLongPackageName(PackageOrFile, PackageName))
			{
				return NAME_None;
			}
		}
		return FName(*PackageName);
	}

	int32 Scan(FName PackageName, bool bForce, TArray<FString>* OutMissing)
	{
		if (PackageName.IsNone() || GScanning.Contains(PackageName) || GStandInPackages.Contains(PackageName))
		{
			return 0;
		}
		const FString Name = PackageName.ToString();
		if (!Name.StartsWith(TEXT("/Game/")))
		{
			return 0;
		}
		FString Filename;
		if (!FPackageName::DoesPackageExist(Name, nullptr, &Filename))
		{
			return 0;
		}
		RebirthPackageHeader::FHeader Header;
		FString Error;
		if (!RebirthPackageHeader::Read(Filename, Header, false, Error))
		{
			ReportOnce(ELogVerbosity::Warning, FString::Printf(TEXT("%s: its references to game assets that are not in this project cannot be kept (%s: %s)."),
				*Name, *Filename, *Error));
			return 0;
		}
		const bool bForced = bForce || GForced.Contains(PackageName);
		if (Header.IsCooked() && !bForced)
		{
			return 0;
		}
		GScanning.Add(PackageName);
		TArray<FString> Missing;
		const int32 Created = EnsureForImports(Header.Imports, Name, &Missing);
		GScanning.Remove(PackageName);
		GScanned.Add(PackageName);
		if (bForced)
		{
			UE_LOG(LogRebirthGameReferences, Display, TEXT("%s: %d import(s); %d game package(s) not in this project (%d stand-in object(s) created now)."),
				*Name, Header.Imports.Num(), Missing.Num(), Created);
		}
		if (OutMissing)
		{
			for (const FString& Package : Missing)
			{
				OutMissing->AddUnique(Package);
			}
		}
		return Created;
	}

	void OnSyncLoadPackage(const FString& PackageOrFile)
	{
		if (!IsInGameThread() || GIsSavingPackage || IsGarbageCollecting())
		{
			return;
		}
		Scan(PackageNameOf(PackageOrFile), false, nullptr);
	}

	bool IsPackageOKToSave(UPackage* Package, const FString& Filename, FOutputDevice* Error)
	{
		if (Package && GStandInPackages.Contains(Package->GetFName()))
		{
			if (Error)
			{
				Error->Logf(ELogVerbosity::Warning, TEXT("%s stands in for a game asset that is not in this project; it is never saved."), *Package->GetName());
			}
			return false;
		}
		return GPreviousIsOKToSave.IsBound() ? GPreviousIsOKToSave.Execute(Package, Filename, Error) : true;
	}
}

namespace RebirthGameReferences
{
	using namespace RebirthGameReferencesDetail;

	void Install()
	{
		if (GInstalled)
		{
			return;
		}
		GSyncLoadHandle = FCoreDelegates::OnSyncLoadPackage.AddStatic(&OnSyncLoadPackage);
		GPreviousIsOKToSave = FCoreUObjectDelegates::IsPackageOKToSaveDelegate;
		FCoreUObjectDelegates::IsPackageOKToSaveDelegate.BindStatic(&IsPackageOKToSave);
		GInstalled = true;
	}

	void Uninstall()
	{
		if (!GInstalled)
		{
			return;
		}
		FCoreDelegates::OnSyncLoadPackage.Remove(GSyncLoadHandle);
		GSyncLoadHandle.Reset();
		FCoreUObjectDelegates::IsPackageOKToSaveDelegate = GPreviousIsOKToSave;
		GPreviousIsOKToSave.Unbind();
		GInstalled = false;
	}

	int32 EnsureForPackage(const FString& PackageName, TArray<FString>* OutMissingPackages)
	{
		const FName Name = PackageNameOf(PackageName);
		if (Name.IsNone())
		{
			return 0;
		}
		GForced.Add(Name);
		return Scan(Name, true, OutMissingPackages);
	}

	bool IsStandInPackage(const UPackage* Package)
	{
		return Package && GStandInPackages.Contains(Package->GetFName());
	}

	bool IsStandIn(const UObject* Object)
	{
		return Object && IsStandInPackage(Object->GetOutermost());
	}

	TArray<FString> GetStandInPackageNames()
	{
		TArray<FString> Names;
		for (const FName& Name : GStandInPackages)
		{
			Names.Add(Name.ToString());
		}
		Names.Sort();
		return Names;
	}

	UObject* FindOrStandIn(const FString& ObjectPath, UClass* Class, FString& OutError)
	{
		FString PackageName;
		FString ObjectName;
		if (!ObjectPath.Split(TEXT("."), &PackageName, &ObjectName) || !PackageName.StartsWith(TEXT("/")) || ObjectName.IsEmpty() ||
			ObjectName.Contains(TEXT(".")) || ObjectName.Contains(TEXT(":")))
		{
			OutError = ObjectPath + TEXT(" is not an object path like /Game/Folder/Package.Object");
			return nullptr;
		}
		if (!Class)
		{
			OutError = TEXT("no class for ") + ObjectPath;
			return nullptr;
		}
		const FName Package(*PackageName);
		if (ExistsReally(Package))
		{
			UObject* Real = LoadRealObject(ObjectPath);
			if (!Real)
			{
				OutError = ObjectPath + TEXT(" does not load (its package is in this project)");
			}
			return Real;
		}
		RebirthGameAssets::FGameIndex& Index = RebirthGameAssets::FGameIndex::Get();
		FString IndexError;
		if (!GStandInPackages.Contains(Package) && Index.Initialize(IndexError) && !Index.Contains(Package))
		{
			OutError = PackageName + TEXT(" is neither in this project nor in the game's paks");
			return nullptr;
		}
		if (!ShouldStandIn(Package))
		{
			OutError = PackageName + TEXT(" cannot be kept as a reference to a game asset (only /Game/ and /Engine/ packages can)");
			return nullptr;
		}
		// The same two imports an asset that references the object has: its package, and the object in it.
		TArray<FImport> Imports;
		FImport& PackageImport = Imports.AddDefaulted_GetRef();
		PackageImport.ClassPackage = FName(TEXT("/Script/CoreUObject"));
		PackageImport.ClassName = NAME_Package;
		PackageImport.OuterIndex = 0;
		PackageImport.ObjectName = Package;
		FImport& ObjectImport = Imports.AddDefaulted_GetRef();
		ObjectImport.ClassPackage = Class->GetOutermost()->GetFName();
		ObjectImport.ClassName = Class->GetFName();
		ObjectImport.OuterIndex = -1;
		ObjectImport.ObjectName = FName(*ObjectName);
		FStandInBuilder Builder(Imports);
		UObject* Object = Builder.Build(1);
		if (!Object)
		{
			OutError = TEXT("no stand-in could be made for ") + ObjectPath + TEXT(" (the log says why)");
			return nullptr;
		}
		if (!Object->IsA(Class))
		{
			OutError = FString::Printf(TEXT("%s is a %s, not a %s"), *ObjectPath, *Object->GetClass()->GetName(), *Class->GetName());
			return nullptr;
		}
		if (Builder.NumCreated > 0)
		{
			UE_LOG(LogRebirthGameReferences, Display, TEXT("%s: kept as a reference to the game's asset (stand-in made)."), *ObjectPath);
		}
		return Object;
	}
}
