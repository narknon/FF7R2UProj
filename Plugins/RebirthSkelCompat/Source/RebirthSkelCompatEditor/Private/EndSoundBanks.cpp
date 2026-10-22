// Sound Banks (editor 1.14): new sound banks for the game made from WAV files, as Create a Character System's sound bank
// maker makes them (SoundBankCore.hpp, shared with its command-line tool): each line's WAV encoded as the game's voice
// banks are (CRI HCA 2.0), in a SEAD sound bank, in a cooked SQEXSEADSound package (one per voice language for a voice
// bank), in a ~mods IoStore container (<Container>.utoc, .ucas, .pak) the game loads as it is. No cook is needed.
#include "EndSkeletonCompatDataObject.h"

#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/MessageDialog.h"
#include "Misc/Paths.h"

#include <string>
#include <vector>

#include "SoundBankCore.hpp"

namespace RebirthSkelCompatSoundBanks
{
std::string Narrow(const FString& Text)
{
	return std::string(TCHAR_TO_UTF8(*Text));
}

FString Wide(const std::string& Text)
{
	return FString(UTF8_TO_TCHAR(Text.c_str()));
}

// A language folder's name as the game has it (US, JP, FR, DE), from what the data object says (us, English...).
FString LanguageCode(const FString& Language)
{
	const FString L = Language.TrimStartAndEnd().ToUpper();
	if (L == TEXT("EN") || L == TEXT("ENGLISH") || L == TEXT("US"))
	{
		return TEXT("US");
	}
	if (L == TEXT("JA") || L == TEXT("JAPANESE") || L == TEXT("JP"))
	{
		return TEXT("JP");
	}
	if (L == TEXT("FRENCH") || L == TEXT("FR"))
	{
		return TEXT("FR");
	}
	if (L == TEXT("GERMAN") || L == TEXT("DE"))
	{
		return TEXT("DE");
	}
	return L;
}

// The WAV folder's language folders (the bank's Languages), as written.
TArray<FString> LanguagesOf(const FEndSoundBank& Bank)
{
	TArray<FString> Out;
	for (const FString& Language : Bank.Languages)
	{
		const FString Code = LanguageCode(Language);
		if (!Code.IsEmpty())
		{
			Out.AddUnique(Code);
		}
	}
	return Out;
}

FString FolderOf(const FDirectoryPath& Directory)
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

FString FileOf(const FFilePath& File)
{
	FString Path = File.FilePath.TrimStartAndEnd();
	if (!Path.IsEmpty() && FPaths::IsRelative(Path))
	{
		Path = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir(), Path);
	}
	return Path;
}

// The WAV files of a folder, by name (cue), sorted.
TArray<FString> WavNames(const FString& Folder)
{
	TArray<FString> Files;
	IFileManager::Get().FindFiles(Files, *FPaths::Combine(Folder, TEXT("*.wav")), true, false);
	TArray<FString> Names;
	for (const FString& File : Files)
	{
		Names.AddUnique(FPaths::GetBaseFilename(File));
	}
	Names.Sort();
	return Names;
}

bool ValidCue(const FString& Cue)
{
	if (Cue.IsEmpty() || Cue.Len() > 63)
	{
		return false;
	}
	for (const TCHAR C : Cue)
	{
		if (!(FChar::IsAlnum(C) || C == TEXT('_') || C == TEXT('-')))
		{
			return false;
		}
	}
	return true;
}

bool LoadWav(const FString& Path, CacsSound::Pcm& Out, FString& Error)
{
	TArray<uint8> Data;
	if (!FFileHelper::LoadFileToArray(Data, *Path))
	{
		Error = TEXT("cannot read ") + Path;
		return false;
	}
	std::string Why;
	if (!CacsSound::ReadWav(Data.GetData(), static_cast<size_t>(Data.Num()), Out, Why))
	{
		Error = Path + TEXT(": ") + Wide(Why);
		return false;
	}
	return true;
}

