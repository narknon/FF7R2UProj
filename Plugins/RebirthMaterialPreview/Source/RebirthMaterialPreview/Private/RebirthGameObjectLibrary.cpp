#include "RebirthGameObjectLibrary.h"

#include "RebirthGameAssets.h"
#include "RebirthGameReferences.h"

#include "Misc/PackageName.h"
#include "UObject/Class.h"
#include "UObject/UObjectGlobals.h"

UObject* URebirthGameObjectLibrary::GetGameObject(const FString& ObjectPath, const FString& ClassPath, FString& Message)
{
	Message.Reset();
	const FString Path = ObjectPath.TrimStartAndEnd();
	const FString ClassName = ClassPath.TrimStartAndEnd();
	UClass* Class = ClassName.IsEmpty() ? nullptr : FindObject<UClass>(nullptr, *ClassName);
	if (!Class && !ClassName.IsEmpty())
	{
		Class = LoadObject<UClass>(nullptr, *ClassName, nullptr, LOAD_NoWarn | LOAD_Quiet);
	}
	if (!Class)
	{
		Message = TEXT("class ") + ClassName + TEXT(" not found");
		return nullptr;
	}
	return RebirthGameReferences::FindOrStandIn(Path, Class, Message);
}

TArray<FString> URebirthGameObjectLibrary::FindGamePackages(const FString& ShortName)
{
	TArray<FString> Found;
	const FString Name = ShortName.TrimStartAndEnd();
	RebirthGameAssets::FGameIndex& Index = RebirthGameAssets::FGameIndex::Get();
	FString Error;
	if (Name.IsEmpty() || !Index.Initialize(Error))
	{
		return Found;
	}
	TArray<FName> Packages;
	Index.GetPackageNames(Packages);
	for (const FName& Package : Packages)
	{
		const FString Path = Package.ToString();
		if (FPackageName::GetShortName(Path).Equals(Name, ESearchCase::IgnoreCase))
		{
			Found.Add(Path);
		}
	}
	Found.Sort();
	return Found;
}
