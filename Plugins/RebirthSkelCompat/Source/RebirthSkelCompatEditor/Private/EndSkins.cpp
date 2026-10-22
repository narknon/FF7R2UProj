// Skins (editor 1.15): Build Skins. A skin is a folder of the game's own (zen) packages and a skin.json, not a pak
// (SkinCore.hpp, shared with the game mod):
//
//   1. the skin's packages (its model, the model's skeleton and physics asset, its Extra Assets; never one the game has)
//      are cooked here for WindowsNoEditor the way the cooker saves them (versioned, the exports in a .uexp next to the
//      .uasset, the bulk data in a .ubulk), into <Skins Output Folder>/_work/<Folder>/Cooked;
//   2. the engine's own IoStore commandlet turns them into the game's package format, in a container of their own
//      (uncompressed), the way packaging does it for a mod chunk: <Work>/Container/<Folder>.utoc;
//   3. that container is read back: each package and its bulk data go to <Skins Output Folder>/<Folder>/Content/... with
//      the store entry the commandlet gave it in skin.json;
//   4. with Install Skins on, the folder is copied into the game's Create a Character System folder (skins/<Folder>) and
//      every installed skin goes into one ~mods container, CreateACharacterSkins_P, which the game mounts (it only loads
//      zen packages from a mounted container). The game mod puts the skins on (Create a Character System 3.10).
#include "EndSkeletonCompatDataObject.h"

#include "Animation/AnimSequence.h"
#include "Animation/Skeleton.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/World.h"
#include "FileHelpers.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformProcess.h"
#include "HAL/PlatformTime.h"
#include "Interfaces/ITargetPlatform.h"
#include "Interfaces/ITargetPlatformManagerModule.h"
#include "Materials/MaterialInterface.h"
#include "Misc/App.h"
#include "Misc/DateTime.h"
#include "Misc/FileHelper.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "Misc/ScopedSlowTask.h"
#include "PhysicsEngine/PhysicsAsset.h"
#include "ReferenceSkeleton.h"
#include "ShaderCompiler.h"
#include "UObject/Package.h"
#include "UObject/UObjectHash.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "SkinCore.hpp"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthSkins, Log, All);

// The data object's lookups of the game's assets (EndSkeletonCompatDataObject.cpp): RebirthGameObjectLibrary of the
// Rebirth Cooked Asset Preview plugin, which knows the packages in the game's paks.
namespace RebirthSkelCompatEditor
{
bool GameObjectToolsLoaded();
TArray<FString> GamePackagesNamed(const FString& ShortName);
}

namespace RebirthSkelCompatSkins
{
const TCHAR* const GameModFolder = TEXT("End/Binaries/Win64/ue4ss/Mods/RebirthSkelCompat");   // the game mod's folder
const TCHAR* const GameModsFolder = TEXT("End/Content/Paks/~mods");
const TCHAR* const EditorVersion = TEXT("Create a Character System editor 1.15.0");
constexpr double IoStoreTimeoutSeconds = 20.0 * 60.0;
constexpr double CacheTimeoutSeconds = 10.0 * 60.0;

std::string Utf8(const FString& Text) { return std::string(TCHAR_TO_UTF8(*Text)); }
FString FromUtf8(const std::string& Text) { return FString(UTF8_TO_TCHAR(Text.c_str())); }

// A directory property as a full path (a relative one from the project folder), no closing slash.
FString FullFolderOf(const FDirectoryPath& Directory)
{
	FString Path = Directory.Path.TrimStartAndEnd();
	if (Path.IsEmpty())
	{
		return Path;
	}
	if (FPaths::IsRelative(Path))
	{
		Path = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir(), Path);
	}
	FPaths::NormalizeDirectoryName(Path);
	return Path;
}

FString FullFileOf(const FFilePath& File)
{
	FString Path = File.FilePath.TrimStartAndEnd();
	if (!Path.IsEmpty() && FPaths::IsRelative(Path))
	{
		Path = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir(), Path);
	}
	FPaths::NormalizeFilename(Path);
	return Path;
}

// A path as Windows programs take it on a command line: backslashes, in quotes.
FString Quoted(FString Path)
{
	FPaths::MakePlatformFilename(Path);
	return TEXT("\"") + Path + TEXT("\"");
}

bool LoadBytes(const FString& Path, CacsSound::Bytes& Out)
{
	Out.clear();
	TUniquePtr<FArchive> Reader(IFileManager::Get().CreateFileReader(*Path));
	if (!Reader)
	{
		return false;
	}
	const int64 Size = Reader->TotalSize();
	if (Size < 0)
	{
		return false;
	}
	Out.resize(static_cast<size_t>(Size));
	if (Size > 0)
	{
		Reader->Serialize(Out.data(), Size);
	}
	const bool bOk = !Reader->IsError();
	return Reader->Close() && bOk;
}

bool SaveBytes(const FString& Path, const uint8* Data, size_t Size)
{
	IFileManager::Get().MakeDirectory(*FPaths::GetPath(Path), true);
	TUniquePtr<FArchive> Writer(IFileManager::Get().CreateFileWriter(*Path));
	if (!Writer)
	{
		return false;
	}
	if (Size > 0)
	{
		Writer->Serialize(const_cast<uint8*>(Data), static_cast<int64>(Size));
	}
	const bool bOk = !Writer->IsError();
	return Writer->Close() && bOk;
}

bool SaveBytes(const FString& Path, const CacsSound::Bytes& Data) { return SaveBytes(Path, Data.data(), Data.size()); }

bool SaveText(const FString& Path, const std::string& Text)
{
	return SaveBytes(Path, reinterpret_cast<const uint8*>(Text.data()), Text.size());
}

bool LoadText(const FString& Path, std::string& Out)
{
	CacsSound::Bytes Data;
	if (!LoadBytes(Path, Data))
	{
		return false;
	}
	Out.assign(Data.begin(), Data.end());
	return true;
}

// The Name's letters and digits: Remake Sephiroth -> RemakeSephiroth.
FString FolderFromName(const FString& Name)
{
	FString Out;
	for (const TCHAR C : Name)
	{
		if ((C >= TEXT('A') && C <= TEXT('Z')) || (C >= TEXT('a') && C <= TEXT('z')) || (C >= TEXT('0') && C <= TEXT('9')))
		{
			Out.AppendChar(C);
		}
	}
	return Out;
}