bool SaveBytes(const FString& Path, const CacsSound::Bytes& Bytes)
{
	TArray<uint8> Data;
	Data.Append(Bytes.data(), static_cast<int32>(Bytes.size()));
	return FFileHelper::SaveArrayToFile(Data, *Path);
}
} // namespace RebirthSkelCompatSoundBanks

bool UEndSkeletonCompatDataObject::ReadSoundBankWavsTo(FString& OutReport)
{
	using namespace RebirthSkelCompatSoundBanks;
	bool bOk = true;
	int32 Done = 0;
	for (int32 Index = 0; Index < SoundBanks.Num(); ++Index)
	{
		FEndSoundBank& Bank = SoundBanks[Index];
		const FString Label = FString::Printf(TEXT("Sound bank %d (%s)"), Index, Bank.Bank.IsEmpty() ? TEXT("no name") : *Bank.Bank);
		if (!Bank.bEnabled)
		{
			OutReport += Label + TEXT(": off, skipped\n");
			continue;
		}
		const FString Folder = FolderOf(Bank.WavFolder);
		if (Folder.IsEmpty() || !IFileManager::Get().DirectoryExists(*Folder))
		{
			OutReport += Label + TEXT(": its WAV Folder ") + (Folder.IsEmpty() ? FString(TEXT("is empty")) : Folder + TEXT(" is not there")) + TEXT("\n");
			bOk = false;
			continue;
		}
		const TArray<FString> Languages = LanguagesOf(Bank);
		const FString From = Languages.Num() > 0 ? FPaths::Combine(Folder, Languages[0]) : Folder;
		const TArray<FString> Names = WavNames(From);
		if (Names.Num() == 0)
		{
			OutReport += Label + TEXT(": no .wav files in ") + From + TEXT("\n");
			bOk = false;
			continue;
		}
		int32 Added = 0, Kept = 0, Bad = 0;
		for (const FString& Name : Names)
		{
			if (!ValidCue(Name))
			{
				++Bad;
				OutReport += Label + TEXT(": ") + Name + TEXT(".wav left out (a cue is letters, digits, _ or -)\n");
				continue;
			}
			if (Bank.Lines.ContainsByPredicate([&](const FEndSoundBankLine& Line) { return Line.Cue.TrimStartAndEnd().Equals(Name, ESearchCase::IgnoreCase); }))
			{
				++Kept;
				continue;
			}
			FEndSoundBankLine Line;
			Line.Cue = Name;
			Bank.Lines.Add(Line);
			++Added;
		}
		// the lines whose WAV is not in the folder (and that name none of their own)
		TArray<FString> Missing;
		for (const FEndSoundBankLine& Line : Bank.Lines)
		{
			if (FileOf(Line.Wav).IsEmpty() && !Names.ContainsByPredicate([&](const FString& Name) { return Name.Equals(Line.Cue.TrimStartAndEnd(), ESearchCase::IgnoreCase); }))
			{
				Missing.Add(Line.Cue);
			}
		}
		OutReport += Label + FString::Printf(TEXT(": %d line(s) added, %d kept from %s"), Added, Kept, *From);
		if (Bad > 0)
		{
			OutReport += FString::Printf(TEXT(", %d left out"), Bad);
		}
		if (Missing.Num() > 0)
		{
			OutReport += TEXT("; no WAV for ") + FString::Join(Missing, TEXT(", "));
		}
		OutReport += TEXT("\n");
		++Done;
	}
	if (SoundBanks.Num() == 0)
	{
		OutReport += TEXT("No sound banks: add one to Sound Banks (its Bank name, its WAV Folder), then press Read Sound Bank WAVs.\n");
	}
	if (Done > 0)
	{
		Modify();
		MarkPackageDirty();
	}
	return bOk && Done > 0;
}

