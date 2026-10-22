#include "RebirthFxLinkPaths.h"

#include "DesktopPlatformModule.h"
#include "Framework/Application/SlateApplication.h"
#include "HAL/FileManager.h"
#include "IDesktopPlatform.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

#if PLATFORM_WINDOWS
#include "Windows/WindowsHWrapper.h"
#endif

namespace RebirthFxLinkPathsDetail
{
	const TCHAR* const ConfigSection = TEXT("RebirthFxLiveLink");
	const TCHAR* const ConfigKey = TEXT("GamePaksDirectory");
	// The End project's own tools save the same choice here.
	const TCHAR* const OldConfigSection = TEXT("RebirthDataObjects");

	const TCHAR* const GameFolder = TEXT("FINAL FANTASY VII REBIRTH");

	/** The "path" values of a Steam libraryfolders.vdf. */
	void SteamLibraries(const FString& Vdf, TArray<FString>& Out)
	{
		TArray<FString> Lines;
		Vdf.ParseIntoArrayLines(Lines);
		for (const FString& Line : Lines)
		{
			const FString Trimmed = Line.TrimStartAndEnd();
			if (!Trimmed.StartsWith(TEXT("\"path\"")))
			{
				continue;
			}
			FString Rest = Trimmed.Mid(6).TrimStartAndEnd();
			if (Rest.Len() >= 2 && Rest.StartsWith(TEXT("\"")) && Rest.EndsWith(TEXT("\"")))
			{
				Rest = Rest.Mid(1, Rest.Len() - 2).Replace(TEXT("\\\\"), TEXT("\\"));
				Out.AddUnique(Rest);
			}
		}
	}

	void SteamCandidates(TArray<FString>& Out)
	{
		TArray<FString> Steams;
#if PLATFORM_WINDOWS
		FString Value;
		if (FWindowsPlatformMisc::QueryRegKey(HKEY_CURRENT_USER, TEXT("Software\\Valve\\Steam"), TEXT("SteamPath"), Value) && !Value.IsEmpty())
		{
			Steams.AddUnique(Value);
		}
		if (FWindowsPlatformMisc::QueryRegKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\WOW6432Node\\Valve\\Steam"), TEXT("InstallPath"), Value) && !Value.IsEmpty())
		{
			Steams.AddUnique(Value);
		}
#endif
		Steams.AddUnique(TEXT("C:/Program Files (x86)/Steam"));
		TArray<FString> Libraries = Steams;
		for (const FString& Steam : Steams)
		{
			for (const TCHAR* Vdf : { TEXT("steamapps/libraryfolders.vdf"), TEXT("config/libraryfolders.vdf") })
			{
				FString Text;
				if (FFileHelper::LoadFileToString(Text, *(Steam / Vdf)))
				{
					SteamLibraries(Text, Libraries);
				}
			}
		}
		for (const FString& Library : Libraries)
		{
			Out.AddUnique(Library / TEXT("steamapps/common") / GameFolder);
		}
	}
}

namespace RebirthFxLinkPaths
{
	using namespace RebirthFxLinkPathsDetail;

	bool IsPaksDirectory(const FString& Directory)
	{
		TArray<FString> Found;
		IFileManager::Get().FindFiles(Found, *(Directory / TEXT("pakchunk0-*.utoc")), true, false);
		return Found.Num() > 0;
	}

	FString ResolvePaksDirectory(const FString& InDirectory)
	{
		if (InDirectory.IsEmpty())
		{
			return FString();
		}
		FString Directory = FPaths::ConvertRelativePathToFull(InDirectory);
		FPaths::NormalizeDirectoryName(Directory);
		if (IsPaksDirectory(Directory))
		{
			return Directory;
		}
		static const TCHAR* const Subfolders[] = { TEXT("End/Content/Paks"), TEXT("Content/Paks"), TEXT("Paks") };
		for (const TCHAR* Subfolder : Subfolders)
		{
			const FString Candidate = Directory / Subfolder;
			if (IsPaksDirectory(Candidate))
			{
				return Candidate;
			}
		}
		return FString();
	}

	FString FindPaksDirectory(bool bAsk)
	{
		if (GConfig)
		{
			for (const TCHAR* Section : { ConfigSection, OldConfigSection })
			{
				FString Saved;
				if (GConfig->GetString(Section, ConfigKey, Saved, GEditorPerProjectIni))
				{
					const FString Paks = ResolvePaksDirectory(Saved);
					if (!Paks.IsEmpty())
					{
						return Paks;
					}
				}
			}
		}
		TArray<FString> Candidates;
		SteamCandidates(Candidates);
		for (const TCHAR* Drive : { TEXT("C:"), TEXT("D:"), TEXT("E:"), TEXT("F:"), TEXT("G:") })
		{
			Candidates.AddUnique(FString(Drive) / TEXT("SteamLibrary/steamapps/common") / GameFolder);
			Candidates.AddUnique(FString(Drive) / TEXT("Epic Games") / GameFolder);
			Candidates.AddUnique(FString(Drive) / TEXT("Program Files/Epic Games") / GameFolder);
		}
		for (const FString& Candidate : Candidates)
		{
			const FString Paks = ResolvePaksDirectory(Candidate);
			if (!Paks.IsEmpty())
			{
				return Paks;
			}
		}
		if (bAsk && FSlateApplication::IsInitialized())
		{
			if (IDesktopPlatform* Desktop = FDesktopPlatformModule::Get())
			{
				FString Chosen;
				const void* ParentWindow = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);
				if (Desktop->OpenDirectoryDialog(ParentWindow, TEXT("Select the FINAL FANTASY VII REBIRTH game folder"), FString(), Chosen))
				{
					const FString Paks = ResolvePaksDirectory(Chosen);
					if (!Paks.IsEmpty() && GConfig)
					{
						GConfig->SetString(ConfigSection, ConfigKey, *Paks, GEditorPerProjectIni);
						GConfig->Flush(false, GEditorPerProjectIni);
					}
					return Paks;
				}
			}
		}
		return FString();
	}
}