bool ValidFolderName(const FString& Folder)
{
	if (Folder.IsEmpty() || Folder.Len() > 64 || Folder.StartsWith(TEXT("_")))
	{
		return false;
	}
	for (const TCHAR C : Folder)
	{
		const bool bOk = (C >= TEXT('A') && C <= TEXT('Z')) || (C >= TEXT('a') && C <= TEXT('z')) || (C >= TEXT('0') && C <= TEXT('9')) || C == TEXT('_') || C == TEXT('-');
		if (!bOk)
		{
			return false;
		}
	}
	return true;
}

// The game's packages, through the data object's lookup (one lookup per short name).
struct FGamePackages
{
	bool bTools = false;
	TMap<FString, TArray<FString>> ByShortName;

	FGamePackages() : bTools(RebirthSkelCompatEditor::GameObjectToolsLoaded()) {}

	bool Has(const FString& PackageName)
	{
		if (!bTools)
		{
			return false;
		}
		const FString Short = FPackageName::GetShortName(PackageName);
		TArray<FString>* Found = ByShortName.Find(Short);
		if (!Found)
		{
			Found = &ByShortName.Add(Short, RebirthSkelCompatEditor::GamePackagesNamed(Short));
		}
		for (const FString& Package : *Found)
		{
			if (Package.Equals(PackageName, ESearchCase::IgnoreCase))
			{
				return true;
			}
		}
		return false;
	}
};

// The progress dialog, with Cancel.
struct FProgress
{
	FScopedSlowTask& Task;

	void Step(const FString& Text, float Work = 1.f) { Task.EnterProgressFrame(Work, FText::FromString(Text)); }
	void Say(const FString& Text) { Task.FrameMessage = FText::FromString(Text); }
	bool Cancelled() const { return Task.ShouldCancel(); }
};

// One package the skin has: /Game/<Rel>.
struct FSkinPackageName
{
	FString Package;
	FString Rel;
};

const TCHAR* const PackageExtensions[] = {TEXT(".uasset"), TEXT(".uexp"), TEXT(".ubulk"), TEXT(".uptnl"), TEXT(".m.ubulk"), TEXT(".uexp.uregs"), TEXT(".ubulk.uregs")};
const TCHAR* const BulkExtensions[] = {TEXT(".ubulk"), TEXT(".uptnl"), TEXT(".m.ubulk")};

// A package saved as the cooker saves it for WindowsNoEditor: the platform data its objects cache for the target first
// (a texture's, a material's shaders), versioned (the game's mods are cooked so: tagged properties, which do not depend
// on the editor's classes matching the game's), the exports in a .uexp, the bulk data in a .ubulk (SAVE_Async: the
// writes finish in UPackage::WaitForAsyncFileWrites).
bool CookPackage(UPackage* Package, const ITargetPlatform* Platform, const FString& Filename, FProgress& Progress, FString& Problem)
{
	Package->FullyLoad();
	TArray<UObject*> Objects;
	GetObjectsWithOuter(Package, Objects, true);
	for (UObject* Object : Objects)
	{
		Object->BeginCacheForCookedPlatformData(Platform);
	}
	const double Started = FPlatformTime::Seconds();
	for (;;)
	{
		bool bAll = true;
		for (UObject* Object : Objects)
		{
			if (!Object->IsCachedCookedPlatformDataLoaded(Platform))
			{
				bAll = false;
				break;
			}
		}
		if (bAll)
		{
			break;
		}
		if (GShaderCompilingManager)
		{
			GShaderCompilingManager->ProcessAsyncResults(true, false);
		}
		if (Progress.Cancelled())
		{
			Problem = TEXT("cancelled");
			return false;
		}
		if (FPlatformTime::Seconds() - Started > CacheTimeoutSeconds)
		{
			Problem = TEXT("its platform data (textures, shaders) was not ready after 10 minutes");
			return false;
		}
		FPlatformProcess::Sleep(0.02f);
	}
	IFileManager::Get().MakeDirectory(*FPaths::GetPath(Filename), true);
	const uint32 Flags = Package->GetPackageFlags();
	Package->SetPackageFlags(PKG_FilterEditorOnly);
	const bool bSaved = UPackage::SavePackage(Package, nullptr, RF_Public, *Filename, GWarn, nullptr, false, false,
		SAVE_NoError | SAVE_KeepGUID | SAVE_Async, Platform, FDateTime::MinValue(), false);
	Package->SetPackageFlagsTo(Flags);
	for (UObject* Object : Objects)
	{
		Object->ClearAllCachedCookedPlatformData();
	}
	if (!bSaved)
	{
		Problem = TEXT("could not be cooked to ") + Filename;
	}
	return bSaved;
}

// A cooked .uasset written whole (no .uexp next to it): split at its summary's TotalHeaderSize, as the cooker splits it.
bool SplitCookedPackage(const FString& UAsset, FString& Problem)
{
	CacsSound::Bytes Data;
	if (!LoadBytes(UAsset, Data) || Data.size() < 32)
	{
		Problem = TEXT("cannot read ") + UAsset;
		return false;
	}
	const uint32 Tag = CacsSound::GetU32(Data.data());
	const int32 Legacy = static_cast<int32>(CacsSound::GetU32(Data.data() + 4));
	if (Tag != 0x9E2A83C1u || (Legacy != -7 && Legacy != -6))
	{
		Problem = UAsset + TEXT(" is not a package this editor writes");
		return false;
	}
	const uint32 CustomVersions = CacsSound::GetU32(Data.data() + 20);
	const size_t At = 24 + static_cast<size_t>(CustomVersions) * 20;
	if (CustomVersions > 100000 || At + 4 > Data.size())
	{
		Problem = UAsset + TEXT("'s summary does not read");
		return false;
	}
	const int32 HeaderSize = static_cast<int32>(CacsSound::GetU32(Data.data() + At));
	if (HeaderSize <= 0 || static_cast<size_t>(HeaderSize) > Data.size())
	{
		Problem = UAsset + TEXT("'s header size does not read");
		return false;
	}
	const FString UExp = FPaths::ChangeExtension(UAsset, TEXT(".uexp"));
	if (!SaveBytes(UExp, Data.data() + HeaderSize, Data.size() - static_cast<size_t>(HeaderSize)) || !SaveBytes(UAsset, Data.data(), static_cast<size_t>(HeaderSize)))
	{
		Problem = TEXT("cannot write ") + UExp;
		return false;
	}
	return true;
}