bool UEndSkeletonCompatDataObject::BuildSoundBanksTo(FString& OutReport)
{
	using namespace RebirthSkelCompatSoundBanks;
	bool bOk = true;
	int32 Built = 0;
	for (int32 Index = 0; Index < SoundBanks.Num(); ++Index)
	{
		const FEndSoundBank& Bank = SoundBanks[Index];
		const FString Label = FString::Printf(TEXT("Sound bank %d (%s)"), Index, Bank.Bank.IsEmpty() ? TEXT("no name") : *Bank.Bank);
		if (!Bank.bEnabled)
		{
			OutReport += Label + TEXT(": off, skipped\n");
			continue;
		}
		CacsSound::Build::Request Request;
		Request.Container = Narrow(Bank.Container.TrimStartAndEnd());
		Request.Bank = Narrow(Bank.Bank.TrimStartAndEnd());
		Request.BankId = static_cast<uint16_t>(FMath::Clamp(Bank.BankId, 0, 65535));
		FString Folder = Bank.Folder.TrimStartAndEnd();
		while (Folder.EndsWith(TEXT("/")))
		{
			Folder.LeftChopInline(1);
		}
		Request.Folder = Narrow(Folder);
		FString Alias = Bank.AliasSetting.TrimStartAndEnd();
		int32 Dot = INDEX_NONE;
		if (Alias.FindLastChar(TEXT('.'), Dot) && Alias.Find(TEXT("/"), ESearchCase::CaseSensitive, ESearchDir::FromEnd) < Dot)
		{
			Alias = Alias.Left(Dot);   // (the package: /Game/Sound/Config/AliasSetting/VO_PC0010_00_Sephiroth)
		}
		Request.AliasSetting = Narrow(Alias);
		FString Attenuation = Bank.Attenuation.TrimStartAndEnd();
		if (Attenuation.FindLastChar(TEXT('.'), Dot) && Attenuation.Find(TEXT("/"), ESearchCase::CaseSensitive, ESearchDir::FromEnd) < Dot)
		{
			Attenuation = Attenuation.Left(Dot);
		}
		Request.Attenuation = Narrow(Attenuation);
		Request.Kbps = FMath::Clamp(static_cast<double>(Bank.Kbps), 16.0, 512.0);
		Request.Rate = FMath::Clamp(Bank.SampleRate, 0, 96000);
		Request.Channels = FMath::Clamp(Bank.Channels, 0, 8);
		const FString WavFolder = FolderOf(Bank.WavFolder);
		const TArray<FString> Languages = LanguagesOf(Bank);
		const bool bVoice = Folder.Contains(TEXT("{language}"));
		if (Languages.Num() > 0 && !bVoice)
		{
			OutReport += Label + TEXT(": Languages are for a voice bank (a Folder with {language}); the lines of ") + Languages[0] + TEXT(" are used\n");
		}
		FString Problem;
		for (const FEndSoundBankLine& Entry : Bank.Lines)
		{
			const FString Cue = Entry.Cue.TrimStartAndEnd();
			if (!ValidCue(Cue))
			{
				Problem = TEXT("a line's cue \"") + Cue + TEXT("\" is not 1-63 letters, digits, _ or -");
				break;
			}
			CacsSound::Build::Line Line;
			Line.Cue = Narrow(Cue);
			Line.Volume = FMath::Clamp(Entry.Volume, 0.f, 4.f);
			Line.Category = static_cast<uint8_t>(FMath::Clamp(Entry.Category, 0, 255));
			Line.Bus = static_cast<uint8_t>(FMath::Clamp(Entry.Bus, 0, 255));
			Line.Id = Entry.Id < 0 ? -1 : FMath::Clamp(Entry.Id, 0, 65535);
			Line.Length = Entry.Length > 0.f ? Entry.Length : -1.f;
			// its WAV: the line's own, else <WAV Folder>/<cue>.wav, or with Languages <WAV Folder>/<language>/<cue>.wav for each
			const FString Own = FileOf(Entry.Wav);
			if (!Own.IsEmpty())
			{
				CacsSound::Pcm Pcm;
				if (!LoadWav(Own, Pcm, Problem))
				{
					break;
				}
				Line.Audio.emplace_back(Languages.Num() > 0 && bVoice ? Narrow(Languages[0]) : std::string(), std::move(Pcm));
			}
			else if (Languages.Num() > 0 && bVoice)
			{
				for (const FString& Language : Languages)
				{
					const FString Path = FPaths::Combine(WavFolder, Language, Cue + TEXT(".wav"));
					if (!FPaths::FileExists(Path))
					{
						continue;   // (that language falls back to the first one's line)
					}
					CacsSound::Pcm Pcm;
					if (!LoadWav(Path, Pcm, Problem))
					{
						break;
					}
					Line.Audio.emplace_back(Narrow(Language), std::move(Pcm));
				}
				if (!Problem.IsEmpty())
				{
					break;
				}
			}
			else
			{
				const FString Path = FPaths::Combine(WavFolder, (Languages.Num() > 0 ? Languages[0] + TEXT("/") : FString()) + Cue + TEXT(".wav"));
				CacsSound::Pcm Pcm;
				if (!LoadWav(Path, Pcm, Problem))
				{
					break;
				}
				Line.Audio.emplace_back(std::string(), std::move(Pcm));
			}
			if (Line.Audio.empty())
			{
				Problem = TEXT("line ") + Cue + TEXT(" has no WAV (") + WavFolder + TEXT(")");
				break;
			}
			Request.Lines.push_back(std::move(Line));
		}
		if (!Problem.IsEmpty())
		{
			OutReport += Label + TEXT(": NOT built: ") + Problem + TEXT("\n");
			bOk = false;
			continue;
		}
		const double Started = FPlatformTime::Seconds();
		const CacsSound::Build::Result Result = CacsSound::Build::Make(Request);
		if (!Result.Ok)
		{
			OutReport += Label + TEXT(": NOT built: ") + Wide(Result.Error) + TEXT("\n");
			bOk = false;
			continue;
		}
		FString Out = FolderOf(Bank.OutputFolder);
		if (Out.IsEmpty())
		{
			Out = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("RebirthSkelCompat"), TEXT("SoundBanks"), Bank.Container.TrimStartAndEnd());
			Out = FPaths::ConvertRelativePathToFull(Out);
		}
		IFileManager::Get().MakeDirectory(*Out, true);
		const FString Base = FPaths::Combine(Out, Bank.Container.TrimStartAndEnd());
		if (!SaveBytes(Base + TEXT(".utoc"), Result.Utoc) || !SaveBytes(Base + TEXT(".ucas"), Result.Ucas) || !SaveBytes(Base + TEXT(".pak"), Result.Pak))
		{
			OutReport += Label + TEXT(": NOT written to ") + Out + TEXT("\n");
			bOk = false;
			continue;
		}
		OutReport += Label + FString::Printf(TEXT(": %s.utoc/.ucas/.pak in %s (%.1f s)\n"), *Bank.Container.TrimStartAndEnd(), *Out, FPlatformTime::Seconds() - Started);
		for (const std::string& Line : Result.Report)
		{
			OutReport += TEXT("    ") + Wide(Line) + TEXT("\n");
		}
		OutReport += TEXT("    Put the three files in the game's ~mods folder (End/Content/Paks/~mods). Give a character the bank with Voice on its row or form");
		if (!Result.Packages.empty())
		{
			FString Named = Wide(Result.Packages.front());
			if (bVoice)
			{
				Named = Folder + TEXT("/") + Bank.Bank.TrimStartAndEnd();
			}
			OutReport += TEXT(" (") + Named + TEXT(")");
		}
		OutReport += TEXT(", and list it in its CharaSpec pack so the game loads it.\n");
		++Built;
	}
	if (SoundBanks.Num() == 0)
	{
		OutReport += TEXT("No sound banks: add one to Sound Banks (its Container, its Bank name, its WAV Folder), then press Read Sound Bank WAVs and Build Sound Banks.\n");
	}
	return bOk && Built > 0;
}

void UEndSkeletonCompatDataObject::ReadSoundBankWavs()
{
	FString Report;
	const bool bOk = ReadSoundBankWavsTo(Report);
	ShowResult(TEXT("Read Sound Bank WAVs"), Report, bOk);
}

void UEndSkeletonCompatDataObject::BuildSoundBanks()
{
	FString Report;
	const bool bOk = BuildSoundBanksTo(Report);
	ShowResult(TEXT("Build Sound Banks"), Report, bOk);
}