// UE4Editor-Cmd.exe next to the running editor (else the editor itself: it runs commandlets too).
FString CommandletExecutable()
{
	const FString Running = FPlatformProcess::ExecutablePath();
	const FString Cmd = FPaths::Combine(FPaths::GetPath(Running), TEXT("UE4Editor-Cmd.exe"));
	return FPaths::FileExists(Cmd) ? Cmd : Running;
}

// The lines of a log that hold "Error:", the last Count of them (LogIoStore's first).
FString LastErrors(const FString& LogText, int32 Count)
{
	TArray<FString> Lines;
	LogText.ParseIntoArrayLines(Lines);
	TArray<FString> IoStore, Others;
	for (const FString& Line : Lines)
	{
		if (Line.Contains(TEXT("Error:")))
		{
			(Line.Contains(TEXT("LogIoStore")) ? IoStore : Others).Add(Line.TrimStartAndEnd());
		}
	}
	TArray<FString>& Pick = IoStore.Num() > 0 ? IoStore : Others;
	const int32 First = FMath::Max(0, Pick.Num() - Count);
	FString Out;
	for (int32 Index = First; Index < Pick.Num(); ++Index)
	{
		Out += TEXT("      ") + Pick[Index].Left(400) + TEXT("\n");
	}
	return Out;
}

// What the IoStore commandlet's own Main returned, from its log ("finished execution (result 0)"); -1: not there.
int32 CommandletResult(const FString& LogText)
{
	const TCHAR* const Marker = TEXT("finished execution (result ");
	const int32 At = LogText.Find(Marker, ESearchCase::CaseSensitive, ESearchDir::FromEnd);
	if (At == INDEX_NONE)
	{
		return -1;
	}
	int32 Value = 0;
	bool bDigits = false;
	bool bNegative = false;
	for (int32 Index = At + FCString::Strlen(Marker); Index < LogText.Len(); ++Index)
	{
		const TCHAR C = LogText[Index];
		if (C == TEXT('-') && !bDigits && !bNegative)
		{
			bNegative = true;
			continue;
		}
		if (C < TEXT('0') || C > TEXT('9'))
		{
			break;
		}
		bDigits = true;
		Value = Value * 10 + (C - TEXT('0'));
	}
	return bDigits ? (bNegative ? -Value : Value) : -1;
}

// Files of a folder from an earlier skin.json that the new one does not have: removed (only paths inside the folder).
int32 RemoveStaleFiles(const FString& Folder, const std::vector<std::string>& Before, const std::vector<std::string>& Now)
{
	int32 Removed = 0;
	for (const std::string& File : Before)
	{
		if (!CacsSkin::SafeRelativePath(File) || std::find(Now.begin(), Now.end(), File) != Now.end())
		{
			continue;
		}
		const FString Path = FPaths::Combine(Folder, FromUtf8(File));
		if (FPaths::FileExists(Path) && IFileManager::Get().Delete(*Path, false, true, true))
		{
			++Removed;
		}
	}
	return Removed;
}

// The files a skin folder's skin.json lists now (empty when it has none, or one that does not read).
std::vector<std::string> ListedFiles(const FString& Folder)
{
	std::string Text;
	CacsSkin::SkinInfo Old;
	std::string Error;
	if (!LoadText(FPaths::Combine(Folder, TEXT("skin.json")), Text) || !CacsSkin::ReadSkinJson(Text, Old, Error))
	{
		return {};
	}
	return CacsSkin::FilesOf(Old);
}

// A skin folder with every file its skin.json lists read in (for the skins container).
bool ReadSkinFolder(const FString& Folder, const FString& Name, CacsSkin::SkinFolder& Out, FString& Problem)
{
	Out = CacsSkin::SkinFolder{};
	Out.Folder = Utf8(Name);
	std::string Text;
	std::string Error;
	if (!LoadText(FPaths::Combine(Folder, TEXT("skin.json")), Text))
	{
		Problem = TEXT("its skin.json does not read");
		return false;
	}
	if (!CacsSkin::ReadSkinJson(Text, Out.Info, Error))
	{
		Problem = FromUtf8(Error);
		return false;
	}
	if (!Out.Info.Enabled)
	{
		return true;   // (off: its files are not needed)
	}
	for (CacsSkin::SkinPackage& Package : Out.Info.Packages)
	{
		if (!LoadBytes(FPaths::Combine(Folder, FromUtf8(Package.File)), Package.Data) || Package.Data.empty())
		{
			Problem = FromUtf8(Package.File) + TEXT(" is missing");
			return false;
		}
		for (CacsSkin::SkinBulk& Bulk : Package.Bulk)
		{
			if (!LoadBytes(FPaths::Combine(Folder, FromUtf8(Bulk.File)), Bulk.Data))
			{
				Problem = FromUtf8(Bulk.File) + TEXT(" is missing");
				return false;
			}
		}
	}
	return true;
}

// Writes the three files of a container, only once all three can be written (a running game keeps them open): each
// one to <name>.new first, then over the old one.
bool WriteContainer(const FString& Base, const CacsSkin::CacheResult& Cache, FString& Problem)
{
	const FString Paths[3] = {Base + TEXT(".utoc"), Base + TEXT(".ucas"), Base + TEXT(".pak")};
	const CacsSound::Bytes* Data[3] = {&Cache.Utoc, &Cache.Ucas, &Cache.Pak};
	for (const FString& Path : Paths)
	{
		if (FPaths::FileExists(Path))
		{
			TUniquePtr<FArchive> Probe(IFileManager::Get().CreateFileWriter(*Path, FILEWRITE_Append));
			if (!Probe)
			{
				Problem = Path + TEXT(" is in use (close the game, then press Build Skins again); the skins container was NOT changed");
				return false;
			}
			Probe->Close();
		}
	}
	for (int32 Index = 0; Index < 3; ++Index)
	{
		if (!SaveBytes(Paths[Index] + TEXT(".new"), *Data[Index]))
		{
			Problem = TEXT("cannot write ") + Paths[Index] + TEXT(".new");
			return false;
		}
	}
	for (int32 Index = 0; Index < 3; ++Index)
	{
		if (!IFileManager::Get().Move(*Paths[Index], *(Paths[Index] + TEXT(".new")), true, true))
		{
			Problem = TEXT("cannot replace ") + Paths[Index] + TEXT(" (close the game, then press Build Skins again)");
			return false;
		}
	}
	return true;
}

// Every installed skin (skins/*/skin.json in the game mod's folder) into ~mods/CreateACharacterSkins_P.
bool RemakeSkinsContainer(const FString& GameDirectory, FString& Report)
{
	const FString SkinsRoot = FPaths::Combine(GameDirectory, GameModFolder, TEXT("skins"));
	TArray<FString> Folders;
	IFileManager::Get().FindFiles(Folders, *FPaths::Combine(SkinsRoot, TEXT("*")), false, true);
	std::vector<CacsSkin::SkinFolder> Skins;
	for (const FString& Name : Folders)
	{
		const FString Folder = FPaths::Combine(SkinsRoot, Name);
		if (!FPaths::FileExists(FPaths::Combine(Folder, TEXT("skin.json"))))
		{
			continue;
		}
		CacsSkin::SkinFolder Skin;
		FString Problem;
		if (!ReadSkinFolder(Folder, Name, Skin, Problem))
		{
			Report += TEXT("    skins/") + Name + TEXT(": left out of the skins container: ") + Problem + TEXT("\n");
			continue;
		}
		Skins.push_back(std::move(Skin));
	}
	const CacsSkin::CacheResult Cache = CacsSkin::BuildCache(std::move(Skins));
	if (!Cache.Ok)
	{
		Report += TEXT("    The skins container was NOT made: ") + FromUtf8(Cache.Error) + TEXT("\n");
		return false;
	}
	const FString Mods = FPaths::Combine(GameDirectory, GameModsFolder);
	IFileManager::Get().MakeDirectory(*Mods, true);
	const FString Base = FPaths::Combine(Mods, FromUtf8(CacsSkin::CacheName));
	FString Problem;
	if (!WriteContainer(Base, Cache, Problem))
	{
		Report += TEXT("    ") + Problem + TEXT("\n");
		return false;
	}
	Report += FString::Printf(TEXT("    Skins container: %s.utoc/.ucas/.pak in %s, %d package(s) of every installed skin (%.1f MB)\n"),
		UTF8_TO_TCHAR(CacsSkin::CacheName), *Mods, static_cast<int32>(Cache.Packages), Cache.Ucas.size() / (1024.0 * 1024.0));
	for (const std::string& Line : Cache.Report)
	{
		Report += TEXT("      ") + FromUtf8(Line) + TEXT("\n");
	}
	return true;
}

// Copies a built skin folder into the game mod's skins folder (its files as its skin.json lists them, skin.json last;
// the files an installed earlier build listed and this one does not are removed).
bool InstallSkinFolder(const FString& From, const FString& To, const CacsSkin::SkinInfo& Skin, FString& Problem)
{
	if (FPaths::IsSamePath(From, To))
	{
		return true;
	}
	const std::vector<std::string> Before = ListedFiles(To);
	const std::vector<std::string> Now = CacsSkin::FilesOf(Skin);
	for (const std::string& File : Now)
	{
		const FString Name = FromUtf8(File);
		const FString Dest = FPaths::Combine(To, Name);
		IFileManager::Get().MakeDirectory(*FPaths::GetPath(Dest), true);
		if (IFileManager::Get().Copy(*Dest, *FPaths::Combine(From, Name), true, true) != COPY_OK)
		{
			Problem = TEXT("cannot copy ") + Name + TEXT(" to ") + To + TEXT(" (close the game, then press Build Skins again)");
			return false;
		}
	}
	if (IFileManager::Get().Copy(*FPaths::Combine(To, TEXT("skin.json")), *FPaths::Combine(From, TEXT("skin.json")), true, true) != COPY_OK)
	{
		Problem = TEXT("cannot copy skin.json to ") + To;
		return false;
	}
	RemoveStaleFiles(To, Before, Now);
	return true;
}

// One skin: built into <OutRoot>/<Folder>. Report gets its lines; false: not built.
bool BuildSkin(const FEndCharacterSkin& Skin, const FString& Label, const FString& Folder, const FString& OutRoot, FGamePackages& Game,
	FProgress& Progress, CacsSkin::SkinInfo& OutInfo, FString& Report)
{
	TArray<FString> Notes;
	auto Fail = [&](const FString& Why)
	{
		Report += Label + TEXT(": NOT built: ") + Why + TEXT("\n");
		for (const FString& Note : Notes)
		{
			Report += TEXT("    ") + Note + TEXT("\n");
		}
		return false;
	};

	// 1. its packages
	Progress.Step(Label + TEXT(": its packages"));
	if (Skin.Model.IsNull())
	{
		return Fail(TEXT("no Model"));
	}
	USkeletalMesh* Model = Skin.Model.LoadSynchronous();
	if (!Model)
	{
		return Fail(TEXT("its Model ") + Skin.Model.ToString() + TEXT(" does not load"));
	}
	if (!Model->Skeleton)
	{
		return Fail(Model->GetPathName() + TEXT(" has no skeleton"));
	}
	TArray<FSkinPackageName> Packages;
	TArray<FString> FromGame;
	FString Refused;
	auto Consider = [&](const UObject* Asset, const FString& PackageName, const TCHAR* What) -> bool
	{
		if (PackageName.IsEmpty())
		{
			return true;
		}
		if (Packages.ContainsByPredicate([&](const FSkinPackageName& P) { return P.Package.Equals(PackageName, ESearchCase::IgnoreCase); }))
		{
			return true;
		}
		if (!PackageName.StartsWith(TEXT("/Game/")))
		{
			Notes.Add(FString::Printf(TEXT("%s %s is not under /Game: left out (the game has the engine's own)"), What, *PackageName));
			return true;
		}
		if (Game.Has(PackageName))
		{
			FromGame.Add(PackageName);
			return true;
		}
		const UPackage* Package = Asset ? Asset->GetOutermost() : nullptr;
		if (Package && Package->HasAnyPackageFlags(PKG_Cooked))
		{
			Refused = FString(What) + TEXT(" ") + PackageName + TEXT(" is a cooked asset the game does not have: it cannot be cooked again");
			return false;
		}
		FSkinPackageName Entry;
		Entry.Package = PackageName;
		Entry.Rel = PackageName.RightChop(6);
		Packages.Add(Entry);
		return true;
	};
	if (!Consider(Model, Model->GetOutermost()->GetName(), TEXT("the model")) ||
		!Consider(Model->Skeleton, Model->Skeleton->GetOutermost()->GetName(), TEXT("its skeleton")) ||
		(Model->PhysicsAsset && !Consider(Model->PhysicsAsset, Model->PhysicsAsset->GetOutermost()->GetName(), TEXT("its physics asset"))))
	{
		return Fail(Refused);
	}
	for (const FSoftObjectPath& Extra : Skin.ExtraAssets)
	{
		if (Extra.IsNull())
		{
			continue;
		}
		UObject* Asset = Extra.TryLoad();
		if (!Asset)
		{
			return Fail(TEXT("its Extra Asset ") + Extra.ToString() + TEXT(" does not load"));
		}
		if (Asset->IsA<UAnimSequence>() || Asset->IsA<UWorld>())
		{
			Notes.Add(FString::Printf(TEXT("Extra Asset %s left out: a skin has no %s"), *Extra.ToString(), Asset->IsA<UWorld>() ? TEXT("maps") : TEXT("animations (they belong to the character's sets)")));
			continue;
		}
		if (!Consider(Asset, Asset->GetOutermost()->GetName(), TEXT("Extra Asset")))
		{
			return Fail(Refused);
		}
	}
	if (!Game.bTools)
	{
		Notes.Add(TEXT("the game's packages were not looked at (no RebirthGameObjectLibrary: the Rebirth Cooked Asset Preview plugin): every /Game package went into the skin"));
	}
	for (const FString& Package : FromGame)
	{
		Notes.Add(Package + TEXT(" is the game's: the skin uses the game's own (left out)"));
	}
	// what in game has to come from elsewhere: the materials
	auto InSkin = [&](const FString& PackageName) { return Packages.ContainsByPredicate([&](const FSkinPackageName& P) { return P.Package.Equals(PackageName, ESearchCase::IgnoreCase); }); };
	for (int32 Slot = 0; Slot < Model->Materials.Num(); ++Slot)
	{
		const FSkeletalMaterial& Material = Model->Materials[Slot];
		const FString SlotName = Material.MaterialSlotName.IsNone() ? FString::FromInt(Slot) : Material.MaterialSlotName.ToString();
		if (!Material.MaterialInterface)
		{
			Notes.Add(TEXT("material slot ") + SlotName + TEXT(" has no material (in game: the default material)"));
			continue;
		}
		const FString PackageName = Material.MaterialInterface->GetOutermost()->GetName();
		if (InSkin(PackageName) || !PackageName.StartsWith(TEXT("/Game/")) || Game.Has(PackageName))
		{
			continue;
		}
		Notes.Add(TEXT("material slot ") + SlotName + TEXT(": ") + PackageName + TEXT(" is not in the game or the skin: it must come from a mod (e.g. your game materials mod), else the slot shows the default material"));
	}
	// the family
	if (!Skin.Family.IsNull())
	{
		USkeleton* Hub = Skin.Family.LoadSynchronous();
		if (!Hub)
		{
			Notes.Add(TEXT("its Family ") + Skin.Family.ToString() + TEXT(" does not load here (the game still joins the model's skeleton to it)"));
		}
		else if (Hub == Model->Skeleton)
		{
			Notes.Add(TEXT("the model is on its Family skeleton itself: Family is not needed"));
		}
		else
		{
			const FReferenceSkeleton& HubBones = Hub->GetReferenceSkeleton();
			TArray<FString> Missing;
			for (int32 Bone = 0; Bone < Model->RefSkeleton.GetNum(); ++Bone)
			{
				const FName BoneName = Model->RefSkeleton.GetBoneName(Bone);
				if (HubBones.FindBoneIndex(BoneName) == INDEX_NONE)
				{
					Missing.Add(BoneName.ToString());
				}
			}
			if (Missing.Num() > 0)
			{
				const int32 Shown = FMath::Min(Missing.Num(), 10);
				Notes.Add(FString::Printf(TEXT("%d of the model's %d bones are not in its Family %s (no animation of the family moves them: physics bones are fine): %s%s"),
					Missing.Num(), Model->RefSkeleton.GetNum(), *Hub->GetName(), *FString::Join(TArrayView<const FString>(Missing.GetData(), Shown), TEXT(", ")),
					Missing.Num() > Shown ? TEXT(", ...") : TEXT("")));
			}
		}
	}
	if (Skin.Characters.Num() == 0)
	{
		Notes.Add(TEXT("no Characters: in game no character wears it"));
	}

	// 2. saved, then cooked
	const FString Work = FPaths::Combine(OutRoot, TEXT("_work"), Folder);
	const FString CookedRoot = FPaths::Combine(Work, TEXT("Cooked"));
	const FString CookedContent = FPaths::Combine(CookedRoot, FApp::GetProjectName(), TEXT("Content"));
	TArray<UPackage*> Loaded;
	for (const FSkinPackageName& Entry : Packages)
	{
		UPackage* Package = FindPackage(nullptr, *Entry.Package);
		if (!Package)
		{
			Package = LoadPackage(nullptr, *Entry.Package, LOAD_None);
		}
		if (!Package)
		{
			return Fail(Entry.Package + TEXT(" does not load"));
		}
		if (UWorld::FindWorldInPackage(Package))
		{
			return Fail(Entry.Package + TEXT(" is a map"));
		}
		Loaded.Add(Package);
	}
	TArray<UPackage*> Dirty;
	for (UPackage* Package : Loaded)
	{
		if (Package->IsDirty())
		{
			Dirty.Add(Package);
		}
	}
	if (Dirty.Num() > 0)
	{
		TArray<UPackage*> NotSaved;
		FEditorFileUtils::PromptForCheckoutAndSave(Dirty, false, false, &NotSaved);
		if (NotSaved.Num() > 0)
		{
			return Fail(NotSaved[0]->GetName() + TEXT(" could not be saved"));
		}
	}
	const ITargetPlatform* Platform = Packages.Num() > 0 ? GetTargetPlatformManagerRef().FindTargetPlatform(TEXT("WindowsNoEditor")) : nullptr;
	if (Packages.Num() > 0 && !Platform)
	{
		return Fail(TEXT("the WindowsNoEditor target platform is not available in this editor"));
	}
	Progress.Step(Label + TEXT(": cooking"));
	for (int32 Index = 0; Index < Packages.Num(); ++Index)
	{
		const FString Base = FPaths::Combine(CookedContent, Packages[Index].Rel);
		for (const TCHAR* Extension : PackageExtensions)
		{
			IFileManager::Get().Delete(*(Base + Extension), false, true, true);
		}
		Progress.Say(Label + TEXT(": cooking ") + Packages[Index].Package);
		FString Problem;
		if (!CookPackage(Loaded[Index], Platform, Base + TEXT(".uasset"), Progress, Problem))
		{
			UPackage::WaitForAsyncFileWrites();
			return Fail(Packages[Index].Package + TEXT(": ") + Problem);
		}
	}
	UPackage::WaitForAsyncFileWrites();
	FString Response;
	const FString Destination = FString(TEXT("../../../")) + FApp::GetProjectName() + TEXT("/Content/");
	for (const FSkinPackageName& Entry : Packages)
	{
		const FString Base = FPaths::Combine(CookedContent, Entry.Rel);
		if (!FPaths::FileExists(Base + TEXT(".uasset")))
		{
			return Fail(Entry.Package + TEXT(" was not cooked (no ") + Base + TEXT(".uasset)"));
		}
		if (!FPaths::FileExists(Base + TEXT(".uexp")))
		{
			FString Problem;
			if (!SplitCookedPackage(Base + TEXT(".uasset"), Problem))
			{
				return Fail(Problem);
			}
			Notes.Add(Entry.Package + TEXT(" came out whole: split into .uasset and .uexp"));
		}
		Response += FString::Printf(TEXT("\"%s.uasset\" \"%s%s.uasset\"\r\n"), *Base, *Destination, *Entry.Rel);
		for (const TCHAR* Extension : BulkExtensions)
		{
			if (FPaths::FileExists(Base + Extension))
			{
				Response += FString::Printf(TEXT("\"%s%s\" \"%s%s%s\"\r\n"), *Base, Extension, *Destination, *Entry.Rel, Extension);
			}
		}
	}

	// 3. the game's package format: the engine's IoStore commandlet
	std::vector<CacsSkin::SkinPackage> Built;
	if (Packages.Num() > 0)
	{
		Progress.Step(Label + TEXT(": the game's package format (the engine's IoStore, about 20 s)"));
		const FString ContainerDir = FPaths::Combine(Work, TEXT("Container"));
		const FString GlobalDir = FPaths::Combine(Work, TEXT("Global"));
		const FString Utoc = FPaths::Combine(ContainerDir, Folder + TEXT(".utoc"));
		const FString Ucas = FPaths::Combine(ContainerDir, Folder + TEXT(".ucas"));
		const FString LogPath = FPaths::Combine(Work, TEXT("iostore.log"));
		const FString ResponseFile = FPaths::Combine(Work, TEXT("Skin.txt"));
		const FString CommandsFile = FPaths::Combine(Work, TEXT("IoStoreCommands.txt"));
		IFileManager::Get().MakeDirectory(*ContainerDir, true);
		IFileManager::Get().MakeDirectory(*GlobalDir, true);
		IFileManager::Get().Delete(*Utoc, false, true, true);
		IFileManager::Get().Delete(*Ucas, false, true, true);
		IFileManager::Get().Delete(*LogPath, false, true, true);
		const FString Commands = FString::Printf(TEXT("-Output=\"%s\" -ContainerName=%s -ResponseFile=\"%s\"\r\n"), *Utoc, *Folder, *ResponseFile);
		if (!SaveText(ResponseFile, Utf8(Response)) || !SaveText(CommandsFile, Utf8(Commands)))
		{
			return Fail(TEXT("cannot write ") + ResponseFile);
		}
		const FString Executable = CommandletExecutable();
		const FString Project = FPaths::ConvertRelativePathToFull(FPaths::GetProjectFilePath());
		const FString Arguments = Quoted(Project) + TEXT(" -run=IoStore") +
			TEXT(" -CreateGlobalContainer=") + Quoted(FPaths::Combine(GlobalDir, TEXT("global.utoc"))) +
			TEXT(" -CookedDirectory=") + Quoted(CookedRoot) +
			TEXT(" -Commands=") + Quoted(CommandsFile) +
			TEXT(" -TargetPlatform=WindowsNoEditor -ddc=InstalledDerivedDataBackendGraph -unattended -NoLogTimes -UTF8Output") +
			TEXT(" -abslog=") + Quoted(LogPath);
		UE_LOG(LogRebirthSkins, Log, TEXT("Build Skins: %s %s"), *Executable, *Arguments);
		uint32 ProcessId = 0;
		FProcHandle Process = FPlatformProcess::CreateProc(*Executable, *Arguments, false, true, true, &ProcessId, 0, nullptr, nullptr, nullptr);
		if (!Process.IsValid())
		{
			return Fail(TEXT("the IoStore commandlet did not start (") + Executable + TEXT(")"));
		}
		const double Started = FPlatformTime::Seconds();
		bool bStopped = false;
		FString Stopped;
		while (FPlatformProcess::IsProcRunning(Process))
		{
			const double Seconds = FPlatformTime::Seconds() - Started;
			Progress.Say(FString::Printf(TEXT("%s: the game's package format (the engine's IoStore, %.0f s)"), *Label, Seconds));
			if (Progress.Cancelled() || Seconds > IoStoreTimeoutSeconds)
			{
				Stopped = Seconds > IoStoreTimeoutSeconds ? TEXT("the IoStore commandlet took over 20 minutes: stopped") : TEXT("cancelled");
				FPlatformProcess::TerminateProc(Process, true);
				bStopped = true;
				break;
			}
			FPlatformProcess::Sleep(0.25f);
		}
		FPlatformProcess::WaitForProc(Process);
		int32 ExitCode = -1;
		FPlatformProcess::GetProcReturnCode(Process, &ExitCode);
		FPlatformProcess::CloseProc(Process);
		if (bStopped)
		{
			return Fail(Stopped);
		}
		FString LogText;
		FFileHelper::LoadFileToString(LogText, *LogPath);
		// (the commandlet's exit code is 1 whenever the project logs an error of its own while it starts, e.g. an asset
		// with a malformed tag, so its own result decides, with the container on disk)
		const int32 Result = CommandletResult(LogText);
		if (Result != 0 || !FPaths::FileExists(Utoc) || !FPaths::FileExists(Ucas))
		{
			return Fail(FString::Printf(TEXT("the IoStore commandlet failed (exit code %d, result %d%s); its log: %s\n%s"), ExitCode, Result,
				FPaths::FileExists(Utoc) ? TEXT("") : TEXT(", no container"), *LogPath, *LastErrors(LogText, 6)));
		}
		Progress.Step(Label + TEXT(": reading the container"));
		CacsSound::Bytes TocBytes, CasBytes;
		if (!LoadBytes(Utoc, TocBytes) || !LoadBytes(Ucas, CasBytes))
		{
			return Fail(TEXT("cannot read ") + Utoc);
		}
		CacsSkin::Toc Container;
		std::string Error;
		if (!CacsSkin::ReadToc(TocBytes.data(), TocBytes.size(), Container, Error) || !CacsSkin::ExtractPackages(Container, CasBytes.data(), CasBytes.size(), Built, Error))
		{
			return Fail(Utoc + TEXT(": ") + FromUtf8(Error));
		}
		for (const FSkinPackageName& Entry : Packages)
		{
			const std::string Name = Utf8(Entry.Package);
			if (std::find_if(Built.begin(), Built.end(), [&](const CacsSkin::SkinPackage& P) { return P.Package == Name; }) == Built.end())
			{
				return Fail(Entry.Package + TEXT(" is not in the container the IoStore commandlet made (") + LogPath + TEXT(")"));
			}
		}
	}
	else
	{
		Progress.Step(Label + TEXT(": nothing to cook (every package is the game's)"));
		Progress.Step(Label + TEXT(": writing"), 0.f);
	}

	// 4. the skin folder
	Progress.Step(Label + TEXT(": writing ") + Folder);
	const FString Out = FPaths::Combine(OutRoot, Folder);
	CacsSkin::SkinInfo& Info = OutInfo;
	Info = CacsSkin::SkinInfo{};
	Info.Name = Utf8(Skin.Name.TrimStartAndEnd().IsEmpty() ? Folder : Skin.Name.TrimStartAndEnd());
	Info.Author = Utf8(Skin.Author.TrimStartAndEnd());
	Info.Description = Utf8(Skin.Description.TrimStartAndEnd());
	for (const FString& Row : Skin.Characters)
	{
		const FString Trimmed = Row.TrimStartAndEnd();
		if (!Trimmed.IsEmpty())
		{
			Info.Characters.push_back(Utf8(Trimmed));
		}
	}
	Info.Model = Utf8(Model->GetPathName());
	Info.Skeleton = Utf8(Model->Skeleton->GetPathName());
	Info.Family = Skin.Family.IsNull() ? std::string() : Utf8(Skin.Family.ToSoftObjectPath().ToString());
	Info.Proportions = Skin.bKeepProportions;
	for (const FString& Bone : Skin.ProportionBones)
	{
		const FString Trimmed = Bone.TrimStartAndEnd();
		if (!Trimmed.IsEmpty())
		{
			Info.ProportionBones.push_back(Utf8(Trimmed));
		}
	}
	Info.Voice = Utf8(Skin.Voice.TrimStartAndEnd());
	Info.Weapon = Utf8(Skin.Weapon.TrimStartAndEnd());
	Info.AnimBlueprint = Utf8(Skin.AnimBlueprint.TrimStartAndEnd());
	Info.Enabled = true;
	Info.Built = Utf8(FDateTime::UtcNow().ToString(TEXT("%Y-%m-%dT%H:%M:%SZ")));
	Info.BuiltWith = Utf8(EditorVersion);
	const FString Preview = FullFileOf(Skin.Preview);
	if (!Preview.IsEmpty())
	{
		if (!Preview.EndsWith(TEXT(".png"), ESearchCase::IgnoreCase) || !FPaths::FileExists(Preview))
		{
			Notes.Add(TEXT("its Preview ") + Preview + TEXT(" is not a .png file that is there: no preview"));
		}
		else
		{
			Info.Preview = "preview.png";
		}
	}
	const std::vector<std::string> Before = ListedFiles(Out);
	size_t TotalBytes = 0;
	for (CacsSkin::SkinPackage& Package : Built)
	{
		if (!SaveBytes(FPaths::Combine(Out, FromUtf8(Package.File)), Package.Data))
		{
			return Fail(TEXT("cannot write ") + FPaths::Combine(Out, FromUtf8(Package.File)));
		}
		TotalBytes += Package.Data.size();
		for (const CacsSkin::SkinBulk& Bulk : Package.Bulk)
		{
			if (!SaveBytes(FPaths::Combine(Out, FromUtf8(Bulk.File)), Bulk.Data))
			{
				return Fail(TEXT("cannot write ") + FPaths::Combine(Out, FromUtf8(Bulk.File)));
			}
			TotalBytes += Bulk.Data.size();
		}
	}
	if (!Info.Preview.empty() && IFileManager::Get().Copy(*FPaths::Combine(Out, TEXT("preview.png")), *Preview, true, true) != COPY_OK)
	{
		Notes.Add(TEXT("its Preview could not be copied: no preview"));
		Info.Preview.clear();
	}
	for (CacsSkin::SkinPackage& Package : Built)
	{
		Package.Data.clear();
		Package.Data.shrink_to_fit();
		for (CacsSkin::SkinBulk& Bulk : Package.Bulk)
		{
			Bulk.Data.clear();
			Bulk.Data.shrink_to_fit();
		}
	}
	Info.Packages = std::move(Built);
	if (!SaveText(FPaths::Combine(Out, TEXT("skin.json")), CacsSkin::WriteSkinJson(Info)))
	{
		return Fail(TEXT("cannot write ") + FPaths::Combine(Out, TEXT("skin.json")));
	}
	const int32 Removed = RemoveStaleFiles(Out, Before, CacsSkin::FilesOf(Info));
	Report += FString::Printf(TEXT("%s: %s, %d package(s) (%.1f MB)%s\n"), *Label, *Out, static_cast<int32>(Info.Packages.size()),
		TotalBytes / (1024.0 * 1024.0), Removed > 0 ? *FString::Printf(TEXT(", %d file(s) of its last build removed"), Removed) : TEXT(""));
	for (const CacsSkin::SkinPackage& Package : Info.Packages)
	{
		Report += FString::Printf(TEXT("    %s: %d export(s), %d import(s)%s\n"), UTF8_TO_TCHAR(Package.Package.c_str()), Package.ExportCount,
			static_cast<int32>(Package.Imports.size()), Package.Bulk.empty() ? TEXT("") : *FString::Printf(TEXT(", %d bulk data file(s)"), static_cast<int32>(Package.Bulk.size())));
	}
	for (const FString& Note : Notes)
	{
		Report += TEXT("    ") + Note + TEXT("\n");
	}
	return true;
}
} // namespace RebirthSkelCompatSkins

bool UEndSkeletonCompatDataObject::BuildSkinsTo(FString& OutReport)
{
	int32 Enabled = 0;
	for (const FEndCharacterSkin& Skin : Skins)
	{
		Enabled += Skin.bEnabled ? 1 : 0;
	}
	if (Enabled == 0)
	{
		OutReport += Skins.Num() == 0 ? TEXT("No skins: add one to Skins (its Name, its Model, the Characters that wear it, its Family), then press Build Skins.\n")
									  : TEXT("Every skin is off.\n");
		return false;
	}
	FString OutRoot = RebirthSkelCompatSkins::FullFolderOf(SkinsOutputFolder);
	if (OutRoot.IsEmpty())
	{
		OutRoot = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("RebirthSkelCompat"), TEXT("Skins")));
	}
	FScopedSlowTask Task(static_cast<float>(Enabled * 5 + 1), FText::FromString(TEXT("Build Skins")));
	Task.MakeDialog(true);
	RebirthSkelCompatSkins::FProgress Progress{Task};
	RebirthSkelCompatSkins::FGamePackages Game;
	bool bOk = true;
	std::vector<std::pair<FString, CacsSkin::SkinInfo>> Built;   // (folder, its skin.json); std types stay out of TArray
	TArray<FString> Folders;
	for (int32 Index = 0; Index < Skins.Num(); ++Index)
	{
		const FEndCharacterSkin& Skin = Skins[Index];
		const FString Name = Skin.Name.TrimStartAndEnd();
		const FString Label = FString::Printf(TEXT("Skin %d (%s)"), Index, Name.IsEmpty() ? TEXT("no name") : *Name);
		if (!Skin.bEnabled)
		{
			OutReport += Label + TEXT(": off, skipped (a copy installed before stays as it is)\n");
			continue;
		}
		FString Folder = Skin.Folder.TrimStartAndEnd();
		if (Folder.IsEmpty())
		{
			Folder = RebirthSkelCompatSkins::FolderFromName(Name);
		}
		if (!RebirthSkelCompatSkins::ValidFolderName(Folder))
		{
			OutReport += Label + TEXT(": NOT built: its Folder \"") + Folder + TEXT("\" is not 1-64 letters, digits, _ or - (not starting with _); give it a Name or a Folder\n");
			bOk = false;
			continue;
		}
		if (Folders.ContainsByPredicate([&](const FString& Other) { return Other.Equals(Folder, ESearchCase::IgnoreCase); }))
		{
			OutReport += Label + TEXT(": NOT built: another skin of this data object has the folder ") + Folder + TEXT("\n");
			bOk = false;
			continue;
		}
		Folders.Add(Folder);
		CacsSkin::SkinInfo Info;
		if (RebirthSkelCompatSkins::BuildSkin(Skin, Label, Folder, OutRoot, Game, Progress, Info, OutReport))
		{
			Built.emplace_back(Folder, std::move(Info));
		}
		else
		{
			bOk = false;
		}
		if (Task.ShouldCancel())
		{
			OutReport += TEXT("Cancelled.\n");
			return false;
		}
	}
	Progress.Step(TEXT("Installing"));
	if (!Built.empty() && bInstallSkins)
	{
		const FString GameRoot = RebirthSkelCompatSkins::FullFolderOf(GameDirectory);
		const FString ModRoot = GameRoot.IsEmpty() ? FString() : FPaths::Combine(GameRoot, RebirthSkelCompatSkins::GameModFolder);
		if (GameRoot.IsEmpty() || !IFileManager::Get().DirectoryExists(*ModRoot))
		{
			OutReport += TEXT("\nNOT installed: ") + (GameRoot.IsEmpty() ? FString(TEXT("Game Directory is empty")) : TEXT("the game has no Create a Character System (") + ModRoot + TEXT(")")) +
						 TEXT(". Copy the skin folders into the game's ue4ss\\Mods\\RebirthSkelCompat\\skins and build again with Game Directory set.\n");
			bOk = false;
		}
		else
		{
			OutReport += TEXT("\nInstalled into ") + FPaths::Combine(ModRoot, TEXT("skins")) + TEXT(":\n");
			for (const std::pair<FString, CacsSkin::SkinInfo>& Skin : Built)
			{
				FString Problem;
				const FString To = FPaths::Combine(ModRoot, TEXT("skins"), Skin.first);
				if (RebirthSkelCompatSkins::InstallSkinFolder(FPaths::Combine(OutRoot, Skin.first), To, Skin.second, Problem))
				{
					OutReport += TEXT("    skins/") + Skin.first + TEXT("\n");
				}
				else
				{
					OutReport += TEXT("    skins/") + Skin.first + TEXT(": NOT installed: ") + Problem + TEXT("\n");
					bOk = false;
				}
			}
			bOk &= RebirthSkelCompatSkins::RemakeSkinsContainer(GameRoot, OutReport);
			OutReport += TEXT("    Start the game (Create a Character System 3.10) to wear them.\n");
		}
	}
	else if (!Built.empty())
	{
		OutReport += TEXT("\nInstall Skins is off: the skins are only in ") + OutRoot + TEXT(". With Install Skins on, Build Skins copies them into the game's ue4ss\\Mods\\RebirthSkelCompat\\skins and makes the skins container (~mods\\CreateACharacterSkins_P) of every installed skin.\n");
	}
	return bOk && !Built.empty();
}

void UEndSkeletonCompatDataObject::BuildSkins()
{
	FString Report;
	const bool bOk = BuildSkinsTo(Report);
	ShowResult(TEXT("Build Skins"), Report, bOk);
}
