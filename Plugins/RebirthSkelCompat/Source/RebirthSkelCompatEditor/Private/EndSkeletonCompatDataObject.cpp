// RebirthSkelCompat: KH3-style compatible skeletons for FINAL FANTASY VII REBIRTH mods.
#include "EndSkeletonCompatDataObject.h"
#include "EndMoveMaker.h"

#include "Animation/AnimBoneCompressionCodec.h"
#include "Animation/AnimBoneCompressionSettings.h"
#include "Animation/AnimComposite.h"
#include "Animation/AnimCurveCompressionSettings.h"
#include "Animation/AnimCurveCompressionCodec.h"
#include "Animation/AnimCurveTypes.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Animation/AnimSequence.h"
#include "Animation/Skeleton.h"
#include "AnimationBlueprintLibrary.h"   // (1.13.1) Flatten Root: RemoveBoneAnimation
#include "Animation/SmartName.h"
#include "AssetRegistryModule.h"
#include "Containers/StringConv.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "EdGraphSchema_K2.h"
#include "Editor.h"
#include "Engine/AssetUserData.h"
#include "Engine/Blueprint.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/PrimaryAssetLabel.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/SkeletalMeshSocket.h"
#include "FileHelpers.h"
#include "HAL/FileManager.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Misc/FileHelper.h"
#include "Misc/MessageDialog.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "Modules/ModuleManager.h"
#include "ObjectTools.h"
#include "ReferenceSkeleton.h"
#include "SkeletalMeshTypes.h"          // (1.13.1) FSkinnedMeshComponentRecreateRenderStateContext
#include "NiagaraTypes.h"   // (1.12.4) an effect's Niagara parameters (UnwritableNiagara)
#include "ScopedTransaction.h"
#include "Settings/ProjectPackagingSettings.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "UObject/Linker.h"
#include "UObject/MetaData.h"          // (1.13.1) Flatten Root marks what it did
#include "HAL/PlatformFilemanager.h"     // (1.13.1) Cook For Game
#include "Interfaces/ITargetPlatform.h"
#include "Interfaces/ITargetPlatformManagerModule.h"
#include "Serialization/MemoryWriter.h"
#include "UObject/Package.h"
#include "UObject/PackageFileSummary.h"
#include "UObject/StructOnScope.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/UnrealType.h"

#include <string>
#include <type_traits>

// The game mod's own rules (config parsing, families, the bone-hierarchy test and the hierarchy fix), shared so this
// data object shows exactly what the game will do. A copy of Tools/RebirthSkelCompat/src/SkelCompatCore.hpp.
THIRD_PARTY_INCLUDES_START
#include "SkelCompatCore.hpp"
THIRD_PARTY_INCLUDES_END

DEFINE_LOG_CATEGORY_STATIC(LogRebirthSkelCompat, Log, All);

static_assert(std::is_same<TCHAR, wchar_t>::value, "The shared SkelCompat core uses wchar_t strings (Windows).");

namespace RebirthSkelCompatEditor
{
// The Blueprint the UE4SS mod reads in game. Parent is the native AssetUserData, which the retail game has.
const TCHAR* const CarrierPackage = TEXT("/Game/RebirthSkelCompat/BP_SkelCompatUserData");
const TCHAR* const CarrierName = TEXT("BP_SkelCompatUserData");
const TCHAR* const AnimationSkeletonsVariable = TEXT("AnimationSkeletons");
const TCHAR* const ReceivingMeshesVariable = TEXT("ReceivingMeshes");
const TCHAR* const DefaultGameDirectory = TEXT("C:/Program Files (x86)/Steam/steamapps/common/FINAL FANTASY VII REBIRTH");
const TCHAR* const ModFolder = TEXT("End/Binaries/Win64/ue4ss/Mods/RebirthSkelCompat");
constexpr int32 MaxMeshesPerPair = 32;
constexpr int32 MaxNamesListed = 10;
constexpr int64 MaxConfigFileBytes = 1 << 20; // the mod skips larger files

FString PathOf(const UObject* Object) { return Object ? Object->GetPathName() : FString(TEXT("None")); }

// Assets loaded from the game's cooked files. Saving one from the editor turns it into an editor copy of a
// retail file, and rebinding a game mesh changes it everywhere the game shows it.
bool IsCookedAsset(const UObject* Object)
{
	const UPackage* Package = Object ? Object->GetOutermost() : nullptr;
	return Package && Package->HasAnyPackageFlags(PKG_Cooked);
}

std::wstring Wide(const FString& Text) { return std::wstring(*Text); }
FString FromWide(const std::wstring& Text) { return FString(Text.c_str()); }

// ------------------------------------------------------------------------------------------------
// Paths, names and the mod's JSON
// ------------------------------------------------------------------------------------------------
// "/Game/A/B", "Skeleton'/Game/A/B.B'", "\Game\A\B.B" -> "/Game/A/B.B" (the form FSoftObjectPath::ToString gives).
FString NormalizedObjectPath(FString Path)
{
	Path.TrimStartAndEndInline();
	Path.ReplaceInline(TEXT("\\"), TEXT("/"));
	int32 Quote = INDEX_NONE;
	if (Path.FindChar(TEXT('\''), Quote))
	{
		Path = Path.Mid(Quote + 1);
		Path.RemoveFromEnd(TEXT("'"));
	}
	while (Path.EndsWith(TEXT("/")))
	{
		Path.LeftChopInline(1);
	}
	int32 Slash = INDEX_NONE;
	int32 Dot = INDEX_NONE;
	Path.FindLastChar(TEXT('/'), Slash);
	Path.FindLastChar(TEXT('.'), Dot);
	if (Slash != INDEX_NONE && (Dot == INDEX_NONE || Dot < Slash))
	{
		Path += TEXT(".") + Path.Mid(Slash + 1);
	}
	return Path;
}

bool SamePath(const FString& A, const FString& B)
{
	return NormalizedObjectPath(A).Equals(NormalizedObjectPath(B), ESearchCase::IgnoreCase);
}

FString SoftPath(const TSoftObjectPtr<USkeleton>& Soft) { return Soft.ToSoftObjectPath().ToString(); }

// "/Game/A/PC0000_00_Skeleton.PC0000_00_Skeleton" -> "PC0000_00_Skeleton"
FString ShortName(const FString& Path)
{
	int32 Cut = INDEX_NONE;
	if (Path.FindLastChar(TEXT('.'), Cut) || Path.FindLastChar(TEXT('/'), Cut))
	{
		return Path.Mid(Cut + 1);
	}
	return Path;
}

FString ShortName(const std::wstring& Path) { return ShortName(FromWide(Path)); }

// "~mods\SephirothOverCloud_P.pak" -> "SephirothOverCloud_P": the name the mod compares installed paks and mod folders by.
FString PakName(FString Name)
{
	Name.TrimStartAndEndInline();
	Name.ReplaceInline(TEXT("\\"), TEXT("/"));
	while (Name.EndsWith(TEXT("/")))
	{
		Name.LeftChopInline(1);
	}
	int32 Slash = INDEX_NONE;
	if (Name.FindLastChar(TEXT('/'), Slash))
	{
		Name = Name.Mid(Slash + 1);
	}
	for (const TCHAR* Extension : {TEXT(".pak"), TEXT(".utoc"), TEXT(".ucas"), TEXT(".sig")})
	{
		if (Name.RemoveFromEnd(Extension, ESearchCase::IgnoreCase))
		{
			break;
		}
	}
	Name.TrimStartAndEndInline();
	return Name;
}

// Trimmed, non-empty, without duplicates (case-insensitive, like the mod).
TArray<FString> CleanList(const TArray<FString>& Items, bool bPakNames)
{
	TArray<FString> Out;
	for (const FString& Item : Items)
	{
		FString Clean = bPakNames ? PakName(Item) : Item.TrimStartAndEnd();
		if (!Clean.IsEmpty())
		{
			Out.AddUnique(Clean); // FString == ignores case
		}
	}
	return Out;
}

FString ListText(const TArray<FString>& Items)
{
	return Items.Num() > 0 ? FString::Join(Items, TEXT(", ")) : FString(TEXT("(none)"));
}

FString ShortList(const std::vector<std::wstring>& Paths)
{
	TArray<FString> Names;
	for (const std::wstring& Path : Paths)
	{
		Names.Add(ShortName(Path));
	}
	return ListText(Names);
}

// True when some name in A is not in B.
bool HasNamesMissingFrom(const TArray<FString>& A, const TArray<FString>& B)
{
	for (const FString& Name : A)
	{
		if (!B.Contains(Name))
		{
			return true;
		}
	}
	return false;
}

const TCHAR* MethodText(EEndSkelCompatMethod Method)
{
	switch (Method)
	{
	case EEndSkelCompatMethod::Mesh: return TEXT("mesh");
	case EEndSkelCompatMethod::Family: return TEXT("family");
	default: return TEXT("animations");
	}
}

const TCHAR* MethodLabel(EEndSkelCompatMethod Method)
{
	switch (Method)
	{
	case EEndSkelCompatMethod::Mesh: return TEXT("Mesh rebind");
	case EEndSkelCompatMethod::Family: return TEXT("Family");
	default: return TEXT("Animations");
	}
}

// The mod's reading of "method": mesh and family spellings, anything else is the animations method.
EEndSkelCompatMethod ParseMethod(FString Text)
{
	Text.TrimStartAndEndInline();
	for (const TCHAR* Mesh : {TEXT("mesh"), TEXT("meshes"), TEXT("rebind")})
	{
		if (Text.Equals(Mesh, ESearchCase::IgnoreCase))
		{
			return EEndSkelCompatMethod::Mesh;
		}
	}
	for (const TCHAR* Family : {TEXT("family"), TEXT("group"), TEXT("share"), TEXT("shared"), TEXT("both"), TEXT("both_ways"), TEXT("bidirectional")})
	{
		if (Text.Equals(Family, ESearchCase::IgnoreCase))
		{
			return EEndSkelCompatMethod::Family;
		}
	}
	return EEndSkelCompatMethod::Animations;
}

TArray<FString> StringsOf(const TSharedPtr<FJsonValue>& Value)
{
	TArray<FString> Out;
	if (!Value.IsValid())
	{
		return Out;
	}
	if (Value->Type == EJson::String)
	{
		Out.Add(Value->AsString());
	}
	else if (Value->Type == EJson::Array)
	{
		for (const TSharedPtr<FJsonValue>& Item : Value->AsArray())
		{
			if (Item.IsValid() && Item->Type == EJson::String)
			{
				Out.Add(Item->AsString());
			}
		}
	}
	return Out;
}

bool BoolField(const TSharedPtr<FJsonObject>& Entry, const TCHAR* Key, bool& bOut)
{
	const TSharedPtr<FJsonValue> Value = Entry->TryGetField(Key);
	if (!Value.IsValid() || Value->Type != EJson::Boolean)
	{
		return false;
	}
	bOut = Value->AsBool();
	return true;
}

TArray<TSharedPtr<FJsonValue>> JsonStrings(const TArray<FString>& Items)
{
	TArray<TSharedPtr<FJsonValue>> Values;
	for (const FString& Item : Items)
	{
		Values.Add(MakeShared<FJsonValueString>(Item));
	}
	return Values;
}

FString StringField(const TSharedPtr<FJsonObject>& Entry, const TCHAR* Key)
{
	FString Text;
	return Entry.IsValid() && Entry->TryGetStringField(Key, Text) ? Text.TrimStartAndEnd() : FString();
}

// ------------------------------------------------------------------------------------------------
// Animation set rows (RebirthSkelCompat 3.1, 3.2 options): the row's JSON entry, both ways.
// ------------------------------------------------------------------------------------------------
// "PC0000_00_Cloud_Standard", "CharaSpec_PC0000_00_Cloud_Standard" or the pack's path -> the CharaSpec row name.
FString CharaSpecRowName(const FString& Character)
{
	const FString Pack = FromWide(SkelCompat::CharacterPackPath(Wide(Character)));
	FString Name = Pack.IsEmpty() ? FString() : ShortName(Pack);
	Name.RemoveFromStart(TEXT("CharaSpec_"), ESearchCase::IgnoreCase);
	return Name;
}

// Where Build Moves puts a row's built animations (a content folder, no trailing slash).
FString BuildFolderOf(const FEndAnimSetRow& Row)
{
	FString Folder = Row.BuildFolder.TrimStartAndEnd().Replace(TEXT("\\"), TEXT("/"));
	while (Folder.EndsWith(TEXT("/")))
	{
		Folder.LeftChopInline(1);
	}
	if (!Folder.IsEmpty())
	{
		return Folder;
	}
	const TArray<FString> Characters = CleanList(Row.Characters, false);
	const FString Character = Characters.Num() > 0 ? CharaSpecRowName(Characters[0]) : FString();
	return TEXT("/Game/RebirthSkelCompat/Built/") + (Character.IsEmpty() ? FString(TEXT("Character")) : Character);
}

// The package of a move's built animation: <Build Folder>/<Set>/<Name>.
FString BuiltPackageOf(const FEndAnimSetRow& Row, const FEndAnimSetMove& Move)
{
	FString Path = BuildFolderOf(Row) + TEXT("/");
	const FString Set = Move.Set.TrimStartAndEnd();
	if (!Set.IsEmpty())
	{
		Path += Set + TEXT("/");
	}
	return Path + Move.Name.TrimStartAndEnd();
}

FString BuiltObjectPathOf(const FEndAnimSetRow& Row, const FEndAnimSetMove& Move)
{
	return BuiltPackageOf(Row, Move) + TEXT(".") + Move.Name.TrimStartAndEnd();
}

bool SameHit(const FEndMoveHit& A, const FEndMoveHit& B)
{
	return FMath::IsNearlyEqual(A.Time, B.Time, 0.0005f) && FMath::IsNearlyEqual(A.Window, B.Window, 0.0005f) &&
		   A.DamageSourceID.TrimStartAndEnd().Equals(B.DamageSourceID.TrimStartAndEnd(), ESearchCase::IgnoreCase) &&
		   SamePath(A.Effect.TrimStartAndEnd(), B.Effect.TrimStartAndEnd()) && A.EffectSocket == B.EffectSocket && A.EffectOn == B.EffectOn &&
		   FMath::IsNearlyEqual(A.EffectTime, B.EffectTime, 0.0005f) && SamePath(A.SoundBank.TrimStartAndEnd(), B.SoundBank.TrimStartAndEnd()) &&
		   A.Sound == B.Sound && A.Weapon == B.Weapon;
}

// The same move as far as the game and Build Moves are concerned.
bool SameMove(const FEndAnimSetMove& A, const FEndAnimSetMove& B)
{
	if (!SamePath(A.Animation.TrimStartAndEnd(), B.Animation.TrimStartAndEnd()) || A.bBuild != B.bBuild || CleanList(A.ThenPlay, false) != CleanList(B.ThenPlay, false))
	{
		return false;
	}
	if (!A.bBuild)
	{
		return true;
	}
	if (A.bShot != B.bShot || !FMath::IsNearlyEqual(A.HitAt, B.HitAt, 0.0005f) || !SamePath(A.NotifiesFrom.TrimStartAndEnd(), B.NotifiesFrom.TrimStartAndEnd()) ||
		A.Retarget != B.Retarget || A.bKeepSourceEffects != B.bKeepSourceEffects || A.Hits.Num() != B.Hits.Num() ||
		!FMath::IsNearlyEqual(A.ClipStart, B.ClipStart, 0.0005f) || !FMath::IsNearlyEqual(A.ClipEnd, B.ClipEnd, 0.0005f) || !FMath::IsNearlyEqual(A.Speed, B.Speed, 0.0005f) ||
		!SamePath(A.Base.TrimStartAndEnd(), B.Base.TrimStartAndEnd()) || A.bBaseLoop != B.bBaseLoop || !SamePath(A.MotionFrom.TrimStartAndEnd(), B.MotionFrom.TrimStartAndEnd()) ||
		!A.LeanBone.TrimStartAndEnd().Equals(B.LeanBone.TrimStartAndEnd(), ESearchCase::IgnoreCase) || !FMath::IsNearlyEqual(A.Lean, B.Lean, 0.0005f) ||
		!A.BoneMap.TrimStartAndEnd().Equals(B.BoneMap.TrimStartAndEnd(), ESearchCase::IgnoreCase) || !FMath::IsNearlyEqual(A.SourceTurn, B.SourceTurn, 0.0005f) ||
		A.bKeepBaseRoot != B.bKeepBaseRoot || A.bSourceSoundsOnly != B.bSourceSoundsOnly)
	{
		return false;
	}
	for (int32 Index = 0; Index < A.Hits.Num(); ++Index)
	{
		if (!SameHit(A.Hits[Index], B.Hits[Index]))
		{
			return false;
		}
	}
	return true;
}

// The Directories To Never Cook entry (Project Settings > Packaging) that Folder is in, or empty when the project cooks it.
FString NeverCookDirectoryOf(const FString& Folder)
{
	const FString Path = Folder + TEXT("/");
	for (const FDirectoryPath& Directory : GetDefault<UProjectPackagingSettings>()->DirectoriesToNeverCook)
	{
		FString Root = Directory.Path.TrimStartAndEnd().Replace(TEXT("\\"), TEXT("/"));
		if (Root.IsEmpty())
		{
			continue;
		}
		if (!Root.StartsWith(TEXT("/")))
		{
			Root = TEXT("/Game/") + Root;
		}
		while (Root.EndsWith(TEXT("/")))
		{
			Root.LeftChopInline(1);
		}
		if (Path.StartsWith(Root + TEXT("/"), ESearchCase::IgnoreCase))
		{
			return Root;
		}
	}
	return FString();
}

// Seconds for the JSON, without float noise (0.08, not 0.07999999821).
double JsonSeconds(float Value) { return FMath::RoundToDouble(static_cast<double>(Value) * 1000.0) / 1000.0; }

// A built move's hits in the JSON's "build" (editor only; the mod skips it).
TArray<TSharedPtr<FJsonValue>> HitsToJson(const TArray<FEndMoveHit>& Hits)
{
	TArray<TSharedPtr<FJsonValue>> Out;
	for (const FEndMoveHit& Hit : Hits)
	{
		TSharedRef<FJsonObject> Object = MakeShared<FJsonObject>();
		Object->SetNumberField(TEXT("time"), JsonSeconds(Hit.Time));
		if (Hit.Window > 0.f)
		{
			Object->SetNumberField(TEXT("window"), JsonSeconds(Hit.Window));
		}
		if (!Hit.DamageSourceID.TrimStartAndEnd().IsEmpty())
		{
			Object->SetStringField(TEXT("damage"), Hit.DamageSourceID.TrimStartAndEnd());
		}
		if (!Hit.Effect.TrimStartAndEnd().IsEmpty())
		{
			Object->SetStringField(TEXT("effect"), Hit.Effect.TrimStartAndEnd());
			if (!Hit.EffectSocket.IsNone())
			{
				Object->SetStringField(TEXT("socket"), Hit.EffectSocket.ToString());
			}
			Object->SetStringField(TEXT("on"), Hit.EffectOn == EEndMoveEffectAttach::Character ? TEXT("character") : TEXT("weapon"));
			Object->SetNumberField(TEXT("effect_time"), JsonSeconds(Hit.EffectTime));
		}
		if (!Hit.SoundBank.TrimStartAndEnd().IsEmpty())
		{
			Object->SetStringField(TEXT("sound_bank"), Hit.SoundBank.TrimStartAndEnd());
			Object->SetStringField(TEXT("sound"), Hit.Sound.ToString());
		}
		if (Hit.Weapon != 1)
		{
			Object->SetNumberField(TEXT("weapon"), Hit.Weapon);
		}
		Out.Add(MakeShared<FJsonValueObject>(Object));
	}
	return Out;
}

TArray<FEndMoveHit> HitsFromJson(const TSharedPtr<FJsonValue>& Value)
{
	TArray<FEndMoveHit> Hits;
	if (!Value.IsValid() || Value->Type != EJson::Array)
	{
		return Hits;
	}
	for (const TSharedPtr<FJsonValue>& Item : Value->AsArray())
	{
		const TSharedPtr<FJsonObject> Object = Item.IsValid() && Item->Type == EJson::Object ? Item->AsObject() : nullptr;
		if (!Object.IsValid())
		{
			continue;
		}
		FEndMoveHit Hit;
		double Number = 0.0;
		if (Object->TryGetNumberField(TEXT("time"), Number)) { Hit.Time = FMath::Max(0.f, static_cast<float>(Number)); }
		if (Object->TryGetNumberField(TEXT("window"), Number)) { Hit.Window = FMath::Max(0.f, static_cast<float>(Number)); }
		if (Object->TryGetNumberField(TEXT("effect_time"), Number)) { Hit.EffectTime = FMath::Max(0.01f, static_cast<float>(Number)); }
		if (Object->TryGetNumberField(TEXT("weapon"), Number)) { Hit.Weapon = FMath::Clamp(static_cast<int32>(Number), 1, 8); }
		Object->TryGetStringField(TEXT("damage"), Hit.DamageSourceID);
		Object->TryGetStringField(TEXT("effect"), Hit.Effect);
		FString Text;
		if (Object->TryGetStringField(TEXT("socket"), Text)) { Hit.EffectSocket = FName(*Text); }
		if (Object->TryGetStringField(TEXT("on"), Text)) { Hit.EffectOn = Text.Equals(TEXT("character"), ESearchCase::IgnoreCase) ? EEndMoveEffectAttach::Character : EEndMoveEffectAttach::Weapon; }
		Object->TryGetStringField(TEXT("sound_bank"), Hit.SoundBank);
		if (Object->TryGetStringField(TEXT("sound"), Text)) { Hit.Sound = FName(*Text); }
		Hits.Add(Hit);
	}
	return Hits;
}

// "auto" in the mod's JSON: false, "basic", true (attacks, abilities, limits) or "all".
TSharedPtr<FJsonValue> AutoMatchJson(EEndAnimSetAutoMatch Mode)
{
	switch (Mode)
	{
	case EEndAnimSetAutoMatch::BasicAttacks: return MakeShared<FJsonValueString>(TEXT("basic"));
	case EEndAnimSetAutoMatch::Attacks: return MakeShared<FJsonValueBoolean>(true);
	case EEndAnimSetAutoMatch::WholeSet: return MakeShared<FJsonValueString>(TEXT("all"));
	default: return MakeShared<FJsonValueBoolean>(false);
	}
}

// "auto" / "match" of a source entry, as the mod reads it.
EEndAnimSetAutoMatch AutoMatchOf(const TSharedPtr<FJsonObject>& Object)
{
	EEndAnimSetAutoMatch Mode = EEndAnimSetAutoMatch::Off;
	for (const TCHAR* Key : {TEXT("auto"), TEXT("match")})
	{
		const TSharedPtr<FJsonValue> Value = Object.IsValid() ? Object->TryGetField(Key) : nullptr;
		if (!Value.IsValid() || (Value->Type != EJson::Boolean && Value->Type != EJson::String))
		{
			continue;
		}
		SkelCompat::Json Text;
		if (Value->Type == EJson::Boolean)
		{
			Text.type = SkelCompat::Json::Type::Bool;
			Text.boolean = Value->AsBool();
		}
		else
		{
			Text.type = SkelCompat::Json::Type::String;
			Text.string = TCHAR_TO_UTF8(*Value->AsString());
		}
		SkelCompat::AutoMatchMode Parsed = SkelCompat::AutoMatchMode::Off;
		if (SkelCompat::Detail::ParseAutoMatch(Text, Parsed))
		{
			Mode = Parsed == SkelCompat::AutoMatchMode::Basic ? EEndAnimSetAutoMatch::BasicAttacks
				 : Parsed == SkelCompat::AutoMatchMode::Attacks ? EEndAnimSetAutoMatch::Attacks
				 : Parsed == SkelCompat::AutoMatchMode::All ? EEndAnimSetAutoMatch::WholeSet
				 : EEndAnimSetAutoMatch::Off;
		}
		else
		{
			Mode = EEndAnimSetAutoMatch::Attacks; // the mod reads an unknown value as "attacks"
		}
	}
	return Mode;
}

// ------------------------------------------------------------------------------------------------
// 3.6 forms in the mod's JSON: "forms": {"button": ..., "title": ..., "parts": [...], "list": [{"name": "WINGED",
// "pack": "Battle02", "show": ["Wing"], "effects": [...], "sounds": [...], "fly": true}, ...]}
// ------------------------------------------------------------------------------------------------
TArray<TSharedPtr<FJsonValue>> FormEffectsToJson(const TArray<FEndFormEffect>& Effects)
{
	TArray<TSharedPtr<FJsonValue>> Out;
	for (const FEndFormEffect& Effect : Effects)
	{
		const FString Path = Effect.Effect.TrimStartAndEnd();
		if (Path.IsEmpty())
		{
			continue;
		}
		const FString Socket = Effect.Socket.TrimStartAndEnd();
		if (Socket.IsEmpty() && FMath::IsNearlyEqual(Effect.Scale, 1.f) && Effect.Seconds <= 0.f)
		{
			Out.Add(MakeShared<FJsonValueString>(NormalizedObjectPath(Path)));
			continue;
		}
		TSharedRef<FJsonObject> Object = MakeShared<FJsonObject>();
		Object->SetStringField(TEXT("effect"), NormalizedObjectPath(Path));
		if (!Socket.IsEmpty())
		{
			Object->SetStringField(TEXT("socket"), Socket);
		}
		if (!FMath::IsNearlyEqual(Effect.Scale, 1.f))
		{
			Object->SetNumberField(TEXT("scale"), JsonSeconds(Effect.Scale));
		}
		if (Effect.Seconds > 0.f)
		{
			Object->SetNumberField(TEXT("seconds"), JsonSeconds(Effect.Seconds));
		}
		Out.Add(MakeShared<FJsonValueObject>(Object));
	}
	return Out;
}

TArray<FEndFormEffect> FormEffectsFromJson(const TSharedPtr<FJsonValue>& Value)
{
	TArray<FEndFormEffect> Out;
	TArray<TSharedPtr<FJsonValue>> Items;
	if (Value.IsValid() && Value->Type == EJson::Array) { Items = Value->AsArray(); }
	else if (Value.IsValid()) { Items.Add(Value); }
	for (const TSharedPtr<FJsonValue>& Item : Items)
	{
		FEndFormEffect Effect;
		if (Item.IsValid() && Item->Type == EJson::String)
		{
			Effect.Effect = Item->AsString().TrimStartAndEnd();
		}
		else if (Item.IsValid() && Item->Type == EJson::Object)
		{
			const TSharedPtr<FJsonObject> Object = Item->AsObject();
			for (const TCHAR* Key : {TEXT("effect"), TEXT("path"), TEXT("system"), TEXT("particle")})
			{
				if (Effect.Effect.IsEmpty()) { Effect.Effect = StringField(Object, Key); }
			}
			Effect.Socket = StringField(Object, TEXT("socket"));
			if (Effect.Socket.IsEmpty()) { Effect.Socket = StringField(Object, TEXT("bone")); }
			double Number = 0.0;
			if (Object->TryGetNumberField(TEXT("scale"), Number) && Number > 0.0) { Effect.Scale = static_cast<float>(Number); }
			if (Object->TryGetNumberField(TEXT("seconds"), Number) && Number >= 0.0) { Effect.Seconds = static_cast<float>(Number); }
		}
		if (!Effect.Effect.IsEmpty())
		{
			Out.Add(Effect);
		}
	}
	return Out;
}

// (1.14) A JSON value the data object holds as text (a MultiLine field): a JSON value as typed, else the text as a string.
TSharedPtr<FJsonValue> JsonValueOfText(const FString& Text)
{
	const FString Trimmed = Text.TrimStartAndEnd();
	if (Trimmed.IsEmpty())
	{
		return nullptr;
	}
	TSharedPtr<FJsonObject> Holder;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(TEXT("{\"v\":") + Trimmed + TEXT("}"));
	if (FJsonSerializer::Deserialize(Reader, Holder) && Holder.IsValid())
	{
		const TSharedPtr<FJsonValue> Value = Holder->TryGetField(TEXT("v"));
		if (Value.IsValid())
		{
			return Value;
		}
	}
	return MakeShared<FJsonValueString>(Trimmed);
}

// (1.14) A JSON value as the text the data object holds (condensed JSON; a string as it is). Empty: none.
FString TextOfJsonValue(const TSharedPtr<FJsonValue>& Value)
{
	if (!Value.IsValid() || Value->Type == EJson::Null || Value->Type == EJson::None)
	{
		return FString();
	}
	if (Value->Type == EJson::String)
	{
		return Value->AsString().TrimStartAndEnd();
	}
	TSharedRef<FJsonObject> Holder = MakeShared<FJsonObject>();
	Holder->SetField(TEXT("v"), Value);
	FString Out;
	const TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Out);
	FJsonSerializer::Serialize(Holder, Writer);
	const FString Prefix = TEXT("{\"v\":");
	if (Out.StartsWith(Prefix) && Out.EndsWith(TEXT("}")))
	{
		return Out.Mid(Prefix.Len(), Out.Len() - Prefix.Len() - 1);
	}
	return Out;
}

// (1.14) "voice" as the mod reads it: a bank path, "own", or {"bank": path, "replaces": [paths]}. Null: none.
TSharedPtr<FJsonValue> VoiceToJson(const FString& Voice, const TArray<FString>& Replaces)
{
	const FString Bank = Voice.TrimStartAndEnd();
	if (Bank.IsEmpty())
	{
		return nullptr;
	}
	const bool bOwn = Bank.Equals(TEXT("own"), ESearchCase::IgnoreCase) || Bank.Equals(TEXT("none"), ESearchCase::IgnoreCase);
	const FString Path = bOwn ? FString(TEXT("own")) : NormalizedObjectPath(Bank);
	TArray<FString> From;
	for (const FString& One : CleanList(Replaces, false))
	{
		From.AddUnique(NormalizedObjectPath(One));
	}
	if (bOwn || From.Num() == 0)
	{
		return MakeShared<FJsonValueString>(Path);
	}
	TSharedRef<FJsonObject> Object = MakeShared<FJsonObject>();
	Object->SetStringField(TEXT("bank"), Path);
	Object->SetArrayField(TEXT("replaces"), JsonStrings(From));
	return MakeShared<FJsonValueObject>(Object);
}

// (1.14) "voice" back into the data object's Voice and Voice Replaces.
void VoiceFromJson(const TSharedPtr<FJsonValue>& Value, FString& OutVoice, TArray<FString>& OutReplaces)
{
	OutVoice.Reset();
	OutReplaces.Reset();
	if (!Value.IsValid())
	{
		return;
	}
	if (Value->Type == EJson::String)
	{
		OutVoice = Value->AsString().TrimStartAndEnd();
		return;
	}
	if (Value->Type != EJson::Object)
	{
		return;
	}
	const TSharedPtr<FJsonObject> Object = Value->AsObject();
	OutVoice = StringField(Object, TEXT("bank"));
	if (OutVoice.IsEmpty())
	{
		OutVoice = TEXT("own");
	}
	OutReplaces = CleanList(StringsOf(Object->TryGetField(TEXT("replaces"))), false);
}

// (1.14) [x, y, z] of a vector or a rotator (pitch, yaw, roll), and back.
TArray<TSharedPtr<FJsonValue>> JsonThree(float X, float Y, float Z)
{
	TArray<TSharedPtr<FJsonValue>> Out;
	Out.Add(MakeShared<FJsonValueNumber>(JsonSeconds(X)));
	Out.Add(MakeShared<FJsonValueNumber>(JsonSeconds(Y)));
	Out.Add(MakeShared<FJsonValueNumber>(JsonSeconds(Z)));
	return Out;
}

bool ThreeFromJson(const TSharedPtr<FJsonObject>& Object, const TCHAR* Key, float& X, float& Y, float& Z)
{
	const TArray<TSharedPtr<FJsonValue>>* Items = nullptr;
	if (!Object.IsValid() || !Object->TryGetArrayField(Key, Items) || !Items || Items->Num() != 3)
	{
		return false;
	}
	double Values[3] = {0.0, 0.0, 0.0};
	for (int32 Index = 0; Index < 3; ++Index)
	{
		if (!(*Items)[Index].IsValid() || !(*Items)[Index]->TryGetNumber(Values[Index]))
		{
			return false;
		}
	}
	X = static_cast<float>(Values[0]);
	Y = static_cast<float>(Values[1]);
	Z = static_cast<float>(Values[2]);
	return true;
}

// (1.14) A socket stand-in has a placement of its own on its bone (Location, Rotation, Scale, Hidden).
bool HasPlacement(const FEndSocketStandIn& Socket)
{
	return Socket.bHidden || !Socket.Location.IsNearlyZero() || !Socket.Rotation.IsNearlyZero() || !Socket.Scale.Equals(FVector(1.f, 1.f, 1.f));
}

// (1.14) A socket stand-in as the mod reads it: {"socket", "use"} and its placement ("location", "rotation", "scale", "hidden").
TSharedRef<FJsonObject> SocketStandInToJson(const FEndSocketStandIn& Socket)
{
	TSharedRef<FJsonObject> Object = MakeShared<FJsonObject>();
	Object->SetStringField(TEXT("socket"), Socket.Socket.TrimStartAndEnd());
	Object->SetStringField(TEXT("use"), Socket.Use.TrimStartAndEnd());
	if (!Socket.Location.IsNearlyZero())
	{
		Object->SetArrayField(TEXT("location"), JsonThree(Socket.Location.X, Socket.Location.Y, Socket.Location.Z));
	}
	if (!Socket.Rotation.IsNearlyZero())
	{
		Object->SetArrayField(TEXT("rotation"), JsonThree(Socket.Rotation.Pitch, Socket.Rotation.Yaw, Socket.Rotation.Roll));
	}
	if (Socket.bHidden)
	{
		Object->SetBoolField(TEXT("hidden"), true);
	}
	else if (!Socket.Scale.Equals(FVector(1.f, 1.f, 1.f)))
	{
		if (FMath::IsNearlyEqual(Socket.Scale.X, Socket.Scale.Y) && FMath::IsNearlyEqual(Socket.Scale.X, Socket.Scale.Z))
		{
			Object->SetNumberField(TEXT("scale"), JsonSeconds(Socket.Scale.X));
		}
		else
		{
			Object->SetArrayField(TEXT("scale"), JsonThree(Socket.Scale.X, Socket.Scale.Y, Socket.Scale.Z));
		}
	}
	return Object;
}

// (1.14) A socket stand-in's placement from the mod's entry.
void SocketPlacementFromJson(const TSharedPtr<FJsonObject>& Object, FEndSocketStandIn& Socket)
{
	if (!Object.IsValid())
	{
		return;
	}
	float X = 0.f, Y = 0.f, Z = 0.f;
	if (ThreeFromJson(Object, TEXT("location"), X, Y, Z))
	{
		Socket.Location = FVector(X, Y, Z);
	}
	if (ThreeFromJson(Object, TEXT("rotation"), X, Y, Z))
	{
		Socket.Rotation = FRotator(X, Y, Z);
	}
	BoolField(Object, TEXT("hidden"), Socket.bHidden);
	double Number = 0.0;
	if (Object->TryGetNumberField(TEXT("scale"), Number))
	{
		Socket.Scale = FVector(static_cast<float>(Number));
	}
	else if (ThreeFromJson(Object, TEXT("scale"), X, Y, Z))
	{
		Socket.Scale = FVector(X, Y, Z);
	}
}

TSharedRef<FJsonObject> FormsToJson(const FEndCharacterForms& Forms)
{
	TSharedRef<FJsonObject> Object = MakeShared<FJsonObject>();
	Object->SetStringField(TEXT("button"), Forms.Button.TrimStartAndEnd().IsEmpty() ? FString(TEXT("Gamepad_FaceButton_Top")) : Forms.Button.TrimStartAndEnd());
	if (!Forms.Key.TrimStartAndEnd().IsEmpty())
	{
		Object->SetStringField(TEXT("key"), Forms.Key.TrimStartAndEnd());
	}
	Object->SetNumberField(TEXT("hold_seconds"), JsonSeconds(Forms.HoldSeconds));
	if (!Forms.Title.TrimStartAndEnd().IsEmpty())
	{
		Object->SetStringField(TEXT("title"), Forms.Title.TrimStartAndEnd());
	}
	TArray<FString> Parts = CleanList(Forms.Parts, false);
	for (const FEndCharacterForm& Form : Forms.List)
	{
		for (const FString& Part : CleanList(Form.ShowParts, false))
		{
			Parts.AddUnique(Part); // a part a form shows is one the forms show or hide
		}
	}
	if (Parts.Num() > 0)
	{
		Object->SetArrayField(TEXT("parts"), JsonStrings(Parts));
	}
	if (Forms.FadeSeconds > 0.f)
	{
		Object->SetNumberField(TEXT("fade_seconds"), JsonSeconds(Forms.FadeSeconds));
		Object->SetStringField(TEXT("fade_parameter"), Forms.FadeParameter.TrimStartAndEnd().IsEmpty() ? FString(TEXT("NativePrimitiveCoverage")) : Forms.FadeParameter.TrimStartAndEnd());
	}
	if (Forms.ShowEffects.Num() > 0)
	{
		Object->SetArrayField(TEXT("show_effects"), FormEffectsToJson(Forms.ShowEffects));
	}
	if (Forms.HideEffects.Num() > 0)
	{
		Object->SetArrayField(TEXT("hide_effects"), FormEffectsToJson(Forms.HideEffects));
	}
	if (!FMath::IsNearlyEqual(Forms.EffectSeconds, 2.5f))
	{
		Object->SetNumberField(TEXT("effect_seconds"), JsonSeconds(Forms.EffectSeconds));
	}
	if (!Forms.bHideOnOthers)
	{
		Object->SetBoolField(TEXT("hide_on_others"), false);
	}
	if (!Forms.bShowTimer)
	{
		Object->SetBoolField(TEXT("timer_at"), false);
	}
	else if (!FMath::IsNearlyEqual(Forms.TimerAt.X, 0.97f) || !FMath::IsNearlyEqual(Forms.TimerAt.Y, 0.55f))
	{
		TArray<TSharedPtr<FJsonValue>> At;
		At.Add(MakeShared<FJsonValueNumber>(JsonSeconds(FMath::Clamp(Forms.TimerAt.X, 0.f, 1.f))));
		At.Add(MakeShared<FJsonValueNumber>(JsonSeconds(FMath::Clamp(Forms.TimerAt.Y, 0.f, 1.f))));
		Object->SetArrayField(TEXT("timer_at"), At);
	}
	TArray<TSharedPtr<FJsonValue>> List;
	for (const FEndCharacterForm& Form : Forms.List)
	{
		TSharedRef<FJsonObject> Entry = MakeShared<FJsonObject>();
		Entry->SetStringField(TEXT("name"), Form.Name.TrimStartAndEnd());
		if (!Form.Pack.TrimStartAndEnd().IsEmpty())
		{
			Entry->SetStringField(TEXT("pack"), Form.Pack.TrimStartAndEnd());
		}
		const TArray<FString> Show = CleanList(Form.ShowParts, false);
		if (Show.Num() > 0)
		{
			Entry->SetArrayField(TEXT("show"), JsonStrings(Show));
		}
		if (!Form.Model.TrimStartAndEnd().IsEmpty())
		{
			Entry->SetStringField(TEXT("model"), NormalizedObjectPath(Form.Model));
		}
		if (!Form.AnimBlueprint.TrimStartAndEnd().IsEmpty())
		{
			Entry->SetStringField(TEXT("anim_class"), NormalizedObjectPath(Form.AnimBlueprint));
		}
		if (Form.Scale > 0.f)
		{
			Entry->SetNumberField(TEXT("scale"), JsonSeconds(Form.Scale));
		}
		if (Form.ModelTurn != 0.f)
		{
			Entry->SetNumberField(TEXT("model_turn"), JsonSeconds(Form.ModelTurn));
		}
		if (Form.ModelLift != 0.f)
		{
			Entry->SetNumberField(TEXT("model_lift"), JsonSeconds(Form.ModelLift));
		}
		TArray<TSharedPtr<FJsonValue>> Meshes;
		for (const FEndFormMesh& Mesh : Form.Meshes)
		{
			if (Mesh.Mesh.TrimStartAndEnd().IsEmpty())
			{
				continue;
			}
			if (Mesh.Socket.TrimStartAndEnd().IsEmpty() && Mesh.bFollowPose)
			{
				Meshes.Add(MakeShared<FJsonValueString>(NormalizedObjectPath(Mesh.Mesh)));
				continue;
			}
			TSharedRef<FJsonObject> Part = MakeShared<FJsonObject>();
			Part->SetStringField(TEXT("mesh"), NormalizedObjectPath(Mesh.Mesh));
			if (!Mesh.Socket.TrimStartAndEnd().IsEmpty())
			{
				Part->SetStringField(TEXT("socket"), Mesh.Socket.TrimStartAndEnd());
			}
			if (!Mesh.bFollowPose)
			{
				Part->SetBoolField(TEXT("follow_pose"), false);
			}
			Meshes.Add(MakeShared<FJsonValueObject>(Part));
		}
		if (Meshes.Num() > 0)
		{
			Entry->SetArrayField(TEXT("meshes"), Meshes);
		}
		if (Form.bHideWeapon)
		{
			Entry->SetBoolField(TEXT("hide_weapon"), true);
		}
		if (Form.Effects.Num() > 0)
		{
			Entry->SetArrayField(TEXT("effects"), FormEffectsToJson(Form.Effects));
		}
		if (Form.KeepEffects.Num() > 0)
		{
			Entry->SetArrayField(TEXT("keep_effects"), FormEffectsToJson(Form.KeepEffects));
		}
		TArray<TSharedPtr<FJsonValue>> Sounds;
		for (const FEndFormSound& Sound : Form.Sounds)
		{
			if (Sound.Bank.TrimStartAndEnd().IsEmpty() || Sound.Cue.TrimStartAndEnd().IsEmpty())
			{
				continue;
			}
			TSharedRef<FJsonObject> Cue = MakeShared<FJsonObject>();
			Cue->SetStringField(TEXT("bank"), NormalizedObjectPath(Sound.Bank));
			Cue->SetStringField(TEXT("cue"), Sound.Cue.TrimStartAndEnd());
			Sounds.Add(MakeShared<FJsonValueObject>(Cue));
		}
		if (Sounds.Num() > 0)
		{
			Entry->SetArrayField(TEXT("sounds"), Sounds);
		}
		if (Form.bFly)
		{
			const bool bPlain = FMath::IsNearlyEqual(Form.FlyHeight, 250.f) && FMath::IsNearlyEqual(Form.FlySpeed, 600.f) && FMath::IsNearlyEqual(Form.FlyMax, 3000.f) &&
								Form.FlyUp.TrimStartAndEnd().Equals(TEXT("Gamepad_DPad_Up"), ESearchCase::IgnoreCase) &&
								Form.FlyDown.TrimStartAndEnd().Equals(TEXT("Gamepad_DPad_Down"), ESearchCase::IgnoreCase);
			if (bPlain)
			{
				Entry->SetBoolField(TEXT("fly"), true);
			}
			else
			{
				TSharedRef<FJsonObject> Fly = MakeShared<FJsonObject>();
				Fly->SetNumberField(TEXT("height"), JsonSeconds(Form.FlyHeight));
				Fly->SetNumberField(TEXT("speed"), JsonSeconds(Form.FlySpeed));
				Fly->SetNumberField(TEXT("max"), JsonSeconds(Form.FlyMax));
				Fly->SetStringField(TEXT("up"), Form.FlyUp.TrimStartAndEnd().IsEmpty() ? FString(TEXT("Gamepad_DPad_Up")) : Form.FlyUp.TrimStartAndEnd());
				Fly->SetStringField(TEXT("down"), Form.FlyDown.TrimStartAndEnd().IsEmpty() ? FString(TEXT("Gamepad_DPad_Down")) : Form.FlyDown.TrimStartAndEnd());
				Entry->SetObjectField(TEXT("fly"), Fly);
			}
		}
		if (!Form.After.TrimStartAndEnd().IsEmpty())
		{
			Entry->SetStringField(TEXT("after"), Form.After.TrimStartAndEnd());
		}
		TArray<TSharedPtr<FJsonValue>> AbilityEffects;
		for (const FEndFormAbilityEffects& One : Form.AbilityEffects)
		{
			const TArray<FString> Abilities = CleanList(One.Abilities, false);
			const TArray<TSharedPtr<FJsonValue>> Effects = FormEffectsToJson(One.Effects);
			if (Abilities.Num() == 0 || Effects.Num() == 0)
			{
				continue;
			}
			TSharedRef<FJsonObject> Item = MakeShared<FJsonObject>();
			if (Abilities.Num() == 1)
			{
				Item->SetStringField(TEXT("ability"), Abilities[0]);
			}
			else
			{
				Item->SetArrayField(TEXT("abilities"), JsonStrings(Abilities));
			}
			Item->SetArrayField(TEXT("effects"), Effects);
			AbilityEffects.Add(MakeShared<FJsonValueObject>(Item));
		}
		if (AbilityEffects.Num() > 0)
		{
			Entry->SetArrayField(TEXT("ability_effects"), AbilityEffects);
		}
		if (Form.bSuperArmor)
		{
			Entry->SetBoolField(TEXT("super_armor"), true);
		}
		if (Form.Seconds > 0.f)
		{
			Entry->SetNumberField(TEXT("seconds"), JsonSeconds(Form.Seconds));
		}
		if (Form.Cooldown > 0.f)
		{
			Entry->SetNumberField(TEXT("cooldown"), JsonSeconds(Form.Cooldown));
		}
		if (!Form.RevertTo.TrimStartAndEnd().IsEmpty())
		{
			Entry->SetStringField(TEXT("revert_to"), Form.RevertTo.TrimStartAndEnd());
		}
		// (1.14) the model the game's way, the form's weapon, its sets, its voice, its cameras, its entrance, its shooter
		if (Form.bAsLook)
		{
			Entry->SetBoolField(TEXT("as_look"), true);
		}
		if (!Form.Weapon.TrimStartAndEnd().IsEmpty())
		{
			Entry->SetStringField(TEXT("weapon"), NormalizedObjectPath(Form.Weapon));
		}
		if (Form.Sets.Num() > 0)
		{
			TSharedRef<FJsonObject> Sets = MakeShared<FJsonObject>();
			for (const TPair<FString, FString>& Set : Form.Sets)
			{
				const FString From = Set.Key.TrimStartAndEnd(), To = Set.Value.TrimStartAndEnd();
				if (!From.IsEmpty() && !To.IsEmpty() && !Sets->HasField(From))
				{
					Sets->SetStringField(From, To);
				}
			}
			if (Sets->Values.Num() > 0)
			{
				Entry->SetObjectField(TEXT("sets"), Sets);
			}
		}
		if (const TSharedPtr<FJsonValue> Voice = VoiceToJson(Form.Voice, Form.VoiceReplaces))
		{
			Entry->SetField(TEXT("voice"), Voice);
		}
		if (const TSharedPtr<FJsonValue> Camera = JsonValueOfText(Form.CameraJson))
		{
			Entry->SetField(TEXT("camera"), Camera);
		}
		if (const TSharedPtr<FJsonValue> Cameras = JsonValueOfText(Form.AbilityCamerasJson))
		{
			Entry->SetField(TEXT("ability_cameras"), Cameras);
		}
		if (const TSharedPtr<FJsonValue> Entrance = JsonValueOfText(Form.EntranceJson))
		{
			Entry->SetField(TEXT("entrance"), Entrance);
		}
		if (const TSharedPtr<FJsonValue> Shooter = JsonValueOfText(Form.ShooterJson))
		{
			Entry->SetField(TEXT("shooter"), Shooter);
		}
		List.Add(MakeShared<FJsonValueObject>(Entry));
	}
	Object->SetArrayField(TEXT("list"), List);
	return Object;
}

// "forms" as the mod reads it: an object with the menu's settings and the forms as "list", or just the list.
FEndCharacterForms FormsFromJson(const TSharedPtr<FJsonValue>& Value)
{
	FEndCharacterForms Forms;
	if (!Value.IsValid())
	{
		return Forms;
	}
	TSharedPtr<FJsonValue> List = Value;
	if (Value->Type == EJson::Object)
	{
		const TSharedPtr<FJsonObject> Object = Value->AsObject();
		List = Object->TryGetField(TEXT("list"));
		if (!List.IsValid()) { List = Object->TryGetField(TEXT("forms")); }
		FString Text;
		if (Object->TryGetStringField(TEXT("button"), Text) && !Text.TrimStartAndEnd().IsEmpty()) { Forms.Button = Text.TrimStartAndEnd(); }
		if (Object->TryGetStringField(TEXT("key"), Text)) { Forms.Key = Text.TrimStartAndEnd(); }
		if (Object->TryGetStringField(TEXT("title"), Text) && !Text.TrimStartAndEnd().IsEmpty()) { Forms.Title = Text.TrimStartAndEnd(); }
		if (Object->TryGetStringField(TEXT("fade_parameter"), Text) && !Text.TrimStartAndEnd().IsEmpty()) { Forms.FadeParameter = Text.TrimStartAndEnd(); }
		double Number = 0.0;
		if (Object->TryGetNumberField(TEXT("hold_seconds"), Number) && Number >= 0.0) { Forms.HoldSeconds = FMath::Max(0.1f, static_cast<float>(Number)); }
		if (Object->TryGetNumberField(TEXT("fade_seconds"), Number) && Number >= 0.0) { Forms.FadeSeconds = static_cast<float>(Number); }
		if (Object->TryGetNumberField(TEXT("effect_seconds"), Number) && Number >= 0.0) { Forms.EffectSeconds = static_cast<float>(Number); }
		Forms.Parts = CleanList(StringsOf(Object->TryGetField(TEXT("parts"))), false);
		Forms.ShowEffects = FormEffectsFromJson(Object->TryGetField(TEXT("show_effects")));
		Forms.HideEffects = FormEffectsFromJson(Object->TryGetField(TEXT("hide_effects")));
		BoolField(Object, TEXT("hide_on_others"), Forms.bHideOnOthers);
		const TSharedPtr<FJsonValue> TimerAt = Object->TryGetField(TEXT("timer_at"));
		if (TimerAt.IsValid() && TimerAt->Type == EJson::Boolean)
		{
			Forms.bShowTimer = TimerAt->AsBool();
		}
		else if (TimerAt.IsValid() && TimerAt->Type == EJson::Array && TimerAt->AsArray().Num() == 2)
		{
			Forms.TimerAt = FVector2D(static_cast<float>(TimerAt->AsArray()[0]->AsNumber()), static_cast<float>(TimerAt->AsArray()[1]->AsNumber()));
		}
	}
	if (!List.IsValid() || List->Type != EJson::Array)
	{
		return Forms;
	}
	for (const TSharedPtr<FJsonValue>& Item : List->AsArray())
	{
		FEndCharacterForm Form;
		if (Item.IsValid() && Item->Type == EJson::String)
		{
			Form.Pack = Item->AsString().TrimStartAndEnd();
			Form.Name = Form.Pack;
			Forms.List.Add(Form);
			continue;
		}
		if (!Item.IsValid() || Item->Type != EJson::Object)
		{
			continue;
		}
		const TSharedPtr<FJsonObject> Object = Item->AsObject();
		Form.Name = StringField(Object, TEXT("name"));
		Form.Pack = StringField(Object, TEXT("pack"));
		Form.ShowParts = CleanList(StringsOf(Object->TryGetField(TEXT("show"))), false);
		Form.Model = StringField(Object, TEXT("model"));
		Form.AnimBlueprint = StringField(Object, TEXT("anim_class"));
		double Number = 0.0;
		if (Object->TryGetNumberField(TEXT("scale"), Number) && Number > 0.0) { Form.Scale = static_cast<float>(Number); }
		if (Object->TryGetNumberField(TEXT("model_turn"), Number)) { Form.ModelTurn = FMath::Clamp(static_cast<float>(Number), -180.f, 180.f); }
		if (Object->TryGetNumberField(TEXT("model_lift"), Number)) { Form.ModelLift = static_cast<float>(Number); }
		const TSharedPtr<FJsonValue> Meshes = Object->TryGetField(TEXT("meshes"));
		TArray<TSharedPtr<FJsonValue>> Parts;
		if (Meshes.IsValid() && Meshes->Type == EJson::Array) { Parts = Meshes->AsArray(); }
		else if (Meshes.IsValid()) { Parts.Add(Meshes); }
		for (const TSharedPtr<FJsonValue>& Part : Parts)
		{
			FEndFormMesh Mesh;
			if (Part.IsValid() && Part->Type == EJson::String)
			{
				Mesh.Mesh = Part->AsString().TrimStartAndEnd();
			}
			else if (Part.IsValid() && Part->Type == EJson::Object)
			{
				Mesh.Mesh = StringField(Part->AsObject(), TEXT("mesh"));
				Mesh.Socket = StringField(Part->AsObject(), TEXT("socket"));
				BoolField(Part->AsObject(), TEXT("follow_pose"), Mesh.bFollowPose);
			}
			if (!Mesh.Mesh.IsEmpty())
			{
				Form.Meshes.Add(Mesh);
			}
		}
		BoolField(Object, TEXT("hide_weapon"), Form.bHideWeapon);
		Form.Effects = FormEffectsFromJson(Object->TryGetField(TEXT("effects")));
		Form.KeepEffects = FormEffectsFromJson(Object->TryGetField(TEXT("keep_effects")));
		const TSharedPtr<FJsonValue> Sounds = Object->TryGetField(TEXT("sounds"));
		if (Sounds.IsValid() && Sounds->Type == EJson::Array)
		{
			for (const TSharedPtr<FJsonValue>& Cue : Sounds->AsArray())
			{
				const TSharedPtr<FJsonObject> One = Cue.IsValid() && Cue->Type == EJson::Object ? Cue->AsObject() : nullptr;
				FEndFormSound Sound;
				Sound.Bank = StringField(One, TEXT("bank"));
				if (Sound.Bank.IsEmpty()) { Sound.Bank = StringField(One, TEXT("voice")); }
				for (const TCHAR* Key : {TEXT("cue"), TEXT("name"), TEXT("sound")})
				{
					if (Sound.Cue.IsEmpty()) { Sound.Cue = StringField(One, Key); }
				}
				if (!Sound.Bank.IsEmpty() && !Sound.Cue.IsEmpty())
				{
					Form.Sounds.Add(Sound);
				}
			}
		}
		const TSharedPtr<FJsonValue> Fly = Object->TryGetField(TEXT("fly"));
		if (Fly.IsValid() && Fly->Type == EJson::Boolean)
		{
			Form.bFly = Fly->AsBool();
		}
		else if (Fly.IsValid() && Fly->Type == EJson::Object)
		{
			const TSharedPtr<FJsonObject> Settings = Fly->AsObject();
			Form.bFly = true;
			BoolField(Settings, TEXT("enabled"), Form.bFly);
			if (Settings->TryGetNumberField(TEXT("height"), Number)) { Form.FlyHeight = static_cast<float>(Number); }
			if (Settings->TryGetNumberField(TEXT("speed"), Number)) { Form.FlySpeed = static_cast<float>(Number); }
			if (Settings->TryGetNumberField(TEXT("max"), Number)) { Form.FlyMax = static_cast<float>(Number); }
			const FString Up = StringField(Settings, TEXT("up")), Down = StringField(Settings, TEXT("down"));
			if (!Up.IsEmpty()) { Form.FlyUp = Up; }
			if (!Down.IsEmpty()) { Form.FlyDown = Down; }
		}
		Form.After = StringField(Object, TEXT("after"));
		// "ability_effects": [{"ability" or "abilities", "effects"}] or {"<ability>": effects}
		const TSharedPtr<FJsonValue> AbilityEffects = Object->TryGetField(TEXT("ability_effects"));
		if (AbilityEffects.IsValid() && AbilityEffects->Type == EJson::Array)
		{
			for (const TSharedPtr<FJsonValue>& Item2 : AbilityEffects->AsArray())
			{
				const TSharedPtr<FJsonObject> One = Item2.IsValid() && Item2->Type == EJson::Object ? Item2->AsObject() : nullptr;
				if (!One.IsValid())
				{
					continue;
				}
				FEndFormAbilityEffects Entry;
				Entry.Abilities = StringsOf(One->TryGetField(TEXT("ability")));
				Entry.Abilities.Append(StringsOf(One->TryGetField(TEXT("abilities"))));
				Entry.Abilities = CleanList(Entry.Abilities, false);
				Entry.Effects = FormEffectsFromJson(One->TryGetField(TEXT("effects")));
				if (Entry.Abilities.Num() > 0 || Entry.Effects.Num() > 0)
				{
					Form.AbilityEffects.Add(Entry);
				}
			}
		}
		else if (AbilityEffects.IsValid() && AbilityEffects->Type == EJson::Object)
		{
			for (const auto& Pair : AbilityEffects->AsObject()->Values)
			{
				FEndFormAbilityEffects Entry;
				Entry.Abilities.Add(Pair.Key.TrimStartAndEnd());
				Entry.Effects = FormEffectsFromJson(Pair.Value);
				Form.AbilityEffects.Add(Entry);
			}
		}
		BoolField(Object, TEXT("super_armor"), Form.bSuperArmor);
		if ((Object->TryGetNumberField(TEXT("seconds"), Number) || Object->TryGetNumberField(TEXT("time_limit"), Number)) && Number >= 0.0)
		{
			Form.Seconds = static_cast<float>(Number);
		}
		if ((Object->TryGetNumberField(TEXT("cooldown"), Number) || Object->TryGetNumberField(TEXT("cooldown_seconds"), Number)) && Number >= 0.0)
		{
			Form.Cooldown = static_cast<float>(Number);
		}
		Form.RevertTo = StringField(Object, TEXT("revert_to"));
		// (1.14) the model the game's way, the form's weapon, its sets, its voice, its cameras, its entrance, its shooter
		BoolField(Object, TEXT("as_look"), Form.bAsLook);
		Form.Weapon = StringField(Object, TEXT("weapon"));
		const TSharedPtr<FJsonObject>* Sets = nullptr;
		if (Object->TryGetObjectField(TEXT("sets"), Sets) && Sets && Sets->IsValid())
		{
			for (const auto& Set : (*Sets)->Values)
			{
				FString To;
				const FString From = Set.Key.TrimStartAndEnd();
				if (!From.IsEmpty() && Set.Value.IsValid() && Set.Value->TryGetString(To) && !To.TrimStartAndEnd().IsEmpty())
				{
					Form.Sets.Add(From, To.TrimStartAndEnd());
				}
			}
		}
		VoiceFromJson(Object->TryGetField(TEXT("voice")), Form.Voice, Form.VoiceReplaces);
		Form.CameraJson = TextOfJsonValue(Object->TryGetField(TEXT("camera")));
		Form.AbilityCamerasJson = TextOfJsonValue(Object->TryGetField(TEXT("ability_cameras")));
		Form.EntranceJson = TextOfJsonValue(Object->TryGetField(TEXT("entrance")));
		Form.ShooterJson = TextOfJsonValue(Object->TryGetField(TEXT("shooter")));
		Forms.List.Add(Form);
	}
	return Forms;
}

// The form whose pack is `Set` (none for the character's own pack), or null.
const FEndCharacterForm* FormOfPack(const FEndAnimSetRow& Row, const FString& Set)
{
	const FString Name = Set.TrimStartAndEnd();
	if (Name.IsEmpty() || Name.Equals(TEXT("Battle00"), ESearchCase::IgnoreCase))
	{
		return nullptr;
	}
	return Row.Forms.List.FindByPredicate([&](const FEndCharacterForm& Form) { return Form.Pack.TrimStartAndEnd().Equals(Name, ESearchCase::IgnoreCase); });
}

// (1.12) The skeleton of a move's Base (an animation of the skeleton the move is built on), or none.
USkeleton* BaseSkeletonOf(const FEndAnimSetMove& Move)
{
	const FString Path = Move.Base.TrimStartAndEnd();
	const UAnimSequence* Base = Path.IsEmpty() ? nullptr : Cast<UAnimSequence>(FSoftObjectPath(NormalizedObjectPath(Path)).TryLoad());
	return Base ? Base->GetSkeleton() : nullptr;
}

// 3.6: the skeleton a move of a form's pack is built on when that form wears another model: the model's (null: the row's).
USkeleton* FormModelSkeleton(const FEndAnimSetRow& Row, const FString& Set, FString* OutModel = nullptr)
{
	const FEndCharacterForm* Form = FormOfPack(Row, Set);
	if (!Form || Form->Model.TrimStartAndEnd().IsEmpty())
	{
		return nullptr;
	}
	if (OutModel) { *OutModel = NormalizedObjectPath(Form->Model); }
	const USkeletalMesh* Model = Cast<USkeletalMesh>(FSoftObjectPath(NormalizedObjectPath(Form->Model)).TryLoad());
	return Model ? Model->Skeleton : nullptr;
}

TSharedRef<FJsonObject> RowToJson(const FEndAnimSetRow& Row)
{
	TSharedRef<FJsonObject> Entry = MakeShared<FJsonObject>();
	Entry->SetArrayField(TEXT("characters"), JsonStrings(CleanList(Row.Characters, false)));
	const auto Sources = [&](const TCHAR* Key, const TArray<FEndAnimSetSource>& List)
	{
		TArray<TSharedPtr<FJsonValue>> Values;
		for (const FEndAnimSetSource& Source : List)
		{
			const FString Path = Source.Path.TrimStartAndEnd();
			const FString As = Source.As.TrimStartAndEnd();
			if (Path.IsEmpty())
			{
				continue;
			}
			if (As.IsEmpty() && Source.AutoMatch == EEndAnimSetAutoMatch::Off)
			{
				Values.Add(MakeShared<FJsonValueString>(Path));
				continue;
			}
			TSharedRef<FJsonObject> Renamed = MakeShared<FJsonObject>();
			Renamed->SetStringField(TEXT("from"), Path);
			if (!As.IsEmpty())
			{
				Renamed->SetStringField(TEXT("as"), As);
			}
			if (Source.AutoMatch != EEndAnimSetAutoMatch::Off)
			{
				Renamed->SetField(TEXT("auto"), AutoMatchJson(Source.AutoMatch));
				// "only" (3.2): the auto match uses only animations with one of these words in their name.
				const TArray<FString> Only = CleanList(Source.OnlyNamesWith, false);
				if (Only.Num() > 0)
				{
					Renamed->SetArrayField(TEXT("only"), JsonStrings(Only));
				}
			}
			Values.Add(MakeShared<FJsonValueObject>(Renamed));
		}
		if (Values.Num() > 0)
		{
			Entry->SetArrayField(Key, Values);
		}
	};
	Sources(TEXT("battle"), Row.Battle);
	Sources(TEXT("field"), Row.Field);
	TArray<TSharedPtr<FJsonValue>> Moves;
	for (const FEndAnimSetMove& Move : Row.Moves)
	{
		if (Move.Name.TrimStartAndEnd().IsEmpty() || Move.Animation.TrimStartAndEnd().IsEmpty())
		{
			continue;
		}
		TSharedRef<FJsonObject> Object = MakeShared<FJsonObject>();
		if (!Move.Set.TrimStartAndEnd().IsEmpty())
		{
			Object->SetStringField(TEXT("set"), Move.Set.TrimStartAndEnd());
		}
		Object->SetStringField(TEXT("key"), Move.Name.TrimStartAndEnd());
		const TArray<FString> Then = CleanList(Move.ThenPlay, false);
		if (Move.bBuild)
		{
			// Built in the editor (Build Moves): the game plays the built animation; "build" (editor only, the mod skips it)
			// says what it is built from.
			Object->SetStringField(TEXT("animation"), BuiltObjectPathOf(Row, Move));
			TSharedRef<FJsonObject> Build = MakeShared<FJsonObject>();
			Build->SetStringField(TEXT("from"), Move.Animation.TrimStartAndEnd());
			if (Move.bShot)
			{
				Build->SetBoolField(TEXT("shot"), true);
			}
			if (Move.HitAt > 0.f)
			{
				Build->SetNumberField(TEXT("hit_at"), JsonSeconds(Move.HitAt));
			}
			if (!Move.NotifiesFrom.TrimStartAndEnd().IsEmpty())
			{
				Build->SetStringField(TEXT("notifies_from"), Move.NotifiesFrom.TrimStartAndEnd());
			}
			if (Move.Hits.Num() > 0)
			{
				Build->SetArrayField(TEXT("hits"), HitsToJson(Move.Hits));
			}
			if (Move.Retarget == EEndMoveRetarget::AsIs)
			{
				Build->SetStringField(TEXT("retarget"), TEXT("as_is"));
			}
			else if (Move.Retarget == EEndMoveRetarget::Motion)
			{
				Build->SetStringField(TEXT("retarget"), TEXT("motion"));
			}
			else if (Move.Retarget == EEndMoveRetarget::Lean)
			{
				Build->SetStringField(TEXT("retarget"), TEXT("lean"));
				if (!Move.LeanBone.TrimStartAndEnd().IsEmpty())
				{
					Build->SetStringField(TEXT("lean_bone"), Move.LeanBone.TrimStartAndEnd());
				}
				Build->SetNumberField(TEXT("lean"), Move.Lean);
			}
			if (!Move.Base.TrimStartAndEnd().IsEmpty())
			{
				Build->SetStringField(TEXT("base"), Move.Base.TrimStartAndEnd());
				if (Move.bBaseLoop)
				{
					Build->SetBoolField(TEXT("base_loop"), true);
				}
			}
			if (!Move.MotionFrom.TrimStartAndEnd().IsEmpty())
			{
				Build->SetStringField(TEXT("motion_from"), Move.MotionFrom.TrimStartAndEnd());
			}
			if (!Move.BoneMap.TrimStartAndEnd().IsEmpty())
			{
				Build->SetStringField(TEXT("bone_map"), Move.BoneMap.TrimStartAndEnd());
			}
			if (!FMath::IsNearlyZero(Move.SourceTurn))
			{
				Build->SetNumberField(TEXT("source_turn"), Move.SourceTurn);
			}
			if (Move.bKeepBaseRoot)
			{
				Build->SetBoolField(TEXT("keep_root"), true);
			}
			if (!Move.bKeepSourceEffects)
			{
				Build->SetBoolField(TEXT("source_effects"), false);
			}
			else if (Move.bSourceSoundsOnly)
			{
				Build->SetBoolField(TEXT("source_sounds_only"), true);   // (1.12.3)
			}
			if (Move.ClipStart > 0.f || Move.ClipEnd > 0.f)
			{
				TArray<TSharedPtr<FJsonValue>> Clip;
				Clip.Add(MakeShared<FJsonValueNumber>(JsonSeconds(Move.ClipStart)));
				Clip.Add(MakeShared<FJsonValueNumber>(JsonSeconds(Move.ClipEnd)));
				Build->SetArrayField(TEXT("clip"), Clip);
			}
			if (!FMath::IsNearlyEqual(Move.Speed, 1.f, 0.0005f) && Move.Speed > 0.f)
			{
				Build->SetNumberField(TEXT("speed"), JsonSeconds(Move.Speed));
			}
			Object->SetObjectField(TEXT("build"), Build);
		}
		else if (Then.Num() > 0)
		{
			// A chain: the animations played one after another (RebirthSkelCompat 3.2).
			TArray<FString> Chain{Move.Animation.TrimStartAndEnd()};
			Chain.Append(Then);
			Object->SetArrayField(TEXT("animation"), JsonStrings(Chain));
		}
		else
		{
			Object->SetStringField(TEXT("animation"), Move.Animation.TrimStartAndEnd());
		}
		Moves.Add(MakeShared<FJsonValueObject>(Object));
	}
	if (Moves.Num() > 0)
	{
		Entry->SetArrayField(TEXT("moves"), Moves);
	}
	const TArray<FString> Sets = CleanList(Row.MoreSetNames, false);
	if (Sets.Num() > 0)
	{
		Entry->SetArrayField(TEXT("sets"), JsonStrings(Sets));
	}
	if (!Row.FieldActions.TrimStartAndEnd().IsEmpty())
	{
		Entry->SetStringField(TEXT("field_actions"), Row.FieldActions.TrimStartAndEnd());
	}
	if (!Row.Cutscene.IsNull())
	{
		Entry->SetStringField(TEXT("cutscene"), SoftPath(Row.Cutscene));
	}
	if (!Row.CharacterSkeleton.IsNull())
	{
		Entry->SetStringField(TEXT("skeleton"), SoftPath(Row.CharacterSkeleton));
	}
	TArray<TSharedPtr<FJsonValue>> Sockets;
	for (const FEndSocketStandIn& Socket : Row.Sockets)
	{
		const FString Wanted = Socket.Socket.TrimStartAndEnd();
		const FString Use = Socket.Use.TrimStartAndEnd();
		if (!Wanted.IsEmpty() && !Use.IsEmpty())
		{
			Sockets.Add(MakeShared<FJsonValueObject>(SocketStandInToJson(Socket)));   // (1.14: with its placement)
		}
	}
	if (Sockets.Num() > 0)
	{
		Entry->SetArrayField(TEXT("sockets"), Sockets);
	}
	// Limit breaks in order (null keeps that limit as it is); empty ones at the end are left out.
	TArray<TSharedPtr<FJsonValue>> Limits;
	for (const FEndLimitBreak& Limit : Row.LimitBreaks)
	{
		const FString Animation = Limit.Animation.TrimStartAndEnd();
		const TArray<FString> Then = CleanList(Limit.ThenPlay, false);
		if (Animation.IsEmpty())
		{
			Limits.Add(MakeShared<FJsonValueNull>());
		}
		else if (Then.Num() == 0)
		{
			Limits.Add(MakeShared<FJsonValueString>(Animation));
		}
		else
		{
			TArray<FString> Chain{Animation};
			Chain.Append(Then);
			Limits.Add(MakeShared<FJsonValueArray>(JsonStrings(Chain)));
		}
	}
	while (Limits.Num() > 0 && Limits.Last()->Type == EJson::Null)
	{
		Limits.Pop();
	}
	if (Limits.Num() > 0)
	{
		Entry->SetArrayField(TEXT("limit_breaks"), Limits);
	}
	if (Row.bKeepProportions)
	{
		Entry->SetBoolField(TEXT("proportions"), true);
	}
	if (Row.bOverride)
	{
		Entry->SetBoolField(TEXT("override"), true);
	}
	// 3.3: the character's commands and limit breaks per animation pack, and objects to keep loaded.
	const FString Player = Row.PlayerParameter.TrimStartAndEnd();
	if (!Player.IsEmpty())
	{
		Entry->SetStringField(TEXT("player"), Player);
	}
	TArray<TSharedPtr<FJsonValue>> Abilities;
	for (const FEndPackAbilities& Pack : Row.Abilities)
	{
		const FString Name = Pack.Pack.TrimStartAndEnd();
		if (Name.IsEmpty() || (!Pack.bSetCommands && !Pack.bSetLimits && !Pack.bSetWeaponAbilities))
		{
			continue;
		}
		TSharedRef<FJsonObject> Object = MakeShared<FJsonObject>();
		Object->SetStringField(TEXT("pack"), Name);
		if (Pack.bSetCommands)
		{
			Object->SetArrayField(TEXT("commands"), JsonStrings(CleanList(Pack.Commands, false)));
		}
		if (Pack.bSetLimits)
		{
			Object->SetArrayField(TEXT("limits"), JsonStrings(CleanList(Pack.Limits, false)));
		}
		if (Pack.bSetWeaponAbilities)
		{
			// 3.4: {"<the ability a weapon gives>": "<the ability it gives in this pack>"}
			TSharedRef<FJsonObject> Weapons = MakeShared<FJsonObject>();
			for (const FEndWeaponAbility& Weapon : Pack.WeaponAbilities)
			{
				const FString Given = Weapon.Weapon.TrimStartAndEnd(), Instead = Weapon.Ability.TrimStartAndEnd();
				if (!Given.IsEmpty() && !Instead.IsEmpty() && !Weapons->HasField(Given))
				{
					Weapons->SetStringField(Given, Instead);
				}
			}
			Object->SetObjectField(TEXT("weapon_abilities"), Weapons);
		}
		Abilities.Add(MakeShared<FJsonValueObject>(Object));
	}
	if (Abilities.Num() > 0)
	{
		Entry->SetArrayField(TEXT("abilities"), Abilities);
	}
	if (!Row.bRefreshAbilities)
	{
		Entry->SetBoolField(TEXT("refresh_abilities"), false);
	}
	TArray<FString> Preload;
	for (const FString& Path : CleanList(Row.Preload, false))
	{
		Preload.AddUnique(NormalizedObjectPath(Path));
	}
	if (Preload.Num() > 0)
	{
		Entry->SetArrayField(TEXT("preload"), JsonStrings(Preload));
	}
	TArray<FString> PackAssets;
	for (const FString& Path : CleanList(Row.PackAssets, false))
	{
		PackAssets.AddUnique(NormalizedObjectPath(Path));
	}
	if (PackAssets.Num() > 0)
	{
		Entry->SetArrayField(TEXT("pack_assets"), JsonStrings(PackAssets));
	}
	// 3.6: the forms and the forms menu.
	if (Row.Forms.List.Num() > 0)
	{
		Entry->SetObjectField(TEXT("forms"), FormsToJson(Row.Forms));
	}
	// (1.14) the voice, the slot owner's looks, the skeleton of the slot's AnimBlueprints, the cutscene weapon socket, the shooter
	if (const TSharedPtr<FJsonValue> Voice = VoiceToJson(Row.Voice, Row.VoiceReplaces))
	{
		Entry->SetField(TEXT("voice"), Voice);
	}
	if (!Row.LooksFrom.TrimStartAndEnd().IsEmpty())
	{
		Entry->SetStringField(TEXT("looks_from"), NormalizedObjectPath(Row.LooksFrom));
	}
	if (!Row.AnimBlueprintsFrom.IsNull())
	{
		Entry->SetStringField(TEXT("anim_blueprints_from"), SoftPath(Row.AnimBlueprintsFrom));
	}
	if (!Row.CutsceneWeaponSocket.TrimStartAndEnd().IsEmpty())
	{
		Entry->SetStringField(TEXT("cutscene_weapon_socket"), Row.CutsceneWeaponSocket.TrimStartAndEnd());
	}
	if (const TSharedPtr<FJsonValue> Shooter = JsonValueOfText(Row.ShooterJson))
	{
		Entry->SetField(TEXT("shooter"), Shooter);
	}
	// Build Moves settings (editor only; the mod skips them).
	if (!Row.BuildFolder.TrimStartAndEnd().IsEmpty())
	{
		Entry->SetStringField(TEXT("build_folder"), BuildFolderOf(Row));
	}
	const FEndShotEffects& Shot = Row.ShotEffects;
	if (!Shot.MuzzleEffect.TrimStartAndEnd().IsEmpty() || !Shot.SoundBank.TrimStartAndEnd().IsEmpty())
	{
		TSharedRef<FJsonObject> Object = MakeShared<FJsonObject>();
		if (!Shot.MuzzleEffect.TrimStartAndEnd().IsEmpty())
		{
			Object->SetStringField(TEXT("muzzle"), Shot.MuzzleEffect.TrimStartAndEnd());
			Object->SetStringField(TEXT("socket"), Shot.MuzzleSocket.ToString());
			Object->SetNumberField(TEXT("muzzle_time"), JsonSeconds(Shot.MuzzleTime));
		}
		if (!Shot.SoundBank.TrimStartAndEnd().IsEmpty())
		{
			Object->SetStringField(TEXT("sound_bank"), Shot.SoundBank.TrimStartAndEnd());
			Object->SetStringField(TEXT("sound"), Shot.Sound.ToString());
		}
		if (Shot.Weapon != 1)
		{
			Object->SetNumberField(TEXT("weapon"), Shot.Weapon);
		}
		Entry->SetObjectField(TEXT("shot_effects"), Object);
	}
	const TArray<FString> Requires = CleanList(Row.RequiresPaks, true);
	if (Requires.Num() > 0)
	{
		Entry->SetArrayField(TEXT("requires_paks"), JsonStrings(Requires));
	}
	Entry->SetBoolField(TEXT("enabled"), Row.bEnabled);
	return Entry;
}

// The mod's "animation_sets" entry as a row (for Import From Game Json). False without a character.
bool RowFromJson(const TSharedPtr<FJsonObject>& Entry, FEndAnimSetRow& Row)
{
	Row = FEndAnimSetRow();
	if (!Entry.IsValid())
	{
		return false;
	}
	BoolField(Entry, TEXT("enabled"), Row.bEnabled);
	TArray<FString> Characters = StringsOf(Entry->TryGetField(TEXT("character")));
	Characters.Append(StringsOf(Entry->TryGetField(TEXT("characters"))));
	Row.Characters = CleanList(Characters, false);
	for (const TCHAR* Key : {TEXT("battle"), TEXT("field")})
	{
		TArray<FEndAnimSetSource>& List = FCString::Strcmp(Key, TEXT("battle")) == 0 ? Row.Battle : Row.Field;
		const TSharedPtr<FJsonValue> Value = Entry->TryGetField(Key);
		TArray<TSharedPtr<FJsonValue>> Items;
		if (Value.IsValid() && Value->Type == EJson::Array) { Items = Value->AsArray(); }
		else if (Value.IsValid()) { Items.Add(Value); }
		for (const TSharedPtr<FJsonValue>& Item : Items)
		{
			FEndAnimSetSource Source;
			if (Item.IsValid() && Item->Type == EJson::String)
			{
				Source.Path = Item->AsString().TrimStartAndEnd();
			}
			else if (Item.IsValid() && Item->Type == EJson::Object)
			{
				const TSharedPtr<FJsonObject> Object = Item->AsObject();
				for (const TCHAR* From : {TEXT("from"), TEXT("set"), TEXT("path"), TEXT("use")})
				{
					if (Source.Path.IsEmpty()) { Source.Path = StringField(Object, From); }
				}
				Source.As = StringField(Object, TEXT("as"));
				Source.AutoMatch = AutoMatchOf(Object);
				Source.OnlyNamesWith = CleanList(StringsOf(Object->TryGetField(TEXT("only"))), false);
			}
			if (!Source.Path.IsEmpty())
			{
				List.Add(Source);
			}
		}
	}
	const TSharedPtr<FJsonValue> Moves = Entry->TryGetField(TEXT("moves"));
	FString BuiltSeen;          // the first built animation's path, for a row without "build_folder"
	FEndAnimSetMove BuiltSeenMove;
	if (Moves.IsValid() && Moves->Type == EJson::Object)
	{
		for (const auto& Pair : Moves->AsObject()->Values)
		{
			const TArray<FString> Chain = StringsOf(Pair.Value);
			if (Chain.Num() == 0)
			{
				continue;
			}
			FEndAnimSetMove Move;
			const FString Key = Pair.Key.TrimStartAndEnd();
			FString Set, Name;
			if (Key.Split(TEXT("/"), &Set, &Name))
			{
				Move.Set = Set.TrimStartAndEnd();
				Move.Name = Name.TrimStartAndEnd();
			}
			else
			{
				Move.Name = Key;
			}
			Move.Animation = Chain[0].TrimStartAndEnd();
			for (int32 Index = 1; Index < Chain.Num(); ++Index)
			{
				Move.ThenPlay.Add(Chain[Index].TrimStartAndEnd());
			}
			Row.Moves.Add(Move);
		}
	}
	else if (Moves.IsValid() && Moves->Type == EJson::Array)
	{
		for (const TSharedPtr<FJsonValue>& Item : Moves->AsArray())
		{
			if (!Item.IsValid() || Item->Type != EJson::Object)
			{
				continue;
			}
			const TSharedPtr<FJsonObject> Object = Item->AsObject();
			FEndAnimSetMove Move;
			Move.Set = StringField(Object, TEXT("set"));
			Move.Name = StringField(Object, TEXT("key"));
			TArray<FString> Chain;
			for (const TCHAR* Key : {TEXT("animation"), TEXT("use"), TEXT("chain")})
			{
				if (Chain.Num() == 0) { Chain = StringsOf(Object->TryGetField(Key)); }
			}
			// Built in the editor: "animation" is the built one, "build" says what it is made from.
			const TSharedPtr<FJsonObject>* Build = nullptr;
			if (Object->TryGetObjectField(TEXT("build"), Build) && Build && Build->IsValid())
			{
				Move.bBuild = true;
				if (Chain.Num() > 0 && BuiltSeen.IsEmpty())
				{
					BuiltSeen = NormalizedObjectPath(Chain[0]);
					BuiltSeenMove = Move;
				}
				Chain = StringsOf((*Build)->TryGetField(TEXT("from")));
				BoolField(*Build, TEXT("shot"), Move.bShot);
				double HitAt = 0.0;
				if ((*Build)->TryGetNumberField(TEXT("hit_at"), HitAt))
				{
					Move.HitAt = FMath::Max(0.f, static_cast<float>(HitAt));
				}
				Move.NotifiesFrom = StringField(*Build, TEXT("notifies_from"));
				Move.Hits = HitsFromJson((*Build)->TryGetField(TEXT("hits")));
				const FString RetargetName = StringField(*Build, TEXT("retarget"));
				Move.Retarget = RetargetName.Equals(TEXT("as_is"), ESearchCase::IgnoreCase)	  ? EEndMoveRetarget::AsIs
								: RetargetName.Equals(TEXT("motion"), ESearchCase::IgnoreCase) ? EEndMoveRetarget::Motion
								: RetargetName.Equals(TEXT("lean"), ESearchCase::IgnoreCase)   ? EEndMoveRetarget::Lean
																								 : EEndMoveRetarget::Proportions;
				Move.LeanBone = StringField(*Build, TEXT("lean_bone"));
				double LeanDegrees = Move.Lean;
				if ((*Build)->TryGetNumberField(TEXT("lean"), LeanDegrees))
				{
					Move.Lean = FMath::Clamp(static_cast<float>(LeanDegrees), 0.f, 60.f);
				}
				Move.Base = StringField(*Build, TEXT("base"));
				BoolField(*Build, TEXT("base_loop"), Move.bBaseLoop);
				Move.MotionFrom = StringField(*Build, TEXT("motion_from"));
				Move.BoneMap = StringField(*Build, TEXT("bone_map"));
				double Turn = 0.0;
				if ((*Build)->TryGetNumberField(TEXT("source_turn"), Turn))
				{
					Move.SourceTurn = FMath::Clamp(static_cast<float>(Turn), -180.f, 180.f);
				}
				BoolField(*Build, TEXT("keep_root"), Move.bKeepBaseRoot);
				BoolField(*Build, TEXT("source_effects"), Move.bKeepSourceEffects);
				BoolField(*Build, TEXT("source_sounds_only"), Move.bSourceSoundsOnly);
				const TArray<TSharedPtr<FJsonValue>>* Clip = nullptr;
				if ((*Build)->TryGetArrayField(TEXT("clip"), Clip) && Clip && Clip->Num() == 2)
				{
					Move.ClipStart = FMath::Max(0.f, static_cast<float>((*Clip)[0]->AsNumber()));
					Move.ClipEnd = FMath::Max(0.f, static_cast<float>((*Clip)[1]->AsNumber()));
				}
				double Speed = 1.0;
				if ((*Build)->TryGetNumberField(TEXT("speed"), Speed) && Speed > 0.0)
				{
					Move.Speed = FMath::Clamp(static_cast<float>(Speed), 0.1f, 10.f);
				}
			}
			if (Chain.Num() > 0)
			{
				Move.Animation = Chain[0].TrimStartAndEnd();
				for (int32 Index = 1; Index < Chain.Num(); ++Index)
				{
					Move.ThenPlay.Add(Chain[Index].TrimStartAndEnd());
				}
			}
			Row.Moves.Add(Move);
		}
	}
	Row.MoreSetNames = CleanList(StringsOf(Entry->TryGetField(TEXT("sets"))), false);
	Row.FieldActions = StringField(Entry, TEXT("field_actions"));
	FString Skeleton = StringField(Entry, TEXT("skeleton"));
	FString Hub = StringField(Entry, TEXT("cutscene"));
	const TSharedPtr<FJsonObject>* Cutscene = nullptr;
	if (Entry->TryGetObjectField(TEXT("cutscene"), Cutscene) && Cutscene)
	{
		Hub = StringField(*Cutscene, TEXT("hub"));
		if (Hub.IsEmpty()) { Hub = StringField(*Cutscene, TEXT("plays")); }
		const FString Own = StringField(*Cutscene, TEXT("skeleton"));
		if (!Own.IsEmpty()) { Skeleton = Own; }
	}
	if (!Hub.IsEmpty()) { Row.Cutscene = TSoftObjectPtr<USkeleton>(FSoftObjectPath(NormalizedObjectPath(Hub))); }
	if (!Skeleton.IsEmpty()) { Row.CharacterSkeleton = TSoftObjectPtr<USkeleton>(FSoftObjectPath(NormalizedObjectPath(Skeleton))); }
	const auto AddSocket = [&Row](const FString& Wanted, const FString& Use, const TSharedPtr<FJsonObject>& Placement)
	{
		if (!Wanted.IsEmpty() && !Use.IsEmpty() && !Row.Sockets.ContainsByPredicate([&](const FEndSocketStandIn& S) { return S.Socket.Equals(Wanted, ESearchCase::IgnoreCase); }))
		{
			FEndSocketStandIn Socket;
			Socket.Socket = Wanted;
			Socket.Use = Use;
			SocketPlacementFromJson(Placement, Socket);   // (1.14)
			Row.Sockets.Add(Socket);
		}
	};
	const TSharedPtr<FJsonValue> Sockets = Entry->TryGetField(TEXT("sockets"));
	if (Sockets.IsValid() && Sockets->Type == EJson::Array)
	{
		for (const TSharedPtr<FJsonValue>& Item : Sockets->AsArray())
		{
			const TSharedPtr<FJsonObject> Object = Item.IsValid() && Item->Type == EJson::Object ? Item->AsObject() : nullptr;
			FString Wanted = StringField(Object, TEXT("socket"));
			if (Wanted.IsEmpty()) { Wanted = StringField(Object, TEXT("name")); }
			FString Use = StringField(Object, TEXT("use"));
			if (Use.IsEmpty()) { Use = StringField(Object, TEXT("to")); }
			if (Use.IsEmpty()) { Use = StringField(Object, TEXT("bone")); }
			AddSocket(Wanted, Use, Object);
		}
	}
	else if (Sockets.IsValid() && Sockets->Type == EJson::Object)
	{
		for (const auto& Socket : Sockets->AsObject()->Values)
		{
			if (Socket.Value.IsValid() && Socket.Value->Type == EJson::String)
			{
				AddSocket(Socket.Key.TrimStartAndEnd(), Socket.Value->AsString().TrimStartAndEnd(), nullptr);
			}
		}
	}
	// Limit breaks: an array in order (null or "" keeps that one), or an object by number / B_AtkLimit name.
	TSharedPtr<FJsonValue> Limits = Entry->TryGetField(TEXT("limit_breaks"));
	if (!Limits.IsValid()) { Limits = Entry->TryGetField(TEXT("limits")); }
	const auto SetLimit = [&Row](int32 Number, const TSharedPtr<FJsonValue>& Value)
	{
		const TArray<FString> Chain = StringsOf(Value);
		if (Number < 1 || Number > 99 || Chain.Num() == 0 || Chain[0].TrimStartAndEnd().IsEmpty())
		{
			return;
		}
		if (Row.LimitBreaks.Num() < Number) { Row.LimitBreaks.SetNum(Number); }
		FEndLimitBreak& Limit = Row.LimitBreaks[Number - 1];
		Limit.Animation = Chain[0].TrimStartAndEnd();
		Limit.ThenPlay.Reset();
		for (int32 Index = 1; Index < Chain.Num(); ++Index) { Limit.ThenPlay.Add(Chain[Index].TrimStartAndEnd()); }
	};
	if (Limits.IsValid() && Limits->Type == EJson::Array)
	{
		const TArray<TSharedPtr<FJsonValue>>& Items = Limits->AsArray();
		for (int32 Index = 0; Index < Items.Num(); ++Index) { SetLimit(Index + 1, Items[Index]); }
	}
	else if (Limits.IsValid() && Limits->Type == EJson::Object)
	{
		for (const auto& Limit : Limits->AsObject()->Values)
		{
			FString Key = Limit.Key.TrimStartAndEnd();
			if (Key.StartsWith(TEXT("B_AtkLimit"), ESearchCase::IgnoreCase))
			{
				Key = Key.Mid(10);
				Key.RemoveFromEnd(TEXT("_0"));
			}
			if (Key.IsNumeric()) { SetLimit(FCString::Atoi(*Key), Limit.Value); }
		}
	}
	for (const TCHAR* Key : {TEXT("proportions"), TEXT("keep_proportions")})
	{
		BoolField(Entry, Key, Row.bKeepProportions);
	}
	BoolField(Entry, TEXT("override"), Row.bOverride);
	// 3.3: commands and limits per animation pack (an array of {pack, commands, limits}, or an object by pack), preload.
	for (const TCHAR* Key : {TEXT("player"), TEXT("player_parameter"), TEXT("battle_player_parameter")})
	{
		if (Row.PlayerParameter.IsEmpty()) { Row.PlayerParameter = StringField(Entry, Key); }
	}
	const auto AddPack = [&Row](const FString& Name, const TSharedPtr<FJsonValue>& Value)
	{
		if (Name.TrimStartAndEnd().IsEmpty() || !Value.IsValid() ||
			Row.Abilities.ContainsByPredicate([&](const FEndPackAbilities& P) { return P.Pack.Equals(Name.TrimStartAndEnd(), ESearchCase::IgnoreCase); }))
		{
			return;
		}
		FEndPackAbilities Pack;
		Pack.Pack = Name.TrimStartAndEnd();
		Pack.bSetCommands = false;
		if (Value->Type == EJson::Array || Value->Type == EJson::String)
		{
			Pack.bSetCommands = true;
			Pack.Commands = CleanList(StringsOf(Value), false);
		}
		else if (Value->Type == EJson::Object)
		{
			const TSharedPtr<FJsonObject> Object = Value->AsObject();
			for (const TCHAR* Key : {TEXT("commands"), TEXT("command"), TEXT("atb")})
			{
				if (const TSharedPtr<FJsonValue> List = Object->TryGetField(Key); List.IsValid() && !Pack.bSetCommands)
				{
					Pack.bSetCommands = true;
					Pack.Commands = CleanList(StringsOf(List), false);
				}
			}
			for (const TCHAR* Key : {TEXT("limits"), TEXT("limit"), TEXT("limit_breaks")})
			{
				if (const TSharedPtr<FJsonValue> List = Object->TryGetField(Key); List.IsValid() && !Pack.bSetLimits)
				{
					Pack.bSetLimits = true;
					Pack.Limits = CleanList(StringsOf(List), false);
				}
			}
			// 3.4: weapon abilities, {"weapon's ability": "ability"} or [["weapon's ability", "ability"], {"weapon": ..., "ability": ...}]
			for (const TCHAR* Key : {TEXT("weapon_abilities"), TEXT("weapons")})
			{
				const TSharedPtr<FJsonValue> Weapons = Object->TryGetField(Key);
				if (!Weapons.IsValid() || Pack.bSetWeaponAbilities)
				{
					continue;
				}
				Pack.bSetWeaponAbilities = true;
				const auto AddWeapon = [&Pack](const FString& Given, const FString& Instead) {
					FEndWeaponAbility Weapon;
					Weapon.Weapon = Given.TrimStartAndEnd();
					Weapon.Ability = Instead.TrimStartAndEnd();
					if (!Weapon.Weapon.IsEmpty() && !Weapon.Ability.IsEmpty() &&
						!Pack.WeaponAbilities.ContainsByPredicate([&](const FEndWeaponAbility& W) { return W.Weapon.Equals(Weapon.Weapon, ESearchCase::IgnoreCase); }))
					{
						Pack.WeaponAbilities.Add(Weapon);
					}
				};
				if (Weapons->Type == EJson::Object)
				{
					for (const auto& Pair : Weapons->AsObject()->Values)
					{
						FString Instead;
						if (Pair.Value.IsValid() && Pair.Value->TryGetString(Instead)) { AddWeapon(Pair.Key, Instead); }
					}
				}
				else if (Weapons->Type == EJson::Array)
				{
					for (const TSharedPtr<FJsonValue>& Item : Weapons->AsArray())
					{
						if (!Item.IsValid()) { continue; }
						if (Item->Type == EJson::Array && Item->AsArray().Num() == 2)
						{
							FString Given, Instead;
							if (Item->AsArray()[0]->TryGetString(Given) && Item->AsArray()[1]->TryGetString(Instead)) { AddWeapon(Given, Instead); }
						}
						else if (Item->Type == EJson::Object)
						{
							const TSharedPtr<FJsonObject> Pair = Item->AsObject();
							FString Given = StringField(Pair, TEXT("weapon")), Instead = StringField(Pair, TEXT("ability"));
							if (Given.IsEmpty()) { Given = StringField(Pair, TEXT("from")); }
							if (Instead.IsEmpty()) { Instead = StringField(Pair, TEXT("to")); }
							AddWeapon(Given, Instead);
						}
					}
				}
			}
		}
		if (Pack.bSetCommands || Pack.bSetLimits || Pack.bSetWeaponAbilities)
		{
			Row.Abilities.Add(Pack);
		}
	};
	const TSharedPtr<FJsonValue> Abilities = Entry->TryGetField(TEXT("abilities"));
	if (Abilities.IsValid() && Abilities->Type == EJson::Array)
	{
		for (const TSharedPtr<FJsonValue>& Item : Abilities->AsArray())
		{
			const TSharedPtr<FJsonObject> Object = Item.IsValid() && Item->Type == EJson::Object ? Item->AsObject() : nullptr;
			FString Name = StringField(Object, TEXT("pack"));
			if (Name.IsEmpty()) { Name = StringField(Object, TEXT("set")); }
			if (Name.IsEmpty()) { Name = StringField(Object, TEXT("form")); }
			AddPack(Name, Item);
		}
	}
	else if (Abilities.IsValid() && Abilities->Type == EJson::Object)
	{
		for (const auto& Pack : Abilities->AsObject()->Values) { AddPack(Pack.Key, Pack.Value); }
	}
	BoolField(Entry, TEXT("refresh_abilities"), Row.bRefreshAbilities);
	Row.Preload = CleanList(StringsOf(Entry->TryGetField(TEXT("preload"))), false);
	Row.PackAssets = CleanList(StringsOf(Entry->TryGetField(TEXT("pack_assets"))), false);
	Row.Forms = FormsFromJson(Entry->TryGetField(TEXT("forms")));
	// (1.14) the voice, the slot owner's looks, the skeleton of the slot's AnimBlueprints, the cutscene weapon socket, the shooter
	VoiceFromJson(Entry->TryGetField(TEXT("voice")), Row.Voice, Row.VoiceReplaces);
	Row.LooksFrom = StringField(Entry, TEXT("looks_from"));
	Row.LooksFrom.RemoveFromEnd(TEXT("_C"));   // (the blueprint, as the data object names it; the mod adds its class's _C)
	const FString AnimBlueprintsFrom = StringField(Entry, TEXT("anim_blueprints_from"));
	if (!AnimBlueprintsFrom.IsEmpty())
	{
		Row.AnimBlueprintsFrom = TSoftObjectPtr<USkeleton>(FSoftObjectPath(NormalizedObjectPath(AnimBlueprintsFrom)));
	}
	Row.CutsceneWeaponSocket = StringField(Entry, TEXT("cutscene_weapon_socket"));
	Row.ShooterJson = TextOfJsonValue(Entry->TryGetField(TEXT("shooter")));
	// Build Moves settings.
	Row.BuildFolder = StringField(Entry, TEXT("build_folder"));
	if (Row.BuildFolder.IsEmpty() && !BuiltSeen.IsEmpty())
	{
		// <folder>/<Set>/<Name>.<Name> -> <folder>
		FString Folder = FPackageName::ObjectPathToPackageName(BuiltSeen);
		Folder.RemoveFromEnd(TEXT("/") + BuiltSeenMove.Name.TrimStartAndEnd());
		const FString Set = BuiltSeenMove.Set.TrimStartAndEnd();
		if (!Set.IsEmpty())
		{
			Folder.RemoveFromEnd(TEXT("/") + Set);
		}
		Row.BuildFolder = Folder;
	}
	const TSharedPtr<FJsonObject>* Shot = nullptr;
	if (Entry->TryGetObjectField(TEXT("shot_effects"), Shot) && Shot && Shot->IsValid())
	{
		Row.ShotEffects.MuzzleEffect = StringField(*Shot, TEXT("muzzle"));
		const FString Socket = StringField(*Shot, TEXT("socket"));
		if (!Socket.IsEmpty())
		{
			Row.ShotEffects.MuzzleSocket = FName(*Socket);
		}
		double Number = 0.0;
		if ((*Shot)->TryGetNumberField(TEXT("muzzle_time"), Number) && Number > 0.0)
		{
			Row.ShotEffects.MuzzleTime = static_cast<float>(Number);
		}
		Row.ShotEffects.SoundBank = StringField(*Shot, TEXT("sound_bank"));
		const FString Sound = StringField(*Shot, TEXT("sound"));
		Row.ShotEffects.Sound = Sound.IsEmpty() ? NAME_None : FName(*Sound);
		if ((*Shot)->TryGetNumberField(TEXT("weapon"), Number))
		{
			Row.ShotEffects.Weapon = FMath::Clamp(static_cast<int32>(Number), 1, 8);
		}
	}
	TArray<FString> Paks = StringsOf(Entry->TryGetField(TEXT("requires_paks")));
	Paks.Append(StringsOf(Entry->TryGetField(TEXT("requires_pak"))));
	Row.RequiresPaks = CleanList(Paks, true);
	return Row.Characters.Num() > 0;
}

// The row as the game reads it: parsed and settled by the mod's own code (alone, without the other compat files).
bool RowAsGameReadsIt(const FEndAnimSetRow& Row, SkelCompat::AnimSetRow& Out, std::vector<std::wstring>& Notes, std::vector<SkelCompat::Pair>& Families)
{
	TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
	Root->SetStringField(TEXT("schema"), TEXT("RebirthSkelCompat/1"));
	FEndAnimSetRow On = Row;
	On.bEnabled = true;
	On.RequiresPaks.Reset();
	TArray<TSharedPtr<FJsonValue>> Rows;
	Rows.Add(MakeShared<FJsonValueObject>(RowToJson(On)));
	Root->SetArrayField(TEXT("animation_sets"), Rows);
	FString Text;
	const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Text);
	FJsonSerializer::Serialize(Root, Writer);
	SkelCompat::Config Config;
	const FTCHARToUTF8 Utf8(*Text);
	SkelCompat::AppendConfig(std::string_view(Utf8.Get(), static_cast<size_t>(Utf8.Length())), L"row", Config);
	SkelCompat::FinishConfig(Config, [](const std::wstring&) { return true; });
	Notes = Config.Messages;
	Families = Config.Pairs;
	if (Config.AnimSets.empty())
	{
		return false;
	}
	Out = Config.AnimSets.front();
	return true;
}

// ------------------------------------------------------------------------------------------------
// RebirthDataObjectLibrary (Rebirth Cooked Asset Preview plugin): the project's data object tools, called through
// reflection so this plugin does not depend on that one.
// ------------------------------------------------------------------------------------------------
class FDataObjectCall
{
public:
	// Library: RebirthDataObjectLibrary (data objects) or RebirthGameObjectLibrary (game assets, editor 1.7).
	explicit FDataObjectCall(const TCHAR* Name, const TCHAR* LibraryName = TEXT("RebirthDataObjectLibrary"))
	{
		UClass* Library = FindObject<UClass>(ANY_PACKAGE, LibraryName);
		Function = Library ? Library->FindFunctionByName(FName(Name)) : nullptr;
		if (Function)
		{
			Params = MakeUnique<FStructOnScope>(Function);
		}
	}

	explicit operator bool() const { return Function != nullptr; }

	bool SetString(const TCHAR* Param, const FString& Value)
	{
		FStrProperty* Property = CastField<FStrProperty>(Find(Param));
		if (Property) { Property->SetPropertyValue_InContainer(Memory(), Value); }
		return Property != nullptr;
	}

	bool SetName(const TCHAR* Param, const FString& Value)
	{
		FNameProperty* Property = CastField<FNameProperty>(Find(Param));
		if (Property) { Property->SetPropertyValue_InContainer(Memory(), FName(*Value)); }
		return Property != nullptr;
	}

	bool SetNames(const TCHAR* Param, const TArray<FName>& Value)
	{
		FArrayProperty* Property = CastField<FArrayProperty>(Find(Param));
		if (!Property || !CastField<FNameProperty>(Property->Inner)) { return false; }
		*Property->ContainerPtrToValuePtr<TArray<FName>>(Memory()) = Value;
		return true;
	}

	void Run()
	{
		if (Function) { Function->GetOwnerClass()->GetDefaultObject()->ProcessEvent(Function, Memory()); }
	}

	bool ResultBool() const
	{
		const FBoolProperty* Property = CastField<FBoolProperty>(Find(TEXT("ReturnValue")));
		return Property && Property->GetPropertyValue_InContainer(Memory());
	}

	FString ResultString(const TCHAR* Param = TEXT("ReturnValue")) const
	{
		const FStrProperty* Property = CastField<FStrProperty>(Find(Param));
		return Property ? Property->GetPropertyValue_InContainer(Memory()) : FString();
	}

	TArray<FName> ResultNames() const
	{
		const FArrayProperty* Property = CastField<FArrayProperty>(Find(TEXT("ReturnValue")));
		return Property && CastField<FNameProperty>(Property->Inner) ? *Property->ContainerPtrToValuePtr<TArray<FName>>(Memory()) : TArray<FName>();
	}

	TArray<FString> ResultStrings() const
	{
		const FArrayProperty* Property = CastField<FArrayProperty>(Find(TEXT("ReturnValue")));
		return Property && CastField<FStrProperty>(Property->Inner) ? *Property->ContainerPtrToValuePtr<TArray<FString>>(Memory()) : TArray<FString>();
	}

	UObject* ResultObject() const
	{
		const FObjectPropertyBase* Property = CastField<FObjectPropertyBase>(Find(TEXT("ReturnValue")));
		return Property ? Property->GetObjectPropertyValue_InContainer(Memory()) : nullptr;
	}

private:
	UFunction* Function = nullptr;
	TUniquePtr<FStructOnScope> Params;

	FProperty* Find(const TCHAR* Param) const { return Function ? Function->FindPropertyByName(FName(Param)) : nullptr; }
	uint8* Memory() const { return Params->GetStructMemory(); }
};

struct FCharaSpecTable
{
	FString Package;
	bool bAvailable = false;     // the tools are loaded
	TArray<FName> Rows;

	explicit FCharaSpecTable(const FString& InPackage) : Package(InPackage.TrimStartAndEnd())
	{
		FDataObjectCall Call(TEXT("GetDataObjectRowNames"));
		bAvailable = static_cast<bool>(Call) && !Package.IsEmpty();
		if (bAvailable && Call.SetString(TEXT("PackageName"), Package))
		{
			Call.Run();
			Rows = Call.ResultNames();
		}
	}

	bool Has(const FString& Row) const { return Rows.Contains(FName(*Row)); }

	FString Field(const FString& Row, const TCHAR* FieldName) const
	{
		FDataObjectCall Call(TEXT("GetDataObjectRowField"));
		if (!Call || !Call.SetString(TEXT("PackageName"), Package) || !Call.SetName(TEXT("RowName"), Row) || !Call.SetName(TEXT("FieldName"), FieldName))
		{
			return FString();
		}
		Call.Run();
		return Call.ResultString().TrimStartAndEnd();
	}

	bool SetField(const FString& Row, const TCHAR* FieldName, const FString& Value, FString& Message) const
	{
		FDataObjectCall Call(TEXT("SetDataObjectRowField"));
		if (!Call || !Call.SetString(TEXT("PackageName"), Package) || !Call.SetName(TEXT("RowName"), Row) || !Call.SetName(TEXT("FieldName"), FieldName) ||
			!Call.SetString(TEXT("Value"), Value))
		{
			Message = TEXT("SetDataObjectRowField is not available");
			return false;
		}
		Call.Run();
		Message = Call.ResultString(TEXT("Message"));
		return Call.ResultBool();
	}

	bool Save(FString& Message) const
	{
		FDataObjectCall Call(TEXT("SaveDataObject"));
		if (!Call || !Call.SetString(TEXT("PackageName"), Package))
		{
			Message = TEXT("SaveDataObject is not available");
			return false;
		}
		Call.Run();
		Message = Call.ResultString(TEXT("Message"));
		return Call.ResultBool();
	}

	TArray<FString> Check(const TArray<FName>& Which) const
	{
		FDataObjectCall Call(TEXT("CheckCharaSpecRows"));
		if (!Call || !Call.SetString(TEXT("PackageName"), Package) || !Call.SetNames(TEXT("Rows"), Which))
		{
			return {};
		}
		Call.Run();
		return Call.ResultStrings();
	}
};

// Names in a field's copy text: (Battle00,Neutral00,None,...) or ("Battle00","Neutral00",...).
TArray<FString> NamesInText(FString Text)
{
	Text.TrimStartAndEndInline();
	Text.RemoveFromStart(TEXT("("));
	Text.RemoveFromEnd(TEXT(")"));
	TArray<FString> Parts;
	Text.ParseIntoArray(Parts, TEXT(","), true);
	TArray<FString> Names;
	for (FString Part : Parts)
	{
		Part.TrimStartAndEndInline();
		Part.TrimQuotesInline();
		if (!Part.IsEmpty() && !Part.Equals(TEXT("None"), ESearchCase::IgnoreCase))
		{
			Names.AddUnique(Part);
		}
	}
	return Names;
}

IAssetRegistry& AssetRegistry() { return FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get(); }

bool InProject(const FString& ObjectPath) { return AssetRegistry().GetAssetByObjectPath(FName(*NormalizedObjectPath(ObjectPath))).IsValid(); }

// ------------------------------------------------------------------------------------------------
// Weapon swaps (editor 1.6). A weapon's CharaSpec pack says which blueprint spawns (Asset Class List) and what loads with
// it (effect packs, sound banks); its CharaSpec row says which model that is (ContentsModel) and lists the same effects
// and sounds. A row that still describes the old weapon next to a pack that spawns another one keeps every cutscene
// with that weapon from starting. A replaced weapon's row is made to describe the weapon its pack spawns: the new
// weapon's model, the new weapon in its Shared CharaSpec List, and the effects and sounds its pack loads.
// ------------------------------------------------------------------------------------------------
FString PackPackageOf(const FString& Row) { return TEXT("/Game/DataAsset/Game/CharaSpec/CharaSpec_") + Row; }

// "WE0011_00_Vincent_Quiksilver" -> "WE0011_00": a model's id, the first two parts of its name.
FString ModelIdOf(const FString& Name)
{
	TArray<FString> Parts;
	Name.ParseIntoArray(Parts, TEXT("_"), true);
	return Parts.Num() >= 2 ? Parts[0] + TEXT("_") + Parts[1] : Name;
}

// The skeleton in a weapon's model folder: /Game/Character/Weapon/<model>/Model/<id>_Skeleton.<id>_Skeleton.
FString WeaponSkeletonPathOf(const FString& Model)
{
	const FString Skeleton = ModelIdOf(Model) + TEXT("_Skeleton");
	return FString::Printf(TEXT("/Game/Character/Weapon/%s/Model/%s.%s"), *Model, *Skeleton, *Skeleton);
}

// A field value for an array of names or strings in the editor's copy format: ("A","B"), or () when empty.
FString ArrayText(const TArray<FString>& Items)
{
	TArray<FString> Quoted;
	for (const FString& Item : Items)
	{
		Quoted.Add(TEXT("\"") + Item + TEXT("\""));
	}
	return TEXT("(") + FString::Join(Quoted, TEXT(",")) + TEXT(")");
}

bool SameNames(const TArray<FString>& A, const TArray<FString>& B) { return !HasNamesMissingFrom(A, B) && !HasNamesMissingFrom(B, A); }

// A field's value for a report: a list for arrays, the name otherwise.
FString FieldShown(const TCHAR* Field, const FString& Text)
{
	if (FString(Field).EndsWith(TEXT("_Array")))
	{
		return TEXT("[") + FString::Join(NamesInText(Text), TEXT(", ")) + TEXT("]");
	}
	return Text.IsEmpty() ? FString(TEXT("(empty)")) : Text;
}

TSharedRef<FJsonObject> WeaponSwapToJson(const FEndWeaponSwap& Swap)
{
	TSharedRef<FJsonObject> Entry = MakeShared<FJsonObject>();
	Entry->SetArrayField(TEXT("weapons"), JsonStrings(CleanList(Swap.Weapons, false)));
	Entry->SetStringField(TEXT("new_weapon"), Swap.NewWeapon.TrimStartAndEnd());
	Entry->SetBoolField(TEXT("cutscene_family"), Swap.bCutsceneFamily);
	if (!Swap.WeaponSkeleton.IsNull())
	{
		Entry->SetStringField(TEXT("weapon_skeleton"), SoftPath(Swap.WeaponSkeleton));
	}
	if (!Swap.NewWeaponSkeleton.IsNull())
	{
		Entry->SetStringField(TEXT("new_weapon_skeleton"), SoftPath(Swap.NewWeaponSkeleton));
	}
	TArray<TSharedPtr<FJsonValue>> Sockets;
	for (const FEndSocketStandIn& Socket : Swap.Sockets)
	{
		if (!Socket.Socket.TrimStartAndEnd().IsEmpty() && !Socket.Use.TrimStartAndEnd().IsEmpty())
		{
			Sockets.Add(MakeShared<FJsonValueObject>(SocketStandInToJson(Socket)));   // (1.14: with its placement)
		}
	}
	if (Sockets.Num() > 0)
	{
		Entry->SetArrayField(TEXT("sockets"), Sockets);
	}
	const TArray<FString> Requires = CleanList(Swap.RequiresPaks, true);
	if (Requires.Num() > 0)
	{
		Entry->SetArrayField(TEXT("requires_paks"), JsonStrings(Requires));
	}
	Entry->SetBoolField(TEXT("enabled"), Swap.bEnabled);
	return Entry;
}

bool WeaponSwapFromJson(const TSharedPtr<FJsonObject>& Entry, FEndWeaponSwap& Swap)
{
	if (!Entry.IsValid())
	{
		return false;
	}
	Swap.Weapons = CleanList(StringsOf(Entry->TryGetField(TEXT("weapons"))), false);
	Swap.NewWeapon = StringField(Entry, TEXT("new_weapon"));
	BoolField(Entry, TEXT("cutscene_family"), Swap.bCutsceneFamily);
	const FString Weapon = StringField(Entry, TEXT("weapon_skeleton"));
	const FString New = StringField(Entry, TEXT("new_weapon_skeleton"));
	if (!Weapon.IsEmpty())
	{
		Swap.WeaponSkeleton = TSoftObjectPtr<USkeleton>(FSoftObjectPath(NormalizedObjectPath(Weapon)));
	}
	if (!New.IsEmpty())
	{
		Swap.NewWeaponSkeleton = TSoftObjectPtr<USkeleton>(FSoftObjectPath(NormalizedObjectPath(New)));
	}
	const TArray<TSharedPtr<FJsonValue>>* Sockets = nullptr;
	if (Entry->TryGetArrayField(TEXT("sockets"), Sockets) && Sockets)
	{
		for (const TSharedPtr<FJsonValue>& Item : *Sockets)
		{
			const TSharedPtr<FJsonObject> Object = Item.IsValid() && Item->Type == EJson::Object ? Item->AsObject() : nullptr;
			FEndSocketStandIn Socket;
			Socket.Socket = StringField(Object, TEXT("socket"));
			Socket.Use = StringField(Object, TEXT("use"));
			SocketPlacementFromJson(Object, Socket);   // (1.14)
			if (!Socket.Socket.IsEmpty() && !Socket.Use.IsEmpty())
			{
				Swap.Sockets.Add(Socket);
			}
		}
	}
	Swap.RequiresPaks = CleanList(StringsOf(Entry->TryGetField(TEXT("requires_paks"))), true);
	BoolField(Entry, TEXT("enabled"), Swap.bEnabled);
	return !Swap.NewWeapon.IsEmpty() || Swap.Weapons.Num() > 0;
}

// What a CharaSpec pack of this project loads, from its package dependencies (known even when the game assets they
// name are not in the project), by package short name.
struct FPackContents
{
	bool bInProject = false;
	bool bCooked = false;            // a cooked game copy: it cannot be saved from the editor (make it editable first)
	TArray<FString> Blueprints;      // under /Game/BluePrint/Character/: the character or weapon it spawns
	TArray<FString> Effects;         // *_Effect__Pack
	TArray<FString> SoundSE;         // SE_* sound banks
	TArray<FString> SoundAutoSE;     // AS_* sound banks
	TArray<FString> Voices;          // VO_* banks under /Game/Sound/Voice/ (one name for all languages)
	TArray<FString> LipSyncs;        // LSD_* packs under /Game/LipSync/
	TArray<FString> AIBlueprints;    // under /Game/BluePrint/AI/ (the CharaSpec row's End2AIList)
	TArray<FString> MotionFolders;   // folders of the animation sets it lists, e.g. /Game/Motion/Player/PC0010_Sephiroth
};

FPackContents ReadPack(const FString& Row)
{
	FPackContents Out;
	const FName Package(*PackPackageOf(Row));
	TArray<FAssetData> Assets;
	AssetRegistry().GetAssetsByPackageName(Package, Assets);
	Out.bInProject = Assets.Num() > 0;
	if (!Out.bInProject)
	{
		return Out;
	}
	Out.bCooked = (Assets[0].PackageFlags & PKG_Cooked) != 0;
	TArray<FName> Dependencies;
	AssetRegistry().GetDependencies(Package, Dependencies);
	for (const FName& Dependency : Dependencies)
	{
		const FString Path = Dependency.ToString();
		const FString Name = FPackageName::GetShortName(Path);
		const bool bSound = Path.StartsWith(TEXT("/Game/Sound/"), ESearchCase::IgnoreCase);
		if (Path.StartsWith(TEXT("/Game/BluePrint/Character/"), ESearchCase::IgnoreCase))
		{
			Out.Blueprints.AddUnique(Name);
		}
		else if (Path.StartsWith(TEXT("/Game/BluePrint/AI/"), ESearchCase::IgnoreCase))
		{
			Out.AIBlueprints.AddUnique(Name);
		}
		else if (Name.EndsWith(TEXT("_Effect__Pack"), ESearchCase::IgnoreCase))
		{
			Out.Effects.AddUnique(Name);
		}
		else if (Path.StartsWith(TEXT("/Game/Sound/Voice/"), ESearchCase::IgnoreCase))
		{
			Out.Voices.AddUnique(Name);
		}
		else if (Path.StartsWith(TEXT("/Game/LipSync/"), ESearchCase::IgnoreCase))
		{
			Out.LipSyncs.AddUnique(Name);
		}
		else if (bSound && Name.StartsWith(TEXT("SE_"), ESearchCase::IgnoreCase))
		{
			Out.SoundSE.AddUnique(Name);
		}
		else if (bSound && Name.StartsWith(TEXT("AS_"), ESearchCase::IgnoreCase))
		{
			Out.SoundAutoSE.AddUnique(Name);
		}
		else if (Path.StartsWith(TEXT("/Game/Motion/"), ESearchCase::IgnoreCase))
		{
			Out.MotionFolders.AddUnique(FPackageName::GetLongPackagePath(Path));
		}
	}
	for (TArray<FString>* List : {&Out.Blueprints, &Out.Effects, &Out.SoundSE, &Out.SoundAutoSE, &Out.Voices, &Out.LipSyncs, &Out.AIBlueprints, &Out.MotionFolders})
	{
		List->Sort();
	}
	return Out;
}

// One field Apply To CharaSpec writes into a row.
struct FWeaponFieldChange
{
	const TCHAR* Field = nullptr;
	FString Current; // the field's text now
	FString Value;   // the text Apply writes
};
using FFieldChange = FWeaponFieldChange;

// The items of a field's copy text in order, "None" kept (slots, e.g. Override Weapon Socket Names lined up with the
// equipment list): (None,None,Attach_Tonfa01) or ("A","B").
TArray<FString> SlotsInText(FString Text)
{
	Text.TrimStartAndEndInline();
	Text.RemoveFromStart(TEXT("("));
	Text.RemoveFromEnd(TEXT(")"));
	TArray<FString> Parts;
	Text.ParseIntoArray(Parts, TEXT(","), true);
	TArray<FString> Items;
	for (FString Part : Parts)
	{
		Part.TrimStartAndEndInline();
		Part.TrimQuotesInline();
		Items.Add(Part.IsEmpty() ? FString(TEXT("None")) : Part);
	}
	return Items;
}

// ------------------------------------------------------------------------------------------------
// Game assets for packs to point at (editor 1.7): RebirthGameObjectLibrary of the Rebirth Cooked Asset Preview plugin finds
// them in the game's paks, and for the ones this project does not have it makes in-memory stand-ins (never saved or cooked;
// in game the reference resolves to the game's own asset).
// ------------------------------------------------------------------------------------------------
const TCHAR* const GameObjectLibrary = TEXT("RebirthGameObjectLibrary");
const TCHAR* const GameObjectToolsMissing = TEXT("the Rebirth Cooked Asset Preview plugin of this project has no RebirthGameObjectLibrary yet (it is older than RebirthSkelCompat 1.7): rebuild the editor plugins (Tools\\EndEditorPlugins\\run_build_editor_plugins.cmd)");

bool GameObjectToolsLoaded() { return static_cast<bool>(FDataObjectCall(TEXT("GetGameObject"), GameObjectLibrary)); }

// Packages with this short name in the game's paks, e.g. VO_PC0000_02_Cloud_Insanity (empty without the tools).
TArray<FString> GamePackagesNamed(const FString& ShortName)
{
	FDataObjectCall Call(TEXT("FindGamePackages"), GameObjectLibrary);
	if (!Call || !Call.SetString(TEXT("ShortName"), ShortName))
	{
		return {};
	}
	Call.Run();
	return Call.ResultStrings();
}

// The object path of the game asset ShortName under Folder (with Suffix, _C for a blueprint class), or empty. Of several,
// the one under a /JP/ folder: the game's packs list the Japanese voice and lip sync (the game finds the voice language's).
FString GameObjectPathOf(const FString& ShortName, const TCHAR* Folder, const TCHAR* Suffix = TEXT(""))
{
	FString Best;
	for (const FString& Package : GamePackagesNamed(ShortName))
	{
		if (!Package.StartsWith(Folder, ESearchCase::IgnoreCase))
		{
			continue;
		}
		if (Best.IsEmpty() || (Package.Contains(TEXT("/JP/")) && !Best.Contains(TEXT("/JP/"))))
		{
			Best = Package;
		}
	}
	return Best.IsEmpty() ? FString() : Best + TEXT(".") + ShortName + Suffix;
}

// The game asset at ObjectPath (this project's when it has it, else a stand-in), of the class at ClassPath.
UObject* GameObject(const FString& ObjectPath, const FString& ClassPath, FString& Error)
{
	FDataObjectCall Call(TEXT("GetGameObject"), GameObjectLibrary);
	if (!Call || !Call.SetString(TEXT("ObjectPath"), ObjectPath) || !Call.SetString(TEXT("ClassPath"), ClassPath))
	{
		Error = GameObjectToolsMissing;
		return nullptr;
	}
	Call.Run();
	Error = Call.ResultString(TEXT("Message"));
	return Call.ResultObject();
}

// The folder of a character's kind under /Game/Character, /Game/BluePrint/Character and /Game/Motion: Player (PC...),
// Weapon (WE...), Enemy (EN..., EB...), NonPlayer (NP...).
const TCHAR* KindFolderOf(const FString& Name)
{
	if (Name.StartsWith(TEXT("WE"), ESearchCase::IgnoreCase))
	{
		return TEXT("Weapon");
	}
	if (Name.StartsWith(TEXT("EN"), ESearchCase::IgnoreCase) || Name.StartsWith(TEXT("EB"), ESearchCase::IgnoreCase))
	{
		return TEXT("Enemy");
	}
	if (Name.StartsWith(TEXT("NP"), ESearchCase::IgnoreCase))
	{
		return TEXT("NonPlayer");
	}
	return TEXT("Player");
}

// The skeleton in a model's folder: /Game/Character/<kind>/<model>/Model/<id>_Skeleton.<id>_Skeleton.
FString ModelSkeletonPathOf(const FString& Model)
{
	const FString Skeleton = ModelIdOf(Model) + TEXT("_Skeleton");
	return FString::Printf(TEXT("/Game/Character/%s/%s/Model/%s.%s"), KindFolderOf(Model), *Model, *Skeleton, *Skeleton);
}

// "PC0000_00_Cloud_Standard" -> "PC0000_": what every model and blueprint of that character starts with.
FString CharacterIdOf(const FString& Name)
{
	int32 Underscore = INDEX_NONE;
	return Name.FindChar(TEXT('_'), Underscore) ? Name.Left(Underscore + 1) : Name;
}

bool IsBlueprintOf(const FString& Blueprint, const FString& Character)
{
	return !Character.IsEmpty() && Blueprint.StartsWith(CharacterIdOf(Character), ESearchCase::IgnoreCase);
}

// "PC0000_00_Cloud_Standard" -> "/Game/Motion/Player/PC0000_Cloud": the motion folder named the way the game names them.
FString MotionFolderByName(const FString& Model)
{
	TArray<FString> Parts;
	Model.ParseIntoArray(Parts, TEXT("_"), true);
	return Parts.Num() >= 3 ? FString::Printf(TEXT("/Game/Motion/%s/%s_%s"), KindFolderOf(Model), *Parts[0], *Parts[2]) : FString();
}

// The class path of the blueprint that spawns this CharaSpec row's model (the game names a blueprint like its model's row).
FString BlueprintClassPathOf(const FString& Row)
{
	const FString Found = GameObjectPathOf(Row, TEXT("/Game/BluePrint/Character/"), TEXT("_C"));
	return !Found.IsEmpty() ? Found : FString::Printf(TEXT("/Game/BluePrint/Character/%s/%s.%s_C"), KindFolderOf(Row), *Row, *Row);
}

// "/Game/BluePrint/Character/Player/PC0000_00_Cloud_Standard.PC0000_00_Cloud_Standard_C" -> "PC0000_00_Cloud_Standard"
FString AssetNameOf(const FString& ObjectPath)
{
	FString Name = ShortName(ObjectPath);
	Name.RemoveFromEnd(TEXT("_C"));
	return Name;
}

// ------------------------------------------------------------------------------------------------
// Pack edits (editor 1.7). A CharaSpec pack (CharaSpec_<row>, End Asset Data Asset) spawns the classes in its Asset Class
// List (the character or weapon blueprint, the AI blueprint) and loads the objects in its Asset Data List (motion sets,
// effect packs, sound banks, voice, lip sync, battle camera). A swap points them at the new character or weapon.
// ------------------------------------------------------------------------------------------------
struct FPackEdit
{
	FString Blueprint; // class to spawn in place of its character or weapon blueprint (object path)
	FString Voice;     // voice bank in place of its voice banks
	FString LipSync;   // lip sync in place of its lip syncs
	FString Effect;    // effect pack in place of its effect packs (weapons)
	bool HasWork() const { return !Blueprint.IsEmpty() || !Voice.IsEmpty() || !LipSync.IsEmpty() || !Effect.IsEmpty(); }
};

TArray<FString> PackEditLines(const FPackEdit& Edit, const FPackContents& Pack)
{
	TArray<FString> Lines;
	const auto Was = [](const TArray<FString>& Items) { return Items.Num() > 0 ? FString::Join(Items, TEXT(", ")) : FString(TEXT("nothing")); };
	if (!Edit.Blueprint.IsEmpty())
	{
		Lines.Add(FString::Printf(TEXT("spawn %s (was %s)"), *AssetNameOf(Edit.Blueprint), *Was(Pack.Blueprints)));
	}
	if (!Edit.Voice.IsEmpty())
	{
		Lines.Add(FString::Printf(TEXT("voice %s (was %s)"), *AssetNameOf(Edit.Voice), *Was(Pack.Voices)));
	}
	if (!Edit.LipSync.IsEmpty())
	{
		Lines.Add(FString::Printf(TEXT("lip sync %s (was %s)"), *AssetNameOf(Edit.LipSync), *Was(Pack.LipSyncs)));
	}
	if (!Edit.Effect.IsEmpty())
	{
		Lines.Add(FString::Printf(TEXT("effects %s (was %s)"), *AssetNameOf(Edit.Effect), *Was(Pack.Effects)));
	}
	return Lines;
}

UObject* LoadPack(const FString& Row)
{
	return LoadObject<UObject>(nullptr, *(PackPackageOf(Row) + TEXT(".CharaSpec_") + Row), nullptr, LOAD_NoWarn | LOAD_Quiet);
}

bool InFolder(const UObject* Object, const TCHAR* Folder)
{
	return Object && Object->GetOutermost()->GetName().StartsWith(Folder, ESearchCase::IgnoreCase);
}

bool IsEffectPack(const UObject* Object)
{
	return Object && Object->GetName().EndsWith(TEXT("_Effect__Pack"), ESearchCase::IgnoreCase);
}

// One of a pack's lists (AssetDataList or AssetClassList): each entry's AssetUserData array of objects (classes).
struct FPackList
{
	FArrayProperty* List = nullptr;
	FArrayProperty* Items = nullptr;
	FObjectPropertyBase* Item = nullptr;

	FPackList(UObject* Pack, const TCHAR* Name)
	{
		List = Pack ? FindFProperty<FArrayProperty>(Pack->GetClass(), Name) : nullptr;
		FStructProperty* Entry = List ? CastField<FStructProperty>(List->Inner) : nullptr;
		Items = Entry ? FindFProperty<FArrayProperty>(Entry->Struct, TEXT("AssetUserData")) : nullptr;
		Item = Items ? CastField<FObjectPropertyBase>(Items->Inner) : nullptr;
	}

	explicit operator bool() const { return Item != nullptr; }

	// Every object, entry by entry.
	void ForEach(UObject* Pack, TFunctionRef<void(UObject*)> Visit) const
	{
		FScriptArrayHelper Entries(List, List->ContainerPtrToValuePtr<void>(Pack));
		for (int32 E = 0; E < Entries.Num(); ++E)
		{
			FScriptArrayHelper Objects(Items, Items->ContainerPtrToValuePtr<void>(Entries.GetRawPtr(E)));
			for (int32 I = 0; I < Objects.Num(); ++I)
			{
				Visit(Item->GetObjectPropertyValue(Objects.GetRawPtr(I)));
			}
		}
	}

	// The objects Match picks are replaced by New: in each entry the first one becomes New, the others are taken out.
	int32 Replace(UObject* Pack, TFunctionRef<bool(const UObject*)> Match, UObject* New) const
	{
		int32 Picked = 0;
		FScriptArrayHelper Entries(List, List->ContainerPtrToValuePtr<void>(Pack));
		for (int32 E = 0; E < Entries.Num(); ++E)
		{
			FScriptArrayHelper Objects(Items, Items->ContainerPtrToValuePtr<void>(Entries.GetRawPtr(E)));
			bool bPlaced = false;
			for (int32 I = 0; I < Objects.Num(); ++I)
			{
				bPlaced = bPlaced || Item->GetObjectPropertyValue(Objects.GetRawPtr(I)) == New;
			}
			for (int32 I = 0; I < Objects.Num(); ++I)
			{
				UObject* Current = Item->GetObjectPropertyValue(Objects.GetRawPtr(I));
				if (!Current || Current == New || !Match(Current))
				{
					continue;
				}
				++Picked;
				if (!bPlaced)
				{
					Item->SetObjectPropertyValue(Objects.GetRawPtr(I), New);
					bPlaced = true;
				}
				else
				{
					Objects.RemoveValues(I, 1);
					--I;
				}
			}
		}
		return Picked;
	}
};

// Makes a pack of this project match an edit (the package is marked dirty and added to Dirty; saving is the caller's).
bool ApplyPackEdit(const FString& Row, const FPackEdit& Edit, TArray<UPackage*>& Dirty, FString& Report)
{
	UObject* Pack = LoadPack(Row);
	if (!Pack)
	{
		Report += FString::Printf(TEXT("CharaSpec_%s: ERROR: the pack does not load\n"), *Row);
		return false;
	}
	if (IsCookedAsset(Pack))
	{
		Report += FString::Printf(TEXT("CharaSpec_%s: ERROR: a cooked game copy cannot be saved; make it editable first\n"), *Row);
		return false;
	}
	const FPackList Classes(Pack, TEXT("AssetClassList"));
	const FPackList Datas(Pack, TEXT("AssetDataList"));
	if (!Classes || !Datas)
	{
		Report += FString::Printf(TEXT("CharaSpec_%s: ERROR: %s is not an End Asset Data Asset (no Asset Class List / Asset Data List)\n"), *Row, *Pack->GetClass()->GetName());
		return false;
	}
	bool bOk = true;
	bool bModified = false;
	const auto Put = [&](const FString& Path, const FPackList& List, const TCHAR* What, TFunctionRef<bool(const UObject*)> Match)
	{
		if (Path.IsEmpty())
		{
			return;
		}
		// The new asset is one of a kind with what it replaces.
		UObject* Old = nullptr;
		List.ForEach(Pack, [&](UObject* Object) { if (!Old && Object && Match(Object)) { Old = Object; } });
		if (!Old)
		{
			Report += FString::Printf(TEXT("CharaSpec_%s: no %s to replace\n"), *Row, What);
			return;
		}
		FString Error;
		UObject* New = GameObject(Path, Old->GetClass()->GetPathName(), Error);
		if (!New)
		{
			Report += FString::Printf(TEXT("CharaSpec_%s: ERROR: %s %s not set: %s\n"), *Row, What, *Path, Error.IsEmpty() ? TEXT("not found") : *Error);
			bOk = false;
			return;
		}
		if (!bModified)
		{
			Pack->Modify();
			bModified = true;
		}
		const int32 Picked = List.Replace(Pack, Match, New);
		Report += FString::Printf(TEXT("CharaSpec_%s: %s %s (in place of %d)\n"), *Row, What, *New->GetPathName(), Picked);
	};
	Put(Edit.Blueprint, Classes, TEXT("blueprint"), [](const UObject* Object) { return InFolder(Object, TEXT("/Game/BluePrint/Character/")); });
	Put(Edit.Voice, Datas, TEXT("voice"), [](const UObject* Object) { return InFolder(Object, TEXT("/Game/Sound/Voice/")); });
	Put(Edit.LipSync, Datas, TEXT("lip sync"), [](const UObject* Object) { return InFolder(Object, TEXT("/Game/LipSync/")); });
	Put(Edit.Effect, Datas, TEXT("effect pack"), [](const UObject* Object) { return IsEffectPack(Object); });
	if (bModified)
	{
		Pack->PostEditChange();
		Pack->MarkPackageDirty();
		Dirty.AddUnique(Pack->GetOutermost());
	}
	return bOk;
}

// ------------------------------------------------------------------------------------------------
// Weapon swaps (editor 1.6; packs and socket stand-ins 1.7)
// ------------------------------------------------------------------------------------------------
struct FWeaponRowPlan
{
	FString Row;
	bool bNamed = false;     // named in Weapons itself, not only through a name ending in *
	FPackContents Pack;      // the pack as it is
	FPackContents After;     // the pack once Apply has edited it
	FPackEdit Edit;
	bool bSpawnsNew = false; // its pack spawns the new weapon's blueprint (once edited)
	TArray<FString> Notes;
	TArray<FWeaponFieldChange> Changes;
};

struct FWeaponSwapPlan
{
	FString NewWeapon;         // CharaSpec row
	FString NewModel;          // its model: a weapon's model and blueprint are named like its row
	FString NewRowModel;       // what the new weapon's own row says now (another swap may have changed it)
	FString Error;             // the swap cannot be applied
	TArray<FString> Unknown;   // Weapons entries that name no row
	TArray<FString> RowNames;  // the replaced rows
	TArray<FWeaponRowPlan> Rows;
	FString WeaponSkeleton;    // the family's member (object path)
	FString NewWeaponSkeleton; // the family's hub (object path)
	bool bWeaponSkeletonFromFolder = false;
	bool bNewSkeletonFromFolder = false;
};

// The rows a swap replaces: exact row names (also put in Named), or every row that starts with a name ending in * (never
// the new one).
TArray<FString> SwapRowsOf(const TArray<FString>& Items, const FString& New, const FCharaSpecTable& Table, TArray<FString>& Unknown, TArray<FString>& Named)
{
	TArray<FString> Rows;
	for (const FString& Item : CleanList(Items, false))
	{
		if (Item.EndsWith(TEXT("*")))
		{
			const FString Prefix = Item.LeftChop(1).TrimStartAndEnd();
			int32 Found = 0;
			for (const FName& Name : Table.Rows)
			{
				const FString Row = Name.ToString();
				if (!Prefix.IsEmpty() && Row.StartsWith(Prefix, ESearchCase::IgnoreCase) && !Row.Equals(New, ESearchCase::IgnoreCase))
				{
					Rows.AddUnique(Row);
					++Found;
				}
			}
			if (Found == 0)
			{
				Unknown.Add(Item);
			}
			continue;
		}
		const FString Row = CharaSpecRowName(Item);
		if (Row.IsEmpty() || (Table.bAvailable && !Table.Has(Row)))
		{
			Unknown.Add(Item);
			continue;
		}
		if (!Row.Equals(New, ESearchCase::IgnoreCase))
		{
			Rows.AddUnique(Row);
			Named.AddUnique(Row);
		}
	}
	Rows.Sort();
	return Rows;
}

// bRows: also read each replaced weapon's pack and work out what Apply writes into it and its row. bPackEdits: Apply may
// edit the packs (Apply To Packs on).
FWeaponSwapPlan PlanWeaponSwap(const FEndWeaponSwap& Swap, const FCharaSpecTable& Table, bool bRows, bool bPackEdits)
{
	FWeaponSwapPlan Plan;
	Plan.NewWeapon = CharaSpecRowName(Swap.NewWeapon);
	if (Plan.NewWeapon.IsEmpty())
	{
		Plan.Error = TEXT("New Weapon is empty: name the CharaSpec row of the weapon that takes their place, e.g. WE0011_00_Vincent_Quiksilver");
	}
	else if (Table.bAvailable && !Table.Has(Plan.NewWeapon))
	{
		Plan.Error = Plan.NewWeapon + TEXT(" is not a row of ") + Table.Package;
	}
	// The game names a weapon's model (and its blueprint) like its CharaSpec row. The row itself is not asked: another
	// swap may have changed it (Cloud's Buster Sword row describing Vincent's gun, while Sephiroth's Masamune becomes the
	// Buster Sword).
	Plan.NewModel = Plan.NewWeapon;
	if (Plan.Error.IsEmpty() && Table.bAvailable)
	{
		Plan.NewRowModel = Table.Field(Plan.NewWeapon, TEXT("ContentsModel"));
	}
	TArray<FString> Named;
	Plan.RowNames = SwapRowsOf(Swap.Weapons, Plan.NewWeapon, Table, Plan.Unknown, Named);

	// Skeletons of the cutscene family: as set, or the ones in the model folders.
	if (!Swap.NewWeaponSkeleton.IsNull())
	{
		Plan.NewWeaponSkeleton = SoftPath(Swap.NewWeaponSkeleton);
	}
	else if (!Plan.NewModel.IsEmpty())
	{
		Plan.NewWeaponSkeleton = WeaponSkeletonPathOf(Plan.NewModel);
		Plan.bNewSkeletonFromFolder = true;
	}
	if (!Swap.WeaponSkeleton.IsNull())
	{
		Plan.WeaponSkeleton = SoftPath(Swap.WeaponSkeleton);
	}
	else
	{
		// The base weapon (id ending in _00) has the skeleton its variants share: WE0000_00's for every one of Cloud's.
		FString Base;
		for (const FString& Row : Plan.RowNames)
		{
			if (ModelIdOf(Row).EndsWith(TEXT("_00")))
			{
				Base = Row;
				break;
			}
		}
		if (Base.IsEmpty() && Plan.RowNames.Num() > 0)
		{
			Base = Plan.RowNames[0];
		}
		if (!Base.IsEmpty())
		{
			Plan.WeaponSkeleton = WeaponSkeletonPathOf(Base);
			Plan.bWeaponSkeletonFromFolder = true;
		}
	}
	if (!bRows || !Plan.Error.IsEmpty() || !Table.bAvailable)
	{
		return Plan;
	}
	const bool bTools = bPackEdits && GameObjectToolsLoaded();
	FString NewBlueprint;  // looked up once
	FString NewEffect;
	bool bEffectLooked = false;
	for (const FString& Row : Plan.RowNames)
	{
		FWeaponRowPlan RowPlan;
		RowPlan.Row = Row;
		RowPlan.bNamed = Named.Contains(Row);
		RowPlan.Pack = ReadPack(Row);
		RowPlan.After = RowPlan.Pack;
		RowPlan.bSpawnsNew = RowPlan.Pack.Blueprints.ContainsByPredicate([&](const FString& Blueprint) { return Blueprint.Equals(Plan.NewWeapon, ESearchCase::IgnoreCase); });
		const bool bEditable = RowPlan.Pack.bInProject && !RowPlan.Pack.bCooked;
		if (!RowPlan.bSpawnsNew && bEditable && bPackEdits)
		{
			if (!bTools)
			{
				RowPlan.Notes.Add(GameObjectToolsMissing);
			}
			else
			{
				if (NewBlueprint.IsEmpty())
				{
					NewBlueprint = BlueprintClassPathOf(Plan.NewWeapon);
				}
				RowPlan.Edit.Blueprint = NewBlueprint;
				RowPlan.After.Blueprints = {Plan.NewWeapon};
				RowPlan.bSpawnsNew = true;
			}
		}
		// The new weapon's own effects in place of the old weapon's (the effect pack is named like the weapon's row).
		const FString EffectName = Plan.NewWeapon + TEXT("_Effect__Pack");
		if (RowPlan.bSpawnsNew && bEditable && bTools && RowPlan.Pack.Effects.Num() > 0 &&
			!(RowPlan.Pack.Effects.Num() == 1 && RowPlan.Pack.Effects[0].Equals(EffectName, ESearchCase::IgnoreCase)))
		{
			if (!bEffectLooked)
			{
				NewEffect = GameObjectPathOf(EffectName, TEXT("/Game/Effect/"));
				bEffectLooked = true;
			}
			if (!NewEffect.IsEmpty())
			{
				RowPlan.Edit.Effect = NewEffect;
				RowPlan.After.Effects = {EffectName};
			}
			else
			{
				RowPlan.Notes.Add(FString::Printf(TEXT("the game has no %s: the pack keeps loading %s"), *EffectName, *FString::Join(RowPlan.Pack.Effects, TEXT(", "))));
			}
		}
		if (RowPlan.bSpawnsNew)
		{
			const FString Model = Table.Field(Row, TEXT("ContentsModel"));
			if (!Model.Equals(Plan.NewModel, ESearchCase::IgnoreCase))
			{
				RowPlan.Changes.Add({TEXT("ContentsModel"), Model, Plan.NewModel});
			}
			// The new weapon's own spec loads alongside (as SephirothOverCloud does it), unless another swap made that spec
			// load a different weapon.
			const bool bNewRowIsItself = Plan.NewRowModel.IsEmpty() || Plan.NewRowModel.Equals(Plan.NewWeapon, ESearchCase::IgnoreCase) ||
				Plan.NewRowModel.Equals(TEXT("None"), ESearchCase::IgnoreCase);
			const FString SharedText = Table.Field(Row, TEXT("SharedCharaSpecList_Array"));
			TArray<FString> Shared = NamesInText(SharedText);
			if (bNewRowIsItself && !Shared.Contains(Plan.NewWeapon))
			{
				Shared.Add(Plan.NewWeapon);
				RowPlan.Changes.Add({TEXT("SharedCharaSpecList_Array"), SharedText, ArrayText(Shared)});
			}
			struct FLoaded
			{
				const TCHAR* Field;
				const TArray<FString>* Items;
			};
			const FLoaded Loaded[] = {
				{TEXT("ContentsEffect_Array"), &RowPlan.After.Effects},
				{TEXT("ContentsSoundSE_Array"), &RowPlan.After.SoundSE},
				{TEXT("ContentsSoundAutoSE_Array"), &RowPlan.After.SoundAutoSE},
			};
			for (const FLoaded& Field : Loaded)
			{
				const FString Text = Table.Field(Row, Field.Field);
				if (!SameNames(NamesInText(Text), *Field.Items))
				{
					RowPlan.Changes.Add({Field.Field, Text, ArrayText(*Field.Items)});
				}
			}
		}
		Plan.Rows.Add(MoveTemp(RowPlan));
	}
	return Plan;
}

// A row matched only through a name ending in * whose pack is the game's own: the swap does not include that weapon.
bool LeftOut(const FWeaponRowPlan& Row) { return !Row.bNamed && !Row.Pack.bInProject; }

// Why a replaced weapon's row is left as it is, or empty when Apply can write it.
FString WeaponRowProblem(const FWeaponRowPlan& Row, const FString& NewWeapon)
{
	if (!Row.Pack.bInProject)
	{
		return FString::Printf(TEXT("CharaSpec_%s is not in this project, so the game's own pack spawns the old weapon. Make that pack editable in this project, then press Apply To CharaSpec again"),
			*Row.Row);
	}
	if (!Row.bSpawnsNew)
	{
		if (Row.Pack.bCooked)
		{
			return FString::Printf(TEXT("CharaSpec_%s in this project is a cooked game copy, which cannot be saved: make it editable first"), *Row.Row);
		}
		return FString::Printf(TEXT("its pack spawns %s, not %s. Set Asset Class List > 0 > Asset User Data of CharaSpec_%s to %s_C (or turn Apply To Packs on)"),
			Row.Pack.Blueprints.Num() > 0 ? *FString::Join(Row.Pack.Blueprints, TEXT(", ")) : TEXT("no blueprint"), *NewWeapon, *Row.Row, *NewWeapon);
	}
	return FString();
}

// Report lines for a weapon's socket stand-ins: the old weapon's sockets the new one lacks, and each stand-in's socket.
void ReportWeaponSockets(const FEndWeaponSwap& Swap, const FWeaponSwapPlan& Plan, FString& Report, bool& bOk)
{
	USkeleton* New = Plan.NewWeaponSkeleton.IsEmpty() ? nullptr : Cast<USkeleton>(FSoftObjectPath(Plan.NewWeaponSkeleton).TryLoad());
	USkeleton* Old = Plan.WeaponSkeleton.IsEmpty() ? nullptr : Cast<USkeleton>(FSoftObjectPath(Plan.WeaponSkeleton).TryLoad());
	if (Old && New && Old != New)
	{
		TArray<FString> Lacks;
		for (const USkeletalMeshSocket* Socket : Old->Sockets)
		{
			if (Socket && !New->FindSocket(Socket->SocketName) && New->GetReferenceSkeleton().FindBoneIndex(Socket->SocketName) == INDEX_NONE &&
				!Swap.Sockets.ContainsByPredicate([&](const FEndSocketStandIn& Mine) { return Mine.Socket.TrimStartAndEnd().Equals(Socket->SocketName.ToString(), ESearchCase::IgnoreCase); }))
			{
				Lacks.Add(Socket->SocketName.ToString());
			}
		}
		if (Lacks.Num() > 0)
		{
			Report += FString::Printf(TEXT("    sockets of %s that %s lacks (moves made for the old weapon that hit with them do no damage; give each a stand-in under Sockets): %s\n"),
				*Old->GetName(), *New->GetName(), *ListText(Lacks));
		}
	}
	else if (!Old && Swap.Sockets.Num() == 0)
	{
		Report += FString::Printf(TEXT("    note: %s is not in this project, so its sockets are not compared (moves that hit with sockets the new weapon lacks need Sockets stand-ins)\n"),
			Plan.WeaponSkeleton.IsEmpty() ? TEXT("the old weapon's skeleton") : *ShortName(Plan.WeaponSkeleton));
	}
	for (const FEndSocketStandIn& Socket : Swap.Sockets)
	{
		const FString Wanted = Socket.Socket.TrimStartAndEnd();
		const FString Use = Socket.Use.TrimStartAndEnd();
		if (Wanted.IsEmpty() || Use.IsEmpty())
		{
			Report += TEXT("    WARNING: a socket stand-in without Socket or Use is left out\n");
			continue;
		}
		FString State = TEXT("checked in game");
		if (New)
		{
			if (const USkeletalMeshSocket* Found = New->FindSocket(FName(*Use)))
			{
				State = TEXT("socket on bone ") + Found->BoneName.ToString();
			}
			else if (New->GetReferenceSkeleton().FindBoneIndex(FName(*Use)) != INDEX_NONE)
			{
				State = TEXT("a bone");
			}
			else
			{
				State = TEXT("WARNING: neither a socket nor a bone of ") + New->GetName() + TEXT(" (a socket only the mesh has still works)");
			}
		}
		Report += FString::Printf(TEXT("    socket stand-in (Export Json): %s -> %s (%s)\n"), *Wanted, *Use, *State);
		if (Wanted.Equals(Use, ESearchCase::IgnoreCase))
		{
			Report += TEXT("    WARNING: a socket cannot stand in for itself; this one is left out\n");
		}
	}
	if (Swap.Sockets.Num() > 0 && Plan.NewWeaponSkeleton.IsEmpty())
	{
		Report += TEXT("    ERROR: socket stand-ins need New Weapon Skeleton (Advanced)\n");
		bOk = false;
	}
}

bool CheckWeaponSwap(const FEndWeaponSwap& Swap, int32 Index, const FCharaSpecTable& Table, bool bPackEdits, FString& Report)
{
	Report += FString::Printf(TEXT("Weapon swap %d: %s -> %s\n"), Index, *ListText(CleanList(Swap.Weapons, false)), *Swap.NewWeapon.TrimStartAndEnd());
	if (!Swap.bEnabled)
	{
		Report += TEXT("    disabled\n");
		return true;
	}
	bool bOk = true;
	const FWeaponSwapPlan Plan = PlanWeaponSwap(Swap, Table, true, bPackEdits);
	if (!Plan.Error.IsEmpty())
	{
		Report += TEXT("    ERROR: ") + Plan.Error + TEXT("\n");
		bOk = false;
	}
	for (const FString& Item : Plan.Unknown)
	{
		Report += FString::Printf(TEXT("    WARNING: %s names no row of %s\n"), *Item, *Table.Package);
	}
	if (!Table.bAvailable)
	{
		Report += TEXT("    note: the Rebirth data object tools (Rebirth Cooked Asset Preview plugin) are not loaded, so the CharaSpec rows and packs are not checked\n");
	}
	else if (Plan.Error.IsEmpty())
	{
		Report += FString::Printf(TEXT("    new weapon: blueprint and model %s\n"), *Plan.NewModel);
		if (!Plan.NewRowModel.IsEmpty() && !Plan.NewRowModel.Equals(Plan.NewWeapon, ESearchCase::IgnoreCase))
		{
			Report += FString::Printf(TEXT("    note: %s's own row describes %s now (another swap); the replaced weapons still get %s's own model\n"),
				*Plan.NewWeapon, *Plan.NewRowModel, *Plan.NewWeapon);
		}
		if (Plan.RowNames.Num() == 0)
		{
			Report += TEXT("    ERROR: no weapon rows to replace (Weapons)\n");
			bOk = false;
		}
		int32 Swapped = 0;
		for (const FWeaponRowPlan& Row : Plan.Rows)
		{
			if (LeftOut(Row))
			{
				Report += FString::Printf(TEXT("    %s: left out (its pack is the game's own, so it stays the old weapon)\n"), *Row.Row);
				continue;
			}
			for (const FString& Note : Row.Notes)
			{
				Report += FString::Printf(TEXT("    %s: note: %s\n"), *Row.Row, *Note);
			}
			const FString Problem = WeaponRowProblem(Row, Plan.NewWeapon);
			if (!Problem.IsEmpty())
			{
				Report += FString::Printf(TEXT("    %s: ERROR: %s\n"), *Row.Row, *Problem);
				bOk = false;
				continue;
			}
			++Swapped;
			if (Row.Edit.HasWork())
			{
				Report += FString::Printf(TEXT("    %s: Apply To CharaSpec makes its pack %s\n"), *Row.Row, *FString::Join(PackEditLines(Row.Edit, Row.Pack), TEXT("; ")));
			}
			TArray<FString> Loads = Row.After.Effects;
			Loads.Append(Row.After.SoundSE);
			Loads.Append(Row.After.SoundAutoSE);
			const FString Spawns = FString::Printf(TEXT("pack spawns %s%s%s"), *Plan.NewWeapon, Loads.Num() > 0 ? TEXT(" and loads ") : TEXT(""), *FString::Join(Loads, TEXT(", ")));
			if (Row.Changes.Num() == 0)
			{
				Report += FString::Printf(TEXT("    %s: %s; the row describes it\n"), *Row.Row, *Spawns);
				continue;
			}
			Report += FString::Printf(TEXT("    %s: %s, but the row still describes the old weapon: press Apply To CharaSpec\n"), *Row.Row, *Spawns);
			for (const FWeaponFieldChange& Change : Row.Changes)
			{
				Report += FString::Printf(TEXT("        %s: %s -> %s\n"), Change.Field, *FieldShown(Change.Field, Change.Current), *FieldShown(Change.Field, Change.Value));
			}
		}
		if (Plan.RowNames.Num() > 0 && Swapped == 0 && bOk)
		{
			Report += TEXT("    ERROR: none of these weapons' packs is in this project, so none of them spawns the new weapon\n");
			bOk = false;
		}
	}
	if (Swap.bCutsceneFamily)
	{
		if (Plan.NewWeaponSkeleton.IsEmpty() || Plan.WeaponSkeleton.IsEmpty())
		{
			Report += TEXT("    ERROR: cutscene family: the skeletons are not known; set Weapon Skeleton and New Weapon Skeleton (Advanced)\n");
			bOk = false;
		}
		else if (SamePath(Plan.NewWeaponSkeleton, Plan.WeaponSkeleton))
		{
			Report += TEXT("    cutscene family: not needed, both weapons are on ") + ShortName(Plan.NewWeaponSkeleton) + TEXT("\n");
		}
		else
		{
			Report += FString::Printf(TEXT("    cutscene family (Export Json): hub %s%s, member %s%s\n"), *Plan.NewWeaponSkeleton,
				Plan.bNewSkeletonFromFolder ? TEXT(" (its model folder's)") : TEXT(""), *Plan.WeaponSkeleton,
				Plan.bWeaponSkeletonFromFolder ? TEXT(" (the model folder's of the base weapon; set Weapon Skeleton if its cutscene animations use another)") : TEXT(""));
		}
	}
	ReportWeaponSockets(Swap, Plan, Report, bOk);
	return bOk;
}

// The weapon family a swap adds to the JSON, or null.
TSharedPtr<FJsonObject> WeaponFamilyJson(const FEndWeaponSwap& Swap, const FCharaSpecTable& Table)
{
	if (!Swap.bEnabled || !Swap.bCutsceneFamily)
	{
		return nullptr;
	}
	const FWeaponSwapPlan Plan = PlanWeaponSwap(Swap, Table, false, false);
	if (Plan.NewWeaponSkeleton.IsEmpty() || Plan.WeaponSkeleton.IsEmpty() || SamePath(Plan.NewWeaponSkeleton, Plan.WeaponSkeleton))
	{
		return nullptr;
	}
	TSharedRef<FJsonObject> Entry = MakeShared<FJsonObject>();
	Entry->SetStringField(TEXT("receiving_skeleton"), NormalizedObjectPath(Plan.NewWeaponSkeleton));
	Entry->SetArrayField(TEXT("animation_skeletons"), JsonStrings({NormalizedObjectPath(Plan.WeaponSkeleton)}));
	Entry->SetStringField(TEXT("method"), TEXT("family"));
	Entry->SetStringField(TEXT("hub"), NormalizedObjectPath(Plan.NewWeaponSkeleton));
	const TArray<FString> Requires = CleanList(Swap.RequiresPaks, true);
	if (Requires.Num() > 0)
	{
		Entry->SetArrayField(TEXT("requires_paks"), JsonStrings(Requires));
	}
	// The data object makes this entry from the swap again on every export (Import From Game Json skips it).
	Entry->SetStringField(TEXT("from_weapon_swap"), Plan.NewWeapon.IsEmpty() ? Swap.NewWeapon.TrimStartAndEnd() : Plan.NewWeapon);
	Entry->SetBoolField(TEXT("enabled"), true);
	return Entry;
}

// The animation set row with a weapon swap's socket stand-ins (on the new weapon's meshes), or null.
TSharedPtr<FJsonObject> WeaponSocketsJson(const FEndWeaponSwap& Swap, const FCharaSpecTable& Table)
{
	if (!Swap.bEnabled)
	{
		return nullptr;
	}
	TArray<TSharedPtr<FJsonValue>> Sockets;
	for (const FEndSocketStandIn& Socket : Swap.Sockets)
	{
		const FString Wanted = Socket.Socket.TrimStartAndEnd();
		const FString Use = Socket.Use.TrimStartAndEnd();
		if (!Wanted.IsEmpty() && !Use.IsEmpty() && (!Wanted.Equals(Use, ESearchCase::IgnoreCase) || HasPlacement(Socket)))
		{
			Sockets.Add(MakeShared<FJsonValueObject>(SocketStandInToJson(Socket)));   // (1.14: with its placement)
		}
	}
	const FWeaponSwapPlan Plan = PlanWeaponSwap(Swap, Table, false, false);
	if (Sockets.Num() == 0 || Plan.NewWeaponSkeleton.IsEmpty())
	{
		return nullptr;
	}
	// The mod puts a row's sockets on the meshes of its "skeleton"; its characters only have to be CharaSpec rows.
	TArray<FString> Characters = Plan.RowNames;
	if (Characters.Num() == 0 && !Plan.NewWeapon.IsEmpty())
	{
		Characters.Add(Plan.NewWeapon);
	}
	if (Characters.Num() == 0)
	{
		return nullptr;
	}
	TSharedRef<FJsonObject> Entry = MakeShared<FJsonObject>();
	Entry->SetArrayField(TEXT("characters"), JsonStrings(Characters));
	Entry->SetStringField(TEXT("skeleton"), NormalizedObjectPath(Plan.NewWeaponSkeleton));
	Entry->SetArrayField(TEXT("sockets"), Sockets);
	const TArray<FString> Requires = CleanList(Swap.RequiresPaks, true);
	if (Requires.Num() > 0)
	{
		Entry->SetArrayField(TEXT("requires_paks"), JsonStrings(Requires));
	}
	Entry->SetStringField(TEXT("from_weapon_swap"), Plan.NewWeapon.IsEmpty() ? Swap.NewWeapon.TrimStartAndEnd() : Plan.NewWeapon);
	Entry->SetBoolField(TEXT("enabled"), true);
	return Entry;
}

// ------------------------------------------------------------------------------------------------
// Character swaps (editor 1.7): another character in some CharaSpec rows' place (Cloud in Sephiroth's). Each replaced
// row's pack spawns the new character's blueprint and loads its voice; the row describes what its pack spawns and loads
// (model, voice, effects, sounds, AI), shares his spec, and holds his weapon where Weapon Socket says. The two skeletons
// become a family, and the rows' animation sets come from both characters' motion folders, the moveset's first.
// ------------------------------------------------------------------------------------------------
const TCHAR* MovesetText(EEndSwapMoveset Moveset) { return Moveset == EEndSwapMoveset::NewCharacter ? TEXT("new") : TEXT("replaced"); }

EEndSwapMoveset ParseMoveset(const FString& Text)
{
	for (const TCHAR* Own : {TEXT("new"), TEXT("new_character"), TEXT("own"), TEXT("his"), TEXT("hers")})
	{
		if (Text.TrimStartAndEnd().Equals(Own, ESearchCase::IgnoreCase))
		{
			return EEndSwapMoveset::NewCharacter;
		}
	}
	return EEndSwapMoveset::Replaced;
}

TSharedRef<FJsonObject> CharacterSwapToJson(const FEndCharacterSwap& Swap)
{
	TSharedRef<FJsonObject> Entry = MakeShared<FJsonObject>();
	Entry->SetArrayField(TEXT("characters"), JsonStrings(CleanList(Swap.Characters, false)));
	Entry->SetStringField(TEXT("new_character"), Swap.NewCharacter.TrimStartAndEnd());
	Entry->SetStringField(TEXT("moveset"), MovesetText(Swap.Moveset));
	if (!Swap.Voice.TrimStartAndEnd().IsEmpty())
	{
		Entry->SetStringField(TEXT("voice"), Swap.Voice.TrimStartAndEnd());
	}
	if (!Swap.WeaponSocket.TrimStartAndEnd().IsEmpty())
	{
		Entry->SetStringField(TEXT("weapon_socket"), Swap.WeaponSocket.TrimStartAndEnd());
	}
	Entry->SetBoolField(TEXT("proportions"), Swap.bKeepProportions);
	if (!Swap.ReplacedSkeleton.IsNull())
	{
		Entry->SetStringField(TEXT("replaced_skeleton"), SoftPath(Swap.ReplacedSkeleton));
	}
	if (!Swap.NewSkeleton.IsNull())
	{
		Entry->SetStringField(TEXT("new_skeleton"), SoftPath(Swap.NewSkeleton));
	}
	const TArray<FString> Requires = CleanList(Swap.RequiresPaks, true);
	if (Requires.Num() > 0)
	{
		Entry->SetArrayField(TEXT("requires_paks"), JsonStrings(Requires));
	}
	Entry->SetBoolField(TEXT("enabled"), Swap.bEnabled);
	return Entry;
}

bool CharacterSwapFromJson(const TSharedPtr<FJsonObject>& Entry, FEndCharacterSwap& Swap)
{
	if (!Entry.IsValid())
	{
		return false;
	}
	Swap.Characters = CleanList(StringsOf(Entry->TryGetField(TEXT("characters"))), false);
	Swap.NewCharacter = StringField(Entry, TEXT("new_character"));
	Swap.Moveset = ParseMoveset(StringField(Entry, TEXT("moveset")));
	Swap.Voice = StringField(Entry, TEXT("voice"));
	Swap.WeaponSocket = StringField(Entry, TEXT("weapon_socket"));
	for (const TCHAR* Key : {TEXT("proportions"), TEXT("keep_proportions")})
	{
		BoolField(Entry, Key, Swap.bKeepProportions);
	}
	const FString Replaced = StringField(Entry, TEXT("replaced_skeleton"));
	const FString New = StringField(Entry, TEXT("new_skeleton"));
	if (!Replaced.IsEmpty())
	{
		Swap.ReplacedSkeleton = TSoftObjectPtr<USkeleton>(FSoftObjectPath(NormalizedObjectPath(Replaced)));
	}
	if (!New.IsEmpty())
	{
		Swap.NewSkeleton = TSoftObjectPtr<USkeleton>(FSoftObjectPath(NormalizedObjectPath(New)));
	}
	Swap.RequiresPaks = CleanList(StringsOf(Entry->TryGetField(TEXT("requires_paks"))), true);
	BoolField(Entry, TEXT("enabled"), Swap.bEnabled);
	return !Swap.NewCharacter.IsEmpty() || Swap.Characters.Num() > 0;
}

// The same swap as far as Import From Game Json matches them: the same new character, and a replaced row in common.
bool SameCharacterSwap(const FEndCharacterSwap& A, const FEndCharacterSwap& B)
{
	if (!CharaSpecRowName(A.NewCharacter).Equals(CharaSpecRowName(B.NewCharacter), ESearchCase::IgnoreCase))
	{
		return false;
	}
	const TArray<FString> Theirs = CleanList(B.Characters, false);
	for (const FString& Mine : CleanList(A.Characters, false))
	{
		if (Theirs.Contains(Mine))
		{
			return true;
		}
	}
	return A.Characters.Num() == 0 || B.Characters.Num() == 0;
}

struct FCharacterRowPlan
{
	FString Row;
	bool bNamed = false;           // named in Characters itself, not only through a name ending in *
	FPackContents Pack;            // the pack as it is
	FPackContents After;           // the pack once Apply has edited it
	FPackEdit Edit;
	TArray<FString> Folders;       // the replaced character's motion folders for this row
	FString Problem;               // why Apply leaves the row as it is (empty: it can write it)
	TArray<FString> Notes;
	TArray<FFieldChange> Changes;
};

struct FCharacterSwapPlan
{
	FString NewCharacter;          // CharaSpec row
	FString Error;                 // the swap cannot be applied
	TArray<FString> Unknown;       // Characters entries that name no row
	TArray<FString> RowNames;      // the replaced rows
	TArray<FCharacterRowPlan> Rows;
	FString ReplacedId;            // "PC0010_": the replaced character's models and blueprints start with it
	FString ReplacedSkeleton;      // object paths
	FString NewSkeleton;
	bool bReplacedSkeletonFromFolder = false;
	bool bNewSkeletonFromFolder = false;
	TArray<FString> NewFolders;    // the new character's motion folders
	FString NewFoldersFrom;        // where they come from (for the report)
	FString FieldActions;          // AnimationSetParentFolder for his own moveset, e.g. PC0000_Cloud
	FString NewSpec;               // his row that goes into the Shared CharaSpec Lists (empty: none)
	FString NewSpecNote;
	FString VoiceName, VoicePath;  // the swap's voice and where the game has it
	FString LipSyncName, LipSyncPath;
	TArray<FString> Equipment;     // the weapons the replaced rows equip
};

// A row of his that still describes him: its model is his, and its pack (when this project has it) spawns him.
bool RowDescribes(const FString& Row, const FString& Character, const FCharaSpecTable& Table)
{
	if (!Table.Has(Row) || !Table.Field(Row, TEXT("ContentsModel")).Equals(Character, ESearchCase::IgnoreCase))
	{
		return false;
	}
	const FPackContents Pack = ReadPack(Row);
	return !Pack.bInProject || Pack.Blueprints.ContainsByPredicate([&](const FString& Blueprint) { return IsBlueprintOf(Blueprint, Character); });
}

// The motion folders a row's pack lists sets of, else the row's field-action folder.
TArray<FString> RowFoldersOf(const FString& Row, const FPackContents& Pack, const FCharaSpecTable& Table)
{
	if (Pack.MotionFolders.Num() > 0)
	{
		return Pack.MotionFolders;
	}
	const FString Folder = Table.bAvailable ? Table.Field(Row, TEXT("AnimationSetParentFolder")) : FString();
	if (!Folder.IsEmpty() && !Folder.Equals(TEXT("None"), ESearchCase::IgnoreCase))
	{
		return {FString::Printf(TEXT("/Game/Motion/%s/%s"), KindFolderOf(Row), *Folder)};
	}
	return {};
}

// bRows: also work out what Apply To CharaSpec does to each replaced row and its pack. bPackEdits: Apply may edit packs.
FCharacterSwapPlan PlanCharacterSwap(const FEndCharacterSwap& Swap, const FCharaSpecTable& Table, bool bRows, bool bPackEdits)
{
	FCharacterSwapPlan Plan;
	Plan.NewCharacter = CharaSpecRowName(Swap.NewCharacter);
	if (Plan.NewCharacter.IsEmpty())
	{
		Plan.Error = TEXT("New Character is empty: name the CharaSpec row of the character that takes their place, e.g. PC0000_00_Cloud_Standard");
	}
	else if (Table.bAvailable && !Table.Has(Plan.NewCharacter))
	{
		Plan.Error = Plan.NewCharacter + TEXT(" is not a row of ") + Table.Package;
	}
	TArray<FString> Named;
	Plan.RowNames = SwapRowsOf(Swap.Characters, Plan.NewCharacter, Table, Plan.Unknown, Named);
	// Rows of the new character himself are never replaced by him.
	Plan.RowNames.RemoveAll([&](const FString& Row) { return IsBlueprintOf(Row, Plan.NewCharacter); });
	FString Base;
	for (const FString& Row : Plan.RowNames)
	{
		if (Named.Contains(Row) && ModelIdOf(Row).EndsWith(TEXT("_00")))
		{
			Base = Row;
			break;
		}
	}
	for (const FString& Row : Plan.RowNames)
	{
		if (Base.IsEmpty() && ModelIdOf(Row).EndsWith(TEXT("_00")))
		{
			Base = Row;
		}
	}
	if (Base.IsEmpty() && Plan.RowNames.Num() > 0)
	{
		Base = Plan.RowNames[0];
	}
	Plan.ReplacedId = Base.IsEmpty() ? FString() : CharacterIdOf(Base);
	if (!Swap.ReplacedSkeleton.IsNull())
	{
		Plan.ReplacedSkeleton = SoftPath(Swap.ReplacedSkeleton);
	}
	else if (!Base.IsEmpty())
	{
		Plan.ReplacedSkeleton = ModelSkeletonPathOf(Base);
		Plan.bReplacedSkeletonFromFolder = true;
	}
	if (!Swap.NewSkeleton.IsNull())
	{
		Plan.NewSkeleton = SoftPath(Swap.NewSkeleton);
	}
	else if (!Plan.NewCharacter.IsEmpty())
	{
		Plan.NewSkeleton = ModelSkeletonPathOf(Plan.NewCharacter);
		Plan.bNewSkeletonFromFolder = true;
	}
	// His motion folders: what his own pack lists, else his row's field-action folder while it still describes him, else
	// the folder named the way the game names them.
	if (!Plan.NewCharacter.IsEmpty())
	{
		const FPackContents His = ReadPack(Plan.NewCharacter);
		if (His.MotionFolders.Num() > 0)
		{
			Plan.NewFolders = His.MotionFolders;
			Plan.NewFoldersFrom = TEXT("the sets his pack in this project lists");
		}
		else if (Table.bAvailable && RowDescribes(Plan.NewCharacter, Plan.NewCharacter, Table) && RowFoldersOf(Plan.NewCharacter, His, Table).Num() > 0)
		{
			Plan.NewFolders = RowFoldersOf(Plan.NewCharacter, His, Table);
			Plan.NewFoldersFrom = TEXT("his CharaSpec row");
		}
		else if (!MotionFolderByName(Plan.NewCharacter).IsEmpty())
		{
			Plan.NewFolders = {MotionFolderByName(Plan.NewCharacter)};
			Plan.NewFoldersFrom = TEXT("his name");
		}
		Plan.FieldActions = Plan.NewFolders.Num() > 0 ? FPackageName::GetShortName(Plan.NewFolders[0]) : FString();
	}
	for (const FString& Row : Plan.RowNames)
	{
		FCharacterRowPlan RowPlan;
		RowPlan.Row = Row;
		RowPlan.bNamed = Named.Contains(Row);
		RowPlan.Pack = ReadPack(Row);
		RowPlan.After = RowPlan.Pack;
		RowPlan.Folders = RowFoldersOf(Row, RowPlan.Pack, Table);
		Plan.Rows.Add(MoveTemp(RowPlan));
	}
	if (!bRows || !Plan.Error.IsEmpty() || !Table.bAvailable)
	{
		return Plan;
	}

	// His spec in their Shared CharaSpec Lists, so what his blueprint needs loads with them: his own row while it still
	// describes him, else his _Reserve row (another swap may have changed his own, as SephirothOverCloud does).
	for (const FString& Candidate : {Plan.NewCharacter, Plan.NewCharacter + TEXT("_Reserve")})
	{
		if (RowDescribes(Candidate, Plan.NewCharacter, Table))
		{
			Plan.NewSpec = Candidate;
			break;
		}
	}
	if (Plan.NewSpec.IsEmpty())
	{
		Plan.NewSpecNote = FString::Printf(TEXT("neither %s nor %s_Reserve describes %s any more (another swap?), so no spec of his is shared"),
			*Plan.NewCharacter, *Plan.NewCharacter, *Plan.NewCharacter);
	}

	const bool bTools = bPackEdits && GameObjectToolsLoaded();
	const FString VoiceText = Swap.Voice.TrimStartAndEnd();
	if (!VoiceText.IsEmpty())
	{
		Plan.VoiceName = ShortName(NormalizedObjectPath(VoiceText));
		if (Plan.VoiceName.StartsWith(TEXT("VO_"), ESearchCase::IgnoreCase))
		{
			Plan.LipSyncName = TEXT("LSD_") + Plan.VoiceName.Mid(3);
		}
		if (bTools)
		{
			Plan.VoicePath = GameObjectPathOf(Plan.VoiceName, TEXT("/Game/Sound/Voice/"));
			Plan.LipSyncPath = Plan.LipSyncName.IsEmpty() ? FString() : GameObjectPathOf(Plan.LipSyncName, TEXT("/Game/LipSync/"));
		}
	}
	FString NewBlueprint; // looked up once
	for (FCharacterRowPlan& R : Plan.Rows)
	{
		const FString& Row = R.Row;
		for (const FString& Weapon : NamesInText(Table.Field(Row, TEXT("EquipmentCharaSpecList_Array"))))
		{
			Plan.Equipment.AddUnique(Weapon);
		}
		if (!R.Pack.bInProject)
		{
			if (R.bNamed)
			{
				R.Problem = FString::Printf(TEXT("CharaSpec_%s is not in this project, so the game's own pack spawns %s. Make that pack editable in this project, then press Apply To CharaSpec again"),
					*Row, *Row);
			}
			continue;
		}
		const bool bEditable = !R.Pack.bCooked;
		const bool bHis = R.Pack.Blueprints.ContainsByPredicate([&](const FString& Blueprint) { return IsBlueprintOf(Blueprint, Plan.NewCharacter); });
		if (!bHis)
		{
			if (!bEditable)
			{
				R.Problem = FString::Printf(TEXT("CharaSpec_%s in this project is a cooked game copy, which cannot be saved: make it editable first"), *Row);
			}
			else if (!bPackEdits)
			{
				R.Problem = FString::Printf(TEXT("its pack spawns %s, not %s. Set Asset Class List > 0 > Asset User Data of CharaSpec_%s to %s_C (or turn Apply To Packs on)"),
					R.Pack.Blueprints.Num() > 0 ? *FString::Join(R.Pack.Blueprints, TEXT(", ")) : TEXT("no blueprint"), *Plan.NewCharacter, *Row, *Plan.NewCharacter);
			}
			else if (!bTools)
			{
				R.Problem = FString::Printf(TEXT("its pack spawns %s, and %s"), R.Pack.Blueprints.Num() > 0 ? *FString::Join(R.Pack.Blueprints, TEXT(", ")) : TEXT("no blueprint"),
					GameObjectToolsMissing);
			}
			else
			{
				if (NewBlueprint.IsEmpty())
				{
					NewBlueprint = BlueprintClassPathOf(Plan.NewCharacter);
				}
				R.Edit.Blueprint = NewBlueprint;
				R.After.Blueprints = {Plan.NewCharacter};
			}
		}
		if (!Plan.VoiceName.IsEmpty() && bEditable && bPackEdits)
		{
			if (R.Pack.Voices.Num() == 0)
			{
				R.Notes.Add(TEXT("its pack loads no voice, so it gets none (the Voice replaces a pack's voice)"));
			}
			else if (!(R.Pack.Voices.Num() == 1 && R.Pack.Voices[0].Equals(Plan.VoiceName, ESearchCase::IgnoreCase)))
			{
				if (!bTools)
				{
					R.Notes.Add(FString::Printf(TEXT("Voice not set: %s"), GameObjectToolsMissing));
				}
				else if (Plan.VoicePath.IsEmpty())
				{
					R.Notes.Add(FString::Printf(TEXT("Voice not set: the game's paks have no %s under /Game/Sound/Voice/"), *Plan.VoiceName));
				}
				else
				{
					R.Edit.Voice = Plan.VoicePath;
					R.After.Voices = {Plan.VoiceName};
					if (!Plan.LipSyncPath.IsEmpty() && R.Pack.LipSyncs.Num() > 0)
					{
						R.Edit.LipSync = Plan.LipSyncPath;
						R.After.LipSyncs = {Plan.LipSyncName};
					}
					else if (R.Pack.LipSyncs.Num() > 0)
					{
						R.Notes.Add(FString::Printf(TEXT("the game's paks have no lip sync %s for that voice: the pack keeps %s"),
							*Plan.LipSyncName, *FString::Join(R.Pack.LipSyncs, TEXT(", "))));
					}
				}
			}
		}
		if (!R.Problem.IsEmpty())
		{
			continue;
		}

		// The row describes what its pack spawns and loads.
		const auto Want = [&](const TCHAR* Field, const FString& Value, bool bSet)
		{
			const FString Current = Table.Field(Row, Field);
			const bool bSame = bSet ? SameNames(NamesInText(Current), NamesInText(Value)) : SlotsInText(Current) == SlotsInText(Value);
			if (!bSame && !(Current.IsEmpty() && Value == TEXT("()")))
			{
				R.Changes.Add({Field, Current, Value});
			}
		};
		TArray<FString> Models;
		for (const FString& Blueprint : R.After.Blueprints)
		{
			if (IsBlueprintOf(Blueprint, Plan.NewCharacter))
			{
				Models.AddUnique(Blueprint);
			}
		}
		if (Models.Num() == 1)
		{
			const FString Model = Table.Field(Row, TEXT("ContentsModel"));
			if (!Model.Equals(Models[0], ESearchCase::IgnoreCase))
			{
				R.Changes.Add({TEXT("ContentsModel"), Model, Models[0]});
			}
		}
		else if (Models.Num() > 1)
		{
			R.Notes.Add(TEXT("its pack spawns several of his blueprints, so its model is left as it is: ") + FString::Join(Models, TEXT(", ")));
		}
		if (R.After.Voices.Num() > 0)
		{
			Want(TEXT("ContentSoundVoice_Array"), ArrayText(R.After.Voices), true);
			// A voice that switches with story flags (Cloud's past and insanity lines) is the old character's: it goes.
			const TArray<FString> Packs = NamesInText(Table.Field(Row, TEXT("SoundVoisePack_Array")));
			if (Packs.Num() > 0 && !Packs.Contains(R.After.Voices[0]))
			{
				Want(TEXT("SoundVoisePack_Array"), TEXT("()"), true);
				Want(TEXT("SoundVoisePackEnableStoryFlag_Array"), TEXT("()"), true);
			}
		}
		Want(TEXT("ContentsEffect_Array"), ArrayText(R.After.Effects), true);
		Want(TEXT("ContentsSoundSE_Array"), ArrayText(R.After.SoundSE), true);
		Want(TEXT("ContentsSoundAutoSE_Array"), ArrayText(R.After.SoundAutoSE), true);
		if (R.After.AIBlueprints.Num() > 0)
		{
			Want(TEXT("End2AIList_Array"), ArrayText(R.After.AIBlueprints), true);
		}
		if (!Plan.NewSpec.IsEmpty())
		{
			const FString SharedText = Table.Field(Row, TEXT("SharedCharaSpecList_Array"));
			TArray<FString> Shared = NamesInText(SharedText);
			if (!Shared.Contains(Plan.NewSpec))
			{
				Shared.Add(Plan.NewSpec);
				R.Changes.Add({TEXT("SharedCharaSpecList_Array"), SharedText, ArrayText(Shared)});
			}
		}
		const FString Socket = Swap.WeaponSocket.TrimStartAndEnd();
		if (!Socket.IsEmpty())
		{
			const FString Current = Table.Field(Row, TEXT("OverrideWeaponSocketNames_Array"));
			TArray<FString> Slots = SlotsInText(Current);
			if (Slots.Num() == 0)
			{
				Slots.Add(Socket);
			}
			else
			{
				Slots[0] = Socket;
			}
			Want(TEXT("OverrideWeaponSocketNames_Array"), ArrayText(Slots), false);
		}
		if (Swap.Moveset == EEndSwapMoveset::NewCharacter && !Plan.FieldActions.IsEmpty())
		{
			const FString Current = Table.Field(Row, TEXT("AnimationSetParentFolder"));
			if (!Current.Equals(Plan.FieldActions, ESearchCase::IgnoreCase))
			{
				R.Changes.Add({TEXT("AnimationSetParentFolder"), Current, Plan.FieldActions});
			}
			// Sets the old character's folder has for special scenes (Cloud's bike, piano, ...) are not in his.
			if (NamesInText(Table.Field(Row, TEXT("OverrideAnimationSetString_Array"))).Num() > 0)
			{
				Want(TEXT("OverrideAnimationSetString_Array"), TEXT("()"), true);
			}
		}
	}
	return Plan;
}

// A row matched only through * whose pack is the game's own: the swap does not include it.
bool LeftOut(const FCharacterRowPlan& Row) { return !Row.bNamed && !Row.Pack.bInProject; }

// The family a character swap adds to the JSON (hub: the skeleton whose moves are played), or null.
TSharedPtr<FJsonObject> CharacterFamilyJson(const FEndCharacterSwap& Swap, const FCharacterSwapPlan& Plan)
{
	const bool bTheirs = Swap.Moveset == EEndSwapMoveset::Replaced;
	const FString Hub = bTheirs ? Plan.ReplacedSkeleton : Plan.NewSkeleton;
	const FString Member = bTheirs ? Plan.NewSkeleton : Plan.ReplacedSkeleton;
	if (!Swap.bEnabled || !Plan.Error.IsEmpty() || Hub.IsEmpty() || Member.IsEmpty() || SamePath(Hub, Member))
	{
		return nullptr;
	}
	TSharedRef<FJsonObject> Entry = MakeShared<FJsonObject>();
	Entry->SetStringField(TEXT("receiving_skeleton"), NormalizedObjectPath(Hub));
	Entry->SetArrayField(TEXT("animation_skeletons"), JsonStrings({NormalizedObjectPath(Member)}));
	Entry->SetStringField(TEXT("method"), TEXT("family"));
	Entry->SetStringField(TEXT("hub"), NormalizedObjectPath(Hub));
	if (Swap.bKeepProportions)
	{
		// every member keeps its own bone lengths and height (RebirthSkelCompat 3.2); the mod applies it to the whole
		// family this entry ends up in
		Entry->SetBoolField(TEXT("proportions"), true);
	}
	const TArray<FString> Requires = CleanList(Swap.RequiresPaks, true);
	if (Requires.Num() > 0)
	{
		Entry->SetArrayField(TEXT("requires_paks"), JsonStrings(Requires));
	}
	// The data object makes this entry from the swap again on every export (Import From Game Json skips it).
	Entry->SetStringField(TEXT("from_character_swap"), Plan.NewCharacter);
	Entry->SetBoolField(TEXT("enabled"), true);
	return Entry;
}

// The animation set rows a character swap adds: the swapped rows grouped by their own motion folders, each with both
// characters' folders as battle and field sources, the moveset's first.
TArray<TSharedPtr<FJsonObject>> CharacterRowsJson(const FEndCharacterSwap& Swap, const FCharacterSwapPlan& Plan)
{
	TArray<TSharedPtr<FJsonObject>> Out;
	if (!Swap.bEnabled || !Plan.Error.IsEmpty())
	{
		return Out;
	}
	TArray<TPair<TArray<FString>, TArray<FString>>> Groups; // folders -> rows
	for (const FCharacterRowPlan& Row : Plan.Rows)
	{
		const bool bHis = Row.Pack.Blueprints.ContainsByPredicate([&](const FString& Blueprint) { return IsBlueprintOf(Blueprint, Plan.NewCharacter); });
		if (!Row.Pack.bInProject || (Row.Pack.bCooked && !bHis))
		{
			continue; // the game's own pack (or a cooked copy of it): the old character stays there
		}
		TPair<TArray<FString>, TArray<FString>>* Group = Groups.FindByPredicate([&](const TPair<TArray<FString>, TArray<FString>>& G) { return G.Key == Row.Folders; });
		if (!Group)
		{
			Group = &Groups.Emplace_GetRef(Row.Folders, TArray<FString>());
		}
		Group->Value.Add(Row.Row);
	}
	const TArray<FString> Requires = CleanList(Swap.RequiresPaks, true);
	for (const TPair<TArray<FString>, TArray<FString>>& Group : Groups)
	{
		TArray<FString> Sources = Swap.Moveset == EEndSwapMoveset::Replaced ? Group.Key : Plan.NewFolders;
		for (const FString& Folder : Swap.Moveset == EEndSwapMoveset::Replaced ? Plan.NewFolders : Group.Key)
		{
			Sources.AddUnique(Folder);
		}
		if (Sources.Num() == 0)
		{
			continue;
		}
		TSharedRef<FJsonObject> Entry = MakeShared<FJsonObject>();
		Entry->SetArrayField(TEXT("characters"), JsonStrings(Group.Value));
		Entry->SetArrayField(TEXT("battle"), JsonStrings(Sources));
		Entry->SetArrayField(TEXT("field"), JsonStrings(Sources));
		if (Requires.Num() > 0)
		{
			Entry->SetArrayField(TEXT("requires_paks"), JsonStrings(Requires));
		}
		Entry->SetStringField(TEXT("from_character_swap"), Plan.NewCharacter);
		Entry->SetBoolField(TEXT("enabled"), true);
		Out.Add(Entry);
	}
	return Out;
}

bool CheckCharacterSwap(const FEndCharacterSwap& Swap, int32 Index, const FCharaSpecTable& Table, bool bPackEdits, FString& Report)
{
	Report += FString::Printf(TEXT("Character swap %d: %s -> %s\n"), Index, *ListText(CleanList(Swap.Characters, false)), *Swap.NewCharacter.TrimStartAndEnd());
	if (!Swap.bEnabled)
	{
		Report += TEXT("    disabled\n");
		return true;
	}
	bool bOk = true;
	const FCharacterSwapPlan Plan = PlanCharacterSwap(Swap, Table, true, bPackEdits);
	if (!Plan.Error.IsEmpty())
	{
		Report += TEXT("    ERROR: ") + Plan.Error + TEXT("\n");
		return false;
	}
	for (const FString& Item : Plan.Unknown)
	{
		Report += FString::Printf(TEXT("    WARNING: %s names no row of %s\n"), *Item, *Table.Package);
	}
	if (Plan.RowNames.Num() == 0)
	{
		Report += TEXT("    ERROR: no rows to replace (Characters)\n");
		return false;
	}
	const bool bTheirs = Swap.Moveset == EEndSwapMoveset::Replaced;
	Report += FString::Printf(TEXT("    moves: %s (%s)\n"), bTheirs ? TEXT("the replaced character's, his own fill in") : TEXT("his own, the replaced character's fill in"),
		Plan.NewFolders.Num() > 0 ? *FString::Printf(TEXT("his motion folders from %s: %s"), *Plan.NewFoldersFrom, *ListText(Plan.NewFolders)) : TEXT("WARNING: his motion folders are not known"));
	if (!Table.bAvailable)
	{
		Report += TEXT("    note: the Rebirth data object tools (Rebirth Cooked Asset Preview plugin) are not loaded, so the CharaSpec rows and packs are not checked\n");
	}
	else
	{
		if (!Plan.VoiceName.IsEmpty())
		{
			Report += FString::Printf(TEXT("    voice: %s%s\n"), *Plan.VoiceName, Plan.VoicePath.IsEmpty() ? TEXT(" (not found in the game's paks yet)") :
				*FString::Printf(TEXT(" (%s%s)"), *Plan.VoicePath, Plan.LipSyncPath.IsEmpty() ? TEXT(", no lip sync of that name") : *(TEXT(", lip sync ") + Plan.LipSyncPath)));
		}
		Report += Plan.NewSpec.IsEmpty() ? TEXT("    WARNING: ") + Plan.NewSpecNote + TEXT("\n")
										 : FString::Printf(TEXT("    shared spec: %s (loads what his blueprint needs with the rows)\n"), *Plan.NewSpec);
		int32 Swapped = 0;
		for (const FCharacterRowPlan& Row : Plan.Rows)
		{
			if (LeftOut(Row))
			{
				Report += FString::Printf(TEXT("    %s: left out (its pack is the game's own, so it stays the old character; make CharaSpec_%s editable in this project to swap it too)\n"),
					*Row.Row, *Row.Row);
				continue;
			}
			for (const FString& Note : Row.Notes)
			{
				Report += FString::Printf(TEXT("    %s: note: %s\n"), *Row.Row, *Note);
			}
			if (!Row.Problem.IsEmpty())
			{
				Report += FString::Printf(TEXT("    %s: ERROR: %s\n"), *Row.Row, *Row.Problem);
				bOk = false;
				continue;
			}
			++Swapped;
			if (Row.Edit.HasWork())
			{
				Report += FString::Printf(TEXT("    %s: Apply To CharaSpec makes its pack %s\n"), *Row.Row, *FString::Join(PackEditLines(Row.Edit, Row.Pack), TEXT("; ")));
			}
			if (Row.Changes.Num() == 0)
			{
				Report += FString::Printf(TEXT("    %s: pack spawns %s; the row describes it\n"), *Row.Row, *ListText(Row.After.Blueprints));
				continue;
			}
			Report += FString::Printf(TEXT("    %s: pack spawns %s; Apply To CharaSpec writes:\n"), *Row.Row, *ListText(Row.After.Blueprints));
			for (const FFieldChange& Change : Row.Changes)
			{
				Report += FString::Printf(TEXT("        %s: %s -> %s\n"), Change.Field, *FieldShown(Change.Field, Change.Current), *FieldShown(Change.Field, Change.Value));
			}
		}
		if (Swapped == 0 && bOk)
		{
			Report += TEXT("    ERROR: none of these rows' packs is in this project, so none of them spawns him\n");
			bOk = false;
		}
		TArray<FString> Weapons;
		for (const FString& Weapon : Plan.Equipment)
		{
			if (!Weapon.StartsWith(CharacterIdOf(Plan.NewCharacter)))
			{
				Weapons.Add(Weapon);
			}
		}
		if (Weapons.Num() > 0)
		{
			Report += FString::Printf(TEXT("    note: these rows equip %s: add a weapon swap (New Weapon: his weapon, e.g. his _00 one) to put his weapon in his hands, with Sockets so the moves still hit\n"),
				*ListText(Weapons));
		}
		if (!Swap.WeaponSocket.TrimStartAndEnd().IsEmpty())
		{
			Report += FString::Printf(TEXT("    weapon socket: %s (slot 0, the equipped weapon)\n"), *Swap.WeaponSocket.TrimStartAndEnd());
		}
	}
	// What Export Json adds.
	if (CleanList(Swap.RequiresPaks, true).Num() == 0)
	{
		Report += TEXT("    WARNING: Requires Paks is empty, so the family and moves below stay on in game even without your swap pak (the two characters keep sharing one skeleton): name the pak there\n");
	}
	const FString Hub = bTheirs ? Plan.ReplacedSkeleton : Plan.NewSkeleton;
	const FString Member = bTheirs ? Plan.NewSkeleton : Plan.ReplacedSkeleton;
	if (Hub.IsEmpty() || Member.IsEmpty())
	{
		Report += TEXT("    ERROR: family: the skeletons are not known; set Replaced Skeleton and New Skeleton (Advanced)\n");
		bOk = false;
	}
	else if (SamePath(Hub, Member))
	{
		Report += TEXT("    family: not needed, both characters are on ") + ShortName(Hub) + TEXT("\n");
	}
	else
	{
		for (const FString& Skeleton : {Hub, Member})
		{
			if (!InProject(Skeleton))
			{
				Report += FString::Printf(TEXT("    note: %s is not in this project (checked in game)%s\n"), *Skeleton,
					(SamePath(Skeleton, Plan.ReplacedSkeleton) ? Plan.bReplacedSkeletonFromFolder : Plan.bNewSkeletonFromFolder) ? TEXT("; it is the model folder's, set the skeleton (Advanced) if the animations use another") : TEXT(""));
			}
		}
		Report += FString::Printf(TEXT("    family (Export Json): hub %s, member %s%s\n"), *Hub, *Member,
			Swap.bKeepProportions ? TEXT("; every character keeps its own height (Keep Proportions, RebirthSkelCompat 3.2)") : TEXT("; Keep Proportions off: he takes the height of the skeleton whose moves he plays"));
	}
	for (const TSharedPtr<FJsonObject>& Row : CharacterRowsJson(Swap, Plan))
	{
		Report += FString::Printf(TEXT("    animation sets (Export Json) of %s: battle and field from %s\n"), *ListText(StringsOf(Row->TryGetField(TEXT("characters")))),
			*ListText(StringsOf(Row->TryGetField(TEXT("battle")))));
	}
	return bOk;
}

// Shared CharaSpec Lists that would load each other in a loop once Planned (row -> its new list) is written, as text.
TArray<FString> SharedLoops(const FCharaSpecTable& Table, const TMap<FString, TArray<FString>>& Planned)
{
	TMap<FString, TArray<FString>> Lists = Planned;
	const auto SharedOf = [&](const FString& Row) -> TArray<FString>
	{
		if (const TArray<FString>* Known = Lists.Find(Row))
		{
			return *Known;
		}
		TArray<FString> Read = Table.Has(Row) ? NamesInText(Table.Field(Row, TEXT("SharedCharaSpecList_Array"))) : TArray<FString>();
		Lists.Add(Row, Read);
		return Read;
	};
	TArray<FString> Loops;
	for (const TPair<FString, TArray<FString>>& Start : Planned)
	{
		TArray<TArray<FString>> Stack;
		Stack.Add(TArray<FString>{Start.Key});
		TSet<FString> Seen;
		while (Stack.Num() > 0)
		{
			const TArray<FString> Path = Stack.Pop();
			for (const FString& Next : SharedOf(Path.Last()))
			{
				if (Next.Equals(Start.Key, ESearchCase::IgnoreCase))
				{
					Loops.AddUnique(FString::Join(Path, TEXT(" -> ")) + TEXT(" -> ") + Next);
				}
				else if (!Seen.Contains(Next) && Path.Num() < 16)
				{
					Seen.Add(Next);
					TArray<FString> Longer = Path;
					Longer.Add(Next);
					Stack.Add(Longer);
				}
			}
		}
	}
	return Loops;
}

// Every CharaSpec pack of this project against its row: the model of the blueprint it spawns (wrong ones are what Fix Pack
// Models changes), and the voice, effects, sounds and AI it loads.
struct FPackCheck
{
	FString Row;
	FString Model;    // the row's model now
	FString Spawns;   // the one blueprint the pack spawns (empty: none or several)
	TArray<FString> Differences;
};

// The Shared CharaSpec Lists Apply To CharaSpec would write for these swaps (row -> its new list).
TMap<FString, TArray<FString>> PlannedSharedLists(const TArray<FEndCharacterSwap>& Characters, const TArray<FEndWeaponSwap>& Weapons, const FCharaSpecTable& Table, bool bPackEdits)
{
	TMap<FString, TArray<FString>> Planned;
	const auto Take = [&Planned](const FString& Row, const TArray<FFieldChange>& Changes)
	{
		for (const FFieldChange& Change : Changes)
		{
			if (FCString::Strcmp(Change.Field, TEXT("SharedCharaSpecList_Array")) == 0)
			{
				Planned.Add(Row, NamesInText(Change.Value));
			}
		}
	};
	for (const FEndCharacterSwap& Swap : Characters)
	{
		if (Swap.bEnabled)
		{
			for (const FCharacterRowPlan& Row : PlanCharacterSwap(Swap, Table, true, bPackEdits).Rows)
			{
				Take(Row.Row, Row.Changes);
			}
		}
	}
	for (const FEndWeaponSwap& Swap : Weapons)
	{
		if (Swap.bEnabled)
		{
			for (const FWeaponRowPlan& Row : PlanWeaponSwap(Swap, Table, true, bPackEdits).Rows)
			{
				Take(Row.Row, Row.Changes);
			}
		}
	}
	return Planned;
}

TArray<FPackCheck> CheckProjectPacks(const FCharaSpecTable& Table)
{
	TArray<FPackCheck> Out;
	if (!Table.bAvailable)
	{
		return Out;
	}
	TArray<FAssetData> Assets;
	AssetRegistry().GetAssetsByPath(FName(TEXT("/Game/DataAsset/Game/CharaSpec")), Assets, false);
	Assets.Sort([](const FAssetData& A, const FAssetData& B) { return A.PackageName.ToString() < B.PackageName.ToString(); });
	for (const FAssetData& Asset : Assets)
	{
		FString Row = Asset.AssetName.ToString();
		if (!Row.RemoveFromStart(TEXT("CharaSpec_")) || !Table.Has(Row))
		{
			continue;
		}
		const FPackContents Pack = ReadPack(Row);
		FPackCheck Check;
		Check.Row = Row;
		Check.Model = Table.Field(Row, TEXT("ContentsModel"));
		if (Pack.Blueprints.Num() == 1)
		{
			Check.Spawns = Pack.Blueprints[0];
		}
		const auto Compare = [&](const TCHAR* Field, const TArray<FString>& Loads, bool bOnlyWhenLoaded)
		{
			if (bOnlyWhenLoaded && Loads.Num() == 0)
			{
				return;
			}
			const TArray<FString> Lists = NamesInText(Table.Field(Row, Field));
			if (!SameNames(Lists, Loads))
			{
				Check.Differences.Add(FString::Printf(TEXT("%s lists %s, the pack loads %s"), Field, *ListText(Lists), *ListText(Loads)));
			}
		};
		Compare(TEXT("ContentSoundVoice_Array"), Pack.Voices, true);
		Compare(TEXT("ContentsEffect_Array"), Pack.Effects, false);
		Compare(TEXT("ContentsSoundSE_Array"), Pack.SoundSE, false);
		Compare(TEXT("ContentsSoundAutoSE_Array"), Pack.SoundAutoSE, false);
		Compare(TEXT("End2AIList_Array"), Pack.AIBlueprints, true);
		if (!Check.Spawns.IsEmpty() && !Check.Spawns.Equals(Check.Model, ESearchCase::IgnoreCase))
		{
			Check.Differences.Insert(FString::Printf(TEXT("ERROR: it spawns %s, but the row's model is %s"), *Check.Spawns, *Check.Model), 0);
		}
		if (Check.Differences.Num() > 0)
		{
			Out.Add(MoveTemp(Check));
		}
	}
	return Out;
}

// Something for Apply To CharaSpec to do: field actions or missing row references of rows, character or weapon swaps.
bool HasCharaSpecWork(const TArray<FEndAnimSetRow>& Rows, const TArray<FEndWeaponSwap>& Swaps, const TArray<FEndCharacterSwap>& Characters, bool bFixMissing)
{
	for (const FEndAnimSetRow& Row : Rows)
	{
		if (Row.bEnabled && CleanList(Row.Characters, false).Num() > 0 && (bFixMissing || !Row.FieldActions.TrimStartAndEnd().IsEmpty()))
		{
			return true;
		}
	}
	return Swaps.ContainsByPredicate([](const FEndWeaponSwap& Swap) { return Swap.bEnabled && !Swap.NewWeapon.TrimStartAndEnd().IsEmpty(); }) ||
		Characters.ContainsByPredicate([](const FEndCharacterSwap& Swap) { return Swap.bEnabled && !Swap.NewCharacter.TrimStartAndEnd().IsEmpty(); });
}

// One pair as a compat JSON file states it (a family entry is listed under its hub).
struct FFilePair
{
	FString File;                  // file name, e.g. Cloud_Sephiroth_SkeletonCompat.json
	FString Receiving;             // normalised object path (a family: its hub)
	TArray<FString> Animation;     // normalised object paths (a family: the other members)
	bool bHasMethod = false;
	EEndSkelCompatMethod Method = EEndSkelCompatMethod::Animations;
	TArray<FString> RequiresPaks;
	TArray<FString> AdoptPaths;
	bool bEnabled = true;
	bool bHasFixHierarchy = false;
	bool bFixHierarchy = true;
	bool bHasRepairLiveComponents = false;
	bool bRepairLiveComponents = true;
	bool bHasCarrySockets = false;
	bool bCarrySockets = true;
	bool bHasKeepProportions = false;
	bool bKeepProportions = false;
	bool bHasProportionBones = false;      // (1.14)
	TArray<FString> ProportionBones;
};

// Entries a swap makes again on every export (Import From Game Json skips them).
bool FromSwap(const TSharedPtr<FJsonObject>& Entry)
{
	return Entry.IsValid() && (Entry->HasField(TEXT("from_weapon_swap")) || Entry->HasField(TEXT("from_character_swap")));
}

bool ReadPairsFile(const FString& Path, TArray<FFilePair>& Out, FString& Error, TArray<FEndAnimSetRow>* Rows = nullptr, TArray<FEndWeaponSwap>* Swaps = nullptr,
	TArray<FEndCharacterSwap>* Characters = nullptr)
{
	FString Text;
	if (!FFileHelper::LoadFileToString(Text, *Path))
	{
		Error = TEXT("could not be read");
		return false;
	}
	TSharedPtr<FJsonObject> Root;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Text);
	if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
	{
		Error = TEXT("is not valid JSON");
		return false;
	}
	const TArray<TSharedPtr<FJsonValue>>* PairEntries = nullptr;
	const TArray<TSharedPtr<FJsonValue>>* FamilyEntries = nullptr;
	const TArray<TSharedPtr<FJsonValue>>* RowEntries = nullptr;
	const TArray<TSharedPtr<FJsonValue>>* SwapEntries = nullptr;
	const TArray<TSharedPtr<FJsonValue>>* CharacterEntries = nullptr;
	Root->TryGetArrayField(TEXT("pairs"), PairEntries);
	Root->TryGetArrayField(TEXT("families"), FamilyEntries);
	Root->TryGetArrayField(TEXT("animation_sets"), RowEntries);
	Root->TryGetArrayField(TEXT("weapon_swaps"), SwapEntries);
	Root->TryGetArrayField(TEXT("character_swaps"), CharacterEntries);
	if (!PairEntries && !FamilyEntries && !RowEntries && !SwapEntries && !CharacterEntries)
	{
		Error = TEXT("has no \"pairs\", \"families\", \"animation_sets\", \"weapon_swaps\" or \"character_swaps\" array");
		return false;
	}
	if (Characters && CharacterEntries)
	{
		for (const TSharedPtr<FJsonValue>& Value : *CharacterEntries)
		{
			FEndCharacterSwap Swap;
			if (Value.IsValid() && Value->Type == EJson::Object && CharacterSwapFromJson(Value->AsObject(), Swap))
			{
				Characters->Add(Swap);
			}
		}
	}
	if (Swaps && SwapEntries)
	{
		for (const TSharedPtr<FJsonValue>& Value : *SwapEntries)
		{
			FEndWeaponSwap Swap;
			if (Value.IsValid() && Value->Type == EJson::Object && WeaponSwapFromJson(Value->AsObject(), Swap))
			{
				Swaps->Add(Swap);
			}
		}
	}
	if (Rows && RowEntries)
	{
		for (const TSharedPtr<FJsonValue>& Value : *RowEntries)
		{
			FEndAnimSetRow Row;
			if (Value.IsValid() && Value->Type == EJson::Object && !FromSwap(Value->AsObject()) && RowFromJson(Value->AsObject(), Row))
			{
				Rows->Add(Row);
			}
		}
	}
	const FString FileName = FPaths::GetCleanFilename(Path);
	const auto ReadEntries = [&](const TArray<TSharedPtr<FJsonValue>>& Entries, bool bFamilyList)
	{
		for (const TSharedPtr<FJsonValue>& Value : Entries)
		{
			if (!Value.IsValid() || Value->Type != EJson::Object)
			{
				continue;
			}
			const TSharedPtr<FJsonObject> Entry = Value->AsObject();
			if (!Entry.IsValid() || FromSwap(Entry))
			{
				continue; // a swap's family: the data object makes it from the swap
			}
			FFilePair Pair;
			Pair.File = FileName;
			Pair.Method = bFamilyList ? EEndSkelCompatMethod::Family : EEndSkelCompatMethod::Animations;
			FString Method;
			if (Entry->TryGetStringField(TEXT("method"), Method))
			{
				Pair.bHasMethod = true;
				Pair.Method = ParseMethod(Method);
			}
			FString Hub;
			if (Entry->TryGetStringField(TEXT("hub"), Hub) && !Hub.TrimStartAndEnd().IsEmpty())
			{
				Pair.bHasMethod = true;
				Pair.Method = EEndSkelCompatMethod::Family; // naming a hub makes a family
			}
			TArray<FString> Receivers;
			for (const FString& Skeleton : StringsOf(Entry->TryGetField(TEXT("receiving_skeleton"))))
			{
				Receivers.AddUnique(NormalizedObjectPath(Skeleton));
			}
			for (const FString& Skeleton : StringsOf(Entry->TryGetField(TEXT("receiving_skeletons"))))
			{
				Receivers.AddUnique(NormalizedObjectPath(Skeleton));
			}
			TArray<FString> Animation;
			for (const TCHAR* Key : {TEXT("animation_skeletons"), TEXT("animation_skeleton"), TEXT("skeletons")})
			{
				for (const FString& Skeleton : StringsOf(Entry->TryGetField(Key)))
				{
					Animation.AddUnique(NormalizedObjectPath(Skeleton));
				}
			}
			TArray<FString> Paks = StringsOf(Entry->TryGetField(TEXT("requires_paks")));
			Paks.Append(StringsOf(Entry->TryGetField(TEXT("requires_pak"))));
			Pair.RequiresPaks = CleanList(Paks, true);
			Pair.AdoptPaths = CleanList(StringsOf(Entry->TryGetField(TEXT("adopt_paths"))), false);
			BoolField(Entry, TEXT("enabled"), Pair.bEnabled);
			Pair.bHasFixHierarchy = BoolField(Entry, TEXT("fix_hierarchy"), Pair.bFixHierarchy);
			Pair.bHasRepairLiveComponents = BoolField(Entry, TEXT("repair_live_components"), Pair.bRepairLiveComponents);
			Pair.bHasCarrySockets = BoolField(Entry, TEXT("carry_sockets"), Pair.bCarrySockets);
			for (const TCHAR* Key : {TEXT("proportions"), TEXT("keep_proportions")})
			{
				Pair.bHasKeepProportions |= BoolField(Entry, Key, Pair.bKeepProportions);
			}
			if (Entry->HasField(TEXT("proportion_bones")))   // (1.14)
			{
				Pair.bHasProportionBones = true;
				Pair.ProportionBones = CleanList(StringsOf(Entry->TryGetField(TEXT("proportion_bones"))), false);
			}
			if (Pair.Method == EEndSkelCompatMethod::Family)
			{
				// Listed under its hub: "hub", else the first skeleton named.
				TArray<FString> Members = Receivers;
				for (const FString& Skeleton : Animation)
				{
					Members.AddUnique(Skeleton);
				}
				Pair.Receiving = !Hub.TrimStartAndEnd().IsEmpty() ? NormalizedObjectPath(Hub) : (Members.Num() > 0 ? Members[0] : FString());
				if (Pair.Receiving.IsEmpty())
				{
					continue;
				}
				for (const FString& Member : Members)
				{
					if (!SamePath(Member, Pair.Receiving))
					{
						Pair.Animation.AddUnique(Member);
					}
				}
				Out.Add(MoveTemp(Pair));
				continue;
			}
			for (const FString& Receiving : Receivers)
			{
				FFilePair One = Pair;
				One.Receiving = Receiving;
				for (const FString& Skeleton : Animation)
				{
					if (!SamePath(Skeleton, Receiving))
					{
						One.Animation.AddUnique(Skeleton);
					}
				}
				Out.Add(MoveTemp(One));
			}
		}
	};
	if (PairEntries)
	{
		ReadEntries(*PairEntries, false);
	}
	if (FamilyEntries)
	{
		ReadEntries(*FamilyEntries, true);
	}
	return true;
}

// ------------------------------------------------------------------------------------------------
// Bone hierarchy test (Mesh rebind). Port of UE 4.26 USkeleton::IsCompatibleMesh / DoesParentChainMatch:
// the game only spawns an AnimBlueprint on a mesh when this passes against the AnimBlueprint's skeleton.
// In game the mesh is bound to the animation skeleton, so test against that one. Unlike the engine, the
// test goes on after a bone placed differently, to count what the mod's hierarchy fix renames.
// ------------------------------------------------------------------------------------------------
struct FBoneCheck
{
	bool bCompatible = false; // passes the game's test as it is
	bool bFixable = false;    // fails only on bones placed differently: the mod's hierarchy fix renames them
	int32 Matched = 0;
	int32 MeshOnly = 0;
	int32 AnimationOnly = 0;
	int32 Misplaced = 0;      // mesh bones whose parent chain differs on the animation skeleton
	FString Problem;          // the first problem found
};

FString Chain(const FReferenceSkeleton& Skeleton, int32 Bone)
{
	FString Text;
	for (int32 Guard = 0; Bone != INDEX_NONE && Guard < 6; ++Guard)
	{
		Text += (Text.IsEmpty() ? TEXT("") : TEXT(" < ")) + Skeleton.GetBoneName(Bone).ToString();
		Bone = Skeleton.GetParentIndex(Bone);
	}
	return Bone == INDEX_NONE ? Text : Text + TEXT(" < ...");
}

bool ParentChainMatches(int32 SkeletonBone, const FReferenceSkeleton& Skeleton, const FReferenceSkeleton& Mesh)
{
	if (SkeletonBone == 0)
	{
		return Skeleton.GetBoneName(0) == Mesh.GetBoneName(0);
	}
	int32 MeshBone = Mesh.FindBoneIndex(Skeleton.GetBoneName(SkeletonBone));
	if (MeshBone == INDEX_NONE)
	{
		return false;
	}
	for (;;)
	{
		const int32 SkeletonParent = Skeleton.GetParentIndex(SkeletonBone);
		const int32 MeshParent = Mesh.GetParentIndex(MeshBone);
		if (SkeletonParent == INDEX_NONE || MeshParent == INDEX_NONE)
		{
			return SkeletonParent == MeshParent;
		}
		if (Skeleton.GetBoneName(SkeletonParent) != Mesh.GetBoneName(MeshParent))
		{
			return false;
		}
		SkeletonBone = SkeletonParent;
		MeshBone = MeshParent;
	}
}

FBoneCheck CheckMesh(const FReferenceSkeleton& Mesh, const FReferenceSkeleton& Skeleton)
{
	FBoneCheck Result;
	for (int32 Bone = 0; Bone < Skeleton.GetRawBoneNum(); ++Bone)
	{
		if (Mesh.FindBoneIndex(Skeleton.GetBoneName(Bone)) == INDEX_NONE)
		{
			++Result.AnimationOnly;
		}
	}
	bool bHard = false; // a problem the hierarchy fix cannot solve
	const int32 RawBones = Mesh.GetRawBoneNum();
	for (int32 MeshBone = 0; MeshBone < RawBones && !bHard; ++MeshBone)
	{
		const FName Name = Mesh.GetBoneName(MeshBone);
		int32 SkeletonBone = Skeleton.FindBoneIndex(Name);
		if (SkeletonBone != INDEX_NONE)
		{
			++Result.Matched;
		}
		else
		{
			++Result.MeshOnly;
			int32 Current = MeshBone;
			while (SkeletonBone == INDEX_NONE && Current != INDEX_NONE)
			{
				const int32 Parent = Mesh.GetParentIndex(Current);
				if (Parent != INDEX_NONE)
				{
					SkeletonBone = Skeleton.FindBoneIndex(Mesh.GetBoneName(Parent));
				}
				if (Parent == 0)
				{
					break;
				}
				Current = Parent;
			}
			if (SkeletonBone == INDEX_NONE)
			{
				Result.Problem = MeshBone == 0
					? FString::Printf(TEXT("root bone '%s' is not on the animation skeleton (its root is '%s')"), *Name.ToString(), *Skeleton.GetBoneName(0).ToString())
					: FString::Printf(TEXT("bone '%s' has no ancestor on the animation skeleton"), *Name.ToString());
				bHard = true;
				break;
			}
		}
		if (!ParentChainMatches(SkeletonBone, Skeleton, Mesh))
		{
			if (SkeletonBone == 0)
			{
				Result.Problem = FString::Printf(TEXT("root bone names differ: mesh '%s', animation skeleton '%s'"), *Mesh.GetBoneName(0).ToString(),
					*Skeleton.GetBoneName(0).ToString());
				bHard = true;
				break;
			}
			if (Result.Misplaced == 0)
			{
				const int32 InMesh = Mesh.FindBoneIndex(Skeleton.GetBoneName(SkeletonBone));
				Result.Problem = FString::Printf(TEXT("parent chain of '%s' differs. Mesh: %s. Animation skeleton: %s"), *Skeleton.GetBoneName(SkeletonBone).ToString(),
					*Chain(Mesh, InMesh), *Chain(Skeleton, SkeletonBone));
			}
			++Result.Misplaced;
		}
	}
	if (!bHard && Result.Matched == 0)
	{
		Result.Problem = TEXT("no bone names in common");
		bHard = true;
	}
	Result.bCompatible = !bHard && Result.Misplaced == 0;
	Result.bFixable = !bHard && Result.Misplaced > 0;
	return Result;
}

// The bone list in the form the game mod works on (final bones: raw ones first, then virtual bones).
SkelCompat::BoneTable BonesOf(const FReferenceSkeleton& Reference)
{
	SkelCompat::BoneTable Table;
	const int32 Count = Reference.GetNum();
	Table.Names.reserve(static_cast<size_t>(Count));
	Table.Parents.reserve(static_cast<size_t>(Count));
	for (int32 Bone = 0; Bone < Count; ++Bone)
	{
		Table.Names.push_back(Wide(Reference.GetBoneName(Bone).ToString()));
		Table.Parents.push_back(Reference.GetParentIndex(Bone));
	}
	Table.RawCount = Reference.GetRawBoneNum();
	return Table;
}

// What the mod's hierarchy fix does to a mesh bound to Target that must stay compatible with Keep too (a family member's
// own skeleton, the skeleton an outfit was made for), and whether the game then accepts it for each of them.
struct FFixResult
{
	bool bPossible = true;
	int32 Renamed = 0;
	FString Names;          // the first renamed bones
	bool bTargetOk = false; // AnimBlueprints for the target skeleton run
	TArray<FString> KeepRefused; // skeletons in Keep whose AnimBlueprints would be refused
};

FFixResult PlanFix(USkeletalMesh* Mesh, USkeleton* Target, const TArray<USkeleton*>& Keep, bool bFixHierarchy)
{
	FFixResult Result;
	const SkelCompat::BoneTable MeshBones = BonesOf(Mesh->RefSkeleton);
	const SkelCompat::BoneTable TargetBones = BonesOf(Target->GetReferenceSkeleton());
	std::vector<SkelCompat::BoneTable> KeepTables;
	for (USkeleton* Skeleton : Keep)
	{
		if (Skeleton && Skeleton != Target)
		{
			KeepTables.push_back(BonesOf(Skeleton->GetReferenceSkeleton()));
		}
	}
	std::vector<const SkelCompat::BoneTable*> KeepPointers;
	for (const SkelCompat::BoneTable& Table : KeepTables)
	{
		KeepPointers.push_back(&Table);
	}
	SkelCompat::RenamePlan Plan;
	if (bFixHierarchy)
	{
		Plan = SkelCompat::PlanConflictRenamesFor(MeshBones, TargetBones, KeepPointers);
	}
	Result.bPossible = Plan.Possible;
	const SkelCompat::BoneTable After = SkelCompat::ApplyRenamePlan(MeshBones, Plan);
	Result.Renamed = static_cast<int32>(Plan.Bones.size());
	for (size_t Index = 0; Index < Plan.Bones.size() && Index < static_cast<size_t>(MaxNamesListed); ++Index)
	{
		Result.Names += (Index ? TEXT(", ") : TEXT("")) + FromWide(MeshBones.Names[static_cast<size_t>(Plan.Bones[Index])]);
	}
	if (Plan.Bones.size() > static_cast<size_t>(MaxNamesListed))
	{
		Result.Names += TEXT(" ...");
	}
	Result.bTargetOk = SkelCompat::CheckMeshAgainstSkeleton(After, TargetBones).Compatible;
	size_t KeepIndex = 0;
	for (USkeleton* Skeleton : Keep)
	{
		if (!Skeleton || Skeleton == Target)
		{
			continue;
		}
		if (!SkelCompat::CheckMeshAgainstSkeleton(After, KeepTables[KeepIndex]).Compatible)
		{
			Result.KeepRefused.Add(Skeleton->GetName());
		}
		++KeepIndex;
	}
	return Result;
}

// ------------------------------------------------------------------------------------------------
// Animations method: what carries over from the animation skeleton to the receiving skeleton. A bone's
// track moves when the receiving skeleton has a bone of that name under the same parent chain; curve
// tracks move when the receiving skeleton knows the curve name. The mod logs the same numbers in game.
// ------------------------------------------------------------------------------------------------
struct FCarryOver
{
	int32 Bones = 0;   // raw bones of the animation skeleton
	int32 Carried = 0; // same name and parent chain on the receiving skeleton
	int32 Missing = 0; // not on the receiving skeleton
	int32 Moved = 0;   // on the receiving skeleton under a different parent chain
	FString MovedNames;
};

bool SameParentChain(const FReferenceSkeleton& A, int32 BoneA, const FReferenceSkeleton& B, int32 BoneB)
{
	for (;;)
	{
		const int32 ParentA = A.GetParentIndex(BoneA);
		const int32 ParentB = B.GetParentIndex(BoneB);
		if (ParentA == INDEX_NONE || ParentB == INDEX_NONE)
		{
			return ParentA == ParentB;
		}
		if (A.GetBoneName(ParentA) != B.GetBoneName(ParentB))
		{
			return false;
		}
		BoneA = ParentA;
		BoneB = ParentB;
	}
}

FCarryOver CheckCarryOver(const FReferenceSkeleton& From, const FReferenceSkeleton& To)
{
	FCarryOver Result;
	Result.Bones = From.GetRawBoneNum();
	for (int32 Bone = 0; Bone < Result.Bones; ++Bone)
	{
		const FName Name = From.GetBoneName(Bone);
		const int32 Target = To.FindBoneIndex(Name);
		if (Target == INDEX_NONE)
		{
			++Result.Missing;
		}
		else if (SameParentChain(From, Bone, To, Target))
		{
			++Result.Carried;
		}
		else
		{
			if (Result.Moved < MaxNamesListed)
			{
				if (!Result.MovedNames.IsEmpty())
				{
					Result.MovedNames += TEXT(", ");
				}
				Result.MovedNames += Name.ToString();
			}
			++Result.Moved;
		}
	}
	return Result;
}

// Curve names of From that To does not know (their tracks are left out of adopted animations). OutTotal: From's count.
TArray<FString> CurvesMissing(const USkeleton* From, const USkeleton* To, int32& OutTotal)
{
	TArray<FString> Missing;
	OutTotal = 0;
	const FSmartNameMapping* FromCurves = From ? From->GetSmartNameContainer(USkeleton::AnimCurveMappingName) : nullptr;
	if (!FromCurves)
	{
		return Missing;
	}
	const FSmartNameMapping* ToCurves = To ? To->GetSmartNameContainer(USkeleton::AnimCurveMappingName) : nullptr;
	TArray<FName> Names;
	FromCurves->FillNameArray(Names);
	OutTotal = Names.Num();
	for (const FName& Name : Names)
	{
		if (!ToCurves || !ToCurves->Exists(Name))
		{
			Missing.Add(Name.ToString());
		}
	}
	Missing.Sort();
	return Missing;
}

// One line about what of From's animations survives on To: bones and curves.
void ReportCarryOver(USkeleton* From, USkeleton* To, const TCHAR* Indent, FString& Report, bool& bOk)
{
	const FCarryOver Carry = CheckCarryOver(From->GetReferenceSkeleton(), To->GetReferenceSkeleton());
	Report += FString::Printf(TEXT("%s%s -> %s: %d of %d bones carry over (same name and parent chain), %d missing on %s, %d placed differently%s%s\n"),
		Indent, *From->GetName(), *To->GetName(), Carry.Carried, Carry.Bones, Carry.Missing, *To->GetName(), Carry.Moved,
		Carry.Moved > 0 ? TEXT(" (they keep their own pose or physics): ") : TEXT(""), *Carry.MovedNames);
	if (Carry.Carried == 0)
	{
		Report += FString::Printf(TEXT("%sERROR: no bone carries over (root '%s' on %s, '%s' on %s)\n"), Indent,
			*From->GetReferenceSkeleton().GetBoneName(0).ToString(), *From->GetName(), *To->GetReferenceSkeleton().GetBoneName(0).ToString(), *To->GetName());
		bOk = false;
	}
	int32 Curves = 0;
	const TArray<FString> Missing = CurvesMissing(From, To, Curves);
	if (Missing.Num() > 0)
	{
		TArray<FString> Listed = Missing;
		if (Listed.Num() > MaxNamesListed)
		{
			Listed.SetNum(MaxNamesListed);
			Listed.Add(TEXT("..."));
		}
		Report += FString::Printf(TEXT("%s%d of %d curve name(s) of %s are unknown to %s, so those curve tracks are left out: %s\n"),
			Indent, Missing.Num(), Curves, *From->GetName(), *To->GetName(), *FString::Join(Listed, TEXT(" ")));
	}
}

// ------------------------------------------------------------------------------------------------
// Assets
// ------------------------------------------------------------------------------------------------
// The meshes listed (Receiving Meshes), or every mesh on the skeleton the asset registry knows (up to MaxMeshesPerPair).
TArray<USkeletalMesh*> MeshesFor(USkeleton* Receiving, const TArray<TSoftObjectPtr<USkeletalMesh>>& Listed, const TCHAR* Indent, FString& Report)
{
	TArray<USkeletalMesh*> Meshes;
	if (Listed.Num() > 0)
	{
		for (const TSoftObjectPtr<USkeletalMesh>& Soft : Listed)
		{
			if (Soft.IsNull())
			{
				continue;
			}
			USkeletalMesh* Mesh = Soft.LoadSynchronous();
			if (!Mesh)
			{
				Report += FString::Printf(TEXT("%s! mesh %s could not be loaded\n"), Indent, *Soft.ToString());
				continue;
			}
			if (Mesh->Skeleton != Receiving)
			{
				Report += FString::Printf(TEXT("%s! %s uses %s, not the receiving skeleton: the game will not rebind it\n"), Indent,
					*Mesh->GetName(), *PathOf(Mesh->Skeleton));
			}
			Meshes.Add(Mesh);
		}
		return Meshes;
	}

	IAssetRegistry& Registry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();
	FARFilter Filter;
	Filter.ClassNames.Add(USkeletalMesh::StaticClass()->GetFName());
	Filter.bRecursiveClasses = true;
	Filter.TagsAndValues.Add(FName(TEXT("Skeleton")), FAssetData(Receiving).GetExportTextName());
	TArray<FAssetData> Assets;
	Registry.GetAssets(Filter, Assets);
	for (const FAssetData& Asset : Assets)
	{
		if (Meshes.Num() >= MaxMeshesPerPair)
		{
			Report += FString::Printf(TEXT("%s(only the first %d meshes were checked)\n"), Indent, MaxMeshesPerPair);
			break;
		}
		if (USkeletalMesh* Mesh = Cast<USkeletalMesh>(Asset.GetAsset()))
		{
			Meshes.Add(Mesh);
		}
	}
	return Meshes;
}

TArray<USkeleton*> LoadSkeletons(const std::vector<std::wstring>& Paths)
{
	TArray<USkeleton*> Out;
	for (const std::wstring& Path : Paths)
	{
		if (USkeleton* Skeleton = Cast<USkeleton>(FSoftObjectPath(FromWide(Path)).TryLoad()))
		{
			Out.AddUnique(Skeleton);
		}
	}
	return Out;
}

// Mesh rebind: each mesh against the skeletons it is bound to in game, with the hierarchy fix, and against the skeletons
// whose AnimBlueprints must keep accepting it.
void CheckMeshPair(const FEndSkeletonCompatPair& Pair, USkeleton* Receiving, const TArray<USkeleton*>& Targets, const TArray<USkeleton*>& Keep,
	FString& Report, bool& bOk)
{
	const TArray<USkeletalMesh*> Meshes = MeshesFor(Receiving, Pair.ReceivingMeshes, TEXT("    "), Report);
	if (Meshes.Num() == 0)
	{
		Report += TEXT("    no meshes found on the receiving skeleton to check\n");
	}
	for (USkeletalMesh* Mesh : Meshes)
	{
		if (IsCookedAsset(Mesh))
		{
			Report += FString::Printf(TEXT("    note: %s is a game mesh. While this pair is active it uses the animation skeleton everywhere the game shows it, so its own AnimBlueprints stop working there (its animations stay on its own skeleton; a Family keeps them working). For a replacement character, list your own copy of the mesh instead.\n"), *Mesh->GetName());
		}
		for (USkeleton* Skeleton : Targets)
		{
			const FBoneCheck Check = CheckMesh(Mesh->RefSkeleton, Skeleton->GetReferenceSkeleton());
			FString Verdict;
			if (Check.bCompatible)
			{
				Verdict = TEXT("OK, AnimBlueprints for this skeleton will run");
			}
			else if (Check.bFixable && Pair.bFixHierarchy)
			{
				Verdict = FString::Printf(TEXT("OK with the hierarchy fix: %d bone(s) fail the parent-chain test, the mod renames the ones placed differently in game and they keep the mesh's own pose. First: %s"),
					Check.Misplaced, *Check.Problem);
			}
			else if (Check.bFixable)
			{
				Verdict = TEXT("REFUSED by the game (T-pose), Fix Hierarchy is off: ") + Check.Problem;
				bOk = false;
			}
			else
			{
				Verdict = TEXT("REFUSED by the game (T-pose): ") + Check.Problem;
				bOk = false;
			}
			Report += FString::Printf(TEXT("    %s -> %s: %d shared, %d mesh-only, %d animation-only. %s\n"), *Mesh->GetName(), *Skeleton->GetName(),
				Check.Matched, Check.MeshOnly, Check.AnimationOnly, *Verdict);
			if (Keep.Num() > 0 && (Check.bCompatible || Check.bFixable))
			{
				const FFixResult Fix = PlanFix(Mesh, Skeleton, Keep, Pair.bFixHierarchy);
				TArray<FString> KeepNames;
				for (USkeleton* KeepSkeleton : Keep)
				{
					if (KeepSkeleton && KeepSkeleton != Skeleton && !Fix.KeepRefused.Contains(KeepSkeleton->GetName()))
					{
						KeepNames.Add(KeepSkeleton->GetName());
					}
				}
				if (KeepNames.Num() > 0)
				{
					Report += FString::Printf(TEXT("      AnimBlueprints made for %s still run on it%s\n"), *ListText(KeepNames),
						Fix.Renamed > 0 ? *FString::Printf(TEXT(" (%d bone(s) renamed)"), Fix.Renamed) : TEXT(""));
				}
				if (Fix.KeepRefused.Num() > 0)
				{
					Report += FString::Printf(TEXT("      WARNING: AnimBlueprints made for %s would be refused on it\n"), *ListText(Fix.KeepRefused));
				}
			}
		}
	}
}

// Animations method (moving animations): what carries over from each animation skeleton.
void CheckAnimationsPair(const FEndSkeletonCompatPair& Pair, USkeleton* Receiving, const TArray<USkeleton*>& Animation, FString& Report, bool& bOk)
{
	for (USkeleton* Skeleton : Animation)
	{
		ReportCarryOver(Skeleton, Receiving, TEXT("    "), Report, bOk);
	}
	if (Pair.ReceivingMeshes.Num() > 0)
	{
		Report += TEXT("    note: Receiving Meshes only apply to Mesh rebind pairs; they are not exported for this pair\n");
	}
	if (Pair.RequiresPaks.Num() == 0)
	{
		Report += TEXT("    note: no Requires Paks, so this pair is always on: while it is, the animation skeleton's own characters cannot play the adopted animations, even without your swap pak installed. Name your swap pak in Requires Paks, or make it a Family to share the animations.\n");
	}
}

// A family member: its animations move onto the hub and its meshes are bound to the hub, with the hierarchy fix that
// keeps both the hub's AnimBlueprints and its own running.
void CheckFamilyMember(const FEndSkeletonCompatPair& Pair, USkeleton* Member, USkeleton* Hub, FString& Report, bool& bOk)
{
	Report += FString::Printf(TEXT("    member %s:\n"), *Member->GetName());
	ReportCarryOver(Member, Hub, TEXT("      its animations on the hub: "), Report, bOk);
	const TArray<USkeletalMesh*> Meshes = MeshesFor(Member, TArray<TSoftObjectPtr<USkeletalMesh>>(), TEXT("      "), Report);
	if (Meshes.Num() == 0)
	{
		Report += TEXT("      no meshes found on this skeleton to check\n");
	}
	TArray<USkeleton*> Keep;
	Keep.Add(Member);
	for (USkeletalMesh* Mesh : Meshes)
	{
		const FFixResult Fix = PlanFix(Mesh, Hub, Keep, Pair.bFixHierarchy);
		const FBoneCheck Check = CheckMesh(Mesh->RefSkeleton, Hub->GetReferenceSkeleton());
		FString Verdict;
		if (!Fix.bPossible)
		{
			Verdict = TEXT("REFUSED by the game (T-pose): ") + Check.Problem;
			bOk = false;
		}
		else if (Fix.bTargetOk && Fix.KeepRefused.Num() == 0)
		{
			Verdict = Fix.Renamed > 0
				? FString::Printf(TEXT("OK with the hierarchy fix: %d bone(s) renamed (they keep the mesh's own pose): %s. AnimBlueprints for %s and for %s both run"),
					Fix.Renamed, *Fix.Names, *Hub->GetName(), *Member->GetName())
				: FString::Printf(TEXT("OK, AnimBlueprints for %s and for %s both run"), *Hub->GetName(), *Member->GetName());
		}
		else if (!Pair.bFixHierarchy)
		{
			Verdict = TEXT("REFUSED for the hub's AnimBlueprints (T-pose), Fix Hierarchy is off: ") + Check.Problem;
			bOk = false;
		}
		else
		{
			Verdict = FString::Printf(TEXT("REFUSED (T-pose) for %s even with the hierarchy fix"), Fix.bTargetOk ? *ListText(Fix.KeepRefused) : *Hub->GetName());
			bOk = false;
		}
		Report += FString::Printf(TEXT("      %s on %s: %d shared bones, %d only on the mesh (they keep their own pose or physics). %s\n"), *Mesh->GetName(),
			*Hub->GetName(), Check.Matched, Check.MeshOnly, *Verdict);
	}
}

// ------------------------------------------------------------------------------------------------
// The game's view: every compat file the mod reads plus this data object, settled by the mod's own rules
// (SkelCompat::FinishConfig): families, outfits that follow animations, pairs switched off.
// ------------------------------------------------------------------------------------------------
struct FGameView
{
	bool bHasGame = false;          // the game folder with RebirthSkelCompat was found
	TArray<FString> Files;          // files read, in the mod's order
	TArray<FString> Problems;       // files the mod would skip
	SkelCompat::Config Config;      // as the mod has it after reading every file
};

// Names requires_paks can match, like the mod: every .pak / .utoc under End\Content\Paks and End\Mods (file name without
// extension), and the folders directly inside ~mods and End\Mods.
TSet<FString> InstalledNames(const FString& Game)
{
	TSet<FString> Names;
	const FString Paks = Game / TEXT("End/Content/Paks");
	const FString Mods = Game / TEXT("End/Mods");
	for (const FString& Root : {Paks, Mods})
	{
		for (const TCHAR* Pattern : {TEXT("*.pak"), TEXT("*.utoc")})
		{
			TArray<FString> Found;
			IFileManager::Get().FindFilesRecursive(Found, *Root, Pattern, true, false);
			for (const FString& File : Found)
			{
				Names.Add(FPaths::GetBaseFilename(File).ToLower());
			}
		}
	}
	for (const FString& Root : {Paks / TEXT("~mods"), Mods})
	{
		TArray<FString> Folders;
		IFileManager::Get().FindFiles(Folders, *(Root / TEXT("*")), false, true);
		for (const FString& Folder : Folders)
		{
			Names.Add(Folder.ToLower());
		}
	}
	return Names;
}

struct FConfigSource
{
	FString Path;
	FString Label;
	bool bOwn = false;
};

// The mod reads compat\*.json and every <name>.skelcompat.json in ~mods and End\Mods, sorted by full path (compat\ first,
// by file name). This data object's JSON takes the place of its own compat file, and of a copy shipped in ~mods.
TArray<FConfigSource> ConfigSources(const FString& Game, const FString& OwnName)
{
	TArray<FConfigSource> Sources;
	const FString Compat = Game / ModFolder / TEXT("compat");
	TArray<FString> Files;
	IFileManager::Get().FindFiles(Files, *(Compat / TEXT("*.json")), true, false);
	for (const FString& File : Files)
	{
		FConfigSource Source;
		Source.Path = Compat / File;
		Source.Label = File;
		Source.bOwn = FPaths::GetBaseFilename(File).Equals(OwnName, ESearchCase::IgnoreCase);
		Sources.Add(Source);
	}
	if (!Sources.ContainsByPredicate([](const FConfigSource& Source) { return Source.bOwn; }))
	{
		FConfigSource Own;
		Own.Path = Compat / (OwnName + TEXT(".json"));
		Own.Label = OwnName + TEXT(".json");
		Own.bOwn = true;
		Sources.Add(Own);
	}
	for (const FString& Root : {Game / TEXT("End/Content/Paks/~mods"), Game / TEXT("End/Mods")})
	{
		TArray<FString> Found;
		IFileManager::Get().FindFilesRecursive(Found, *Root, TEXT("*.skelcompat.json"), true, false);
		for (const FString& File : Found)
		{
			const FString Name = FPaths::GetCleanFilename(File);
			if (Name.Equals(OwnName + TEXT(".skelcompat.json"), ESearchCase::IgnoreCase))
			{
				continue;
			}
			FConfigSource Source;
			Source.Path = File;
			Source.Label = Name;
			Sources.Add(Source);
		}
	}
	Sources.Sort([](const FConfigSource& A, const FConfigSource& B) { return A.Path.Compare(B.Path, ESearchCase::CaseSensitive) < 0; });
	return Sources;
}

std::string Utf8Of(const FString& Text)
{
	const FTCHARToUTF8 Converted(*Text);
	return std::string(Converted.Get(), static_cast<size_t>(Converted.Length()));
}

FGameView SettleInGame(const FString& Game, const FString& OwnName, const FString& OwnJson)
{
	FGameView View;
	View.bHasGame = !Game.IsEmpty() && IFileManager::Get().DirectoryExists(*(Game / ModFolder));
	TSet<FString> Installed;
	if (View.bHasGame)
	{
		Installed = InstalledNames(Game);
		for (const FConfigSource& Source : ConfigSources(Game, OwnName))
		{
			std::string Bytes;
			if (Source.bOwn)
			{
				Bytes = Utf8Of(OwnJson);
			}
			else
			{
				TArray<uint8> Data;
				if (IFileManager::Get().FileSize(*Source.Path) > MaxConfigFileBytes || !FFileHelper::LoadFileToArray(Data, *Source.Path))
				{
					View.Problems.Add(Source.Label + TEXT(" could not be read (or is over 1 MB), the mod skips it"));
					continue;
				}
				Bytes.assign(reinterpret_cast<const char*>(Data.GetData()), static_cast<size_t>(Data.Num()));
			}
			SkelCompat::AppendConfig(Bytes, Wide(Source.Label), View.Config);
			View.Files.Add(Source.bOwn ? Source.Label + TEXT(" (this data object)") : Source.Label);
		}
	}
	else
	{
		SkelCompat::AppendConfig(Utf8Of(OwnJson), Wide(OwnName + TEXT(".json")), View.Config);
		View.Files.Add(OwnName + TEXT(".json (this data object)"));
	}
	const bool bHasGame = View.bHasGame;
	SkelCompat::FinishConfig(View.Config, [&](const std::wstring& Name) { return !bHasGame || Installed.Contains(FromWide(Name).ToLower()); });
	return View;
}

// The settled entry for a skeleton: once the mod has settled the pairs, each skeleton receives at most one.
const SkelCompat::Pair* SettledFor(const FGameView& View, const FString& SkeletonPath)
{
	const std::wstring Path = Wide(NormalizedObjectPath(SkeletonPath));
	return View.Config.FindForSkeleton(Path);
}

USkeleton* LoadPath(const std::wstring& Path) { return Cast<USkeleton>(FSoftObjectPath(FromWide(Path)).TryLoad()); }

// ------------------------------------------------------------------------------------------------
// One pair of this data object
// ------------------------------------------------------------------------------------------------
bool CheckPair(const FEndSkeletonCompatPair& Pair, int32 Index, const TArray<FEndSkeletonCompatPair>& All, const FGameView& View, FString& Report)
{
	Report += FString::Printf(TEXT("Pair %d (%s): %s\n"), Index, MethodLabel(Pair.Method),
		Pair.ReceivingSkeleton.IsNull() ? TEXT("(no receiving skeleton)") : *Pair.ReceivingSkeleton.ToString());
	if (!Pair.bEnabled)
	{
		Report += TEXT("    disabled\n");
		return true;
	}
	USkeleton* First = Pair.ReceivingSkeleton.LoadSynchronous();
	if (!First)
	{
		Report += Pair.Method == EEndSkelCompatMethod::Family ? TEXT("    ERROR: the hub (Receiving Skeleton) is not set or not found\n")
															 : TEXT("    ERROR: receiving skeleton not set or not found\n");
		return false;
	}
	bool bOk = true;
	TArray<USkeleton*> Receivers;
	Receivers.Add(First);
	for (const TSoftObjectPtr<USkeleton>& Soft : Pair.MoreReceivingSkeletons)
	{
		if (Soft.IsNull())
		{
			continue;
		}
		USkeleton* Skeleton = Soft.LoadSynchronous();
		if (!Skeleton)
		{
			Report += FString::Printf(TEXT("    ERROR: skeleton %s not found\n"), *Soft.ToString());
			bOk = false;
			continue;
		}
		Receivers.AddUnique(Skeleton);
	}
	TArray<USkeleton*> Animation;
	for (const TSoftObjectPtr<USkeleton>& Soft : Pair.AnimationSkeletons)
	{
		if (Soft.IsNull())
		{
			continue;
		}
		USkeleton* Skeleton = Soft.LoadSynchronous();
		if (!Skeleton)
		{
			Report += FString::Printf(TEXT("    ERROR: animation skeleton %s not found\n"), *Soft.ToString());
			bOk = false;
		}
		else if (Receivers.Contains(Skeleton))
		{
			if (Pair.Method != EEndSkelCompatMethod::Family)
			{
				Report += FString::Printf(TEXT("    note: %s is a receiving skeleton of this pair too; it is left out of its own animation skeletons\n"), *Skeleton->GetName());
			}
		}
		else
		{
			Animation.AddUnique(Skeleton);
		}
	}

	if (Pair.Method == EEndSkelCompatMethod::Family)
	{
		TArray<USkeleton*> Members;
		for (int32 Receiver = 1; Receiver < Receivers.Num(); ++Receiver)
		{
			Members.AddUnique(Receivers[Receiver]);
		}
		for (USkeleton* Skeleton : Animation)
		{
			Members.AddUnique(Skeleton);
		}
		if (Members.Num() == 0)
		{
			Report += TEXT("    ERROR: a family needs at least one skeleton besides the hub (Animation Skeletons)\n");
			return false;
		}
		// In game another entry may already have named a different hub for some of these skeletons.
		USkeleton* Hub = First;
		if (const SkelCompat::Pair* Settled = SettledFor(View, PathOf(Members[0])))
		{
			if (!Settled->FamilyHub.empty() && !SamePath(FromWide(Settled->FamilyHub), PathOf(First)))
			{
				USkeleton* GameHub = LoadPath(Settled->FamilyHub);
				Report += FString::Printf(TEXT("    note: in game this family gathers on %s, named first by %s; the checks below use that hub\n"),
					*ShortName(Settled->FamilyHub), *FromWide(Settled->Origin));
				if (GameHub)
				{
					Hub = GameHub;
					Members.Remove(GameHub);
					Members.AddUnique(First);
				}
			}
		}
		Report += FString::Printf(TEXT("    hub %s: its own characters and animations stay as they are; the members' animations move onto it and their meshes are bound to it\n"),
			*Hub->GetName());
		if (IsCookedAsset(Hub) == false)
		{
			Report += TEXT("    note: the hub is your own skeleton, so every member moves onto it (a union skeleton with all their bones keeps the most animation)\n");
		}
		for (USkeleton* Member : Members)
		{
			CheckFamilyMember(Pair, Member, Hub, Report, bOk);
		}
		if (Pair.AdoptPaths.Num() > 0 || Pair.ReceivingMeshes.Num() > 0)
		{
			Report += TEXT("    note: Adopt Paths and Receiving Meshes are not used by a family (it shares every animation and binds every mesh)\n");
		}
	}
	else
	{
		for (USkeleton* Receiving : Receivers)
		{
			if (Receivers.Num() > 1)
			{
				Report += FString::Printf(TEXT("  receiving %s:\n"), *Receiving->GetName());
			}
			const SkelCompat::Pair* Settled = SettledFor(View, PathOf(Receiving));
			if (Pair.Method == EEndSkelCompatMethod::Mesh)
			{
				if (IsCookedAsset(Receiving))
				{
					Report += TEXT("    note: the receiving skeleton is a game asset, so Apply To Skeletons leaves it alone; use Export Json\n");
				}
				TArray<USkeleton*> Targets = Animation;
				TArray<USkeleton*> Keep;
				if (Settled && Settled->Use == SkelCompat::Method::Mesh)
				{
					Targets = LoadSkeletons(Settled->Animation);
					Keep = LoadSkeletons(Settled->KeepCompatible);
					if (!Settled->FamilyHub.empty())
					{
						Report += FString::Printf(TEXT("    note: in game this skeleton is a member of the family of %s, so its meshes are bound to %s\n"),
							*ShortName(Settled->FamilyHub), *ShortName(Settled->FamilyHub));
					}
					else if (Keep.Num() > 0)
					{
						Report += FString::Printf(TEXT("    note: in game these meshes follow the animations of %s to %s (checked against those, and kept compatible with the AnimBlueprints they were made for)\n"),
							*ShortList(Settled->KeepCompatible), *ShortList(Settled->Animation));
					}
				}
				else if (Settled)
				{
					Report += TEXT("    WARNING: in game this skeleton receives animations through another entry (the earlier entry for a skeleton keeps its method); these meshes are not rebound\n");
				}
				else
				{
					Report += TEXT("    note: in game this pair is off (see the In game section below)\n");
				}
				if (Targets.Num() == 0)
				{
					Report += TEXT("    ERROR: no usable animation skeleton\n");
					bOk = false;
					continue;
				}
				CheckMeshPair(Pair, Receiving, Targets, Keep, Report, bOk);
				if (!Pair.bCarrySockets)
				{
					Report += TEXT("    note: Carry Sockets is off: rebound meshes only find the sockets of the skeleton they are bound to\n");
				}
				continue;
			}

			// Animations
			if (Animation.Num() == 0)
			{
				Report += TEXT("    ERROR: no usable animation skeleton\n");
				bOk = false;
				continue;
			}
			if (Settled && !Settled->FamilyHub.empty())
			{
				// The pairs the game turned into a family: they share instead of moving animations away.
				USkeleton* Hub = LoadPath(Settled->FamilyHub);
				if (!Hub)
				{
					Report += FString::Printf(TEXT("    ERROR: in game this is part of the family of %s, which could not be loaded\n"), *ShortName(Settled->FamilyHub));
					bOk = false;
					continue;
				}
				if (Hub == Receiving)
				{
					Report += FString::Printf(TEXT("    in game: %s is the hub of a family (%s): it keeps its characters and animations, and the members' animations and meshes move onto it\n"),
						*Receiving->GetName(), *FromWide(Settled->Origin));
					for (USkeleton* Member : LoadSkeletons(Settled->Animation))
					{
						CheckFamilyMember(Pair, Member, Hub, Report, bOk);
					}
				}
				else
				{
					Report += FString::Printf(TEXT("    in game: these skeletons share their animations as the family of %s (the pairs want the same animations, or chain): %s's meshes are bound to %s and its animations move there\n"),
						*Hub->GetName(), *Receiving->GetName(), *Hub->GetName());
					CheckFamilyMember(Pair, Receiving, Hub, Report, bOk);
				}
				continue;
			}
			CheckAnimationsPair(Pair, Receiving, Animation, Report, bOk);
			if (!Settled)
			{
				Report += TEXT("    note: in game this pair is off (see the In game section below)\n");
			}
		}
	}

	for (int32 Other = 0; Other < Index; ++Other)
	{
		const FEndSkeletonCompatPair& OtherPair = All[Other];
		if (!OtherPair.bEnabled || OtherPair.ReceivingSkeleton.ToSoftObjectPath() != Pair.ReceivingSkeleton.ToSoftObjectPath() ||
			OtherPair.Method == EEndSkelCompatMethod::Family || Pair.Method == EEndSkelCompatMethod::Family)
		{
			continue;
		}
		Report += OtherPair.Method == Pair.Method
			? FString::Printf(TEXT("    note: same receiving skeleton as pair %d; the mod merges both lists\n"), Other)
			: FString::Printf(TEXT("    WARNING: same receiving skeleton as pair %d with another method; the mod merges both lists and keeps pair %d's method\n"), Other, Other);
	}
	return bOk;
}

// What the game makes of all compat files together, for the skeletons this data object names.
void ReportInGame(const FGameView& View, const TArray<FString>& Mine, const FString& OwnFile, FString& Report)
{
	const auto Involves = [&](const std::wstring& Path) {
		return Mine.ContainsByPredicate([&](const FString& Own) { return SamePath(Own, FromWide(Path)); });
	};
	Report += View.bHasGame
		? FString::Printf(TEXT("\nIn game (RebirthSkelCompat 3.2 rules; files read: %s):\n"), *ListText(View.Files))
		: FString(TEXT("\nIn game (game folder not found: this data object alone, Requires Paks counted as installed):\n"));
	int32 Lines = 0;
	for (const SkelCompat::Pair& Settled : View.Config.Pairs)
	{
		bool bMine = Involves(Settled.Receiving);
		for (const std::wstring& Path : Settled.Animation)
		{
			bMine = bMine || Involves(Path);
		}
		if (!bMine)
		{
			continue;
		}
		++Lines;
		if (Settled.Use == SkelCompat::Method::Animations && !Settled.FamilyHub.empty())
		{
			Report += FString::Printf(TEXT("  family of %s: %s play each other's animations with it (their animations move onto %s, their meshes are bound to it)\n"),
				*ShortName(Settled.Receiving), *ShortList(Settled.Animation), *ShortName(Settled.Receiving));
		}
		else if (Settled.Use == SkelCompat::Method::Animations)
		{
			TArray<FString> Paths;
			for (const std::wstring& Path : Settled.AdoptPaths)
			{
				Paths.Add(FromWide(Path));
			}
			Report += FString::Printf(TEXT("  %s takes over the animations of %s%s\n"), *ShortName(Settled.Receiving), *ShortList(Settled.Animation),
				Paths.Num() > 0 ? *(TEXT(" under ") + ListText(Paths)) : TEXT(""));
		}
		else if (Settled.FamilyHub.empty())
		{
			Report += FString::Printf(TEXT("  meshes on %s are bound to %s%s\n"), *ShortName(Settled.Receiving), *ShortList(Settled.Animation),
				Settled.KeepCompatible.empty() ? TEXT("") : *(TEXT(" (and still accepted by AnimBlueprints made for ") + ShortList(Settled.KeepCompatible) + TEXT(")")));
		}
		else
		{
			--Lines; // a family member's meshes: covered by the family line
		}
	}
	if (Lines == 0)
	{
		Report += TEXT("  none of this data object's pairs is on\n");
	}
	for (const std::wstring& Message : View.Config.Messages)
	{
		const FString Text = FromWide(Message);
		// A file the mod skips (invalid JSON, wrong schema) changes what the game does, whichever skeletons it names.
		const bool bMine = Text.StartsWith(OwnFile) || Text.EndsWith(TEXT("file skipped")) ||
			Mine.ContainsByPredicate([&](const FString& Own) { return Text.Contains(NormalizedObjectPath(Own)); });
		if (bMine)
		{
			Report += TEXT("  note: ") + Text + TEXT("\n");
		}
	}
	for (const FString& Problem : View.Problems)
	{
		Report += TEXT("  note: ") + Problem + TEXT("\n");
	}
}

// "/Game/Motion/Player/PC0000_Cloud/Battle00.Battle00" -> "PC0000_Cloud/Battle00"
FString ShortSource(const FString& Path)
{
	FString Package = Path;
	int32 Dot = INDEX_NONE;
	if (Package.FindChar(TEXT('.'), Dot))
	{
		Package = Package.Left(Dot);
	}
	TArray<FString> Parts;
	Package.ParseIntoArray(Parts, TEXT("/"), true);
	return Parts.Num() >= 2 ? Parts[Parts.Num() - 2] + TEXT("/") + Parts.Last() : Package;
}

// ------------------------------------------------------------------------------------------------
// Auto-match preview (3.2): the picks the game makes, worked out with the mod's own rules from the sets this project
// has, else read from the game's last RebirthSkelCompat.log.
// ------------------------------------------------------------------------------------------------
struct FSetContents
{
	std::vector<uint64_t> Keys;
	std::vector<SkelCompat::MatchAnim> Anims;
};

uint64_t NameKey(const FName& Name)
{
	return (static_cast<uint64_t>(Name.GetComparisonIndex().ToUnstableInt()) << 32) | static_cast<uint32_t>(Name.GetNumber());
}

// A UEndAnimSet's AnimationAssets, by reflection (the EndGame module stays optional for this plugin).
bool ReadEndAnimSet(UObject* Set, FSetContents& Out)
{
	if (!Set) { return false; }
	FMapProperty* Map = FindFProperty<FMapProperty>(Set->GetClass(), TEXT("AnimationAssets"));
	FObjectPropertyBase* Value = Map ? CastField<FObjectPropertyBase>(Map->ValueProp) : nullptr;
	if (!Map || !CastField<FNameProperty>(Map->KeyProp) || !Value) { return false; }
	FScriptMapHelper Helper(Map, Map->ContainerPtrToValuePtr<void>(Set));
	for (int32 Index = 0; Index < Helper.GetMaxIndex(); ++Index)
	{
		if (!Helper.IsValidIndex(Index)) { continue; }
		const FName Key = *reinterpret_cast<const FName*>(Helper.GetKeyPtr(Index));
		UObject* Animation = Value->GetObjectPropertyValue(Helper.GetValuePtr(Index));
		SkelCompat::MatchAnim Anim;
		Anim.Name = Wide(Key.ToString());
		if (const UAnimSequenceBase* Sequence = Cast<UAnimSequenceBase>(Animation)) { Anim.Length = Sequence->SequenceLength; }
		if (const UAnimSequence* Sequence = Cast<UAnimSequence>(Animation)) { Anim.Additive = Sequence->IsValidAdditive(); }
		Out.Keys.push_back(NameKey(Key));
		Out.Anims.push_back(Anim);
	}
	return true;
}

// The pack's own set of that name (CharaSpec pack AssetDataList[].AssetUserData), when the pack is in this project.
UObject* PackOwnSet(const FString& PackPath, const FString& SetName)
{
	if (PackPath.IsEmpty() || !InProject(PackPath)) { return nullptr; }
	UObject* Pack = LoadObject<UObject>(nullptr, *PackPath);
	FArrayProperty* List = Pack ? FindFProperty<FArrayProperty>(Pack->GetClass(), TEXT("AssetDataList")) : nullptr;
	FStructProperty* Entry = List ? CastField<FStructProperty>(List->Inner) : nullptr;
	FArrayProperty* Objects = Entry ? FindFProperty<FArrayProperty>(Entry->Struct, TEXT("AssetUserData")) : nullptr;
	FObjectPropertyBase* Item = Objects ? CastField<FObjectPropertyBase>(Objects->Inner) : nullptr;
	if (!Item) { return nullptr; }
	FScriptArrayHelper Entries(List, List->ContainerPtrToValuePtr<void>(Pack));
	for (int32 E = 0; E < Entries.Num(); ++E)
	{
		FScriptArrayHelper Users(Objects, Objects->ContainerPtrToValuePtr<void>(Entries.GetRawPtr(E)));
		for (int32 U = 0; U < Users.Num(); ++U)
		{
			UObject* Object = Item->GetObjectPropertyValue(Users.GetRawPtr(U));
			if (Object && Object->GetName().Equals(SetName, ESearchCase::IgnoreCase) && FindFProperty<FMapProperty>(Object->GetClass(), TEXT("AnimationAssets")))
			{
				return Object;
			}
		}
	}
	return nullptr;
}

// The game's RebirthSkelCompat.log, or empty.
FString GameLogText(const FString& GameDirectory)
{
	FString Text;
	if (!GameDirectory.IsEmpty()) { FFileHelper::LoadFileToString(Text, *(GameDirectory / ModFolder / TEXT("RebirthSkelCompat.log"))); }
	return Text;
}

// The auto-matched lines of one set from the last "Animation sets of <pack>:" block of the game log.
TArray<FString> LastRunPicks(const FString& Log, const FString& PackPath, const FString& SetName)
{
	TArray<FString> Lines, Picks;
	Log.ParseIntoArrayLines(Lines, false);
	int32 Start = INDEX_NONE;
	const FString Header = TEXT("Animation sets of ") + NormalizedObjectPath(PackPath);
	for (int32 K = Lines.Num() - 1; K >= 0 && Start == INDEX_NONE; --K)
	{
		if (Lines[K].Contains(Header, ESearchCase::IgnoreCase)) { Start = K + 1; }
	}
	if (Start == INDEX_NONE) { return Picks; }
	bool bInSet = false, bInPicks = false;
	for (int32 K = Start; K < Lines.Num() && !Lines[K].StartsWith(TEXT("[")); ++K)
	{
		const FString Trimmed = Lines[K].TrimStart();
		const int32 Indent = Lines[K].Len() - Trimmed.Len();
		if (Indent <= 4)
		{
			bInSet = Trimmed.StartsWith(SetName + TEXT(":"), ESearchCase::IgnoreCase);
			bInPicks = false;
			continue;
		}
		if (!bInSet) { continue; }
		if (Trimmed.StartsWith(TEXT("auto-matched"))) { bInPicks = true; continue; }
		if (bInPicks) { Picks.Add(Trimmed); }
	}
	return Picks;
}

// Validate: what each auto source of the set gives, before the game runs.
void PreviewAutoMatch(const SkelCompat::AnimSetRow& Core, const std::wstring& Name, const TArray<FString>& PackPaths, const FString& GameLog, FString& Report)
{
	const std::vector<SkelCompat::SetSourceRef> Refs = SkelCompat::SetSourcesFor(Core, Name);
	if (std::none_of(Refs.begin(), Refs.end(), [](const SkelCompat::SetSourceRef& Ref) { return Ref.Auto != SkelCompat::AutoMatchMode::Off; })) { return; }
	std::vector<SkelCompat::MergeSource> Inputs;
	TArray<FString> Labels, Missing;
	bool bMissingAuto = false;
	for (const SkelCompat::SetSourceRef& Ref : Refs)
	{
		UObject* Set = nullptr;
		for (const std::wstring& Path : Ref.Paths)
		{
			if (InProject(FromWide(Path))) { Set = LoadObject<UObject>(nullptr, *FromWide(Path)); }
			if (Set) { break; }
		}
		FSetContents Contents;
		if (!Set || !ReadEndAnimSet(Set, Contents))
		{
			Missing.Add(ShortSource(FromWide(Ref.Paths.front())));
			bMissingAuto |= Ref.Auto != SkelCompat::AutoMatchMode::Off;
			continue;
		}
		SkelCompat::MergeSource Input;
		Input.Auto = Ref.Auto;
		Input.Only = Ref.Only;
		Input.Keys = std::move(Contents.Keys);
		Input.Anims = std::move(Contents.Anims);
		Inputs.push_back(std::move(Input));
		Labels.Add(ShortSource(Set->GetPathName()));
	}
	for (const FString& Pack : PackPaths)
	{
		FSetContents Contents;
		if (UObject* Own = PackOwnSet(Pack, FromWide(Name)); Own && ReadEndAnimSet(Own, Contents))
		{
			SkelCompat::MergeSource Input;
			Input.Keys = std::move(Contents.Keys);
			Input.Anims = std::move(Contents.Anims);
			Inputs.push_back(std::move(Input));
			Labels.Add(TEXT("the pack's own ") + FromWide(Name));
			break;
		}
	}
	if (!bMissingAuto && !Inputs.empty())
	{
		const std::vector<SkelCompat::MergedEntry> Merged = SkelCompat::MergeSetSources(Inputs);
		TArray<FString> Lines;
		for (const SkelCompat::MergedEntry& Entry : Merged)
		{
			if (Entry.Tier < 2) { continue; }
			const SkelCompat::MergeSource& From = Inputs[Entry.Source];
			FString Picked = FromWide(From.Anims[Entry.Entry].Name);
			float Length = From.Anims[Entry.Entry].Length;
			if (Entry.Chain.size() > 1)
			{
				Picked.Reset();
				Length = 0.f;
				for (const size_t Piece : Entry.Chain)
				{
					Picked += (Picked.IsEmpty() ? TEXT("") : TEXT(" + ")) + FromWide(From.Anims[Piece].Name);
					Length += From.Anims[Piece].Length;
				}
			}
			FString Asked;
			float Before = 0.f;
			for (const SkelCompat::MergeSource& Other : Inputs)
			{
				if (Other.Auto != SkelCompat::AutoMatchMode::Off) { continue; }
				for (size_t K = 0; K < Other.Keys.size() && Asked.IsEmpty(); ++K)
				{
					if (Other.Keys[K] == Entry.Key)
					{
						Asked = FromWide(Other.Anims[K].Name);
						Before = Other.Anims[K].Length;
					}
				}
				if (!Asked.IsEmpty()) { break; }
			}
			Lines.Add(FString::Printf(TEXT("%s (%.1f s) <- %s (%.1f s, %s)"), *Asked, Before, *Picked, Length,
				Entry.Tier == 2 ? TEXT("another variant of the move") : TEXT("same kind, closest length")));
		}
		Report += FString::Printf(TEXT("    %s auto-match preview (%d pick(s), from %s%s):\n"), *FromWide(Name), Lines.Num(), *ListText(Labels),
			Missing.Num() > 0 ? *(TEXT("; not in this project: ") + ListText(Missing)) : TEXT(""));
		for (const FString& Line : Lines) { Report += TEXT("        ") + Line + TEXT("\n"); }
		return;
	}
	// An auto source is not in this project: show what the game picked the last time it ran.
	for (const FString& Pack : PackPaths)
	{
		const TArray<FString> Picks = LastRunPicks(GameLog, Pack, FromWide(Name));
		if (Picks.Num() == 0) { continue; }
		Report += FString::Printf(TEXT("    %s auto-match: %s not in this project, so these are the picks of the game's last run (RebirthSkelCompat.log):\n"),
			*FromWide(Name), *ListText(Missing));
		for (const FString& Line : Picks) { Report += TEXT("        ") + Line + TEXT("\n"); }
		return;
	}
	Report += FString::Printf(TEXT("    %s auto-match: no preview (%s not in this project, and the game has not logged this set yet)\n"), *FromWide(Name), *ListText(Missing));
}

// ------------------------------------------------------------------------------------------------
// Build Moves: a new animation made from an animation of this project, with the gameplay notifies of the character's own
// animation of that name (so the game's attack works with it), lined up on the first hit, and optional shot effects.
// ------------------------------------------------------------------------------------------------
// The character's own animation of a move's name: Notifies From, else <folder source>/<Set>/<Name> of the row's folder
// sources from the last one up (the slot owner's folder is usually listed last). OutPath: what was found or looked for.
UAnimSequenceBase* FindNotifySource(const FEndAnimSetRow& Row, const FEndAnimSetMove& Move, FString& OutPath)
{
	const FString Name = Move.Name.TrimStartAndEnd();
	const FString Set = Move.Set.TrimStartAndEnd();
	TArray<FString> Candidates;
	if (!Move.NotifiesFrom.TrimStartAndEnd().IsEmpty())
	{
		Candidates.Add(NormalizedObjectPath(Move.NotifiesFrom.TrimStartAndEnd()));
	}
	else if (!Name.IsEmpty())
	{
		const bool bBattle = Set.IsEmpty() ? Name.StartsWith(TEXT("B_"), ESearchCase::IgnoreCase) : SkelCompat::IsBattleSetName(Wide(Set));
		TArray<FString> Sets;
		if (!Set.IsEmpty())
		{
			Sets.Add(Set);
		}
		else if (bBattle)
		{
			Sets = {TEXT("Battle00"), TEXT("Battle01"), TEXT("Battle02")};
		}
		else
		{
			Sets = {TEXT("Neutral00"), TEXT("Neutral01"), TEXT("Neutral10"), TEXT("Neutral20"), TEXT("Emotion00")};
		}
		const TArray<FEndAnimSetSource>& Sources = bBattle ? Row.Battle : Row.Field;
		for (int32 K = Sources.Num() - 1; K >= 0; --K)
		{
			SkelCompat::SetSource Parsed;
			if (!SkelCompat::ParseSetSource(Wide(Sources[K].Path), Parsed) || !Parsed.Folder)
			{
				continue;
			}
			for (const FString& One : Sets)
			{
				Candidates.Add(FromWide(Parsed.Path) + TEXT("/") + One + TEXT("/") + Name + TEXT(".") + Name);
			}
		}
	}
	for (const FString& Path : Candidates)
	{
		if (!InProject(Path))
		{
			continue;
		}
		if (UAnimSequenceBase* Found = Cast<UAnimSequenceBase>(FSoftObjectPath(Path).TryLoad()))
		{
			OutPath = Path;
			return Found;
		}
	}
	OutPath = Candidates.Num() > 0 ? Candidates[0] : FString();
	return nullptr;
}

UObject* NotifyObject(const FAnimNotifyEvent& Event)
{
	return Event.Notify ? static_cast<UObject*>(Event.Notify) : static_cast<UObject*>(Event.NotifyStateClass);
}

bool ClassNameHasAny(const UObject* Object, std::initializer_list<const TCHAR*> Words)
{
	if (!Object)
	{
		return false;
	}
	const FString Name = Object->GetClass()->GetName();
	for (const TCHAR* Word : Words)
	{
		if (Name.Contains(Word))
		{
			return true;
		}
	}
	return false;
}

// A hit: a notify that creates damage (EndAnimNotifyBattleDamage, EndAnimNotifyStateBattleDamage, ...).
bool IsHitNotify(const UObject* Object)
{
	return ClassNameHasAny(Object, {TEXT("BattleDamage")}) && !ClassNameHasAny(Object, {TEXT("Display"), TEXT("Assist"), TEXT("Destroy")});
}

// Left out of a build: what belongs to the original motion and weapon (its weapon and body sounds, weapon trails and
// effects, cloth settings). Everything else is the game's logic for that move and is kept.
// (1.12.3) A sound of the motion (Source Sounds Only keeps those of the motion's sounds and effects).
bool IsSoundNotify(const UObject* Object)
{
	return ClassNameHasAny(Object, {TEXT("WeaponSound"), TEXT("CharacterSound"), TEXT("FootSound"), TEXT("HandSound")});
}

bool IsMotionNotify(const UObject* Object)
{
	return ClassNameHasAny(Object, {TEXT("WeaponSound"), TEXT("CharacterSound"), TEXT("FootSound"), TEXT("HandSound"), TEXT("NiagaraEffect"),
									TEXT("ParticleEffect"), TEXT("EffectCharaProperty"), TEXT("Bonamik")});
}

// ------------------------------------------------------------------------------------------------
// (1.12.4) Effect parameters of the game's that this editor reads but cannot write. Rebirth Material Preview's VFX1 load
// adapter reads the game's own Niagara variables (an effect notify's user parameters, m_UserParams) into variables with
// their names and no native type, and refuses to write one where it would come out lossy: in a package being saved or
// cooked, and in DuplicateObject, which writes the object and reads it back. So copying such a notify stopped the editor
// ("FDuplicateDataReader Overread ... VFXNiagaraUserParameter:m_Variable", Cloud's animations' effects with Keep Source
// Effects). Build Moves copies such a notify in memory instead and takes those parameters out of the copy: the effect
// plays with its own values for them.
// ------------------------------------------------------------------------------------------------
namespace UnwritableNiagara
{
constexpr int32 MostDepth = 16;

bool IsVariableStruct(const UStruct* Struct)
{
	static const FName Base(TEXT("NiagaraVariableBase"));
	static const FName Module(TEXT("/Script/Niagara"));
	for (const UStruct* At = Struct; At; At = At->GetSuperStruct())
	{
		if (At->GetFName() == Base && At->GetOutermost()->GetFName() == Module)
		{
			return true;
		}
	}
	return false;
}

// Named, with no native type: the adapter's own test for the variables it read (and refuses to write).
bool IsUnwritable(const void* Value)
{
	const FNiagaraVariableBase& Variable = *static_cast<const FNiagaraVariableBase*>(Value);
	return !Variable.GetName().IsNone() && !Variable.GetType().IsValid();
}

int32 CountInValue(const FProperty* Property, const void* Value, const UObject* Owner, int32 Depth);

int32 CountInStruct(const UStruct* Struct, const void* Data, const UObject* Owner, int32 Depth)
{
	int32 Count = 0;
	for (TFieldIterator<FProperty> It(Struct); It; ++It)
	{
		for (int32 Index = 0; Index < It->ArrayDim; ++Index)
		{
			Count += CountInValue(*It, It->ContainerPtrToValuePtr<void>(Data, Index), Owner, Depth + 1);
		}
	}
	return Count;
}

// How many of them a value holds: in its structs, arrays, sets and maps, and in the notify's own subobjects.
int32 CountInValue(const FProperty* Property, const void* Value, const UObject* Owner, int32 Depth)
{
	if (!Property || !Value || Depth > MostDepth)
	{
		return 0;
	}
	if (const FStructProperty* StructProperty = CastField<FStructProperty>(Property))
	{
		if (IsVariableStruct(StructProperty->Struct))
		{
			return IsUnwritable(Value) ? 1 : 0;
		}
		return CountInStruct(StructProperty->Struct, Value, Owner, Depth);
	}
	int32 Count = 0;
	if (const FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property))
	{
		FScriptArrayHelper Array(ArrayProperty, Value);
		for (int32 Index = 0; Index < Array.Num(); ++Index)
		{
			Count += CountInValue(ArrayProperty->Inner, Array.GetRawPtr(Index), Owner, Depth + 1);
		}
	}
	else if (const FSetProperty* SetProperty = CastField<FSetProperty>(Property))
	{
		FScriptSetHelper Set(SetProperty, Value);
		for (int32 Index = 0; Index < Set.GetMaxIndex(); ++Index)
		{
			if (Set.IsValidIndex(Index))
			{
				Count += CountInValue(SetProperty->ElementProp, Set.GetElementPtr(Index), Owner, Depth + 1);
			}
		}
	}
	else if (const FMapProperty* MapProperty = CastField<FMapProperty>(Property))
	{
		FScriptMapHelper Map(MapProperty, Value);
		for (int32 Index = 0; Index < Map.GetMaxIndex(); ++Index)
		{
			if (Map.IsValidIndex(Index))
			{
				Count += CountInValue(MapProperty->KeyProp, Map.GetKeyPtr(Index), Owner, Depth + 1);
				Count += CountInValue(MapProperty->ValueProp, Map.GetValuePtr(Index), Owner, Depth + 1);
			}
		}
	}
	else if (const FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
	{
		// a subobject of the notify's own (an instanced object): it is copied with the notify
		const UObject* Inner = ObjectProperty->GetObjectPropertyValue(Value);
		if (Inner && Owner && Inner != Owner && Inner->IsIn(Owner))
		{
			Count += CountInStruct(Inner->GetClass(), Inner, Owner, Depth);
		}
	}
	return Count;
}

int32 DropInValue(const FProperty* Property, void* Value, const UObject* Owner, int32 Depth);

int32 DropInStruct(const UStruct* Struct, void* Data, const UObject* Owner, int32 Depth)
{
	int32 Dropped = 0;
	for (TFieldIterator<FProperty> It(Struct); It; ++It)
	{
		for (int32 Index = 0; Index < It->ArrayDim; ++Index)
		{
			Dropped += DropInValue(*It, It->ContainerPtrToValuePtr<void>(Data, Index), Owner, Depth + 1);
		}
	}
	return Dropped;
}

// Takes every element that holds one out of the arrays in a value (an effect's user parameter, with its value) and
// returns how many of them went with those elements. One outside an array (or in a set or a map) is left where it is.
int32 DropInValue(const FProperty* Property, void* Value, const UObject* Owner, int32 Depth)
{
	if (!Property || !Value || Depth > MostDepth)
	{
		return 0;
	}
	if (const FStructProperty* StructProperty = CastField<FStructProperty>(Property))
	{
		return IsVariableStruct(StructProperty->Struct) ? 0 : DropInStruct(StructProperty->Struct, Value, Owner, Depth);
	}
	int32 Dropped = 0;
	if (const FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property))
	{
		FScriptArrayHelper Array(ArrayProperty, Value);
		for (int32 Index = Array.Num() - 1; Index >= 0; --Index)
		{
			if (CountInValue(ArrayProperty->Inner, Array.GetRawPtr(Index), Owner, Depth + 1) == 0)
			{
				continue;
			}
			// deeper lists first (only what holds one goes), then the element itself if it still holds one
			Dropped += DropInValue(ArrayProperty->Inner, Array.GetRawPtr(Index), Owner, Depth + 1);
			const int32 Held = CountInValue(ArrayProperty->Inner, Array.GetRawPtr(Index), Owner, Depth + 1);
			if (Held > 0)
			{
				Array.RemoveValues(Index, 1);
				Dropped += Held;
			}
		}
	}
	else if (const FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
	{
		UObject* Inner = ObjectProperty->GetObjectPropertyValue(Value);
		if (Inner && Owner && Inner != Owner && Inner->IsIn(Owner))
		{
			Dropped += DropInStruct(Inner->GetClass(), Inner, Owner, Depth);
		}
	}
	return Dropped;
}

int32 CountIn(const UObject* Object)
{
	return Object ? CountInStruct(Object->GetClass(), Object, Object, 0) : 0;
}
}   // namespace UnwritableNiagara

// (1.12.4) A move's own copy of a notify: DuplicateObject as before, unless the notify holds effect parameters this editor
// cannot write (UnwritableNiagara). Then it is copied in memory (NewObject with the notify as its template: its values,
// nothing written and read back) and those parameters are taken out of the copy; or, when one is not in a list, it is
// not copied (nullptr, the notify is left out of the move).
template <class T>
T* CopyNotifyObject(T* Original, UObject* Outer, int32& EffectParameters, int32& NotifiesLeftOut)
{
	if (!Original)
	{
		return nullptr;
	}
	if (UnwritableNiagara::CountIn(Original) == 0)
	{
		return DuplicateObject<T>(Original, Outer);
	}
	T* Copy = NewObject<T>(Outer, Original->GetClass(), NAME_None, RF_Transactional, Original);
	EffectParameters += UnwritableNiagara::DropInStruct(Copy->GetClass(), Copy, Copy, 0);
	if (UnwritableNiagara::CountIn(Copy) > 0)
	{
		Copy->Rename(nullptr, GetTransientPackage(), REN_DontCreateRedirectors | REN_NonTransactional | REN_ForceNoResetLoaders);
		Copy->MarkPendingKill();
		++NotifiesLeftOut;
		return nullptr;
	}
	return Copy;
}

// Times of the original on the new animation: piecewise linear through anchors (an original hit -> its new time), and in
// proportion to the lengths before the first anchor, between anchors and after the last one (no anchor: in proportion).
struct FBuildTimeMap
{
	float OldLength = 0.f;
	float NewLength = 0.f;
	TArray<TPair<float, float>> Anchors; // (time in the original, time in the new animation), both increasing

	float Map(float Time) const
	{
		Time = FMath::Clamp(Time, 0.f, OldLength);
		float PrevOld = 0.f;
		float PrevNew = 0.f;
		for (const TPair<float, float>& Anchor : Anchors)
		{
			if (Time <= Anchor.Key)
			{
				const float Span = Anchor.Key - PrevOld;
				return Span > KINDA_SMALL_NUMBER ? PrevNew + (Time - PrevOld) * (Anchor.Value - PrevNew) / Span : Anchor.Value;
			}
			PrevOld = Anchor.Key;
			PrevNew = Anchor.Value;
		}
		const float Span = OldLength - PrevOld;
		return Span > KINDA_SMALL_NUMBER ? PrevNew + (Time - PrevOld) * (NewLength - PrevNew) / Span : PrevNew;
	}
};

// Links a notify to the sequence at Start (a notify state for Length), on Track.
void PlaceNotify(UAnimSequenceBase* Sequence, FAnimNotifyEvent& Event, float Start, float Length, int32 Track)
{
	Start = FMath::Clamp(Start, 0.f, Sequence->SequenceLength);
	Event.Link(Sequence, Start);
	Event.TriggerTimeOffset = GetTriggerTimeOffsetForType(Sequence->CalculateOffsetForNotify(Start));
	if (Event.NotifyStateClass)
	{
		const float End = FMath::Clamp(Start + Length, Start, Sequence->SequenceLength);
		Event.EndLink.Link(Sequence, End);
		Event.SetDuration(End - Start);
		Event.EndTriggerTimeOffset = GetTriggerTimeOffsetForType(Sequence->CalculateOffsetForNotify(End));
	}
	else
	{
		Event.EndLink.Link(Sequence, Start);
		Event.Duration = 0.f;
		Event.EndTriggerTimeOffset = 0.f;
	}
	Event.TrackIndex = Track;
#if WITH_EDITORONLY_DATA
	Event.Guid = FGuid::NewGuid();
#endif
}

// Sets a property from its text form (the Copy / Paste text of the details panel).
bool SetPropertyText(UObject* Object, const TCHAR* Name, const FString& Text, FString& Notes)
{
	FProperty* Property = Object ? FindFProperty<FProperty>(Object->GetClass(), Name) : nullptr;
	if (!Property)
	{
		Notes += FString::Printf(TEXT("; %s has no %s"), Object ? *Object->GetClass()->GetName() : TEXT("(none)"), Name);
		return false;
	}
	if (!Property->ImportText(*Text, Property->ContainerPtrToValuePtr<void>(Object), PPF_None, Object))
	{
		Notes += FString::Printf(TEXT("; %s.%s did not take %s"), *Object->GetClass()->GetName(), Name, *Text);
		return false;
	}
	return true;
}

// A Niagara effect (AnimNotifyState_EndTimedNiagaraEffect) at Socket, attached as AttachType says (Weapon1..Weapon8 or
// Character). Only the settings the game's own effect notifies set are set; everything else keeps the game's defaults.
bool AddEffectNotify(UAnimSequenceBase* Sequence, const FString& Effect, FName Socket, const FString& AttachType, float Time, float Duration, int32 Track, FString& Notes)
{
	UClass* Class = FindObject<UClass>(ANY_PACKAGE, TEXT("AnimNotifyState_EndTimedNiagaraEffect"));
	if (!Class || !Class->IsChildOf(UAnimNotifyState::StaticClass()))
	{
		Notes += TEXT("; no effect: AnimNotifyState_EndTimedNiagaraEffect (EndGame) is not loaded");
		return false;
	}
	UAnimNotifyState* State = NewObject<UAnimNotifyState>(Sequence, Class, NAME_None, RF_Transactional);
	const FString Params = FString::Printf(TEXT("(m_NiagaraParameterInfo=(m_Template=\"%s\"),m_SocketName=\"%s\")"), *NormalizedObjectPath(Effect), *Socket.ToString());
	if (!SetPropertyText(State, TEXT("m_NiagaraCreateParams"), Params, Notes) || !SetPropertyText(State, TEXT("m_AttachType"), AttachType, Notes))
	{
		return false;
	}
	FAnimNotifyEvent Event;
	Event.NotifyStateClass = State;
	Event.NotifyName = FName(*State->GetNotifyName());
	PlaceNotify(Sequence, Event, Time, FMath::Max(Duration, 0.01f), Track);
	Sequence->Notifies.Add(Event);
	return true;
}

// A sound of a game sound bank: a weapon sound (EndAnimNotifyPlayWeaponSound, of weapon N) or a character sound
// (EndAnimNotifyPlayCharacterSound).
bool AddSoundNotify(UAnimSequenceBase* Sequence, const FString& Bank, FName Sound, bool bWeapon, int32 Weapon, float Time, int32 Track, FString& Notes)
{
	const TCHAR* ClassName = bWeapon ? TEXT("EndAnimNotifyPlayWeaponSound") : TEXT("EndAnimNotifyPlayCharacterSound");
	UClass* Class = FindObject<UClass>(ANY_PACKAGE, ClassName);
	if (!Class || !Class->IsChildOf(UAnimNotify::StaticClass()))
	{
		Notes += FString::Printf(TEXT("; no sound: %s (EndGame) is not loaded"), ClassName);
		return false;
	}
	UAnimNotify* Notify = NewObject<UAnimNotify>(Sequence, Class, NAME_None, RF_Transactional);
	bool bSet = SetPropertyText(Notify, TEXT("SoundRef"), TEXT("\"") + NormalizedObjectPath(Bank) + TEXT("\""), Notes) &&
				SetPropertyText(Notify, TEXT("SoundName"), Sound.ToString(), Notes);
	if (bSet && bWeapon && Weapon != 1)
	{
		bSet = SetPropertyText(Notify, TEXT("WeaponSlot"), FString::Printf(TEXT("EWeaponSlot_%d"), Weapon), Notes);
	}
	if (!bSet)
	{
		return false;
	}
	FAnimNotifyEvent Event;
	Event.Notify = Notify;
	Event.NotifyName = FName(*Notify->GetNotifyName());
	PlaceNotify(Sequence, Event, Time, 0.f, Track);
	Sequence->Notifies.Add(Event);
	return true;
}

// Muzzle flash (a Niagara notify state at the weapon's socket) and gunshot (a weapon sound) at one hit.
int32 AddShotEffects(UAnimSequenceBase* Sequence, const FEndShotEffects& Shot, float Time, int32 Track, FString& Notes)
{
	int32 Added = 0;
	const int32 Weapon = FMath::Clamp(Shot.Weapon, 1, 8);
	const FString Muzzle = Shot.MuzzleEffect.TrimStartAndEnd();
	if (!Muzzle.IsEmpty() && AddEffectNotify(Sequence, Muzzle, Shot.MuzzleSocket, FString::Printf(TEXT("Weapon%d"), Weapon), Time, Shot.MuzzleTime, Track, Notes))
	{
		++Added;
	}
	const FString Bank = Shot.SoundBank.TrimStartAndEnd();
	if (!Bank.IsEmpty() && !Shot.Sound.IsNone() && AddSoundNotify(Sequence, Bank, Shot.Sound, true, Weapon, Time, Track, Notes))
	{
		++Added;
	}
	return Added;
}

// A hit's own effect and sound (editor 1.8).
int32 AddHitEffects(UAnimSequenceBase* Sequence, const FEndMoveHit& Hit, float Time, int32 Track, FString& Notes)
{
	int32 Added = 0;
	const int32 Weapon = FMath::Clamp(Hit.Weapon, 1, 8);
	const bool bOnWeapon = Hit.EffectOn == EEndMoveEffectAttach::Weapon;
	const FString Effect = Hit.Effect.TrimStartAndEnd();
	if (!Effect.IsEmpty() &&
		AddEffectNotify(Sequence, Effect, Hit.EffectSocket, bOnWeapon ? FString::Printf(TEXT("Weapon%d"), Weapon) : FString(TEXT("Character")), Time, Hit.EffectTime, Track, Notes))
	{
		++Added;
	}
	const FString Bank = Hit.SoundBank.TrimStartAndEnd();
	if (!Bank.IsEmpty() && !Hit.Sound.IsNone() && AddSoundNotify(Sequence, Bank, Hit.Sound, bOnWeapon, Weapon, Time, Track, Notes))
	{
		++Added;
	}
	return Added;
}

struct FBuildResult
{
	int32 Copied = 0;
	int32 Left = 0;
	TArray<FString> LeftClasses;
	int32 Hits = 0;          // hits the built move has
	float OldHit = -1.f;
	float NewHit = -1.f;
	int32 Shots = 0;
	int32 HitsLeftOut = 0;   // hits of the original after the move's last hit (Hits shorter than the original's)
	int32 HitsRepeated = 0;  // hits of the move after the original's last one, made from it
	int32 HitsMade = 0;      // new damage notifies (a Damage Source ID and nothing to copy the damage from)
	int32 Effects = 0;       // the hits' own effects and sounds
	int32 EffectParameters = 0;  // (1.12.4) effect parameters of the game's this editor cannot write, taken out of the copies
	int32 NotifiesLeftOut = 0;   // (1.12.4) notifies not copied for one (outside a list)
};

// (1.12.3) The notifies an animation plays, in its time: a composite's own and those of the animations its segments play
// (each segment's that triggers its animation's notifies, every loop of it), so a move can take its gameplay notifies
// from one of the game's composites (its _Comp animations) as well as from an animation.
TArray<FAnimNotifyEvent> PlayedNotifies(const UAnimSequenceBase* From, int32 Depth = 0)
{
	TArray<FAnimNotifyEvent> Out;
	if (!From)
	{
		return Out;
	}
	Out.Append(From->Notifies);
	const UAnimComposite* Composite = Cast<UAnimComposite>(From);
	if (!Composite || Depth > 4)
	{
		return Out;
	}
	UAnimSequenceBase* Owner = const_cast<UAnimSequenceBase*>(From);
	for (const FAnimSegment& Segment : Composite->AnimationTrack.AnimSegments)
	{
		const float Span = Segment.AnimEndTime - Segment.AnimStartTime;
		if (!Segment.AnimReference || !Segment.bTriggerAnimReferenceNotify || Span <= KINDA_SMALL_NUMBER)
		{
			continue;
		}
		const float Rate = FMath::Abs(Segment.GetValidPlayRate());
		const TArray<FAnimNotifyEvent> Inner = PlayedNotifies(Segment.AnimReference, Depth + 1);
		for (int32 Loop = 0; Loop < FMath::Max(Segment.LoopingCount, 1); ++Loop)
		{
			for (const FAnimNotifyEvent& Event : Inner)
			{
				const float At = Event.GetTime();
				if (At < Segment.AnimStartTime - 0.0001f || At > Segment.AnimEndTime + 0.0001f)
				{
					continue;
				}
				const float Time = Segment.StartPos + (Loop * Span + (At - Segment.AnimStartTime)) / Rate;
				const float Lasts = Event.NotifyStateClass ? FMath::Min(Event.GetDuration(), Segment.AnimEndTime - At) / Rate : 0.f;
				FAnimNotifyEvent Copy = Event;
				Copy.Link(Owner, Time);
				Copy.EndLink.Link(Owner, Time + Lasts);
				Copy.SetDuration(Lasts);
				Out.Add(Copy);
			}
		}
	}
	Out.StableSort([](const FAnimNotifyEvent& A, const FAnimNotifyEvent& B) { return A.GetTime() < B.GetTime(); });
	return Out;
}

// The times of the original's hits: damage notifies less than 0.05 s apart are one hit.
TArray<float> HitGroupTimes(const TArray<FAnimNotifyEvent>& Notifies)
{
	TArray<float> Times;
	for (const FAnimNotifyEvent& Event : Notifies)
	{
		if (IsHitNotify(NotifyObject(Event)))
		{
			Times.Add(Event.GetTime());
		}
	}
	Times.Sort();
	TArray<float> Groups;
	for (const float Time : Times)
	{
		if (Groups.Num() == 0 || Time - Groups.Last() >= 0.05f)
		{
			Groups.Add(Time);
		}
	}
	return Groups;
}

// The hit a damage notify of the original belongs to: the last group that starts at or before it.
int32 HitGroupOf(const TArray<float>& Groups, float Time)
{
	int32 Group = 0;
	for (int32 Index = 0; Index < Groups.Num(); ++Index)
	{
		if (Groups[Index] <= Time + 0.0001f)
		{
			Group = Index;
		}
	}
	return Group;
}

// A hit's own damage source on a damage notify (DamageSourceID; a list of them is replaced by this one).
void ApplyHitDamage(UObject* Object, const FEndMoveHit& Hit, FString& Notes)
{
	const FString Id = Hit.DamageSourceID.TrimStartAndEnd();
	if (!Object || Id.IsEmpty())
	{
		return;
	}
	SetPropertyText(Object, TEXT("DamageSourceID"), TEXT("\"") + Id + TEXT("\""), Notes);
	if (FindFProperty<FProperty>(Object->GetClass(), TEXT("DamageSourceIDs")))
	{
		SetPropertyText(Object, TEXT("DamageSourceIDs"), TEXT("()"), Notes);
	}
}

// The gameplay notifies of From (none: the move's own hits only) on Sequence, after the sequence's own: shot effects and
// the hits' own effects on the first new track, the copied notifies on the tracks after it in the original's order.
// With Hits, the original's hits land at their times (more hits repeat its last one, fewer leave its last ones out);
// otherwise its first hit lands at Hit At and the rest in proportion.
FBuildResult BuildNotifies(UAnimSequenceBase* Sequence, const UAnimSequenceBase* From, const FEndAnimSetMove& Move, const FEndShotEffects& Shot, FString& Notes)
{
	FBuildResult Result;
	FBuildTimeMap Map;
	Map.OldLength = From ? From->SequenceLength : Sequence->SequenceLength;
	Map.NewLength = Sequence->SequenceLength;
	const TArray<FAnimNotifyEvent> Played = PlayedNotifies(From);   // (1.12.3: a composite's with its animations')
	const TArray<float> OldGroups = HitGroupTimes(Played);
	TArray<const FEndMoveHit*> Hits;
	for (const FEndMoveHit& Hit : Move.Hits)
	{
		Hits.Add(&Hit);
	}
	Hits.StableSort([](const FEndMoveHit& A, const FEndMoveHit& B) { return A.Time < B.Time; });
	TArray<float> NewTimes;
	for (const FEndMoveHit* Hit : Hits)
	{
		NewTimes.Add(FMath::Clamp(Hit->Time, 0.f, Map.NewLength));
	}
	if (OldGroups.Num() > 0)
	{
		Result.OldHit = OldGroups[0];
		if (Hits.Num() > 0)
		{
			for (int32 Index = 0; Index < FMath::Min(OldGroups.Num(), Hits.Num()); ++Index)
			{
				Map.Anchors.Emplace(OldGroups[Index], NewTimes[Index]);
			}
			Result.NewHit = NewTimes[0];
		}
		else
		{
			Result.NewHit = Move.HitAt > 0.f ? FMath::Min(Move.HitAt, Map.NewLength)
											 : (Map.OldLength > KINDA_SMALL_NUMBER ? OldGroups[0] * Map.NewLength / Map.OldLength : 0.f);
			Map.Anchors.Emplace(OldGroups[0], Result.NewHit);
		}
	}
	else if (Move.HitAt > 0.f && Hits.Num() == 0 && From)
	{
		Notes += TEXT("; Hit At not used: the original has no hit");
	}
	int32 ShotTrack = 0;
#if WITH_EDITORONLY_DATA
	ShotTrack = Sequence->AnimNotifyTracks.Num();
#endif
	int32 LastTrack = ShotTrack;
	TArray<float> NewHits;
	const auto Copy = [&](const FAnimNotifyEvent& Original, float Start, float Length, const FEndMoveHit* Hit)
	{
		FAnimNotifyEvent Event = Original;
		if (Original.Notify)
		{
			Event.Notify = CopyNotifyObject<UAnimNotify>(Original.Notify, Sequence, Result.EffectParameters, Result.NotifiesLeftOut);
			if (!Event.Notify)
			{
				return;
			}
		}
		if (Original.NotifyStateClass)
		{
			Event.NotifyStateClass = CopyNotifyObject<UAnimNotifyState>(Original.NotifyStateClass, Sequence, Result.EffectParameters, Result.NotifiesLeftOut);
			if (!Event.NotifyStateClass)
			{
				return;
			}
		}
		if (Hit)
		{
			ApplyHitDamage(NotifyObject(Event), *Hit, Notes);
		}
		const int32 Track = ShotTrack + 1 + FMath::Clamp(Original.TrackIndex, 0, 30);
		LastTrack = FMath::Max(LastTrack, Track);
		PlaceNotify(Sequence, Event, Start, FMath::Max(Length, 0.f), Track);
		Sequence->Notifies.Add(Event);
		++Result.Copied;
	};
	if (From)
	{
		for (const FAnimNotifyEvent& Original : Played)
		{
			UObject* Object = NotifyObject(Original);
			if (IsMotionNotify(Object))
			{
				++Result.Left;
				Result.LeftClasses.AddUnique(Object->GetClass()->GetName());
				continue;
			}
			const bool bHit = IsHitNotify(Object);
			const int32 Group = bHit && OldGroups.Num() > 0 ? HitGroupOf(OldGroups, Original.GetTime()) : INDEX_NONE;
			if (bHit && Hits.Num() > 0 && Group >= Hits.Num())
			{
				continue; // a hit after the move's last one
			}
			const FEndMoveHit* Hit = bHit && Hits.Num() > 0 ? Hits[Group] : nullptr;
			const float Start = Hit ? NewTimes[Group] + (Original.GetTime() - OldGroups[Group]) : Map.Map(Original.GetTime());
			float Length = 0.f;
			if (Original.NotifyStateClass)
			{
				// A damage window keeps its length (a shorter one could miss) unless the hit sets one; other windows follow the time map.
				Length = bHit ? (Hit && Hit->Window > 0.f ? Hit->Window : Original.GetDuration()) : Map.Map(Original.GetTime() + Original.GetDuration()) - Start;
			}
			Copy(Original, Start, Length, Hit);
			if (bHit)
			{
				NewHits.Add(Start);
			}
		}
		if (Hits.Num() > 0 && OldGroups.Num() > Hits.Num())
		{
			Result.HitsLeftOut = OldGroups.Num() - Hits.Num();
		}
		// More hits than the original has: its last hit again at each later time.
		if (Hits.Num() > OldGroups.Num() && OldGroups.Num() > 0)
		{
			const int32 Last = OldGroups.Num() - 1;
			for (int32 Index = OldGroups.Num(); Index < Hits.Num(); ++Index)
			{
				for (const FAnimNotifyEvent& Original : Played)
				{
					UObject* Object = NotifyObject(Original);
					if (!IsHitNotify(Object) || IsMotionNotify(Object) || HitGroupOf(OldGroups, Original.GetTime()) != Last)
					{
						continue;
					}
					const float Start = NewTimes[Index] + (Original.GetTime() - OldGroups[Last]);
					const float Length = Original.NotifyStateClass ? (Hits[Index]->Window > 0.f ? Hits[Index]->Window : Original.GetDuration()) : 0.f;
					Copy(Original, Start, Length, Hits[Index]);
					NewHits.Add(Start);
				}
				++Result.HitsRepeated;
			}
		}
	}
	// Nothing to copy the damage from: new damage notifies for the hits that name a damage source.
	if (OldGroups.Num() == 0 && Hits.Num() > 0)
	{
		UClass* DamageClass = FindObject<UClass>(ANY_PACKAGE, TEXT("EndAnimNotifyBattleDamage"));
		for (int32 Index = 0; Index < Hits.Num(); ++Index)
		{
			if (Hits[Index]->DamageSourceID.TrimStartAndEnd().IsEmpty())
			{
				Notes += FString::Printf(TEXT("; hit %d (%.2f s) deals no damage: there is no move to copy it from and it has no Damage Source ID"), Index + 1, NewTimes[Index]);
				continue;
			}
			if (!DamageClass || !DamageClass->IsChildOf(UAnimNotify::StaticClass()))
			{
				Notes += TEXT("; no damage notify made: EndAnimNotifyBattleDamage (EndGame) is not loaded");
				break;
			}
			UAnimNotify* Notify = NewObject<UAnimNotify>(Sequence, DamageClass, NAME_None, RF_Transactional);
			ApplyHitDamage(Notify, *Hits[Index], Notes);
			FAnimNotifyEvent Event;
			Event.Notify = Notify;
			Event.NotifyName = FName(*Notify->GetNotifyName());
			LastTrack = FMath::Max(LastTrack, ShotTrack + 1);
			PlaceNotify(Sequence, Event, NewTimes[Index], 0.f, ShotTrack + 1);
			Sequence->Notifies.Add(Event);
			NewHits.Add(NewTimes[Index]);
			++Result.HitsMade;
		}
		if (Result.HitsMade > 0)
		{
			Notes += TEXT("; check the new damage notifies' Create Position settings in the animation editor (they keep the game's defaults)");
		}
	}
	NewHits.Sort();
	for (int32 Index = 0; Index < NewHits.Num(); ++Index)
	{
		if (Index == 0 || NewHits[Index] - NewHits[Index - 1] >= 0.05f)
		{
			++Result.Hits;
		}
	}
	for (int32 Index = 0; Index < Hits.Num(); ++Index)
	{
		Result.Effects += AddHitEffects(Sequence, *Hits[Index], NewTimes[Index], ShotTrack, Notes);
	}
	if (Move.bShot)
	{
		float Last = -1.f;
		for (const float Time : NewHits)
		{
			if (Last >= 0.f && Time - Last < 0.05f)
			{
				continue; // several damage notifies of one hit: one shot
			}
			Last = Time;
			if (AddShotEffects(Sequence, Shot, Time, ShotTrack, Notes) > 0)
			{
				++Result.Shots;
			}
		}
		if (NewHits.Num() == 0)
		{
			Notes += TEXT("; Shot: no hit to put the shot effects on");
		}
	}
#if WITH_EDITORONLY_DATA
	while (Sequence->AnimNotifyTracks.Num() <= LastTrack)
	{
		const int32 Index = Sequence->AnimNotifyTracks.Num();
		const FString TrackName = Index == ShotTrack ? FString(TEXT("Hits")) : FString::FromInt(Index + 1);
		Sequence->AnimNotifyTracks.Add(FAnimNotifyTrack(FName(*TrackName), FLinearColor::White));
	}
#endif
	return Result;
}

// Root motion and the game's blend settings, as the original has them.
void CopyPlaySettings(const UAnimSequenceBase* From, UAnimSequenceBase* To)
{
	for (const TCHAR* Name : {TEXT("bEnableRootMotion"), TEXT("RootMotionRootLock"), TEXT("bForceRootLock"), TEXT("bUseNormalizedRootMotionScale"),
							  TEXT("OverrideBehaviorActionBlendTime"), TEXT("OverrideBehaviorActionBlendOutTime"),
							  TEXT("OverrideBehaviorActionBlendOutSequenceFilter"), TEXT("RootMotionScale")})
	{
		FProperty* Target = FindFProperty<FProperty>(To->GetClass(), Name);
		FProperty* Source = FindFProperty<FProperty>(From->GetClass(), Name);
		if (Target && Target == Source)
		{
			Target->CopyCompleteValue_InContainer(To, From);
		}
	}
}

// Properties of From set on To by name (ones To's class does not have are skipped; an empty object reference is not
// copied, so a default the engine fills in stays).
void CopyNamedProperties(const UObject* From, UObject* To, std::initializer_list<const TCHAR*> Names)
{
	for (const TCHAR* Name : Names)
	{
		FProperty* Target = FindFProperty<FProperty>(To->GetClass(), Name);
		if (!Target || Target != FindFProperty<FProperty>(From->GetClass(), Name))
		{
			continue;
		}
		if (const FObjectProperty* Reference = CastField<FObjectProperty>(Target))
		{
			if (!Reference->GetObjectPropertyValue_InContainer(From))
			{
				continue;
			}
		}
		Target->CopyCompleteValue_InContainer(To, From);
	}
}

// The settings of the animation a move is made from that CreateAnimation does not take over (it takes the keys, curves
// and notifies). Not its compression settings: a built move always gets the game's (GameBoneCompression).
void CopyAnimSettings(const UAnimSequence* From, UAnimSequence* To)
{
	CopyNamedProperties(From, To, {TEXT("RateScale"), TEXT("Interpolation"), TEXT("RetargetSource"), TEXT("bIgnoreTranslationRetargeting"),
								   TEXT("AdditiveAnimType"), TEXT("RefPoseType"), TEXT("RefPoseSeq"), TEXT("RefFrameIndex"),
								   TEXT("CompressionErrorThresholdScale"),
								   TEXT("bAllowFrameStripping"), TEXT("bDoNotOverrideCompression"), TEXT("ImportFileFramerate"),
								   TEXT("ImportResampleFramerate"), TEXT("bLoop"), TEXT("PreviewPoseAsset"), TEXT("PreviewSkeletalMesh")});
}

// The game reads every animation with its own ACL codecs, whatever the animation names: the RebirthEngineV5 loader takes
// AnimBoneCompressionCodec_ACL_0 from the animation's bone settings and AnimCurveCompressionCodec_ACL_0 of the game's curve
// settings. So a built move is compressed with exactly these (the game's own assets, in this project as cooked copies).
const TCHAR* const GameBoneCompression = TEXT("/Game/Animation/CompressionSettings/AnimBoneCompressionSettingsACL.AnimBoneCompressionSettingsACL");
const TCHAR* const GameCurveCompression = TEXT("/Game/Animation/CompressionSettings/AnimCurveCompressionSettingsACL.AnimCurveCompressionSettingsACL");
const TCHAR* const GameBoneCodec = TEXT("AnimBoneCompressionCodec_ACL_0");

// 1.11.1: RebirthEngineV5 reads an animation of the game's memory-mapped layout with AnimBoneCompressionCodec_ACL_0 whatever it
// was compressed with (the handle is hard-coded in FCompressedAnimSequence::SerializeCompressedData), so ACL's safety fallback
// breaks a move: its safe codec's whole quaternions (Quat_128) are more than this editor's ACL decoder reads, and what the
// fallback leaves can even be the engine's own codecs' data, which the game reads as ACL. A huge skeleton trips the fallback's
// 1 cm: Bizarro Sephiroth's (54 m tall) on short clips, for an error of a fraction of a degree (under 1 cm at the size a form
// wears him). So the fallback is off for the game's ACL settings: in memory only (the threshold is editor data, and cooked
// settings load with the class default), for Build Moves, Import Key Animations and the cooker (which compresses every move
// again with them), and the settings stay loaded so it stays off.
bool TurnOffAclSafetyFallback(UAnimBoneCompressionSettings* Settings)
{
	if (!Settings)
	{
		Settings = LoadObject<UAnimBoneCompressionSettings>(nullptr, GameBoneCompression, nullptr, LOAD_NoWarn | LOAD_Quiet);
	}
	if (!Settings)
	{
		return false;
	}
	bool bChanged = false;
	for (UAnimBoneCompressionCodec* Codec : Settings->Codecs)
	{
		FFloatProperty* Threshold = Codec ? FindFProperty<FFloatProperty>(Codec->GetClass(), TEXT("SafetyFallbackThreshold")) : nullptr;
		if (Threshold && Threshold->GetPropertyValue_InContainer(Codec) != 0.f)
		{
			Threshold->SetPropertyValue_InContainer(Codec, 0.f);
			bChanged = true;
		}
	}
	if (bChanged)
	{
		Settings->AddToRoot();
		UE_LOG(LogRebirthSkelCompat, Display, TEXT("ACL's safety fallback is off for %s: the game reads every animation with %s"), *Settings->GetPathName(), GameBoneCodec);
	}
	return true;
}

// The game's ACL bone settings loaded again (or late, in the cooker): the fallback off again.
void TurnOffAclSafetyFallbackOnLoad(UObject* Asset)
{
	UAnimBoneCompressionSettings* Settings = Cast<UAnimBoneCompressionSettings>(Asset);
	if (Settings && Settings->GetPathName().Equals(GameBoneCompression, ESearchCase::IgnoreCase))
	{
		TurnOffAclSafetyFallback(Settings);
	}
}

// A new Anim Sequence Package.Name with Source's keys, curves, notifies and settings. Not a duplicate: in this engine an
// Anim Sequence writes data for the game's memory-mapped layout that it does not read back the same way in memory, so
// duplicating one reads past its data and the editor crashes (FDuplicateDataReader Overread). Nothing here goes
// through that: the keys are copied as they are and the notify objects are duplicated on their own.
UAnimSequence* MakeAnimationFrom(UAnimSequence* Source, const FString& Package, const FString& Name, FString& Error, int32& EffectParameters,
	int32& NotifiesLeftOut)
{
	USkeleton* Skeleton = Source->GetSkeleton();
	if (!Skeleton)
	{
		Error = Source->GetName() + TEXT(" has no skeleton");
		return nullptr;
	}
	UAnimBoneCompressionSettings* BoneCompression = LoadObject<UAnimBoneCompressionSettings>(nullptr, GameBoneCompression, nullptr, LOAD_NoWarn | LOAD_Quiet);
	TurnOffAclSafetyFallback(BoneCompression);
	UAnimCurveCompressionSettings* CurveCompression = LoadObject<UAnimCurveCompressionSettings>(nullptr, GameCurveCompression, nullptr, LOAD_NoWarn | LOAD_Quiet);
	if (!BoneCompression || !CurveCompression)
	{
		Error = FString::Printf(TEXT("the game's animation compression settings are not in this project (%s, %s): the game reads every animation with them"),
			BoneCompression ? TEXT("bone settings found") : GameBoneCompression, CurveCompression ? TEXT("curve settings found") : GameCurveCompression);
		return nullptr;
	}
	UPackage* Outer = CreatePackage(*Package);
	if (!Outer)
	{
		Error = Package + TEXT(" could not be made");
		return nullptr;
	}
	Outer->FullyLoad();
	if (StaticFindObjectFast(nullptr, Outer, FName(*Name)))
	{
		Error = Package + TEXT(" is still loaded (close it, then press Build Moves again)");
		return nullptr;
	}
	UAnimSequence* Sequence = NewObject<UAnimSequence>(Outer, FName(*Name), RF_Public | RF_Standalone | RF_Transactional);
	Sequence->SetSkeleton(Skeleton);
	CopyAnimSettings(Source, Sequence);
	// Before CreateAnimation compresses the keys.
	Sequence->BoneCompressionSettings = BoneCompression;
	Sequence->CurveCompressionSettings = CurveCompression;
	if (!Sequence->CreateAnimation(Source))
	{
		Sequence->ClearFlags(RF_Public | RF_Standalone);
		Sequence->MarkPendingKill();
		Error = Source->GetName() + TEXT(" could not be copied");
		return nullptr;
	}
	CopyNamedProperties(Source, Sequence, {TEXT("RateScale")}); // CreateAnimation resets it
	// CreateAnimation shares the source's notify objects: the new sequence gets its own. (1.12.4) Without the effect
	// parameters of the game's this editor cannot write (CopyNotifyObject), or left out for one outside a list.
	for (int32 Index = 0; Index < Sequence->Notifies.Num();)
	{
		FAnimNotifyEvent& Event = Sequence->Notifies[Index];
		const bool bHadObject = Event.Notify || Event.NotifyStateClass;
		if (Event.Notify)
		{
			Event.Notify = CopyNotifyObject<UAnimNotify>(Event.Notify, Sequence, EffectParameters, NotifiesLeftOut);
		}
		if (Event.NotifyStateClass)
		{
			Event.NotifyStateClass = CopyNotifyObject<UAnimNotifyState>(Event.NotifyStateClass, Sequence, EffectParameters, NotifiesLeftOut);
		}
		if (bHadObject && !Event.Notify && !Event.NotifyStateClass)
		{
			Sequence->Notifies.RemoveAt(Index);
			continue;
		}
		PlaceNotify(Sequence, Event, Event.GetTime(), Event.GetDuration(), Event.TrackIndex);
		++Index;
	}
	Sequence->RefreshCacheData();
	FAssetRegistryModule::AssetCreated(Sequence);
	Sequence->MarkPackageDirty();
	return Sequence;
}

// ------------------------------------------------------------------------------------------------
// Retarget bake (editor 1.8): any animation, another skeleton's or one of the game's (which has no keys in this project,
// only its compressed data), sampled frame by frame onto the character's skeleton. Rotations are taken as they are
// (Square Enix characters share bone names and axes, the way the game mod's families play them); translations follow
// Retarget: with the character's build, the body chain keeps its own bone lengths, the hips are scaled to its height and
// every other bone moves the way the animation moves it from its own rest pose (the rules the game mod's proportions
// use, SkelCompat::ProportionModes).
//
// Editor 1.12: Retarget "Keep the character's own pose" (Motion) gives each bone the animation's change from a pose of
// its skeleton instead of its rotation: the change of the bone relative to the nearest bone above it the character has
// too (so a bone the character lacks, Sephiroth's fourth spine bone on Bizarro, still moves the ones under it, and a
// spine hung from the root instead of the hips gets the hips' motion), turned from the animation's bone axes into the
// character's (both poses in component space), on top of the character's own pose. Without a Base, the change is from
// the animation's rest pose, added to the character's rest pose. A Base (an animation of the character's own skeleton,
// e.g. its idle) plays under the move: the bones the animation does not drive (a monster's wings, tentacles, clouds)
// move as in it, its root stays (no root motion), and the change is from the pose that matches it (Motion From's first
// frame, that character's idle; or the animation's own first frame), added to its pose. Base Loop makes a loop as long
// as Base, the animation repeated to fill it, so a looping move and Base both loop without a jump.
// Retarget "leaning into the animation's root motion" (Lean) takes nothing but the animation's root motion: Base's pose,
// its Lean Bone (with every bone under it) leaning the way the root goes and turning ahead into its turns, for a body
// that has nothing of the animation's (Bizarro Sephiroth on Sephiroth's flying locomotion).
// ------------------------------------------------------------------------------------------------
struct FBakeResult
{
	int32 Bones = 0;           // tracks carried over
	int32 Dropped = 0;         // tracks of bones the character does not have
	int32 Curves = 0;
	int32 CurvesDropped = 0;   // curves the character's skeleton has no name for (none is added to it)
	int32 Frames = 0;
	int32 SourceEffects = 0;   // the animation's own sounds and effects kept
	int32 EffectParameters = 0;  // (1.12.4) effect parameters of the game's this editor cannot write, taken out of them
	int32 NotifiesLeftOut = 0;   // (1.12.4) its sounds and effects not kept for one (outside a list)
	int32 BaseBones = 0;       // (1.12) bones only Base moves
	int32 Loops = 1;           // (1.12) Base Loop: how many times the animation plays in the move
	FName LeanBone;            // (1.12) Lean: the bone that leans (the root: every bone)
	float MostLean = 0.f;      // (1.12) Lean: the most it leans (degrees)
	float MostTwist = 0.f;     // (1.12) Lean: the most it twists into a turn (degrees)
	float RootMotionScale = 0.f; // (1.12.2) over Base: its root moves as the animation's, this many times as far (0: it does not)
	FName MappedAnchor;        // (1.12.3) Bone Map: the bone of the animation its motion is taken relative to
	bool bRetargeted = false;  // made for another skeleton
	bool bCompressed = false;  // sampled from compressed data (a game animation)
};

// Whether `Anim` can be sampled in this editor, and from its keys (`bRaw`) or its compressed data. False with `Error`.
bool SampleableAnimation(UAnimSequence* Anim, bool& bRaw, FString& Error)
{
	bRaw = !IsCookedAsset(Anim) && Anim->GetRawAnimationData().Num() > 0 && Anim->GetRawTrackToSkeletonMapTable().Num() == Anim->GetRawAnimationData().Num();
	if (!bRaw && !Anim->IsCompressedDataValid())
	{
		Error = Anim->GetName() + TEXT(" has neither keys nor compressed data in this editor");
		return false;
	}
	// Some game animations keep their rotations as whole quaternions (ACL's Quat_128 format). This editor's ACL decoder
	// stops the editor on those (a null read in decompress_and_interpolate_rotation), so they are refused instead.
	// The compressed bytes are an ACL compressed clip: {size, hash, tag 0xAC10AC10, version, algorithm} then the clip
	// header {bones, segments, rotation format, ...}; the rotation format is at byte 20.
	if (!bRaw)
	{
		const TArray<uint8>& Bytes = Anim->CompressedData.CompressedByteStream;
		if (Bytes.Num() >= 24 && FPlatformMemory::ReadUnaligned<uint32>(Bytes.GetData() + 8) == 0xAC10AC10u && Bytes[20] == 0)
		{
			Error = Anim->GetName() + TEXT(" keeps its rotations as whole quaternions (ACL Quat_128), which this editor cannot sample without stopping; ")
					TEXT("use another animation");
			return false;
		}
	}
	return true;
}

// The track of each bone of `Skeleton` in `Anim` (INDEX_NONE: none).
TArray<int32> TracksByBone(UAnimSequence* Anim, bool bRaw, const FReferenceSkeleton& Skeleton)
{
	TArray<int32> Of;
	Of.Init(INDEX_NONE, Skeleton.GetNum());
	if (!Anim)
	{
		return Of;
	}
	const TArray<FTrackToSkeletonMap>& Map = bRaw ? Anim->GetRawTrackToSkeletonMapTable() : Anim->GetCompressedTrackToSkeletonMapTable();
	for (int32 Track = 0; Track < Map.Num(); ++Track)
	{
		const int32 Bone = Map[Track].BoneTreeIndex;
		if (Of.IsValidIndex(Bone))
		{
			Of[Bone] = Track;
		}
	}
	return Of;
}

// Each bone's rotation in component space, from its rotation relative to its parent (`Local`, one per bone).
TArray<FQuat> ComponentRotations(const FReferenceSkeleton& Skeleton, const TArray<FQuat>& Local)
{
	TArray<FQuat> Out;
	Out.SetNum(Skeleton.GetNum());
	for (int32 Bone = 0; Bone < Skeleton.GetNum(); ++Bone)
	{
		const int32 Parent = Skeleton.GetParentIndex(Bone);
		const FQuat Own = Local.IsValidIndex(Bone) ? Local[Bone].GetNormalized() : FQuat::Identity;
		Out[Bone] = Parent >= 0 && Parent < Bone ? (Out[Parent] * Own).GetNormalized() : Own;
	}
	return Out;
}

// tanh(X): 0 at 0, rising almost straight at first and easing off towards 1.
float EaseOff(float X)
{
	const float E = FMath::Exp(2.f * FMath::Clamp(X, -20.f, 20.f));
	return (E - 1.f) / (E + 1.f);
}

// Each bone's rotation in component space in the rest pose.
TArray<FQuat> RestRotations(const FReferenceSkeleton& Skeleton)
{
	TArray<FQuat> Local;
	Local.SetNum(Skeleton.GetNum());
	const TArray<FTransform>& Pose = Skeleton.GetRefBonePose();
	for (int32 Bone = 0; Bone < Skeleton.GetNum(); ++Bone)
	{
		Local[Bone] = Pose.IsValidIndex(Bone) ? Pose[Bone].GetRotation() : FQuat::Identity;
	}
	return ComponentRotations(Skeleton, Local);
}

// (1.12.1) A form's model made another way (facing +Y as imported models do, floating high): every bone under the root
// placed as the animation shows it (in component space), turned `TurnDegrees` about the up axis through the root's
// reference place and moved up `Lift`; the root held at its reference pose. The game holds a character's root at its
// reference pose and moves the character itself, so the body then stands in game as the animation shows it, facing the
// game's way (+X). (A root that moves in the animation, as a body sinking in a death, moves the body.)
void StandModel(UAnimSequence* Sequence, const FReferenceSkeleton& Skeleton, float TurnDegrees, float Lift, int32 Frames)
{
	if (!Sequence || Skeleton.GetNum() == 0 || Frames < 1)
	{
		return;
	}
	const TArray<FTransform>& RefPose = Skeleton.GetRefBonePose();
	const FQuat RefRotation = RefPose[0].GetRotation().GetNormalized();
	const FVector RefPlace = RefPose[0].GetTranslation();
	const FQuat Turn(FVector(0.f, 0.f, 1.f), FMath::DegreesToRadians(TurnDegrees));
	TArray<int32> TrackOf;
	TrackOf.Init(INDEX_NONE, Skeleton.GetNum());
	const TArray<FTrackToSkeletonMap>& Map = Sequence->GetRawTrackToSkeletonMapTable();
	for (int32 Track = 0; Track < Map.Num(); ++Track)
	{
		if (TrackOf.IsValidIndex(Map[Track].BoneTreeIndex))
		{
			TrackOf[Map[Track].BoneTreeIndex] = Track;
		}
	}
	// a bone's key at a frame (its reference pose where it has no track; one key: every frame)
	const auto KeyOf = [&](int32 Bone, int32 Frame)
	{
		FTransform Atom = RefPose.IsValidIndex(Bone) ? RefPose[Bone] : FTransform::Identity;
		if (TrackOf[Bone] == INDEX_NONE)
		{
			return Atom;
		}
		const FRawAnimSequenceTrack& Keys = Sequence->GetRawAnimationTrack(TrackOf[Bone]);
		if (Keys.PosKeys.Num() > 0) { Atom.SetTranslation(Keys.PosKeys[FMath::Min(Frame, Keys.PosKeys.Num() - 1)]); }
		if (Keys.RotKeys.Num() > 0) { Atom.SetRotation(Keys.RotKeys[FMath::Min(Frame, Keys.RotKeys.Num() - 1)].GetNormalized()); }
		if (Keys.ScaleKeys.Num() > 0) { Atom.SetScale3D(Keys.ScaleKeys[FMath::Min(Frame, Keys.ScaleKeys.Num() - 1)]); }
		return Atom;
	};
	TArray<int32> Children;
	for (int32 Bone = 1; Bone < Skeleton.GetNum(); ++Bone)
	{
		if (Skeleton.GetParentIndex(Bone) == 0)
		{
			Children.Add(Bone);
		}
	}
	TArray<FRawAnimSequenceTrack> Placed;
	Placed.SetNum(Children.Num());
	for (int32 Frame = 0; Frame < Frames; ++Frame)
	{
		const FTransform Root = KeyOf(0, Frame);
		for (int32 Index = 0; Index < Children.Num(); ++Index)
		{
			const FTransform Child = KeyOf(Children[Index], Frame);
			const FVector Place = Root.GetTranslation() + Root.GetRotation().RotateVector(Child.GetTranslation());   // as the animation shows it
			const FVector Stood = RefPlace + Turn.RotateVector(Place - RefPlace) + FVector(0.f, 0.f, Lift);
			FQuat Rotation = (RefRotation.Inverse() * (Turn * (Root.GetRotation() * Child.GetRotation()))).GetNormalized();
			TArray<FQuat>& RotKeys = Placed[Index].RotKeys;
			if (RotKeys.Num() > 0 && (RotKeys.Last() | Rotation) < 0.f)
			{
				Rotation = FQuat(-Rotation.X, -Rotation.Y, -Rotation.Z, -Rotation.W);
			}
			Placed[Index].PosKeys.Add(RefRotation.Inverse().RotateVector(Stood - RefPlace));
			RotKeys.Add(Rotation);
			Placed[Index].ScaleKeys.Add(Child.GetScale3D());
		}
	}
	for (int32 Index = 0; Index < Children.Num(); ++Index)
	{
		const int32 Bone = Children[Index];
		if (TrackOf[Bone] != INDEX_NONE)
		{
			Sequence->GetRawAnimationTrack(TrackOf[Bone]) = Placed[Index];
		}
		else
		{
			Sequence->AddNewRawTrack(Skeleton.GetBoneName(Bone), &Placed[Index]);
		}
	}
	FRawAnimSequenceTrack Held;
	Held.PosKeys.Add(RefPlace);
	Held.RotKeys.Add(RefRotation);
	Held.ScaleKeys.Add(RefPose[0].GetScale3D());
	if (TrackOf[0] != INDEX_NONE)
	{
		Sequence->GetRawAnimationTrack(TrackOf[0]) = Held;
	}
	else
	{
		Sequence->AddNewRawTrack(Skeleton.GetBoneName(0), &Held);
	}
}

// (1.12.2) A move made over Base (Lean, Motion with a Base) moves the character as its animation does: the game's walks and
// runs move the character by their root's motion (it shows the body under the root's reference pose), so a move that kept
// Base's root (an idle's, which does not go anywhere) walked in place. The root goes as the animation's root goes: the clip,
// and in a loop the clip again from where it ended; `MotionScale` times as far (a form's model at a size of its own: the
// game moves the character by the root's motion in the model's own units, times its size).
void MoveRootAsSource(UAnimSequence* Sequence, const FReferenceSkeleton& Skeleton, UAnimSequence* Source, int32 RootTrack, bool bRaw,
	TFunctionRef<float(float)> SourceTime, int32 Frames, float Step, float Length, bool bLooped, float LoopLength, float From0, float To0,
	float MotionScale)
{
	if (!Sequence || !Source || RootTrack == INDEX_NONE || Skeleton.GetNum() == 0 || Frames < 1)
	{
		return;
	}
	const auto RootAt = [&](float At)
	{
		FTransform Atom = FTransform::Identity;
		Source->GetBoneTransform(Atom, RootTrack, At, bRaw);
		Atom.SetScale3D(FVector(1.f, 1.f, 1.f));
		Atom.NormalizeRotation();
		return Atom;
	};
	// (FTransform A * B: A, then B) the root's move over the clip, from where the clip starts
	const FTransform ClipMove = RootAt(From0).Inverse() * RootAt(To0);
	FRawAnimSequenceTrack Track;
	FTransform Again = FTransform::Identity;   // the clip's move times the loops played before this one
	int32 Played = 0;
	FVector First = FVector::ZeroVector;
	for (int32 Frame = 0; Frame < Frames; ++Frame)
	{
		const float Time = FMath::Min(Frame * Step, Length);
		FTransform Root;
		if (bLooped && LoopLength > KINDA_SMALL_NUMBER)
		{
			const int32 Loop = FMath::Max(0, FMath::FloorToInt(Time / LoopLength));
			const float InLoop = FMath::Clamp(Time - Loop * LoopLength, 0.f, LoopLength);
			while (Played < Loop)
			{
				Again = Again * ClipMove;
				++Played;
			}
			Root = RootAt(From0 + InLoop / LoopLength * (To0 - From0)) * Again;
		}
		else
		{
			Root = RootAt(SourceTime(Time));
		}
		if (Frame == 0)
		{
			First = Root.GetTranslation();
		}
		FQuat Rotation = Root.GetRotation().GetNormalized();
		if (Track.RotKeys.Num() > 0 && (Track.RotKeys.Last() | Rotation) < 0.f)
		{
			Rotation = FQuat(-Rotation.X, -Rotation.Y, -Rotation.Z, -Rotation.W);
		}
		Track.PosKeys.Add(First + (Root.GetTranslation() - First) * MotionScale);
		Track.RotKeys.Add(Rotation);
		Track.ScaleKeys.Add(Skeleton.GetRefBonePose()[0].GetScale3D());
	}
	const TArray<FTrackToSkeletonMap>& Map = Sequence->GetRawTrackToSkeletonMapTable();
	for (int32 Index = 0; Index < Map.Num(); ++Index)
	{
		if (Map[Index].BoneTreeIndex == 0)
		{
			Sequence->GetRawAnimationTrack(Index) = Track;
			return;
		}
	}
	Sequence->AddNewRawTrack(Skeleton.GetBoneName(0), &Track);
}

// `ClipStart` / `ClipEnd` (seconds into Source; 0: its start / end) and `Speed`: the move is that part of Source, played
// that much faster (its own sounds and effects follow). `Base` (1.12, optional, of Target): played under the move.
// `MotionFrom` (1.12, optional, of Source's skeleton; Motion with a Base): its first frame is the pose that matches Base.
// `LeanBone`, `LeanDegrees` (1.12, Lean with a Base): the bone that leans into Source's root motion and how far.
// `ModelTurn`, `ModelLift` (1.12.1, a form's): the model turned and lifted, its root held at its reference pose (StandModel).
// `MotionScale` (1.12.2, Lean or Motion with a Base): the root moves as Source's does, this many times as far (MoveRootAsSource).
// (1.12.3) A move's Bone Map: "Source=Target" pairs (also "Source>Target"), separated by commas, semicolons or lines, and
// "@Bone", the bone of the animation its motion is taken relative to. Out: the character's bone -> the animation's bone.
bool ParseBoneMap(const FString& Text, TMap<FName, FName>& TargetToSource, FName& Anchor, FString& Problems)
{
	TArray<FString> Entries;
	FString Clean = Text.Replace(TEXT(";"), TEXT(",")).Replace(TEXT("\r"), TEXT(",")).Replace(TEXT("\n"), TEXT(","));
	Clean.ParseIntoArray(Entries, TEXT(","), true);
	for (FString Entry : Entries)
	{
		Entry.TrimStartAndEndInline();
		if (Entry.IsEmpty())
		{
			continue;
		}
		if (Entry.StartsWith(TEXT("@")))
		{
			Anchor = FName(*Entry.Mid(1).TrimStartAndEnd());
			continue;
		}
		FString Left, Right;
		if (!Entry.Split(TEXT("="), &Left, &Right) && !Entry.Split(TEXT(">"), &Left, &Right))
		{
			Problems += FString::Printf(TEXT(" \"%s\" is not Source=Target;"), *Entry);
			continue;
		}
		Left.TrimStartAndEndInline();
		Right.TrimStartAndEndInline();
		Right.RemoveFromStart(TEXT(">"));   // (Source->Target)
		Left.RemoveFromEnd(TEXT("-"));
		Left.TrimStartAndEndInline();
		Right.TrimStartAndEndInline();
		if (Left.IsEmpty() || Right.IsEmpty())
		{
			Problems += FString::Printf(TEXT(" \"%s\" is not Source=Target;"), *Entry);
			continue;
		}
		const FName TargetBone(*Right);
		if (TargetToSource.Contains(TargetBone))
		{
			Problems += FString::Printf(TEXT(" %s is mapped twice;"), *Right);
			continue;
		}
		TargetToSource.Add(TargetBone, FName(*Left));
	}
	return Problems.IsEmpty();
}

UAnimSequence* MakeAnimationBySampling(UAnimSequence* Source, USkeleton* Target, const FString& Package, const FString& Name, EEndMoveRetarget Mode,
	bool bKeepSourceEffects, FBakeResult& Result, FString& Error, float ClipStart = 0.f, float ClipEnd = 0.f, float Speed = 1.f,
	UAnimSequence* Base = nullptr, bool bBaseLoop = false, UAnimSequence* MotionFrom = nullptr, const FString& LeanBone = FString(), float LeanDegrees = 18.f,
	float ModelTurn = 0.f, float ModelLift = 0.f, float MotionScale = 1.f, const FString& BoneMap = FString(), float SourceTurn = 0.f, bool bKeepBaseRoot = false,
	bool bSourceSoundsOnly = false)
{
	USkeleton* SourceSkeleton = Source->GetSkeleton();
	// (1.12.3) a Bone Map (Retarget "Keep the character's own pose"): only the mapped bones, each from its bone of Source
	const bool bBoneMap = !BoneMap.TrimStartAndEnd().IsEmpty() && Mode == EEndMoveRetarget::Motion;
	if (!SourceSkeleton || !Target)
	{
		Error = !SourceSkeleton ? Source->GetName() + TEXT(" has no skeleton") : FString(TEXT("there is no skeleton to put it on (set the row's Character Skeleton)"));
		return nullptr;
	}
	if (Source->IsValidAdditive())
	{
		Error = Source->GetName() + TEXT(" is an additive animation; make the move from a whole-body one");
		return nullptr;
	}
	bool bRaw = false;
	if (!SampleableAnimation(Source, bRaw, Error))
	{
		return nullptr;
	}
	bool bBaseRaw = false;
	if (Base)
	{
		if (Base->GetSkeleton() != Target)
		{
			Error = FString::Printf(TEXT("its Base %s is of %s, not of the skeleton the move is built on (%s)"), *Base->GetName(),
				Base->GetSkeleton() ? *Base->GetSkeleton()->GetName() : TEXT("no skeleton"), *Target->GetName());
			return nullptr;
		}
		if (Base->IsValidAdditive())
		{
			Error = TEXT("its Base ") + Base->GetName() + TEXT(" is an additive animation; use a whole-body one (the character's idle)");
			return nullptr;
		}
		FString BaseError;
		if (!SampleableAnimation(Base, bBaseRaw, BaseError))
		{
			Error = TEXT("its Base: ") + BaseError;
			return nullptr;
		}
	}
	if (Mode == EEndMoveRetarget::Lean && !Base)
	{
		Error = TEXT("Retarget \"leaning into the animation's root motion\" needs a Base (the character's own idle) to lean");
		return nullptr;
	}
	// (1.12) Motion From: only "Keep the character's own pose" with a Base uses it
	if (Mode != EEndMoveRetarget::Motion || !Base)
	{
		MotionFrom = nullptr;
	}
	bool bMotionFromRaw = false;
	if (MotionFrom)
	{
		if (MotionFrom->GetSkeleton() != SourceSkeleton)
		{
			Error = FString::Printf(TEXT("its Motion From %s is of %s, not of %s's skeleton (%s)"), *MotionFrom->GetName(),
				MotionFrom->GetSkeleton() ? *MotionFrom->GetSkeleton()->GetName() : TEXT("no skeleton"), *Source->GetName(), *SourceSkeleton->GetName());
			return nullptr;
		}
		if (MotionFrom->IsValidAdditive())
		{
			Error = TEXT("its Motion From ") + MotionFrom->GetName() + TEXT(" is an additive animation; use a whole-body one (that character's idle)");
			return nullptr;
		}
		FString FromError;
		if (!SampleableAnimation(MotionFrom, bMotionFromRaw, FromError))
		{
			Error = TEXT("its Motion From: ") + FromError;
			return nullptr;
		}
	}
	const TArray<FTrackToSkeletonMap>& TrackMap = bRaw ? Source->GetRawTrackToSkeletonMapTable() : Source->GetCompressedTrackToSkeletonMapTable();
	const FReferenceSkeleton& From = SourceSkeleton->GetReferenceSkeleton();
	const FReferenceSkeleton& To = Target->GetReferenceSkeleton();
	const TArray<FTransform>& FromPose = From.GetRefBonePose();
	const TArray<FTransform>& ToPose = To.GetRefBonePose();
	std::vector<std::wstring> Names;
	std::vector<int32_t> Parents;
	for (int32 Bone = 0; Bone < To.GetNum(); ++Bone)
	{
		Names.push_back(Wide(To.GetBoneName(Bone).ToString()));
		Parents.push_back(To.GetParentIndex(Bone));
	}
	const std::vector<SkelCompat::RetargetMode> Modes = SkelCompat::ProportionModes(Names, Parents);
	Result.bRetargeted = SourceSkeleton != Target;
	Result.bCompressed = !bRaw;
	const bool bMotion = Mode == EEndMoveRetarget::Motion;
	const bool bLean = Mode == EEndMoveRetarget::Lean;
	// (1.12.1) the form's model turned and lifted (StandModel, after the bones are made)
	const bool bStand = !FMath::IsNearlyZero(ModelTurn) || !FMath::IsNearlyZero(ModelLift);
	const FQuat StandTurn(FVector(0.f, 0.f, 1.f), FMath::DegreesToRadians(ModelTurn));
	const FQuat RefRootRotation = To.GetNum() > 0 ? To.GetRefBonePose()[0].GetRotation().GetNormalized() : FQuat::Identity;
	const bool bKeepBuild = Result.bRetargeted && Mode == EEndMoveRetarget::Proportions;

	const float SourceLength = Source->SequenceLength;
	int32 SourceFrames = Source->GetRawNumberOfFrames();
	if (SourceFrames < 2 && !bRaw && Source->CompressedData.CompressedDataStructure)
	{
		SourceFrames = Source->CompressedData.CompressedDataStructure->CompressedNumberOfFrames;
	}
	if (SourceFrames < 2)
	{
		SourceFrames = FMath::Max(2, FMath::RoundToInt(SourceLength * 30.f) + 1);
	}
	// The part of Source the move is made of, and how fast it plays it.
	const float From0 = FMath::Clamp(ClipStart, 0.f, SourceLength);
	const float To0 = ClipEnd > 0.f ? FMath::Clamp(ClipEnd, From0, SourceLength) : SourceLength;
	const float Rate = FMath::Clamp(Speed > 0.f ? Speed : 1.f, 0.1f, 10.f);
	if (To0 - From0 < 1.f / 60.f)
	{
		Error = FString::Printf(TEXT("its clip %.3f - %.3f s of %s (%.3f s) is empty"), ClipStart, ClipEnd, *Source->GetName(), SourceLength);
		return nullptr;
	}
	// (1.12) Base Loop: as long as Base, the clip played Loops times in it (each a little faster or slower to fit)
	const float BaseLength = Base ? Base->SequenceLength : 0.f;
	const bool bLooped = Base && bBaseLoop && BaseLength > 1.f / 60.f;
	const float ClipLength = (To0 - From0) / Rate;
	const int32 Loops = bLooped ? FMath::Max(1, FMath::RoundToInt(BaseLength / ClipLength)) : 1;
	const float Length = bLooped ? BaseLength : ClipLength;
	const float LoopLength = Length / static_cast<float>(Loops);
	Result.Loops = Loops;
	const bool bWhole = !bLooped && From0 <= 0.f && To0 >= SourceLength && FMath::IsNearlyEqual(Rate, 1.f);
	const float SourceRate = SourceLength > KINDA_SMALL_NUMBER ? static_cast<float>(SourceFrames - 1) / SourceLength : 30.f;
	const int32 Frames = bWhole ? SourceFrames : FMath::Max(2, FMath::RoundToInt(Length * FMath::Clamp(SourceRate, 15.f, 60.f)) + 1);
	const float Step = Length / static_cast<float>(Frames - 1);
	// The time in Source of a time in the move (a loop: the clip again from its start, the move's end its start).
	const auto SourceTime = [&](float Time)
	{
		if (bLooped)
		{
			const float InLoop = FMath::Fmod(FMath::Max(Time, 0.f), LoopLength);
			return FMath::Clamp(From0 + InLoop / LoopLength * (To0 - From0), From0, To0);
		}
		return FMath::Clamp(From0 + Time * Rate, 0.f, SourceLength);
	};
	// The time in Base of a time in the move (looping under the move).
	const auto BaseTime = [&](float Time)
	{
		if (!Base || BaseLength <= KINDA_SMALL_NUMBER)
		{
			return 0.f;
		}
		return bLooped ? FMath::Clamp(Time, 0.f, BaseLength) : FMath::Fmod(FMath::Max(Time, 0.f), BaseLength);
	};
	Result.Frames = Frames;

	struct FBakeTrack
	{
		FName Bone;
		int32 Track = INDEX_NONE;
		int32 FromBone = INDEX_NONE;
		int32 ToBone = INDEX_NONE;
	};
	TArray<FBakeTrack> Tracks;
	for (int32 Track = 0; Track < TrackMap.Num(); ++Track)
	{
		const int32 FromBone = TrackMap[Track].BoneTreeIndex;
		if (FromBone < 0 || FromBone >= From.GetNum())
		{
			continue;
		}
		const FName Bone = From.GetBoneName(FromBone);
		const int32 ToBone = To.FindBoneIndex(Bone);
		if (ToBone == INDEX_NONE)
		{
			++Result.Dropped;
			continue;
		}
		Tracks.Add(FBakeTrack{Bone, Track, FromBone, ToBone});
	}
	if (Tracks.Num() == 0 && !bMotion && !bLean)
	{
		Error = FString::Printf(TEXT("%s and %s have no bone in common"), *SourceSkeleton->GetName(), *Target->GetName());
		return nullptr;
	}
	UAnimBoneCompressionSettings* BoneCompression = LoadObject<UAnimBoneCompressionSettings>(nullptr, GameBoneCompression, nullptr, LOAD_NoWarn | LOAD_Quiet);
	TurnOffAclSafetyFallback(BoneCompression);
	UAnimCurveCompressionSettings* CurveCompression = LoadObject<UAnimCurveCompressionSettings>(nullptr, GameCurveCompression, nullptr, LOAD_NoWarn | LOAD_Quiet);
	if (!BoneCompression || !CurveCompression)
	{
		Error = FString::Printf(TEXT("the game's animation compression settings are not in this project (%s, %s): the game reads every animation with them"),
			BoneCompression ? TEXT("bone settings found") : GameBoneCompression, CurveCompression ? TEXT("curve settings found") : GameCurveCompression);
		return nullptr;
	}
	UPackage* Outer = CreatePackage(*Package);
	if (!Outer)
	{
		Error = Package + TEXT(" could not be made");
		return nullptr;
	}
	Outer->FullyLoad();
	if (StaticFindObjectFast(nullptr, Outer, FName(*Name)))
	{
		Error = Package + TEXT(" is still loaded (close it, then build again)");
		return nullptr;
	}
	UAnimSequence* Sequence = NewObject<UAnimSequence>(Outer, FName(*Name), RF_Public | RF_Standalone | RF_Transactional);
	Sequence->SetSkeleton(Target);
	CopyNamedProperties(Source, Sequence, {TEXT("RateScale"), TEXT("Interpolation"), TEXT("bLoop")});
	Sequence->BoneCompressionSettings = BoneCompression;
	Sequence->CurveCompressionSettings = CurveCompression;
	Sequence->SequenceLength = Length;
	Sequence->SetRawNumberOfFrame(Frames);
	const TArray<int32> BaseTracks = TracksByBone(Base, bBaseRaw, To);
	// Base's local transform of a bone of the character (its rest pose where Base has no track for it).
	const auto BaseLocal = [&](int32 Bone, float Time)
	{
		FTransform Atom = ToPose.IsValidIndex(Bone) ? ToPose[Bone] : FTransform::Identity;
		if (Base && BaseTracks.IsValidIndex(Bone) && BaseTracks[Bone] != INDEX_NONE)
		{
			Base->GetBoneTransform(Atom, BaseTracks[Bone], Time, bBaseRaw);
		}
		return Atom;
	};
	TArray<bool> Done;
	Done.Init(false, To.GetNum());
	if (bMotion)
	{
		// Each bone of the character: its bone in the animation, and the bone of the animation its change is taken
		// relative to (the one of the nearest bone above it the character has too, when it is above it there as well).
		TArray<int32> SourceOf, AnchorOf;
		SourceOf.Init(INDEX_NONE, To.GetNum());
		AnchorOf.Init(INDEX_NONE, To.GetNum());
		const auto IsAbove = [&](int32 Above, int32 Bone)
		{
			for (int32 Up = From.GetParentIndex(Bone); Up != INDEX_NONE; Up = From.GetParentIndex(Up))
			{
				if (Up == Above)
				{
					return true;
				}
			}
			return false;
		};
		// (1.12.3) a Bone Map: the character's bone -> its bone of Source; "@Bone": the anchor where no mapped bone is above
		TMap<FName, FName> TargetToSource;
		FName MapAnchor = NAME_None;
		int32 AnchorBone = INDEX_NONE;
		if (bBoneMap)
		{
			FString Problems;
			ParseBoneMap(BoneMap, TargetToSource, MapAnchor, Problems);
			for (const TPair<FName, FName>& Pair : TargetToSource)
			{
				if (To.FindBoneIndex(Pair.Key) == INDEX_NONE)
				{
					Problems += FString::Printf(TEXT(" %s is not a bone of %s;"), *Pair.Key.ToString(), *Target->GetName());
				}
				if (From.FindBoneIndex(Pair.Value) == INDEX_NONE)
				{
					Problems += FString::Printf(TEXT(" %s is not a bone of %s;"), *Pair.Value.ToString(), *SourceSkeleton->GetName());
				}
			}
			if (MapAnchor != NAME_None)
			{
				AnchorBone = From.FindBoneIndex(MapAnchor);
				if (AnchorBone == INDEX_NONE)
				{
					Problems += FString::Printf(TEXT(" its anchor %s is not a bone of %s;"), *MapAnchor.ToString(), *SourceSkeleton->GetName());
				}
			}
			if (!Problems.IsEmpty() || TargetToSource.Num() == 0)
			{
				Sequence->ClearFlags(RF_Public | RF_Standalone);
				Sequence->MarkPendingKill();
				Error = TEXT("its Bone Map:") + (Problems.IsEmpty() ? FString(TEXT(" maps no bone")) : Problems.LeftChop(1));
				return nullptr;
			}
		}
		int32 Matched = 0;
		for (int32 Bone = 0; Bone < To.GetNum(); ++Bone)
		{
			int32 Own = INDEX_NONE;
			if (bBoneMap)
			{
				if (const FName* SourceName = TargetToSource.Find(To.GetBoneName(Bone)))
				{
					Own = From.FindBoneIndex(*SourceName);
				}
			}
			else
			{
				Own = From.FindBoneIndex(To.GetBoneName(Bone));
			}
			if (Own == INDEX_NONE)
			{
				continue;
			}
			SourceOf[Bone] = Own;
			++Matched;
			for (int32 Up = To.GetParentIndex(Bone); Up != INDEX_NONE; Up = To.GetParentIndex(Up))
			{
				if (SourceOf[Up] != INDEX_NONE && IsAbove(SourceOf[Up], Own))
				{
					AnchorOf[Bone] = SourceOf[Up];
					break;
				}
			}
			if (AnchorOf[Bone] == INDEX_NONE && AnchorBone != INDEX_NONE && IsAbove(AnchorBone, Own))
			{
				AnchorOf[Bone] = AnchorBone;
			}
		}
		if (Matched == 0)
		{
			Sequence->ClearFlags(RF_Public | RF_Standalone);
			Sequence->MarkPendingKill();
			Error = FString::Printf(TEXT("%s and %s have no bone in common"), *SourceSkeleton->GetName(), *Target->GetName());
			return nullptr;
		}
		// (1.12.3) Source Turn: Source's skeleton turned from the character's about up (its axes into the character's)
		const bool bTurned = !FMath::IsNearlyZero(SourceTurn);
		const FQuat Turn(FVector(0.f, 0.f, 1.f), FMath::DegreesToRadians(SourceTurn));
		Result.MappedAnchor = MapAnchor;
		const TArray<int32> SourceTracks = TracksByBone(Source, bRaw, From);
		// The pose of the animation's skeleton the change is taken from, and its match on the character: without a Base,
		// the two rest poses; with a Base, Motion From's first frame (the animation's own first frame without one) and
		// Base's pose at each time. (A game animation's root is turned from its skeleton's rest pose, and a stance, an arm
		// holding a sword, is not motion: from the rest pose, both would be added to Base's pose a second time.)
		TArray<FQuat> SourceReference;
		if (Base)
		{
			const TArray<int32> ReferenceTracks = TracksByBone(MotionFrom, bMotionFromRaw, From);
			TArray<FQuat> Local;
			Local.SetNum(From.GetNum());
			for (int32 Bone = 0; Bone < From.GetNum(); ++Bone)
			{
				FTransform Atom = FromPose.IsValidIndex(Bone) ? FromPose[Bone] : FTransform::Identity;
				if (MotionFrom ? ReferenceTracks[Bone] != INDEX_NONE : SourceTracks[Bone] != INDEX_NONE)
				{
					if (MotionFrom)
					{
						MotionFrom->GetBoneTransform(Atom, ReferenceTracks[Bone], 0.f, bMotionFromRaw);
					}
					else
					{
						Source->GetBoneTransform(Atom, SourceTracks[Bone], SourceTime(0.f), bRaw);
					}
				}
				Local[Bone] = Atom.GetRotation();
			}
			SourceReference = ComponentRotations(From, Local);
		}
		else
		{
			SourceReference = RestRotations(From);
		}
		const TArray<FQuat> TargetRest = RestRotations(To);
		TArray<FRawAnimSequenceTrack> Out;
		Out.SetNum(To.GetNum());
		TArray<FQuat> NowLocal, UnderLocal;
		TArray<FVector> NowPosition;
		TArray<FTransform> Under;
		NowLocal.SetNum(From.GetNum());
		NowPosition.SetNum(From.GetNum());
		UnderLocal.SetNum(To.GetNum());
		Under.SetNum(To.GetNum());
		for (int32 Frame = 0; Frame < Frames; ++Frame)
		{
			const float Time = FMath::Min(Frame * Step, Length);
			const float At = SourceTime(Time);
			const float BaseAt = BaseTime(Time);
			// the animation's pose (its rest pose where it has no track)
			for (int32 Bone = 0; Bone < From.GetNum(); ++Bone)
			{
				FTransform Atom = FromPose.IsValidIndex(Bone) ? FromPose[Bone] : FTransform::Identity;
				if (SourceTracks[Bone] != INDEX_NONE)
				{
					Source->GetBoneTransform(Atom, SourceTracks[Bone], At, bRaw);
				}
				NowLocal[Bone] = Atom.GetRotation();
				NowPosition[Bone] = Atom.GetTranslation();
			}
			const TArray<FQuat> Now = ComponentRotations(From, NowLocal);
			// the character's pose under the move: Base's (its rest pose where Base has no track), or its rest pose
			for (int32 Bone = 0; Bone < To.GetNum(); ++Bone)
			{
				Under[Bone] = BaseLocal(Bone, BaseAt);
				UnderLocal[Bone] = Under[Bone].GetRotation().GetNormalized();
			}
			const TArray<FQuat> TargetReference = Base ? ComponentRotations(To, UnderLocal) : TargetRest;
			for (int32 Bone = 0; Bone < To.GetNum(); ++Bone)
			{
				const int32 Own = SourceOf[Bone];
				if (Own == INDEX_NONE && !(Base && BaseTracks[Bone] != INDEX_NONE))
				{
					continue;
				}
				const bool bRoot = To.GetParentIndex(Bone) == INDEX_NONE;
				FQuat Rotation = UnderLocal[Bone];
				FVector Position = Under[Bone].GetTranslation();
				// (with a Base, the root keeps Base's here: the body is placed by it; MoveRootAsSource then gives the root
				// the animation's motion, which moves the character)
				if (Own != INDEX_NONE && !(Base && bRoot))
				{
					const int32 Anchor = AnchorOf[Bone];
					const FQuat FromRelative = Anchor == INDEX_NONE ? SourceReference[Own] : SourceReference[Anchor].Inverse() * SourceReference[Own];
					const FQuat NowRelative = Anchor == INDEX_NONE ? Now[Own] : Now[Anchor].Inverse() * Now[Own];
					const FQuat Change = (FromRelative.Inverse() * NowRelative).GetNormalized();                           // in the animation bone's axes
					FQuat World = (SourceReference[Own] * Change * SourceReference[Own].Inverse()).GetNormalized();         // in component axes
					if (bTurned)
					{
						World = (Turn * World * Turn.Inverse()).GetNormalized();   // (1.12.3) in the character's component axes
					}
					const FQuat Mine = (TargetReference[Bone].Inverse() * World * TargetReference[Bone]).GetNormalized();   // in the character bone's axes
					Rotation = (Rotation * Mine).GetNormalized();
					if (bRoot)
					{
						Position = NowPosition[Own];   // (no Base: the animation's root motion)
					}
				}
				TArray<FQuat>& Keys = Out[Bone].RotKeys;
				if (Keys.Num() > 0 && (Keys.Last() | Rotation) < 0.f)
				{
					Rotation = FQuat(-Rotation.X, -Rotation.Y, -Rotation.Z, -Rotation.W);   // (the same rotation, on the side of the last key: no spin between keys)
				}
				Out[Bone].PosKeys.Add(Position);
				Keys.Add(Rotation);
				Out[Bone].ScaleKeys.Add(Under[Bone].GetScale3D());
			}
		}
		for (int32 Bone = 0; Bone < To.GetNum(); ++Bone)
		{
			if (Out[Bone].RotKeys.Num() == 0)
			{
				continue;
			}
			if (Sequence->AddNewRawTrack(To.GetBoneName(Bone), &Out[Bone]) != INDEX_NONE)
			{
				Done[Bone] = true;
				if (SourceOf[Bone] != INDEX_NONE) { ++Result.Bones; }
				else { ++Result.BaseBones; }
			}
		}
	}
	else if (bLean)
	{
		// (1.12) Base's pose, the Lean Bone (with every bone under it) leaning the way the animation's root moves; the
		// root keeps Base's here (1.12.2: then the animation's motion, MoveRootAsSource).
		const TArray<int32> SourceTracks = TracksByBone(Source, bRaw, From);
		const int32 RootTrack = SourceTracks.Num() > 0 ? SourceTracks[0] : INDEX_NONE;
		int32 Leaning = INDEX_NONE;
		const FString LeanName = LeanBone.TrimStartAndEnd();
		if (!LeanName.IsEmpty())
		{
			Leaning = To.FindBoneIndex(FName(*LeanName));
		}
		else
		{
			// the bone under the root with the most bones under it (the hips)
			TArray<int32> Count;
			Count.Init(1, To.GetNum());
			for (int32 Bone = To.GetNum() - 1; Bone > 0; --Bone)
			{
				const int32 Parent = To.GetParentIndex(Bone);
				if (Parent >= 0 && Parent < Bone)
				{
					Count[Parent] += Count[Bone];
				}
			}
			for (int32 Bone = 1; Bone < To.GetNum(); ++Bone)
			{
				if (To.GetParentIndex(Bone) == 0 && (Leaning == INDEX_NONE || Count[Bone] > Count[Leaning]))
				{
					Leaning = Bone;
				}
			}
			if (Leaning == INDEX_NONE && To.GetNum() > 0)
			{
				Leaning = 0;
			}
		}
		if (RootTrack == INDEX_NONE || Leaning == INDEX_NONE)
		{
			Sequence->ClearFlags(RF_Public | RF_Standalone);
			Sequence->MarkPendingKill();
			Error = RootTrack == INDEX_NONE ? Source->GetName() + TEXT(" has no track for its root: there is no root motion to lean into")
											: FString::Printf(TEXT("its Lean Bone %s is not a bone of %s"), *LeanName, *Target->GetName());
			return nullptr;
		}
		const bool bAll = To.GetParentIndex(Leaning) == INDEX_NONE;   // the root: every bone leans, about the root
		Result.LeanBone = To.GetBoneName(Leaning);
		const float Most = FMath::Clamp(LeanDegrees, 0.f, 60.f);
		// The animation's root at a time of it, and how many of its seconds go by in a second of the move.
		const auto RootAt = [&](float SourceAt)
		{
			FTransform Atom = FromPose.IsValidIndex(0) ? FromPose[0] : FTransform::Identity;
			Source->GetBoneTransform(Atom, RootTrack, SourceAt, bRaw);
			return Atom;
		};
		const float SourcePerMove = bLooped ? (To0 - From0) / FMath::Max(LoopLength, KINDA_SMALL_NUMBER) : Rate;
		const float Half = 1.f / 30.f;
		TArray<FRawAnimSequenceTrack> Out;
		Out.SetNum(To.GetNum());
		TArray<FTransform> UnderPose;
		TArray<FQuat> UnderLocal;
		UnderPose.SetNum(To.GetNum());
		UnderLocal.SetNum(To.GetNum());
		for (int32 Frame = 0; Frame < Frames; ++Frame)
		{
			const float Time = FMath::Min(Frame * Step, Length);
			const float At = SourceTime(Time);
			const float BaseAt = BaseTime(Time);
			// The animation's root motion around At: how fast it goes in its root's own axes (cm a second of the move) and
			// how fast it turns (degrees a second, left +).
			FVector Velocity = FVector::ZeroVector;
			float Yaw = 0.f;
			const float A = FMath::Max(From0, At - Half);
			const float B = FMath::Min(To0, At + Half);
			if (B - A > KINDA_SMALL_NUMBER)
			{
				const FTransform RootA = RootAt(A);
				const FTransform RootB = RootAt(B);
				const FTransform RootNow = RootAt(At);
				Velocity = RootNow.GetRotation().Inverse().RotateVector(RootB.GetTranslation() - RootA.GetTranslation()) * (SourcePerMove / (B - A));
				FQuat Turn = (RootA.GetRotation().Inverse() * RootB.GetRotation()).GetNormalized();
				if (Turn.W < 0.f)
				{
					Turn = FQuat(-Turn.X, -Turn.Y, -Turn.Z, -Turn.W);
				}
				FVector Axis = FVector::ZeroVector;
				float Angle = 0.f;
				Turn.ToAxisAndAngle(Axis, Angle);
				Yaw = FMath::RadiansToDegrees(Angle) * Axis.Y * (SourcePerMove / (B - A));
			}
			// The game's root motion: its root's Z is forward and X left, and it turns about its Y (left +). A body stands
			// along the root's Z and faces its X, its left at -Y. It leans its top the way it goes (a run at 6 m/s: Most
			// degrees; a walk at 1 m/s about a third) and turns its front ahead into a turn (a fifth of a second ahead).
			const float Forward = Velocity.Z;
			const float Left = Velocity.X;
			const float Speed = FMath::Sqrt(Forward * Forward + Left * Left);
			FQuat Tilt = FQuat::Identity;
			float Degrees = 0.f;
			if (Speed > 1.f)
			{
				Degrees = Most * EaseOff(Speed / 300.f) / EaseOff(2.f);
				Tilt = FQuat(FVector(Left / Speed, Forward / Speed, 0.f), FMath::DegreesToRadians(Degrees));
			}
			const float Twist = FMath::Clamp(Yaw * 0.2f, -1.4f * Most, 1.4f * Most);
			Result.MostLean = FMath::Max(Result.MostLean, Degrees);
			Result.MostTwist = FMath::Max(Result.MostTwist, FMath::Abs(Twist));
			const FQuat LeanSeen = (Tilt * FQuat(FVector(0.f, 0.f, 1.f), FMath::DegreesToRadians(-Twist))).GetNormalized();   // as the game shows the body
			// Base's pose, in component space too
			for (int32 Bone = 0; Bone < To.GetNum(); ++Bone)
			{
				UnderPose[Bone] = BaseLocal(Bone, BaseAt);
				UnderLocal[Bone] = UnderPose[Bone].GetRotation().GetNormalized();
			}
			const TArray<FQuat> UnderComponent = ComponentRotations(To, UnderLocal);
			const FQuat RootRotation = UnderComponent.Num() > 0 ? UnderComponent[0] : FQuat::Identity;
			// The game shows the body under the root's reference pose (it holds the root there): the lean, in the root's
			// axes, is the one seen through it. (1.12.1) A model the form turns (StandModel) is seen through the animation's
			// root, turned.
			const FQuat Seen = bStand ? (StandTurn * RootRotation).GetNormalized() : RefRootRotation;
			const FQuat LeanLocal = (Seen.Inverse() * LeanSeen * Seen).GetNormalized();
			const FQuat LeanComponent = (RootRotation * LeanLocal * RootRotation.Inverse()).GetNormalized();
			for (int32 Bone = 0; Bone < To.GetNum(); ++Bone)
			{
				const int32 Parent = To.GetParentIndex(Bone);
				const bool bLeans = bAll ? Parent == Leaning : Bone == Leaning;
				if (!bLeans && BaseTracks[Bone] == INDEX_NONE)
				{
					continue;   // (no track: its rest pose, as Base has it)
				}
				FTransform Atom = UnderPose[Bone];
				FQuat Rotation = UnderLocal[Bone];
				if (bLeans && bAll)
				{
					Rotation = (LeanLocal * Rotation).GetNormalized();   // (under the root: turned about it, with its place)
					Atom.SetTranslation(LeanLocal.RotateVector(Atom.GetTranslation()));
				}
				else if (bLeans)
				{
					const FQuat ParentRotation = Parent >= 0 ? UnderComponent[Parent] : FQuat::Identity;
					Rotation = (ParentRotation.Inverse() * LeanComponent * UnderComponent[Bone]).GetNormalized();
				}
				TArray<FQuat>& Keys = Out[Bone].RotKeys;
				if (Keys.Num() > 0 && (Keys.Last() | Rotation) < 0.f)
				{
					Rotation = FQuat(-Rotation.X, -Rotation.Y, -Rotation.Z, -Rotation.W);   // (the same rotation, on the side of the last key: no spin between keys)
				}
				Out[Bone].PosKeys.Add(Atom.GetTranslation());
				Keys.Add(Rotation);
				Out[Bone].ScaleKeys.Add(Atom.GetScale3D());
			}
		}
		for (int32 Bone = 0; Bone < To.GetNum(); ++Bone)
		{
			if (Out[Bone].RotKeys.Num() == 0)
			{
				continue;
			}
			if (Sequence->AddNewRawTrack(To.GetBoneName(Bone), &Out[Bone]) != INDEX_NONE)
			{
				Done[Bone] = true;
				const int32 Parent = To.GetParentIndex(Bone);
				if (bAll ? Parent == Leaning : Bone == Leaning) { ++Result.Bones; }
				else { ++Result.BaseBones; }
			}
		}
	}
	else
	{
		for (const FBakeTrack& Bake : Tracks)
		{
			FRawAnimSequenceTrack Raw;
			Raw.PosKeys.Reserve(Frames);
			Raw.RotKeys.Reserve(Frames);
			Raw.ScaleKeys.Reserve(Frames);
			const FVector FromRest = FromPose.IsValidIndex(Bake.FromBone) ? FromPose[Bake.FromBone].GetTranslation() : FVector::ZeroVector;
			const FVector ToRest = ToPose.IsValidIndex(Bake.ToBone) ? ToPose[Bake.ToBone].GetTranslation() : FromRest;
			const SkelCompat::RetargetMode BoneMode = static_cast<size_t>(Bake.ToBone) < Modes.size() ? Modes[static_cast<size_t>(Bake.ToBone)] : SkelCompat::RetargetMode::Keep;
			const float FromLength = FromRest.Size();
			const float Scale = FromLength > KINDA_SMALL_NUMBER ? ToRest.Size() / FromLength : 1.f;
			for (int32 Frame = 0; Frame < Frames; ++Frame)
			{
				FTransform Atom;
				Source->GetBoneTransform(Atom, Bake.Track, SourceTime(FMath::Min(Frame * Step, Length)), bRaw);
				FVector Position = Atom.GetTranslation();
				if (bKeepBuild)
				{
					if (BoneMode == SkelCompat::RetargetMode::Skeleton)
					{
						Position = ToRest;
					}
					else if (BoneMode == SkelCompat::RetargetMode::AnimationScaled)
					{
						Position *= Scale;
					}
					else
					{
						Position = ToRest + (Position - FromRest);
					}
				}
				Raw.PosKeys.Add(Position);
				Raw.RotKeys.Add(Atom.GetRotation().GetNormalized());
				Raw.ScaleKeys.Add(Atom.GetScale3D());
			}
			if (Sequence->AddNewRawTrack(Bake.Bone, &Raw) != INDEX_NONE)
			{
				Done[Bake.ToBone] = true;
				++Result.Bones;
			}
		}
		// (1.12) the bones only Base moves
		if (Base)
		{
			for (int32 Bone = 0; Bone < To.GetNum(); ++Bone)
			{
				if (Done[Bone] || BaseTracks[Bone] == INDEX_NONE)
				{
					continue;
				}
				FRawAnimSequenceTrack Raw;
				for (int32 Frame = 0; Frame < Frames; ++Frame)
				{
					const FTransform Under = BaseLocal(Bone, BaseTime(FMath::Min(Frame * Step, Length)));
					Raw.PosKeys.Add(Under.GetTranslation());
					Raw.RotKeys.Add(Under.GetRotation().GetNormalized());
					Raw.ScaleKeys.Add(Under.GetScale3D());
				}
				if (Sequence->AddNewRawTrack(To.GetBoneName(Bone), &Raw) != INDEX_NONE)
				{
					Done[Bone] = true;
					++Result.BaseBones;
				}
			}
		}
	}
	if (bStand)
	{
		StandModel(Sequence, To, ModelTurn, ModelLift, Frames);
	}
	// (1.12.2) over Base: the character moves as the animation does (after StandModel, which places the body by Base's root);
	// (1.12.3) Keep Base Root: it stays where Base puts it
	if ((bLean || (bMotion && Base)) && !bKeepBaseRoot)
	{
		const TArray<int32> SourceRootTracks = TracksByBone(Source, bRaw, From);
		const int32 SourceRoot = SourceRootTracks.Num() > 0 ? SourceRootTracks[0] : INDEX_NONE;
		if (SourceRoot != INDEX_NONE)
		{
			const float Scale = MotionScale > KINDA_SMALL_NUMBER ? MotionScale : 1.f;
			MoveRootAsSource(Sequence, To, Source, SourceRoot, bRaw, SourceTime, Frames, Step, Length, bLooped, LoopLength, From0, To0, Scale);
			Result.RootMotionScale = Scale;
		}
	}
	// Curves by name, where the character's skeleton has the name (none is added to it: the skeleton is the game's).
	const auto CurveOf = [&](const FName& CurveName, int32 Flags) -> FFloatCurve*
	{
		FSmartName Smart;
		if (!Target->GetSmartNameByName(USkeleton::AnimCurveMappingName, CurveName, Smart))
		{
			++Result.CurvesDropped;
			return nullptr;
		}
		Sequence->RawCurveData.AddCurveData(Smart, Flags);
		return static_cast<FFloatCurve*>(Sequence->RawCurveData.GetCurveData(Smart.UID, ERawCurveTrackTypes::RCT_Float));
	};
	// (1.12.3) a Bone Map: Source's curves are its own character's (its face, its glow): left out, Base's play
	if (bBoneMap)
	{
		Result.CurvesDropped += bRaw ? Source->RawCurveData.FloatCurves.Num() : Source->CompressedData.CompressedCurveNames.Num();
	}
	else if (bRaw)
	{
		for (const FFloatCurve& Curve : Source->RawCurveData.FloatCurves)
		{
			if (FFloatCurve* New = CurveOf(Curve.Name.DisplayName, Curve.GetCurveTypeFlags()))
			{
				if (bWhole)
				{
					New->FloatCurve = Curve.FloatCurve;
				}
				else
				{
					for (int32 Frame = 0; Frame < Frames; ++Frame)
					{
						const float Time = FMath::Min(Frame * Step, Length);
						New->UpdateOrAddKey(Curve.FloatCurve.Eval(SourceTime(Time)), Time);
					}
				}
				++Result.Curves;
			}
		}
	}
	else if (const UAnimCurveCompressionCodec* CurveCodec = Source->CompressedData.CurveCompressionCodec)
	{
		for (const FSmartName& CurveName : Source->CompressedData.CompressedCurveNames)
		{
			if (FFloatCurve* New = CurveOf(CurveName.DisplayName, AACF_DefaultCurve))
			{
				for (int32 Frame = 0; Frame < Frames; ++Frame)
				{
					const float Time = FMath::Min(Frame * Step, Length);
					New->UpdateOrAddKey(CurveCodec->DecompressCurve(Source->CompressedData, CurveName.UID, SourceTime(Time)), Time);
				}
				++Result.Curves;
			}
		}
	}
	// (1.12) Base's curves the animation has not (its face, its glow), as Base plays under the move.
	if (Base)
	{
		TSet<FName> Have;
		for (const FFloatCurve& Curve : Sequence->RawCurveData.FloatCurves)
		{
			Have.Add(Curve.Name.DisplayName);
		}
		if (bBaseRaw)
		{
			for (const FFloatCurve& Curve : Base->RawCurveData.FloatCurves)
			{
				if (Have.Contains(Curve.Name.DisplayName))
				{
					continue;
				}
				if (FFloatCurve* New = CurveOf(Curve.Name.DisplayName, Curve.GetCurveTypeFlags()))
				{
					for (int32 Frame = 0; Frame < Frames; ++Frame)
					{
						const float Time = FMath::Min(Frame * Step, Length);
						New->UpdateOrAddKey(Curve.FloatCurve.Eval(BaseTime(Time)), Time);
					}
					++Result.Curves;
				}
			}
		}
		else if (const UAnimCurveCompressionCodec* BaseCurveCodec = Base->CompressedData.CurveCompressionCodec)
		{
			for (const FSmartName& CurveName : Base->CompressedData.CompressedCurveNames)
			{
				if (Have.Contains(CurveName.DisplayName))
				{
					continue;
				}
				if (FFloatCurve* New = CurveOf(CurveName.DisplayName, AACF_DefaultCurve))
				{
					for (int32 Frame = 0; Frame < Frames; ++Frame)
					{
						const float Time = FMath::Min(Frame * Step, Length);
						New->UpdateOrAddKey(BaseCurveCodec->DecompressCurve(Base->CompressedData, CurveName.UID, BaseTime(Time)), Time);
					}
					++Result.Curves;
				}
			}
		}
	}
	// The animation's own sounds and effects (swings, trails), on a track of their own; its gameplay notifies (damage,
	// windows) come from the character's move. (1.12) In a loop to Base's length, in each time the clip plays.
	if (bKeepSourceEffects)
	{
		int32 Track = INDEX_NONE;
		const float ClipSpan = To0 - From0;
		for (const FAnimNotifyEvent& Original : Source->Notifies)
		{
			UObject* Object = Original.Notify ? static_cast<UObject*>(Original.Notify) : static_cast<UObject*>(Original.NotifyStateClass);
			if (!Object || !IsMotionNotify(Object) || (bSourceSoundsOnly && !IsSoundNotify(Object)))
			{
				continue;
			}
			// in the move's time: those outside the clip are left out, a window across its edges is cut there
			const float Begin = Original.GetTime(), End = Original.GetTime() + (Original.NotifyStateClass ? Original.GetDuration() : 0.f);
			if (End < From0 - 0.0001f || Begin > To0 + 0.0001f)
			{
				continue;
			}
			const float TimeScale = bLooped ? LoopLength / FMath::Max(ClipSpan, KINDA_SMALL_NUMBER) : 1.f / Rate;
			const float At = (FMath::Max(Begin, From0) - From0) * TimeScale;
			const float Lasts = Original.NotifyStateClass ? (FMath::Min(End, To0) - FMath::Max(Begin, From0)) * TimeScale : 0.f;
			if (Track == INDEX_NONE)
			{
				Track = 0;
			#if WITH_EDITORONLY_DATA
				Track = Sequence->AnimNotifyTracks.Num();
				Sequence->AnimNotifyTracks.Add(FAnimNotifyTrack(FName(TEXT("Source")), FLinearColor::White));
			#endif
			}
			for (int32 Loop = 0; Loop < Loops; ++Loop)
			{
				FAnimNotifyEvent Event = Original;
				// (1.12.4) without the effect parameters of the game's this editor cannot write (CopyNotifyObject)
				if (Original.Notify)
				{
					Event.Notify = CopyNotifyObject<UAnimNotify>(Original.Notify, Sequence, Result.EffectParameters, Result.NotifiesLeftOut);
					if (!Event.Notify)
					{
						continue;
					}
				}
				if (Original.NotifyStateClass)
				{
					Event.NotifyStateClass = CopyNotifyObject<UAnimNotifyState>(Original.NotifyStateClass, Sequence, Result.EffectParameters, Result.NotifiesLeftOut);
					if (!Event.NotifyStateClass)
					{
						continue;
					}
				}
				PlaceNotify(Sequence, Event, FMath::Clamp(At + Loop * LoopLength, 0.f, Length), FMath::Max(Lasts, 0.f), Track);
				Sequence->Notifies.Add(Event);
				++Result.SourceEffects;
			}
		}
	}
	Sequence->MarkRawDataAsModified();
	Sequence->OnRawDataChanged();
	Sequence->RefreshCacheData();
	FAssetRegistryModule::AssetCreated(Sequence);
	Sequence->MarkPackageDirty();
	return Sequence;
}

// (1.12) How Retarget puts an animation of another skeleton on the character's, for the reports.
const TCHAR* RetargetText(EEndMoveRetarget Mode)
{
	switch (Mode)
	{
	case EEndMoveRetarget::AsIs: return TEXT("the animation's bone lengths");
	case EEndMoveRetarget::Motion: return TEXT("the character's own pose kept, the animation's motion added");
	case EEndMoveRetarget::Lean: return TEXT("its Base leaning into the animation's root motion");
	default: return TEXT("the character's build kept");
	}
}

// A Primary Asset Label in Folder that puts its animations (and everything under it) in Chunk when the project is packaged.
// Only those: what they use (the skeleton, the compression settings) stays out of the chunk, since the game or another pak
// has it and a copy in the mod's pak would replace it.
void LabelForChunk(const FString& Folder, int32 Chunk, const TArray<UObject*>& Assets, TArray<UPackage*>& Dirty, FString& Report)
{
	const FString Name = FString::Printf(TEXT("PAL_SkelCompat_Chunk%d"), Chunk);
	const FString Package = Folder + TEXT("/") + Name;
	UPrimaryAssetLabel* Label = LoadObject<UPrimaryAssetLabel>(nullptr, *(Package + TEXT(".") + Name), nullptr, LOAD_NoWarn | LOAD_Quiet);
	const bool bNew = Label == nullptr;
	if (bNew)
	{
		UPackage* Outer = CreatePackage(*Package);
		Label = NewObject<UPrimaryAssetLabel>(Outer, *Name, RF_Public | RF_Standalone | RF_Transactional);
		FAssetRegistryModule::AssetCreated(Label);
	}
	Label->Modify();
	Label->Rules.ChunkId = Chunk;
	Label->Rules.Priority = FMath::Max(Label->Rules.Priority, 1);
	Label->Rules.CookRule = EPrimaryAssetCookRule::AlwaysCook;
	Label->Rules.bApplyRecursively = false;
	Label->bLabelAssetsInMyDirectory = true;
	for (UObject* Asset : Assets)
	{
		Label->ExplicitAssets.AddUnique(TSoftObjectPtr<UObject>(FSoftObjectPath(Asset)));
	}
	Label->MarkPackageDirty();
	Dirty.AddUnique(Label->GetOutermost());
	Report += FString::Printf(TEXT("%s %s: chunk %d for the animations in %s (not the skeleton and settings they use)\n"), bNew ? TEXT("Made") : TEXT("Updated"), *Package, Chunk, *Folder);
}

// ------------------------------------------------------------------------------------------------
// 3.6: a row's forms. Only the asset registry is asked about the assets they use (nothing is loaded: they are often the
// game's own cooked assets).
// ------------------------------------------------------------------------------------------------
// The registry's class of the asset at `Path` ("SkeletalMesh"), "?" for an asset of the package under another name, or
// empty when the package is not in this project.
FString RegisteredClassOf(const FString& Path, FAssetData* OutAsset = nullptr)
{
	const FString Object = NormalizedObjectPath(Path);
	const FAssetData Asset = AssetRegistry().GetAssetByObjectPath(FName(*Object));
	if (Asset.IsValid())
	{
		if (OutAsset) { *OutAsset = Asset; }
		return Asset.AssetClass.ToString();
	}
	TArray<FAssetData> Assets;
	AssetRegistry().GetAssetsByPackageName(FName(*FPackageName::ObjectPathToPackageName(Object)), Assets, true);
	if (Assets.Num() > 0)
	{
		if (OutAsset) { *OutAsset = Assets[0]; }
		return TEXT("?");
	}
	return FString();
}

// A registry tag naming an object ("Skeleton'/Game/A/B.B'" or "/Game/A/B.B") as its object path, or empty.
FString TagPath(const FAssetData& Asset, const TCHAR* Tag)
{
	FString Value;
	if (!Asset.IsValid() || !Asset.GetTagValue(FName(Tag), Value) || Value.IsEmpty() || Value.Equals(TEXT("None"), ESearchCase::IgnoreCase))
	{
		return FString();
	}
	return NormalizedObjectPath(Value);
}

bool CheckForms(const FEndAnimSetRow& Row, const SkelCompat::AnimSetRow& Core, const TArray<FString>& Asked, bool bTable, FString& Report)
{
	bool bOk = true;
	const FEndCharacterForms& Forms = Row.Forms;
	const SkelCompat::FormSettings& Read = Core.Forms;
	if (!Read.HasList())
	{
		Report += FString::Printf(TEXT("    WARNING: Forms: %d form(s) the game mod takes; the forms menu needs two or more (the normal one first), so it ignores them\n"),
			static_cast<int32>(Read.List.size()));
		return true;
	}
	const int32 Count = static_cast<int32>(Read.List.size());
	if (Forms.List.Num() > static_cast<int32>(SkelCompat::MaxForms))
	{
		Report += FString::Printf(TEXT("    WARNING: Forms has %d forms: the menu takes %d (the normal one included), the others are left out\n"), Forms.List.Num(),
			static_cast<int32>(SkelCompat::MaxForms));
	}
	Report += FString::Printf(TEXT("    forms: %d; hold %s%s for %.2f s to open the menu \"%s\" (%d at a time%s), pick one with up / down, let go to switch (needs Create a Character System 3.6)\n"),
		Count, *FromWide(Read.Button), Read.Key.empty() ? TEXT("") : *(TEXT(" or key ") + FromWide(Read.Key)), Read.HoldSeconds, *FromWide(Read.Title),
		FMath::Min(Count, 7), Count > 7 ? TEXT(", the list scrolls") : TEXT(""));
	if (std::any_of(Read.List.begin(), Read.List.end(), [](const SkelCompat::Form& F) { return F.Limited(); }))
	{
		Report += Read.Timer ? FString::Printf(TEXT("      a timed form's time left shows at %.2f, %.2f of the screen in battle\n"), Read.TimerX, Read.TimerY)
							 : FString(TEXT("      a timed form's time left is not on screen (Show Timer off; the menu still shows it)\n"));
	}
	if (!Read.Parts.empty())
	{
		TArray<FString> Parts;
		for (const std::wstring& Part : Read.Parts) { Parts.Add(FromWide(Part)); }
		Report += TEXT("      parts the forms show or hide (material slots of the character's model): ") + ListText(Parts) +
				  (Read.FadeSeconds > 0.f ? FString::Printf(TEXT(", fading in %.2f s (%s)"), Read.FadeSeconds, *FromWide(Read.FadeParameter)) : FString()) + TEXT("\n");
	}
	const auto CheckAsset = [&](const FString& What, const FString& Path, std::initializer_list<const TCHAR*> Classes, FAssetData* OutAsset = nullptr) {
		if (Path.IsEmpty())
		{
			return;
		}
		const FString Class = RegisteredClassOf(Path, OutAsset);
		if (Class.IsEmpty())
		{
			Report += FString::Printf(TEXT("        note: %s %s is not in this project (the game must have it)\n"), *What, *NormalizedObjectPath(Path));
			return;
		}
		if (Class == TEXT("?"))
		{
			return; // its package is here under another asset name (a cooked package): checked in game
		}
		for (const TCHAR* Wanted : Classes)
		{
			if (Class.Equals(Wanted, ESearchCase::IgnoreCase))
			{
				return;
			}
		}
		FString Expected;
		for (const TCHAR* Wanted : Classes) { Expected += (Expected.IsEmpty() ? TEXT("") : TEXT(" or ")) + FString(Wanted); }
		Report += FString::Printf(TEXT("        ERROR: %s %s is a %s, not a %s\n"), *What, *NormalizedObjectPath(Path), *Class, *Expected);
		bOk = false;
	};
	const auto CheckEffects = [&](const TCHAR* What, const std::vector<SkelCompat::FormEffect>& Effects) {
		for (const SkelCompat::FormEffect& Effect : Effects)
		{
			CheckAsset(What, FromWide(Effect.Path), {TEXT("NiagaraSystem"), TEXT("ParticleSystem")});
		}
	};
	CheckEffects(TEXT("show effect"), Read.ShowEffects);
	CheckEffects(TEXT("hide effect"), Read.HideEffects);
	const FString OwnSkeleton = Row.CharacterSkeleton.IsNull() ? FString() : SoftPath(Row.CharacterSkeleton);
	TArray<FString> Names;
	for (int32 Index = 0; Index < Count; ++Index)
	{
		const SkelCompat::Form& Form = Read.List[static_cast<size_t>(Index)];
		const FString Name = FromWide(Form.Name);
		const FString Pack = FromWide(Form.Pack);
		const bool bOwn = Pack.IsEmpty() || Pack.Equals(TEXT("Battle00"), ESearchCase::IgnoreCase);
		if (Names.Contains(Name))
		{
			Report += FString::Printf(TEXT("      note: two forms are called %s\n"), *Name);
		}
		Names.Add(Name);
		TArray<FString> Parts;
		for (const std::wstring& Part : Form.Show) { Parts.Add(FromWide(Part)); }
		FString Line = FString::Printf(TEXT("      %d. %s: pack %s"), Index + 1, *Name, bOwn ? TEXT("Battle00 (its own)") : *Pack);
		if (!Read.Parts.empty())
		{
			Line += Parts.Num() > 0 ? TEXT("; shows ") + ListText(Parts) : FString(TEXT("; the parts hidden"));
		}
		if (!Form.Model.empty())
		{
			Line += TEXT("; wears ") + ShortName(Form.Model) + (Form.AnimClass.empty() ? FString() : TEXT(" with ") + ShortName(Form.AnimClass));
		}
		if (Form.Scale > 0.f)
		{
			Line += FString::Printf(TEXT(", size %.2f"), Form.Scale);
		}
		if (!Form.Meshes.empty())
		{
			Line += FString::Printf(TEXT(", %d part(s) added"), static_cast<int32>(Form.Meshes.size()));
		}
		if (Form.HideWeapon)
		{
			Line += TEXT("; weapons hidden");
		}
		if (!Form.Effects.empty() || !Form.Sounds.empty())
		{
			Line += FString::Printf(TEXT("; %d effect(s) and %d sound(s) as it switches"), static_cast<int32>(Form.Effects.size()), static_cast<int32>(Form.Sounds.size()));
		}
		if (!Form.Keep.empty())
		{
			Line += FString::Printf(TEXT("; %d effect(s) while in it"), static_cast<int32>(Form.Keep.size()));
		}
		if (Form.Fly.On)
		{
			Line += FString::Printf(TEXT("; flies %.0f cm up (%s / %s, up to %.0f cm)"), Form.Fly.Height, *FromWide(Form.Fly.Up), *FromWide(Form.Fly.Down), Form.Fly.Max);
		}
		if (!Form.After.empty())
		{
			Line += TEXT("; switched to when ") + FromWide(Form.After) + TEXT(" ends");
		}
		if (Form.SuperArmor)
		{
			Line += TEXT("; super armor");
		}
		if (Form.Limited())
		{
			Line += FString::Printf(TEXT("; lasts %.0f s, then turns back into %s"), Form.Seconds, *FromWide(Read.List[static_cast<size_t>(Form.RevertIndex)].Name));
		}
		if (Form.Cooldown > 0.f)
		{
			Line += FString::Printf(TEXT("; can be chosen again %.0f s after it ends"), Form.Cooldown);
		}
		Report += Line + TEXT("\n");
		if (!bOwn)
		{
			// its sets: the row's sources and moves of that name, else the character's Battle00 and Battle00_Comp
			const bool bSources = !SkelCompat::SetSourcesFor(Core, Form.Pack).empty();
			const bool bMoves = std::any_of(Core.Moves.begin(), Core.Moves.end(), [&](const SkelCompat::AnimMove& Move) { return SkelCompat::NameEquals(Move.Set, Form.Pack); });
			if (!bSources)
			{
				Report += FString::Printf(TEXT("        its sets: no Battle source is %s, so %s starts from the character's Battle00 and Battle00_Comp%s\n"), *Pack, *Pack,
					bMoves ? TEXT(" with its moves on top") : TEXT(" (the form keeps its moves)"));
			}
			if (bTable && !Asked.ContainsByPredicate([&](const FString& Set) { return Set.Equals(Pack, ESearchCase::IgnoreCase); }))
			{
				Report += FString::Printf(TEXT("        note: the characters' CharaSpec rows do not name %s in their AnimationSetList; the game mod (3.5 or later) gives the set from the pack\n"), *Pack);
			}
			const FEndPackAbilities* Abilities = Row.Abilities.FindByPredicate([&](const FEndPackAbilities& P) { return P.Pack.TrimStartAndEnd().Equals(Pack, ESearchCase::IgnoreCase); });
			if (!Abilities)
			{
				Report += FString::Printf(TEXT("        commands and limits: no Abilities entry for %s (the character's Battle00 ones, else the table's)\n"), *Pack);
			}
		}
		else if (Index > 0)
		{
			Report += TEXT("        note: it plays the character's own pack, like the normal form\n");
		}
		// what it wears
		FAssetData ModelAsset;
		CheckAsset(TEXT("model"), FromWide(Form.Model), {TEXT("SkeletalMesh")}, &ModelAsset);
		FString AnimBlueprint = FromWide(Form.AnimClass);
		AnimBlueprint.RemoveFromEnd(TEXT("_C"));
		FAssetData AnimAsset;
		CheckAsset(TEXT("AnimBlueprint"), AnimBlueprint, {TEXT("AnimBlueprint"), TEXT("AnimBlueprintGeneratedClass")}, &AnimAsset);
		const FString ModelSkeleton = TagPath(ModelAsset, TEXT("Skeleton"));
		if (!ModelSkeleton.IsEmpty() && !OwnSkeleton.IsEmpty() && !SamePath(ModelSkeleton, OwnSkeleton))
		{
			if (Form.AnimClass.empty())
			{
				Report += FString::Printf(TEXT("        WARNING: %s is on %s, not the character's skeleton %s: set AnimBlueprint to one made for its skeleton (its own)\n"),
					*ShortName(Form.Model), *ShortName(ModelSkeleton), *ShortName(OwnSkeleton));
			}
			const FString Target = TagPath(AnimAsset, TEXT("TargetSkeleton"));
			if (!Target.IsEmpty() && !SamePath(Target, ModelSkeleton))
			{
				Report += FString::Printf(TEXT("        WARNING: AnimBlueprint %s is made for %s, but the model is on %s\n"), *ShortName(AnimBlueprint), *ShortName(Target), *ShortName(ModelSkeleton));
			}
			if (!bOwn)
			{
				Report += FString::Printf(TEXT("        its pack's animations must be made for %s (Build Moves builds the moves of %s on it)\n"), *ShortName(ModelSkeleton), *Pack);
			}
		}
		for (const SkelCompat::FormMesh& Mesh : Form.Meshes)
		{
			FAssetData PartAsset;
			CheckAsset(TEXT("part"), FromWide(Mesh.Mesh), {TEXT("SkeletalMesh")}, &PartAsset);
			const FString PartSkeleton = TagPath(PartAsset, TEXT("Skeleton"));
			const FString Body = !ModelSkeleton.IsEmpty() ? ModelSkeleton : (Form.Model.empty() ? OwnSkeleton : FString());
			if (Mesh.FollowPose && !PartSkeleton.IsEmpty() && !Body.IsEmpty() && !SamePath(PartSkeleton, Body))
			{
				Report += FString::Printf(TEXT("        note: part %s is on %s, not %s: following the body's pose needs the same bones (turn Follow Pose off if it has its own)\n"),
					*ShortName(Mesh.Mesh), *ShortName(PartSkeleton), *ShortName(Body));
			}
		}
		CheckEffects(TEXT("effect"), Form.Effects);
		CheckEffects(TEXT("kept effect"), Form.Keep);
		for (const SkelCompat::FormAbilityEffects& Entry : Form.AbilityEffects)
		{
			TArray<FString> Abilities;
			for (const std::wstring& Ability : Entry.Abilities) { Abilities.Add(FromWide(Ability)); }
			TArray<FString> Effects;
			for (const SkelCompat::FormEffect& Effect : Entry.Effects)
			{
				Effects.Add(ShortName(Effect.Path) + (Effect.Socket.empty() ? FString() : TEXT(" at ") + FromWide(Effect.Socket)));
			}
			Report += TEXT("        while ") + FString::Join(Abilities, TEXT(" / ")) + TEXT(" runs: ") + ListText(Effects) + TEXT("\n");
			CheckEffects(TEXT("ability effect"), Entry.Effects);
		}

		for (const SkelCompat::FormSound& Sound : Form.Sounds)
		{
			FString Bank = FromWide(Sound.Bank);
			Bank.ReplaceInline(TEXT("{language}"), TEXT("US"));
			if (RegisteredClassOf(Bank).IsEmpty())
			{
				Report += FString::Printf(TEXT("        note: sound bank %s (cue %s) is not in this project (the game must have it)\n"), *FromWide(Sound.Bank), *FromWide(Sound.Cue));
			}
		}
		if (!Form.After.empty() && !SkelCompat::IsRowName(Form.After))
		{
			Report += FString::Printf(TEXT("        WARNING: After %s is not a BattleAbility row name\n"), *FromWide(Form.After));
		}
	}
	// What the editor has that the game mod leaves out (bad entries), told by the core's notes above.
	if (Forms.List.Num() != Count && Forms.List.Num() <= static_cast<int32>(SkelCompat::MaxForms))
	{
		Report += FString::Printf(TEXT("    WARNING: %d of the %d forms are left out by the game mod (see the notes above)\n"), Forms.List.Num() - Count, Forms.List.Num());
	}
	return bOk;
}

// ------------------------------------------------------------------------------------------------
// One animation set row of this data object
// ------------------------------------------------------------------------------------------------
bool CheckAnimSetRow(const FEndAnimSetRow& Row, int32 Index, const FCharaSpecTable& Table, const FString& GameLog, FString& Report)
{
	Report += FString::Printf(TEXT("Animation set row %d: %s\n"), Index, *ListText(CleanList(Row.Characters, false)));
	if (!Row.bEnabled)
	{
		Report += TEXT("    disabled\n");
		return true;
	}
	bool bOk = true;
	SkelCompat::AnimSetRow Core;
	std::vector<std::wstring> Notes;
	std::vector<SkelCompat::Pair> Families;
	const bool bParsed = RowAsGameReadsIt(Row, Core, Notes, Families);
	for (const std::wstring& Note : Notes)
	{
		FString Text = FromWide(Note);
		Text.RemoveFromStart(TEXT("row: "));
		if (!Text.StartsWith(TEXT("family of"))) // the cutscene family is reported below
		{
			Report += TEXT("    note: ") + Text + TEXT("\n");
		}
	}
	if (!bParsed)
	{
		Report += TEXT("    ERROR: the mod would skip this row (it needs Characters, and Battle, Field, Moves, Field Actions, Sockets, Abilities, Forms or Keep Proportions)\n");
		return false;
	}

	// The characters' CharaSpec rows: the sets the game asks them for, and their field-action folder.
	TArray<FString> Asked;
	TArray<FName> TableRows;
	for (const FString& Character : CleanList(Row.Characters, false))
	{
		const FString Name = CharaSpecRowName(Character);
		if (Name.IsEmpty())
		{
			Report += FString::Printf(TEXT("    ERROR: %s is not a CharaSpec row name (like PC0000_00_Cloud_Standard)\n"), *Character);
			bOk = false;
			continue;
		}
		if (!Table.bAvailable)
		{
			continue;
		}
		if (!Table.Has(Name))
		{
			Report += FString::Printf(TEXT("    WARNING: %s is not a row of %s\n"), *Name, *Table.Package);
			continue;
		}
		TableRows.Add(FName(*Name));
		const TArray<FString> Sets = NamesInText(Table.Field(Name, TEXT("AnimationSetList_Array")));
		for (const FString& Set : Sets)
		{
			Asked.AddUnique(Set);
		}
		const FString Folder = Table.Field(Name, TEXT("AnimationSetParentFolder"));
		const FString Model = Table.Field(Name, TEXT("ContentsModel"));
		Report += FString::Printf(TEXT("    CharaSpec %s: model %s, sets %s, field-action folder %s\n"), *Name, *Model,
			*ListText(Sets), Folder.IsEmpty() ? TEXT("(none)") : *Folder);
		// The blueprint the pack spawns has to be the row's model's (each character has its own blueprint, named like its
		// model): one character's blueprint on another one's model keeps the game on its loading screen.
		const FPackContents Pack = ReadPack(Name);
		if (Pack.bInProject && Pack.Blueprints.Num() > 0 && !Model.IsEmpty() && !Model.Equals(TEXT("None"), ESearchCase::IgnoreCase) &&
			!Pack.Blueprints.Contains(Model))
		{
			Report += FString::Printf(TEXT("    ERROR: CharaSpec_%s in this project spawns %s, but the row's model is %s: a blueprint on another character's model keeps the game on its loading screen. Set the pack's Asset Class List > 0 > Asset User Data to %s_C (and its action sounds to that character's AS_ bank)\n"),
				*Name, *FString::Join(Pack.Blueprints, TEXT(", ")), *Model, *Model);
			bOk = false;
		}
		const FString Wanted = Row.FieldActions.TrimStartAndEnd();
		if (!Wanted.IsEmpty() && !Folder.Equals(Wanted, ESearchCase::IgnoreCase))
		{
			Report += FString::Printf(TEXT("    note: Field Actions is %s: press Apply To CharaSpec to write it into %s\n"), *Wanted, *Name);
		}
	}
	if (!Table.bAvailable)
	{
		Report += TEXT("    note: the Rebirth data object tools (Rebirth Cooked Asset Preview plugin) are not loaded, so the CharaSpec rows are not checked\n");
	}

	// Each set: where it comes from. In game the pack's own set of that name fills in after these.
	std::vector<std::wstring> Names = SkelCompat::RowSetNames(Core);
	for (const FString& Set : Asked)
	{
		if (std::none_of(Names.begin(), Names.end(), [&](const std::wstring& Name) { return SkelCompat::NameEquals(Name, Wide(Set)); }))
		{
			Names.push_back(Wide(Set));
		}
	}
	for (const std::wstring& Name : Names)
	{
		const bool bAsked = Asked.ContainsByPredicate([&](const FString& Set) { return Set.Equals(FromWide(Name), ESearchCase::IgnoreCase); });
		TArray<FString> Here;
		TArray<FString> Elsewhere;
		for (const SkelCompat::SetSourceRef& Ref : SkelCompat::SetSourcesFor(Core, Name))
		{
			FString Auto = Ref.Auto == SkelCompat::AutoMatchMode::Basic ? TEXT(" (auto: basic attacks")
						 : Ref.Auto == SkelCompat::AutoMatchMode::Attacks ? TEXT(" (auto: attacks")
						 : Ref.Auto == SkelCompat::AutoMatchMode::All ? TEXT(" (auto: whole set") : TEXT("");
			if (!Auto.IsEmpty())
			{
				TArray<FString> Words;
				for (const std::wstring& Word : Ref.Only) { Words.Add(FromWide(Word)); }
				Auto += Words.Num() > 0 ? TEXT(", only names with ") + FString::Join(Words, TEXT("/")) + TEXT(")") : FString(TEXT(")"));
			}
			bool bFound = false;
			for (size_t Path = 0; Path < Ref.Paths.size() && !bFound; ++Path)
			{
				if (InProject(FromWide(Ref.Paths[Path])))
				{
					Here.Add(ShortSource(FromWide(Ref.Paths[Path])) + Auto + (Path > 0 ? TEXT(" (its first set of the kind)") : TEXT("")));
					bFound = true;
				}
			}
			if (!bFound)
			{
				FString Text = ShortSource(FromWide(Ref.Paths.front())) + Auto;
				if (Ref.Paths.size() > 1) { Text += TEXT(", else ") + ShortSource(FromWide(Ref.Paths[1])); }
				Elsewhere.Add(Text);
			}
		}
		if (Here.Num() == 0 && !bAsked)
		{
			continue; // a usual set name nothing here has: the game may have it, the log will say
		}
		FString Line = Here.Num() > 0 ? ListText(Here) : FString(TEXT("no source in this project"));
		if (Elsewhere.Num() > 0)
		{
			Line += FString::Printf(TEXT("; also looked for in the game: %s"), *ListText(Elsewhere));
		}
		if (Here.Num() == 0 && Elsewhere.Num() == 0)
		{
			Line = TEXT("no source: the character keeps the pack's own set");
		}
		Report += FString::Printf(TEXT("    %s%s: %s\n"), *FromWide(Name), bAsked || !Table.bAvailable ? TEXT("") : TEXT(" (not one its CharaSpec lists)"), *Line);
	}
	for (const SkelCompat::AnimMove& Move : Core.Moves)
	{
		TArray<FString> Parts;
		bool bAllHere = true;
		for (const std::wstring& Path : SkelCompat::MoveAnimations(Move))
		{
			Parts.Add(FromWide(Path));
			bAllHere = bAllHere && InProject(FromWide(Path));
		}
		Report += FString::Printf(TEXT("    move %s%s -> %s%s%s\n"), Move.Set.empty() ? TEXT("") : *(FromWide(Move.Set) + TEXT("/")), *FromWide(Move.Key),
			*FString::Join(Parts, TEXT(" then ")), Parts.Num() > 1 ? TEXT(" (played one after another)") : TEXT(""),
			bAllHere ? TEXT("") : TEXT(" (not all in this project: the game must have them)"));
	}
	// Moves built in the editor (Build Moves).
	const bool bBuildsMoves = Row.Moves.ContainsByPredicate([](const FEndAnimSetMove& Move) { return Move.bBuild; });
	const FString NeverCook = bBuildsMoves ? NeverCookDirectoryOf(BuildFolderOf(Row)) : FString();
	if (!NeverCook.IsEmpty())
	{
		Report += FString::Printf(TEXT("    ERROR: Build Folder %s is in %s, which Project Settings > Packaging > Directories To Never Cook lists: ")
								  TEXT("the built animations would never be packaged. Set Build Folder outside it (for example /Game/RebirthSkelCompat/Built/<Character>).\n"),
			*BuildFolderOf(Row), *NeverCook);
		bOk = false;
	}
	for (const FEndAnimSetMove& Move : Row.Moves)
	{
		if (!Move.bBuild)
		{
			continue;
		}
		const FString Name = (Move.Set.TrimStartAndEnd().IsEmpty() ? FString() : Move.Set.TrimStartAndEnd() + TEXT("/")) + Move.Name.TrimStartAndEnd();
		const FString Built = BuiltObjectPathOf(Row, Move);
		const bool bSourceHere = !Move.Animation.TrimStartAndEnd().IsEmpty() && InProject(Move.Animation.TrimStartAndEnd());
		const UAnimSequence* Source = bSourceHere ? Cast<UAnimSequence>(FSoftObjectPath(NormalizedObjectPath(Move.Animation.TrimStartAndEnd())).TryLoad()) : nullptr;
		FString NotifyPath;
		const UAnimSequenceBase* From = FindNotifySource(Row, Move, NotifyPath);
		const int32 Hits = HitGroupTimes(PlayedNotifies(From)).Num();
		const bool bHitsNameDamage = Move.Hits.ContainsByPredicate([](const FEndMoveHit& Hit) { return !Hit.DamageSourceID.TrimStartAndEnd().IsEmpty(); });
		FString Notifies = From ? ShortSource(NotifyPath) + FString::Printf(TEXT(", %d hit(s)"), Hits)
								: (bHitsNameDamage ? FString(TEXT("nothing: new damage notifies from the hits' Damage Source IDs"))
												   : TEXT("nothing: ") + NotifyPath + TEXT(" is not in this project (set Notifies From, or a Damage Source ID on each hit)"));
		FString Made;
		if (Source)
		{
			FString FormModel;
			const USkeleton* FormSkeleton = FormModelSkeleton(Row, Move.Set, &FormModel);
			const USkeleton* BaseSkeleton = BaseSkeletonOf(Move);
			const USkeleton* Target = FormSkeleton ? FormSkeleton
								   : !FormModel.IsEmpty() ? (BaseSkeleton ? BaseSkeleton : Source->GetSkeleton()) // (the form's model is not here: its Base's or animation's skeleton)
								   : Row.CharacterSkeleton.IsNull() ? Source->GetSkeleton() : Row.CharacterSkeleton.LoadSynchronous();
			if (Target && Source->GetSkeleton() && Target != Source->GetSkeleton())
			{
				Made = FString::Printf(TEXT(", put on %s from %s (%s)"), *Target->GetName(), *Source->GetSkeleton()->GetName(), RetargetText(Move.Retarget));
			}
			else if (IsCookedAsset(Source) || Source->GetRawAnimationData().Num() == 0)
			{
				Made = TEXT(", sampled from the game animation");
			}
		}
		FString HitText;
		if (Move.Hits.Num() > 0)
		{
			TArray<FString> Times;
			int32 Effects = 0;
			for (const FEndMoveHit& Hit : Move.Hits)
			{
				Times.Add(FString::Printf(TEXT("%.2f"), Hit.Time));
				Effects += (Hit.Effect.TrimStartAndEnd().IsEmpty() ? 0 : 1) + (Hit.SoundBank.TrimStartAndEnd().IsEmpty() || Hit.Sound.IsNone() ? 0 : 1);
			}
			HitText = FString::Printf(TEXT("; hits at %s s"), *FString::Join(Times, TEXT(", ")));
			if (From && Hits > 0 && Move.Hits.Num() != Hits)
			{
				HitText += Move.Hits.Num() > Hits ? FString::Printf(TEXT(" (%d more than the original: its last hit repeats)"), Move.Hits.Num() - Hits)
												  : FString::Printf(TEXT(" (its last %d hit(s) left out)"), Hits - Move.Hits.Num());
			}
			if (Effects > 0)
			{
				HitText += FString::Printf(TEXT(", %d effect(s) and sound(s)"), Effects);
			}
		}
		Report += FString::Printf(TEXT("    build %s: %s from %s%s%s; gameplay notifies from %s%s%s\n"), *Name,
			InProject(Built) ? TEXT("built") : TEXT("NOT built yet (press Build Moves)"), *ShortSource(Move.Animation),
			bSourceHere ? (Source ? TEXT("") : TEXT(" (ERROR: not an Anim Sequence)")) : TEXT(" (ERROR: not in this project, so it cannot be built here)"), *Made, *Notifies, *HitText,
			Move.bShot ? (Row.ShotEffects.MuzzleEffect.IsEmpty() && Row.ShotEffects.SoundBank.IsEmpty() ? TEXT("; Shot on but the row has no Shot Effects") : TEXT("; shot effects at every hit"))
					   : TEXT(""));
		bOk &= Source != nullptr && (From != nullptr || bHitsNameDamage);
	}
	const bool bAuto = std::any_of(Core.Battle.begin(), Core.Battle.end(), [](const SkelCompat::SetSource& Source) { return Source.Auto != SkelCompat::AutoMatchMode::Off; }) ||
					   std::any_of(Core.Field.begin(), Core.Field.end(), [](const SkelCompat::SetSource& Source) { return Source.Auto != SkelCompat::AutoMatchMode::Off; });
	if (bAuto)
	{
		Report += TEXT("    auto sources: the game matches their attacks to the character's attack names when the pack loads (Moves and Limit Breaks win over them):\n");
		TArray<FString> PackPaths;
		for (const FString& Character : CleanList(Row.Characters, false))
		{
			const FString Pack = FromWide(SkelCompat::CharacterPackPath(Wide(Character)));
			if (!Pack.IsEmpty()) { PackPaths.AddUnique(Pack); }
		}
		for (const std::wstring& Name : SkelCompat::RowSetNames(Core)) { PreviewAutoMatch(Core, Name, PackPaths, GameLog, Report); }
	}
	for (const TArray<FEndAnimSetSource>* List : {&Row.Battle, &Row.Field})
	{
		for (const FEndAnimSetSource& Source : *List)
		{
			if (Source.AutoMatch == EEndAnimSetAutoMatch::Off && CleanList(Source.OnlyNamesWith, false).Num() > 0)
			{
				Report += FString::Printf(TEXT("    note: %s has Only Names With but Auto Match is off; the words only pick what an auto match uses\n"), *Source.Path.TrimStartAndEnd());
			}
		}
	}

	// Socket stand-ins on the character's meshes.
	if (Row.Sockets.Num() > 0)
	{
		USkeleton* Own = Row.CharacterSkeleton.IsNull() ? nullptr : Row.CharacterSkeleton.LoadSynchronous();
		if (Row.CharacterSkeleton.IsNull())
		{
			Report += TEXT("    WARNING: Sockets need Character Skeleton (the skeleton whose meshes get the stand-ins)\n");
		}
		for (const FEndSocketStandIn& Socket : Row.Sockets)
		{
			FString State = TEXT("checked in game");
			if (Own)
			{
				const FName Use(*Socket.Use.TrimStartAndEnd());
				if (USkeletalMeshSocket* Found = Own->FindSocket(Use))
				{
					State = TEXT("socket on bone ") + Found->BoneName.ToString();
				}
				else if (Own->GetReferenceSkeleton().FindBoneIndex(Use) != INDEX_NONE)
				{
					State = TEXT("a bone");
				}
				else
				{
					State = TEXT("WARNING: neither a socket nor a bone of ") + Own->GetName() + TEXT(" (a socket only the mesh has still works)");
				}
			}
			Report += FString::Printf(TEXT("    socket %s -> %s (%s)\n"), *Socket.Socket, *Socket.Use, *State);
		}
	}
	if (Row.bKeepProportions)
	{
		Report += Row.CharacterSkeleton.IsNull()
			? FString(TEXT("    WARNING: Keep Proportions needs Character Skeleton\n"))
			: FString(TEXT("    proportions: the pairs and families of ")) + ShortName(SoftPath(Row.CharacterSkeleton)) +
				  TEXT(" keep every body's own bone lengths (body bones from each mesh, hips scaled to its height)\n");
	}

	// Cutscenes: a family with the cutscene skeleton as hub.
	if (!Row.Cutscene.IsNull() || !Row.CharacterSkeleton.IsNull())
	{
		USkeleton* Hub = Row.Cutscene.IsNull() ? nullptr : Row.Cutscene.LoadSynchronous();
		USkeleton* Own = Row.CharacterSkeleton.IsNull() ? nullptr : Row.CharacterSkeleton.LoadSynchronous();
		if (Row.Cutscene.IsNull() || Row.CharacterSkeleton.IsNull())
		{
			Report += TEXT("    WARNING: cutscenes need both Cutscene (the skeleton whose cutscenes it plays) and Character Skeleton (its own)\n");
		}
		else if (!Hub || !Own)
		{
			Report += FString::Printf(TEXT("    ERROR: skeleton %s not found\n"), !Hub ? *Row.Cutscene.ToString() : *Row.CharacterSkeleton.ToString());
			bOk = false;
		}
		else if (Hub == Own)
		{
			Report += TEXT("    note: Cutscene is the character's own skeleton: nothing to do\n");
		}
		else
		{
			Report += FString::Printf(TEXT("    cutscenes: meshes on %s are bound to %s and play its cutscene animations (a family with %s as hub)\n"),
				*Own->GetName(), *Hub->GetName(), *Hub->GetName());
		}
	}

	// 3.3: commands and limit breaks per animation pack.
	if (Row.Abilities.Num() > 0)
	{
		const FString Player = Row.PlayerParameter.TrimStartAndEnd();
		if (Player.IsEmpty())
		{
			Report += TEXT("    WARNING: Abilities need Player Parameter (the character's BattlePlayerParameter row: pt_Cloud in Cloud's slot); the game mod ignores them\n");
		}
		const auto BadNames = [](const TArray<FString>& List) {
			TArray<FString> Bad;
			for (const FString& Name : List)
			{
				if (!SkelCompat::IsRowName(Wide(Name.TrimStartAndEnd()))) { Bad.Add(Name); }
			}
			return Bad;
		};
		const FEndPackAbilities* Default = Row.Abilities.FindByPredicate([](const FEndPackAbilities& P) { return P.Pack.TrimStartAndEnd().Equals(TEXT("Battle00"), ESearchCase::IgnoreCase); });
		for (const FEndPackAbilities& Pack : Row.Abilities)
		{
			const FString Name = Pack.Pack.TrimStartAndEnd();
			if (Name.IsEmpty() || (!Pack.bSetCommands && !Pack.bSetLimits && !Pack.bSetWeaponAbilities))
			{
				Report += FString::Printf(TEXT("    WARNING: an Abilities entry has %s; left out\n"),
					Name.IsEmpty() ? TEXT("no Pack") : TEXT("none of Set Commands, Set Limits and Set Weapon Abilities"));
				continue;
			}
			const bool bOwn = Name.Equals(TEXT("Battle00"), ESearchCase::IgnoreCase);
			const auto Describe = [&](bool bLimits) {
				const bool bSet = bLimits ? Pack.bSetLimits : Pack.bSetCommands;
				if (bSet) { return ListText(CleanList(bLimits ? Pack.Limits : Pack.Commands, false)); }
				if (!bOwn && Default && (bLimits ? Default->bSetLimits : Default->bSetCommands)) { return FString(TEXT("Battle00's")); }
				return FString(TEXT("the table's own"));
			};
			Report += FString::Printf(TEXT("    abilities in pack %s: commands %s; limits %s\n"), *Name, *Describe(false), *Describe(true));
			TArray<FString> Bad = BadNames(Pack.Commands);
			Bad.Append(BadNames(Pack.Limits));
			if (Pack.bSetWeaponAbilities)
			{
				// 3.4: the abilities the character's weapons give in this pack
				FString Weapons;
				for (const FEndWeaponAbility& Weapon : Pack.WeaponAbilities)
				{
					Weapons += (Weapons.IsEmpty() ? TEXT("") : TEXT(", ")) + Weapon.Weapon.TrimStartAndEnd() + TEXT(" -> ") + Weapon.Ability.TrimStartAndEnd();
					Bad.Append(BadNames({Weapon.Weapon, Weapon.Ability}));
				}
				Report += TEXT("      weapon abilities: ") + (Weapons.IsEmpty() ? FString(TEXT("the weapons' own")) : Weapons) +
						  TEXT(" (needs RebirthSkelCompat 3.4; whether each shows is still the weapon's: learned, or equipped)\n");
			}
			else if (!bOwn && Default && Default->bSetWeaponAbilities && Default->WeaponAbilities.Num() > 0)
			{
				Report += TEXT("      weapon abilities: Battle00's\n");
			}
			if (Bad.Num() > 0)
			{
				Report += TEXT("      WARNING: not BattleAbility row names (letters, digits, _ and - only): ") + ListText(Bad) + TEXT("\n");
			}
			if (Pack.bSetCommands && CleanList(Pack.Commands, false).Num() > static_cast<int32>(SkelCompat::MaxCommandAbilities))
			{
				Report += FString::Printf(TEXT("      WARNING: %d commands; the game lists the first %d of a player row (then the character's weapon and materia abilities), the rest are left out\n"),
					CleanList(Pack.Commands, false).Num(), static_cast<int32>(SkelCompat::MaxCommandAbilities));
			}
			if (Pack.bSetLimits && CleanList(Pack.Limits, false).Num() > static_cast<int32>(SkelCompat::MaxLimitAbilities))
			{
				Report += FString::Printf(TEXT("      WARNING: %d limits; the game lists the first %d of a player row, the rest are left out\n"),
					CleanList(Pack.Limits, false).Num(), static_cast<int32>(SkelCompat::MaxLimitAbilities));
			}
		}
		if (!Player.IsEmpty() && SkelCompat::PlayerTypeOf(Wide(Player)) < 0 && Row.bRefreshAbilities)
		{
			Report += TEXT("    note: ") + Player + TEXT(" is not a party member's row (pt_Cloud, pt_Barret, ...): the game mod cannot have the game recalculate its status, so switched lists show when the game next does\n");
		}
		if (!Row.bRefreshAbilities)
		{
			Report += TEXT("    Refresh Abilities is off: switched lists show when the game next recalculates the character's status (a new area, a level up)\n");
		}
		Report += TEXT("    (every ability has to be a row of the resident BattleAbility table in the game; the game mod leaves out the others and logs them)\n");
	}
	for (const FString& Path : CleanList(Row.Preload, false))
	{
		Report += TEXT("    preload: ") + NormalizedObjectPath(Path) + TEXT(" (loaded and kept from the first map load)\n");
	}
	for (const FString& Path : CleanList(Row.PackAssets, false))
	{
		Report += TEXT("    pack asset: ") + NormalizedObjectPath(Path) + TEXT(" (put into the characters' CharaSpec packs when they load; needs RebirthSkelCompat 3.3.1)\n");
	}
	// 3.6: the forms and the forms menu.
	if (Row.Forms.List.Num() > 0)
	{
		bOk &= CheckForms(Row, Core, Asked, Table.bAvailable, Report);
	}
	if (TableRows.Num() > 0)
	{
		for (const FString& Problem : Table.Check(TableRows))
		{
			Report += TEXT("    CharaSpec check: ") + Problem + TEXT("\n");
		}
	}
	return bOk;
}

// The rows the game ends up with for these characters (rows of every compat file joined, paks checked).
void ReportRowsInGame(const FGameView& View, const TArray<FString>& Packs, FString& Report)
{
	for (const SkelCompat::AnimSetRow& Settled : View.Config.AnimSets)
	{
		const FString Pack = FromWide(Settled.Characters.front());
		if (!Packs.ContainsByPredicate([&](const FString& Mine) { return SamePath(Mine, Pack); }))
		{
			continue;
		}
		const auto Sources = [](const std::vector<SkelCompat::SetSource>& List) {
			TArray<FString> Items;
			for (const SkelCompat::SetSource& Source : List)
			{
				Items.Add((Source.Folder ? FromWide(Source.Path) + TEXT("/*") : ShortSource(FromWide(Source.Path))) +
					(Source.As.empty() ? FString() : TEXT(" as ") + FromWide(Source.As)) +
					(Source.Auto == SkelCompat::AutoMatchMode::Off ? FString() : FString(TEXT(" (auto)"))));
			}
			return ListText(Items);
		};
		Report += FString::Printf(TEXT("  sets of %s (%s): battle from %s; field from %s; %d move(s)%s\n"), *ShortName(Pack), *FromWide(Settled.Origin),
			*Sources(Settled.Battle), *Sources(Settled.Field), static_cast<int32>(Settled.Moves.size()),
			Settled.FieldActions.empty() ? TEXT("") : *(TEXT("; field actions ") + FromWide(Settled.FieldActions)));
		// 3.3: what each pack gives the character's BattlePlayerParameter row.
		for (const SkelCompat::PackAbilities& Entry : Settled.Abilities)
		{
			const auto Names = [&](bool bLimits) {
				std::wstring From;
				const std::vector<std::wstring>* List = Settled.ListFor(Entry.Pack, bLimits, &From);
				if (!List) { return FString(TEXT("the table's own")); }
				TArray<FString> Items;
				for (const std::wstring& Name : *List) { Items.Add(FromWide(Name)); }
				return ListText(Items) + (SkelCompat::NameEquals(From, Entry.Pack) ? FString() : TEXT(" (") + FromWide(From) + TEXT("'s)"));
			};
			Report += FString::Printf(TEXT("    %s, pack %s: commands %s; limits %s\n"), *FromWide(Settled.Player), *FromWide(Entry.Pack), *Names(false), *Names(true));
		}
		// 3.6: the forms the game ends up with (the first file's, when several give some).
		if (Settled.Forms.HasList())
		{
			TArray<FString> Items;
			for (const SkelCompat::Form& Form : Settled.Forms.List)
			{
				Items.Add(FromWide(Form.Name) + TEXT(" (") + (Form.Pack.empty() ? FString(TEXT("Battle00")) : FromWide(Form.Pack)) + TEXT(")"));
			}
			Report += FString::Printf(TEXT("    forms menu (hold %s): %s\n"), *FromWide(Settled.Forms.Button), *ListText(Items));
		}
	}
}

// ------------------------------------------------------------------------------------------------
// Carrier Blueprint (AssetUserData) and its two array variables. The arrays hold object paths as
// strings, not soft references: soft references would make the cooker pull the (retail) animation
// skeleton into your mod's cook. The mod also accepts Name or soft/hard reference arrays.
// ------------------------------------------------------------------------------------------------
bool IsPathArrayType(const FEdGraphPinType& Type)
{
	return Type.ContainerType == EPinContainerType::Array &&
		(Type.PinCategory == UEdGraphSchema_K2::PC_String || Type.PinCategory == UEdGraphSchema_K2::PC_Name ||
		 Type.PinCategory == UEdGraphSchema_K2::PC_SoftObject);
}

bool EnsureArrayVariable(UBlueprint* Blueprint, const FName Name, bool& bChanged, FString& Report)
{
	const int32 Existing = FBlueprintEditorUtils::FindNewVariableIndex(Blueprint, Name);
	if (Existing != INDEX_NONE)
	{
		if (!IsPathArrayType(Blueprint->NewVariables[Existing].VarType))
		{
			Report += FString::Printf(TEXT("ERROR: %s.%s exists but is not an array of strings\n"), CarrierName, *Name.ToString());
			return false;
		}
		return true;
	}
	FEdGraphPinType Type;
	Type.PinCategory = UEdGraphSchema_K2::PC_String;
	Type.ContainerType = EPinContainerType::Array;
	if (!FBlueprintEditorUtils::AddMemberVariable(Blueprint, Name, Type))
	{
		Report += FString::Printf(TEXT("ERROR: could not add %s to %s\n"), *Name.ToString(), CarrierName);
		return false;
	}
	FBlueprintEditorUtils::SetBlueprintOnlyEditableFlag(Blueprint, Name, false); // editable on the skeleton's instance
	bChanged = true;
	return true;
}

UClass* FindOrCreateCarrier(bool bCreate, TArray<UPackage*>& Dirty, FString& Report)
{
	const FString ObjectPath = FString(CarrierPackage) + TEXT(".") + CarrierName;
	UBlueprint* Blueprint = LoadObject<UBlueprint>(nullptr, *ObjectPath, nullptr, LOAD_NoWarn | LOAD_Quiet);
	bool bChanged = false;
	if (!Blueprint && !bCreate)
	{
		Report += ObjectPath + TEXT(" does not exist, so no skeleton carries a list\n");
		return nullptr;
	}
	if (!Blueprint)
	{
		UPackage* Package = CreatePackage(CarrierPackage);
		Blueprint = FKismetEditorUtilities::CreateBlueprint(UAssetUserData::StaticClass(), Package, FName(CarrierName), BPTYPE_Normal,
			UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), FName(TEXT("RebirthSkelCompat")));
		if (!Blueprint)
		{
			Report += TEXT("ERROR: could not create ") + ObjectPath + TEXT("\n");
			return nullptr;
		}
		FAssetRegistryModule::AssetCreated(Blueprint);
		Report += TEXT("Created ") + ObjectPath + TEXT("\n");
		bChanged = true;
	}
	if (Blueprint->ParentClass != UAssetUserData::StaticClass())
	{
		Report += TEXT("ERROR: ") + ObjectPath + TEXT(" must have AssetUserData as its parent class\n");
		return nullptr;
	}
	if (!EnsureArrayVariable(Blueprint, AnimationSkeletonsVariable, bChanged, Report) ||
		!EnsureArrayVariable(Blueprint, ReceivingMeshesVariable, bChanged, Report))
	{
		return nullptr;
	}
	if (bChanged || !Blueprint->GeneratedClass || Blueprint->Status != BS_UpToDate)
	{
		FKismetEditorUtilities::CompileBlueprint(Blueprint);
		Blueprint->MarkPackageDirty();
		Dirty.AddUnique(Blueprint->GetOutermost());
	}
	UClass* Generated = Blueprint->GeneratedClass;
	if (!Generated || !Generated->IsChildOf(UAssetUserData::StaticClass()))
	{
		Report += TEXT("ERROR: ") + ObjectPath + TEXT(" did not compile\n");
		return nullptr;
	}
	return Generated;
}

bool SetPathArray(UObject* Target, const FName Name, const TArray<FSoftObjectPath>& Paths)
{
	FArrayProperty* Array = FindFProperty<FArrayProperty>(Target->GetClass(), Name);
	if (!Array)
	{
		return false;
	}
	FStrProperty* AsString = CastField<FStrProperty>(Array->Inner);
	FNameProperty* AsName = CastField<FNameProperty>(Array->Inner);
	FSoftObjectProperty* AsSoft = CastField<FSoftObjectProperty>(Array->Inner);
	if (!AsString && !AsName && !AsSoft)
	{
		return false;
	}
	FScriptArrayHelper Helper(Array, Array->ContainerPtrToValuePtr<void>(Target));
	Helper.EmptyValues();
	for (const FSoftObjectPath& Path : Paths)
	{
		const int32 Index = Helper.AddValue();
		if (AsString)
		{
			AsString->SetPropertyValue(Helper.GetRawPtr(Index), Path.ToString());
		}
		else if (AsName)
		{
			AsName->SetPropertyValue(Helper.GetRawPtr(Index), FName(*Path.ToString()));
		}
		else
		{
			AsSoft->SetPropertyValue(Helper.GetRawPtr(Index), FSoftObjectPtr(Path));
		}
	}
	return true;
}

// Optional: RebirthMaterialPreview's editor-side registry (RegisterCompatibleSkeletons), called by reflection so this
// plugin does not depend on that module.
bool RegisterForEditorPreview(USkeleton* Receiving, USkeleton* Animation, FString& Diagnostic)
{
	UClass* Library = FindObject<UClass>(ANY_PACKAGE, TEXT("RebirthSkeletonCompatibilityEditorLibrary"));
	UFunction* Function = Library ? Library->FindFunctionByName(TEXT("RegisterCompatibleSkeletons")) : nullptr;
	if (!Function)
	{
		Diagnostic = TEXT("RebirthMaterialPreview editor registry not loaded");
		return false;
	}
	FStructOnScope Params(Function);
	uint8* Memory = Params.GetStructMemory();
	FObjectProperty* A = FindFProperty<FObjectProperty>(Function, TEXT("A"));
	FObjectProperty* B = FindFProperty<FObjectProperty>(Function, TEXT("B"));
	FStrProperty* Out = FindFProperty<FStrProperty>(Function, TEXT("OutDiagnostic"));
	FBoolProperty* Persist = FindFProperty<FBoolProperty>(Function, TEXT("bPersistManifest"));
	FBoolProperty* Return = FindFProperty<FBoolProperty>(Function, TEXT("ReturnValue"));
	if (!A || !B || !Return)
	{
		Diagnostic = TEXT("unexpected RegisterCompatibleSkeletons signature");
		return false;
	}
	A->SetObjectPropertyValue_InContainer(Memory, Receiving);
	B->SetObjectPropertyValue_InContainer(Memory, Animation);
	if (Persist)
	{
		Persist->SetPropertyValue_InContainer(Memory, true);
	}
	Library->GetDefaultObject()->ProcessEvent(Function, Memory);
	if (Out)
	{
		Diagnostic = Out->GetPropertyValue_InContainer(Memory);
	}
	return Return->GetPropertyValue_InContainer(Memory);
}
// What the Move Maker lists of a character's animation names (editor 1.8).
bool SlotIsKind(const FString& Name, EEndMoveSlotKind Kind)
{
	if (Kind == EEndMoveSlotKind::Everything)
	{
		return true;
	}
	const SkelCompat::Detail::AnimName Parsed = SkelCompat::Detail::ParseAnimName(Wide(Name));
	const FString Body = FromWide(Parsed.Body);
	const bool bLimit = Body.StartsWith(TEXT("atklimit"));
	const bool bAbility = !bLimit && (Body.StartsWith(TEXT("atkburst")) || Body.Contains(TEXT("ability")));
	switch (Kind)
	{
	case EEndMoveSlotKind::LimitBreaks:
		return bLimit;
	case EEndMoveSlotKind::Abilities:
		return bAbility;
	case EEndMoveSlotKind::Attacks:
	{
		const int Kind2 = SkelCompat::Detail::TargetKind(Parsed);
		return Kind2 == 1 || Kind2 == 2;
	}
	default:
		return true;
	}
}

// ------------------------------------------------------------------------------------------------
// Replacing and saving Anim Sequences in this engine (editor 1.10.1)
// ------------------------------------------------------------------------------------------------
// RebirthEngineV5's UAnimSequence::Serialize writes the game's memory-mapped layout, and its reading half runs for every
// archive that does not save, also for the ones that only look for references. Deleting an asset (ObjectTools::
// ForceDeleteObjects) looks through every object in memory that way, which empties the compressed bytes of every Anim
// Sequence in memory while their codec data still points at the old bytes. An Anim Sequence saved after that records 0
// compressed bytes but holds the old ones, and its package no longer loads: the editor stops with "Unexpected array element
// size" and the cooker with "SerializeNum >= 0". So an earlier import or build is replaced without loading it or deleting
// it as an asset, every Anim Sequence is compressed anew right before it is saved, and its saved file is checked.
enum class EEarlierAsset : uint8
{
	None,     // nothing there
	Replaced, // out of the way (in memory: renamed into the transient package; on disk only: its files deleted)
	Refused,  // not an earlier import or build of ours (see the reason)
};

// The file of an earlier import or build: an editor package (not one of the game's cooked files) that holds only Name, of
// class Expected. Read without loading the package: only its summary and the asset registry's view of it.
bool IsEarlierPackageFile(const FString& Filename, const FString& Package, const FString& Name, const UClass* Expected, FString& OutWhy)
{
	{
		TUniquePtr<FArchive> Reader(IFileManager::Get().CreateFileReader(*Filename));
		if (!Reader)
		{
			OutWhy = TEXT("could not be read");
			return false;
		}
		FPackageFileSummary Summary;
		*Reader << Summary;
		if (Reader->IsError() || static_cast<uint32>(Summary.Tag) != PACKAGE_FILE_TAG)
		{
			OutWhy = TEXT("is not a package this editor reads");
			return false;
		}
		if ((Summary.PackageFlags & (PKG_Cooked | PKG_FilterEditorOnly)) != 0)
		{
			OutWhy = TEXT("is a cooked game asset");
			return false;
		}
	}
	IAssetRegistry& Registry = IAssetRegistry::GetChecked();
	Registry.ScanFilesSynchronous(TArray<FString>{FPaths::ConvertRelativePathToFull(Filename)}, true);
	TArray<FAssetData> Assets;
	Registry.GetAssetsByPackageName(FName(*Package), Assets, true);
	for (const FAssetData& Asset : Assets)
	{
		if (Asset.AssetName != FName(*Name) || (Expected && Asset.AssetClass != Expected->GetFName()))
		{
			OutWhy = FString::Printf(TEXT("holds %s (%s), not only the %s %s"), *Asset.AssetName.ToString(), *Asset.AssetClass.ToString(),
				Expected ? *Expected->GetName() : TEXT("asset"), *Name);
			return false;
		}
	}
	return true;
}

// Puts the earlier import or build at Package (asset Name) out of the way without loading it: one in memory is renamed
// into the transient package (its editors closed), one only on disk has its files deleted. The new one takes its place.
EEarlierAsset ReplaceEarlierAsset(const FString& Package, const FString& Name, UClass* Expected, FString& OutWhy)
{
	if (UPackage* Loaded = FindPackage(nullptr, *Package))
	{
		if (UObject* Old = StaticFindObjectFast(nullptr, Loaded, FName(*Name)))
		{
			if (IsCookedAsset(Old))
			{
				OutWhy = TEXT("is a cooked game asset");
				return EEarlierAsset::Refused;
			}
			if (Expected && !Old->IsA(Expected))
			{
				OutWhy = FString::Printf(TEXT("is a %s, not a %s"), *Old->GetClass()->GetName(), *Expected->GetName());
				return EEarlierAsset::Refused;
			}
			if (GEditor)
			{
				if (UAssetEditorSubsystem* Editors = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
				{
					Editors->CloseAllEditorsForAsset(Old);
				}
			}
			FAssetRegistryModule::AssetDeleted(Old);
			ResetLoaders(Loaded);
			const FName Away = MakeUniqueObjectName(GetTransientPackage(), Old->GetClass(), FName(*(Name + TEXT("_Replaced"))));
			Old->Rename(*Away.ToString(), GetTransientPackage(), REN_DontCreateRedirectors | REN_NonTransactional | REN_DoNotDirty | REN_ForceNoResetLoaders);
			Old->ClearFlags(RF_Public | RF_Standalone | RF_Transactional);
			Old->MarkPendingKill();
			return EEarlierAsset::Replaced; // its file is written over when the new one is saved
		}
		ResetLoaders(Loaded); // nothing of it in memory, but its file may still be open
	}
	FString Filename;
	if (!FPackageName::DoesPackageExist(Package, nullptr, &Filename))
	{
		return EEarlierAsset::None;
	}
	if (!IsEarlierPackageFile(Filename, Package, Name, Expected, OutWhy))
	{
		return EEarlierAsset::Refused;
	}
	const FString Base = FPaths::GetBaseFilename(Filename, false);
	for (const TCHAR* Extension : {TEXT(".uasset"), TEXT(".uexp"), TEXT(".ubulk"), TEXT(".uptnl")})
	{
		const FString File = Base + Extension;
		if (IFileManager::Get().FileExists(*File) && !IFileManager::Get().Delete(*File, false, true, true))
		{
			OutWhy = FString::Printf(TEXT("could not be deleted (%s is open in another program, or read-only)"), *File);
			return EEarlierAsset::Refused;
		}
	}
	return EEarlierAsset::Replaced;
}

// Compressed anew (from the derived data cache when it has it) right before it is saved, so the compressed bytes it saves
// are the ones its codec reads.
void ReadyAnimationToSave(UAnimSequence* Sequence)
{
	if (!IsValid(Sequence))
	{
		return;
	}
	Sequence->RequestSyncAnimRecompression(false);
	if (Sequence->CompressedData.CompressedDataStructure.IsValid())
	{
		Sequence->CompressedData.CompressedDataStructure->Bind(Sequence->CompressedData.CompressedByteStream);
	}
}

// What is wrong with the saved file of an Anim Sequence's package, if anything. In this engine's memory-mapped layout the
// file records how many compressed bytes it holds (a header, two pointers {offset, count, max}, 16 marker bytes, then the
// bytes and the curve bytes, each padded to 16) and one whose count and bytes disagree does not load back.
FString SavedAnimationProblem(const FString& Package)
{
	FString Filename;
	TArray<uint8> Bytes;
	if (!FPackageName::DoesPackageExist(Package, nullptr, &Filename) || !FFileHelper::LoadFileToArray(Bytes, *Filename))
	{
		return TEXT("its saved file could not be read back");
	}
	static const uint8 Marker[16] = {0x30, 0xAF, 0x2F, 0x90, 0x54, 0x94, 0xF4, 0x06, 0x59, 0x00, 0x49, 0x00, 0x49, 0x00, 0x53, 0x00};
	const auto U16 = [&Bytes](int64 At) { uint16 Value = 0; FMemory::Memcpy(&Value, Bytes.GetData() + At, sizeof(Value)); return static_cast<int64>(Value); };
	const auto U32 = [&Bytes](int64 At) { uint32 Value = 0; FMemory::Memcpy(&Value, Bytes.GetData() + At, sizeof(Value)); return static_cast<int64>(Value); };
	const auto U64 = [&Bytes](int64 At) { uint64 Value = 0; FMemory::Memcpy(&Value, Bytes.GetData() + At, sizeof(Value)); return Value; };
	const auto Padded = [](int64 Size) { return Size > 0 ? Size + (16 - Size % 16) % 16 : 0; };
	for (int64 At = 32 + 12; At + 16 <= Bytes.Num(); ++At)
	{
		if (Bytes[At] != Marker[0] || FMemory::Memcmp(Bytes.GetData() + At, Marker, sizeof(Marker)) != 0)
		{
			continue;
		}
		const int64 Pointers = At - 32;
		const int64 Count = static_cast<int32>(U32(Pointers + 8));
		const int64 Curves = (U64(Pointers + 16) >> 1) != 0 ? static_cast<int64>(static_cast<int32>(U32(Pointers + 24))) : 0;
		for (int64 Padding = 0; Padding < 16 && Pointers - Padding - 12 >= 0; ++Padding)
		{
			const int64 Header = Pointers - Padding - 12;
			if (U16(Header + 10) == Padding && U16(Header + 8) == 16 && U32(Header + 4) == 65536)
			{
				const int64 Frozen = U32(Header);
				if (Count < 0 || Curves < 0 || Frozen != 48 + Padded(Count) + Padded(Curves))
				{
					return FString::Printf(TEXT("this engine saved it broken (it records %lld compressed bytes but holds %lld)"), Count, Frozen - 48 - Padded(Curves));
				}
				return FString();
			}
		}
		return FString(); // a layout this check does not know: not checked
	}
	return FString(); // not the memory-mapped layout
}

// Saves Packages. Every Anim Sequence in Sequences is readied first and its saved file checked after; one this engine
// still saved broken is saved once more, and if it is still broken its file is deleted (it would stop the editor and the
// cooker when they load it) and a line says so. Returns the packages not saved; OutBroken counts the deleted ones.
TArray<UPackage*> SaveAnimationPackages(const TArray<UPackage*>& Packages, const TArray<UAnimSequence*>& Sequences, int32& OutBroken, FString& OutReport)
{
	OutBroken = 0;
	for (UAnimSequence* Sequence : Sequences)
	{
		ReadyAnimationToSave(Sequence);
	}
	TArray<UPackage*> Failed;
	FEditorFileUtils::PromptForCheckoutAndSave(Packages, false, false, &Failed);
	TArray<UAnimSequence*> Again;
	for (UAnimSequence* Sequence : Sequences)
	{
		if (IsValid(Sequence) && !Failed.Contains(Sequence->GetOutermost()) && !SavedAnimationProblem(Sequence->GetOutermost()->GetName()).IsEmpty())
		{
			Again.Add(Sequence);
		}
	}
	if (Again.Num() == 0)
	{
		return Failed;
	}
	TArray<UPackage*> AgainPackages;
	for (UAnimSequence* Sequence : Again)
	{
		ReadyAnimationToSave(Sequence);
		AgainPackages.AddUnique(Sequence->GetOutermost());
	}
	TArray<UPackage*> FailedAgain;
	FEditorFileUtils::PromptForCheckoutAndSave(AgainPackages, false, false, &FailedAgain);
	for (UAnimSequence* Sequence : Again)
	{
		UPackage* Outer = Sequence->GetOutermost();
		const FString Problem = FailedAgain.Contains(Outer) ? FString(TEXT("could not be saved again")) : SavedAnimationProblem(Outer->GetName());
		if (Problem.IsEmpty())
		{
			continue;
		}
		FString Filename;
		if (FPackageName::DoesPackageExist(Outer->GetName(), nullptr, &Filename))
		{
			ResetLoaders(Outer);
			IFileManager::Get().Delete(*Filename, false, true, true);
		}
		Failed.AddUnique(Outer);
		++OutBroken;
		OutReport += FString::Printf(TEXT("%s: ERROR: %s, so its file is deleted (it would stop the editor and the cooker); make it again\n"), *Outer->GetName(), *Problem);
	}
	return Failed;
}

} // namespace RebirthSkelCompatEditor

using namespace RebirthSkelCompatEditor;

UEndSkeletonCompatDataObject::UEndSkeletonCompatDataObject()
{
	GameDirectory.Path = DefaultGameDirectory;
}

FString UEndSkeletonCompatDataObject::GameCompatFile() const
{
	if (GameDirectory.Path.IsEmpty())
	{
		return FString();
	}
	return GameDirectory.Path / ModFolder / TEXT("compat") / GetName() + TEXT(".json");
}

bool UEndSkeletonCompatDataObject::ValidatePairs(FString& OutReport) const
{
	OutReport.Reset();
	bool bOk = Pairs.Num() > 0 || AnimationSets.Num() > 0 || WeaponSwaps.Num() > 0 || CharacterSwaps.Num() > 0;
	if (!bOk)
	{
		OutReport += TEXT("No pairs, animation set rows, character swaps or weapon swaps.\n");
	}
	// Every compat file of the game plus this data object, settled as the mod settles them.
	const FGameView View = SettleInGame(GameDirectory.Path, GetName(), ToRuntimeJson());
	for (int32 Index = 0; Index < Pairs.Num(); ++Index)
	{
		bOk &= CheckPair(Pairs[Index], Index, Pairs, View, OutReport);
	}
	TArray<FString> Packs;
	TArray<FString> WeaponSkeletons;
	if (AnimationSets.Num() > 0 || WeaponSwaps.Num() > 0 || CharacterSwaps.Num() > 0 || bFixPackModels)
	{
		const FCharaSpecTable Table(CharaSpecTable);
		const FString GameLog = AnimationSets.Num() > 0 ? GameLogText(GameDirectory.Path) : FString();
		for (int32 Index = 0; Index < AnimationSets.Num(); ++Index)
		{
			bOk &= CheckAnimSetRow(AnimationSets[Index], Index, Table, GameLog, OutReport);
			if (AnimationSets[Index].bEnabled)
			{
				for (const FString& Character : AnimationSets[Index].Characters)
				{
					const FString Pack = FromWide(SkelCompat::CharacterPackPath(Wide(Character)));
					if (!Pack.IsEmpty())
					{
						Packs.AddUnique(Pack);
					}
				}
			}
		}
		// Character swaps: their families and rows count as this data object's in the in-game view below.
		TMap<FString, FString> FamilyHubs; // "member|member" -> hub, to find two swaps that pick different hubs
		for (int32 Index = 0; Index < CharacterSwaps.Num(); ++Index)
		{
			bOk &= CheckCharacterSwap(CharacterSwaps[Index], Index, Table, bApplyToPacks, OutReport);
			const FCharacterSwapPlan Plan = PlanCharacterSwap(CharacterSwaps[Index], Table, false, false);
			if (const TSharedPtr<FJsonObject> Family = CharacterFamilyJson(CharacterSwaps[Index], Plan))
			{
				const FString Hub = StringField(Family, TEXT("hub"));
				TArray<FString> Members{Hub};
				for (const FString& Member : StringsOf(Family->TryGetField(TEXT("animation_skeletons"))))
				{
					Members.AddUnique(Member);
					WeaponSkeletons.AddUnique(Member);
				}
				WeaponSkeletons.AddUnique(Hub);
				Members.Sort();
				const FString Key = FString::Join(Members, TEXT("|"));
				if (const FString* Other = FamilyHubs.Find(Key))
				{
					if (!SamePath(*Other, Hub))
					{
						OutReport += FString::Printf(TEXT("    WARNING: another character swap makes the same family with hub %s; the game uses one hub for both (the first named): give both swaps the same Moveset\n"),
							*ShortName(*Other));
					}
				}
				else
				{
					FamilyHubs.Add(Key, Hub);
				}
			}
			for (const FCharacterRowPlan& Row : Plan.Rows)
			{
				if (Row.Pack.bInProject)
				{
					Packs.AddUnique(FromWide(SkelCompat::CharacterPackPath(Wide(Row.Row))));
				}
			}
		}
		for (int32 Index = 0; Index < WeaponSwaps.Num(); ++Index)
		{
			bOk &= CheckWeaponSwap(WeaponSwaps[Index], Index, Table, bApplyToPacks, OutReport);
			if (const TSharedPtr<FJsonObject> Family = WeaponFamilyJson(WeaponSwaps[Index], Table))
			{
				WeaponSkeletons.AddUnique(StringField(Family, TEXT("receiving_skeleton")));
				for (const FString& Member : StringsOf(Family->TryGetField(TEXT("animation_skeletons"))))
				{
					WeaponSkeletons.AddUnique(Member);
				}
			}
		}
		if (Table.bAvailable && (CharacterSwaps.Num() > 0 || WeaponSwaps.Num() > 0))
		{
			// Shared CharaSpec Lists once Apply To CharaSpec has written them: a loop keeps the game loading forever.
			const TArray<FString> Loops = SharedLoops(Table, PlannedSharedLists(CharacterSwaps, WeaponSwaps, Table, bApplyToPacks));
			for (const FString& Loop : Loops)
			{
				OutReport += TEXT("Shared CharaSpec Lists: ERROR: these specs would load each other in a loop: ") + Loop + TEXT("\n");
			}
			bOk &= Loops.Num() == 0;
		}
		if (Table.bAvailable && bFixPackModels)
		{
			const TArray<FPackCheck> Checks = CheckProjectPacks(Table);
			if (Checks.Num() > 0)
			{
				OutReport += TEXT("CharaSpec packs of this project that disagree with their rows (Apply To CharaSpec gives a row the model of the blueprint its pack spawns; swaps fix the rest):\n");
			}
			for (const FPackCheck& Check : Checks)
			{
				for (const FString& Difference : Check.Differences)
				{
					OutReport += FString::Printf(TEXT("    CharaSpec_%s: %s\n"), *Check.Row, *Difference);
				}
			}
		}
	}
	TArray<FString> Mine = Packs;
	Mine.Append(WeaponSkeletons);
	for (const FEndAnimSetRow& Row : AnimationSets)
	{
		for (const TSoftObjectPtr<USkeleton>* Soft : {&Row.Cutscene, &Row.CharacterSkeleton})
		{
			if (Row.bEnabled && !Soft->IsNull())
			{
				Mine.AddUnique(SoftPath(*Soft));
			}
		}
	}
	for (const FEndSkeletonCompatPair& Pair : Pairs)
	{
		if (!Pair.bEnabled)
		{
			continue;
		}
		for (const TSoftObjectPtr<USkeleton>& Soft : Pair.MoreReceivingSkeletons)
		{
			if (!Soft.IsNull())
			{
				Mine.AddUnique(SoftPath(Soft));
			}
		}
		for (const TSoftObjectPtr<USkeleton>& Soft : Pair.AnimationSkeletons)
		{
			if (!Soft.IsNull())
			{
				Mine.AddUnique(SoftPath(Soft));
			}
		}
		if (!Pair.ReceivingSkeleton.IsNull())
		{
			Mine.AddUnique(SoftPath(Pair.ReceivingSkeleton));
		}
	}
	ReportInGame(View, Mine, GetName() + TEXT(".json"), OutReport);
	ReportRowsInGame(View, Packs, OutReport);
	return bOk;
}

FString UEndSkeletonCompatDataObject::ToRuntimeJson() const
{
	TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
	Root->SetStringField(TEXT("schema"), TEXT("RebirthSkelCompat/1"));
	Root->SetStringField(TEXT("source"), GetPathName());
	TArray<TSharedPtr<FJsonValue>> PairValues;
	auto StringArray = [](const TArray<FString>& Items)
	{
		TArray<TSharedPtr<FJsonValue>> Values;
		for (const FString& Item : Items)
		{
			Values.Add(MakeShared<FJsonValueString>(Item));
		}
		return Values;
	};
	for (const FEndSkeletonCompatPair& Pair : Pairs)
	{
		if (Pair.ReceivingSkeleton.IsNull())
		{
			continue;
		}
		const bool bMesh = Pair.Method == EEndSkelCompatMethod::Mesh;
		const bool bFamily = Pair.Method == EEndSkelCompatMethod::Family;
		const FString Receiving = Pair.ReceivingSkeleton.ToSoftObjectPath().ToString();
		TSharedRef<FJsonObject> Entry = MakeShared<FJsonObject>();
		Entry->SetStringField(TEXT("receiving_skeleton"), Receiving);
		TArray<FString> More;
		for (const TSoftObjectPtr<USkeleton>& Soft : Pair.MoreReceivingSkeletons)
		{
			if (!Soft.IsNull() && !SamePath(SoftPath(Soft), Receiving))
			{
				More.AddUnique(Soft.ToSoftObjectPath().ToString());
			}
		}
		if (More.Num() > 0)
		{
			// A family lists them as more members; other pairs get one pair per receiving skeleton.
			Entry->SetArrayField(bFamily ? TEXT("skeletons") : TEXT("receiving_skeletons"), StringArray(More));
		}
		TArray<FString> Animation;
		for (const TSoftObjectPtr<USkeleton>& Soft : Pair.AnimationSkeletons)
		{
			if (!Soft.IsNull())
			{
				Animation.AddUnique(Soft.ToSoftObjectPath().ToString());
			}
		}
		Entry->SetArrayField(TEXT("animation_skeletons"), StringArray(Animation));
		Entry->SetStringField(TEXT("method"), MethodText(Pair.Method));
		if (bFamily)
		{
			Entry->SetStringField(TEXT("hub"), Receiving);
		}
		const TArray<FString> Requires = CleanList(Pair.RequiresPaks, true);
		if (Requires.Num() > 0)
		{
			Entry->SetArrayField(TEXT("requires_paks"), StringArray(Requires));
		}
		if (!bMesh && !bFamily)
		{
			const TArray<FString> Adopt = CleanList(Pair.AdoptPaths, false);
			if (Adopt.Num() > 0)
			{
				Entry->SetArrayField(TEXT("adopt_paths"), StringArray(Adopt));
			}
		}
		else
		{
			if (bMesh)
			{
				TArray<FString> Meshes;
				for (const TSoftObjectPtr<USkeletalMesh>& Soft : Pair.ReceivingMeshes)
				{
					if (!Soft.IsNull())
					{
						Meshes.AddUnique(Soft.ToSoftObjectPath().ToString());
					}
				}
				if (Meshes.Num() > 0)
				{
					Entry->SetArrayField(TEXT("receiving_meshes"), StringArray(Meshes));
				}
			}
			Entry->SetBoolField(TEXT("fix_hierarchy"), Pair.bFixHierarchy);
			Entry->SetBoolField(TEXT("repair_live_components"), Pair.bRepairLiveComponents);
			Entry->SetBoolField(TEXT("carry_sockets"), Pair.bCarrySockets);
		}
		if (Pair.bKeepProportions)
		{
			Entry->SetBoolField(TEXT("proportions"), true);
			const TArray<FString> ProportionBones = CleanList(Pair.ProportionBones, false);   // (1.14)
			if (ProportionBones.Num() > 0)
			{
				Entry->SetArrayField(TEXT("proportion_bones"), StringArray(ProportionBones));
			}
		}
		Entry->SetBoolField(TEXT("enabled"), Pair.bEnabled);
		PairValues.Add(MakeShared<FJsonValueObject>(Entry));
	}
	// Character and weapon swaps: their families as pairs, their rows (a character swap's moves, a weapon swap's socket
	// stand-ins) after this data object's own rows, and the swaps themselves (the mod skips "character_swaps" and
	// "weapon_swaps"; the data object reads them back with Import From Game Json).
	TArray<TSharedPtr<FJsonValue>> SwapValues;
	TArray<TSharedPtr<FJsonValue>> CharacterValues;
	TArray<TSharedPtr<FJsonValue>> SwapRowValues;
	if (WeaponSwaps.Num() > 0 || CharacterSwaps.Num() > 0)
	{
		const FCharaSpecTable Table(CharaSpecTable);
		TArray<FString> FamilyKeys; // one family per set of skeletons: the first swap's hub
		for (const FEndCharacterSwap& Swap : CharacterSwaps)
		{
			if (Swap.NewCharacter.TrimStartAndEnd().IsEmpty() && CleanList(Swap.Characters, false).Num() == 0)
			{
				continue;
			}
			CharacterValues.Add(MakeShared<FJsonValueObject>(CharacterSwapToJson(Swap)));
			const FCharacterSwapPlan Plan = PlanCharacterSwap(Swap, Table, false, false);
			if (const TSharedPtr<FJsonObject> Family = CharacterFamilyJson(Swap, Plan))
			{
				TArray<FString> Members = StringsOf(Family->TryGetField(TEXT("animation_skeletons")));
				Members.AddUnique(StringField(Family, TEXT("hub")));
				Members.Sort();
				const FString Key = FString::Join(Members, TEXT("|"));
				if (!FamilyKeys.Contains(Key))
				{
					FamilyKeys.Add(Key);
					PairValues.Add(MakeShared<FJsonValueObject>(Family));
				}
			}
			for (const TSharedPtr<FJsonObject>& Row : CharacterRowsJson(Swap, Plan))
			{
				SwapRowValues.Add(MakeShared<FJsonValueObject>(Row));
			}
		}
		for (const FEndWeaponSwap& Swap : WeaponSwaps)
		{
			if (Swap.NewWeapon.TrimStartAndEnd().IsEmpty() && CleanList(Swap.Weapons, false).Num() == 0)
			{
				continue;
			}
			SwapValues.Add(MakeShared<FJsonValueObject>(WeaponSwapToJson(Swap)));
			if (const TSharedPtr<FJsonObject> Family = WeaponFamilyJson(Swap, Table))
			{
				PairValues.Add(MakeShared<FJsonValueObject>(Family));
			}
			if (const TSharedPtr<FJsonObject> Sockets = WeaponSocketsJson(Swap, Table))
			{
				SwapRowValues.Add(MakeShared<FJsonValueObject>(Sockets));
			}
		}
	}
	Root->SetArrayField(TEXT("pairs"), PairValues);
	if (CharacterValues.Num() > 0)
	{
		Root->SetArrayField(TEXT("character_swaps"), CharacterValues);
	}
	if (SwapValues.Num() > 0)
	{
		Root->SetArrayField(TEXT("weapon_swaps"), SwapValues);
	}
	TArray<TSharedPtr<FJsonValue>> RowValues;
	for (const FEndAnimSetRow& Row : AnimationSets)
	{
		if (CleanList(Row.Characters, false).Num() > 0)
		{
			RowValues.Add(MakeShared<FJsonValueObject>(RowToJson(Row)));
		}
	}
	RowValues.Append(SwapRowValues);
	if (RowValues.Num() > 0)
	{
		Root->SetArrayField(TEXT("animation_sets"), RowValues);
	}
	FString Text;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Text);
	FJsonSerializer::Serialize(Root, Writer);
	return Text;
}

bool UEndSkeletonCompatDataObject::WriteRuntimeJson(FString& OutReport) const
{
	OutReport.Reset();
	const FString Json = ToRuntimeJson();
	bool bOk = true;
	auto Write = [&](const FString& File)
	{
		const FString Full = FPaths::ConvertRelativePathToFull(File);
		IFileManager::Get().MakeDirectory(*FPaths::GetPath(Full), true);
		if (FFileHelper::SaveStringToFile(Json, *Full, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
		{
			OutReport += TEXT("Wrote ") + Full + TEXT("\n");
		}
		else
		{
			OutReport += TEXT("ERROR: could not write ") + Full + TEXT("\n");
			bOk = false;
		}
	};
	const FString Directory = ExportDirectory.Path.IsEmpty() ? FPaths::ProjectSavedDir() / TEXT("RebirthSkelCompat") : ExportDirectory.Path;
	Write(Directory / GetName() + TEXT(".skelcompat.json"));
	if (!GameDirectory.Path.IsEmpty())
	{
		const FString ModDirectory = GameDirectory.Path / ModFolder;
		const FString GameFile = GameCompatFile();
		if (!IFileManager::Get().DirectoryExists(*ModDirectory))
		{
			OutReport += TEXT("RebirthSkelCompat is not installed under ") + GameDirectory.Path + TEXT(" (game copy skipped)\n");
		}
		else
		{
			// Settings added to the game's copy by hand that this data object does not have would be lost.
			FString Lost;
			TArray<FFilePair> Existing;
			TArray<FEndAnimSetRow> ExistingRows;
			TArray<FEndWeaponSwap> ExistingSwaps;
			TArray<FEndCharacterSwap> ExistingCharacters;
			FString Error;
			if (IFileManager::Get().FileExists(*GameFile) && ReadPairsFile(GameFile, Existing, Error, &ExistingRows, &ExistingSwaps, &ExistingCharacters))
			{
				// Character swaps, matched by new character and replaced rows.
				for (const FEndCharacterSwap& Old : ExistingCharacters)
				{
					const FEndCharacterSwap* Match = CharacterSwaps.FindByPredicate([&](const FEndCharacterSwap& Swap) { return SameCharacterSwap(Swap, Old); });
					if (!Match)
					{
						Lost += FString::Printf(TEXT("    character swap %s -> %s\n"), *ListText(Old.Characters), *Old.NewCharacter);
						continue;
					}
					if (HasNamesMissingFrom(Old.Characters, CleanList(Match->Characters, false)))
					{
						Lost += FString::Printf(TEXT("    character swap to %s: characters %s\n"), *Old.NewCharacter, *ListText(Old.Characters));
					}
					if (HasNamesMissingFrom(Old.RequiresPaks, CleanList(Match->RequiresPaks, true)))
					{
						Lost += FString::Printf(TEXT("    character swap to %s: requires_paks %s\n"), *Old.NewCharacter, *ListText(Old.RequiresPaks));
					}
				}
				// Weapon swaps, matched by new weapon: swaps and weapons the file has and this data object does not.
				for (const FEndWeaponSwap& Old : ExistingSwaps)
				{
					const FString OldNew = CharaSpecRowName(Old.NewWeapon);
					const FEndWeaponSwap* Match = WeaponSwaps.FindByPredicate([&](const FEndWeaponSwap& Swap) {
						return CharaSpecRowName(Swap.NewWeapon).Equals(OldNew, ESearchCase::IgnoreCase);
					});
					if (!Match)
					{
						Lost += FString::Printf(TEXT("    weapon swap to %s\n"), *OldNew);
						continue;
					}
					if (HasNamesMissingFrom(Old.Weapons, CleanList(Match->Weapons, false)))
					{
						Lost += FString::Printf(TEXT("    weapon swap to %s: weapons %s\n"), *OldNew, *ListText(Old.Weapons));
					}
					if (HasNamesMissingFrom(Old.RequiresPaks, CleanList(Match->RequiresPaks, true)))
					{
						Lost += FString::Printf(TEXT("    weapon swap to %s: requires_paks %s\n"), *OldNew, *ListText(Old.RequiresPaks));
					}
					for (const FEndSocketStandIn& Socket : Old.Sockets)
					{
						if (!Match->Sockets.ContainsByPredicate([&](const FEndSocketStandIn& Mine) { return Mine.Socket.TrimStartAndEnd().Equals(Socket.Socket, ESearchCase::IgnoreCase); }))
						{
							Lost += FString::Printf(TEXT("    weapon swap to %s: socket %s -> %s\n"), *OldNew, *Socket.Socket, *Socket.Use);
						}
					}
				}
				// Animation set rows: characters, sources and moves the file has and this data object does not.
				for (const FEndAnimSetRow& Old : ExistingRows)
				{
					for (const FString& Character : Old.Characters)
					{
						const FString Name = CharaSpecRowName(Character);
						const FEndAnimSetRow* Match = AnimationSets.FindByPredicate([&](const FEndAnimSetRow& Row) {
							return Row.Characters.ContainsByPredicate([&](const FString& Mine) { return CharaSpecRowName(Mine).Equals(Name, ESearchCase::IgnoreCase); });
						});
						if (!Match)
						{
							Lost += FString::Printf(TEXT("    animation set row for %s\n"), *Name);
							continue;
						}
						for (const TArray<FEndAnimSetSource>* List : {&Old.Battle, &Old.Field})
						{
							const TArray<FEndAnimSetSource>& Ours = List == &Old.Battle ? Match->Battle : Match->Field;
							for (const FEndAnimSetSource& Source : *List)
							{
								if (!Ours.ContainsByPredicate([&](const FEndAnimSetSource& Mine) { return SamePath(Mine.Path, Source.Path); }))
								{
									Lost += FString::Printf(TEXT("    %s: source %s\n"), *Name, *Source.Path);
								}
							}
						}
						for (const FEndAnimSetMove& Move : Old.Moves)
						{
							if (!Match->Moves.ContainsByPredicate([&](const FEndAnimSetMove& Mine) { return Mine.Name.Equals(Move.Name, ESearchCase::IgnoreCase) && Mine.Set.Equals(Move.Set, ESearchCase::IgnoreCase); }))
							{
								Lost += FString::Printf(TEXT("    %s: move %s\n"), *Name, *Move.Name);
							}
						}
					}
				}
				for (const FFilePair& Old : Existing)
				{
					const FEndSkeletonCompatPair* Match = Pairs.FindByPredicate([&](const FEndSkeletonCompatPair& Pair) {
						return !Pair.ReceivingSkeleton.IsNull() && SamePath(SoftPath(Pair.ReceivingSkeleton), Old.Receiving);
					});
					if (!Match)
					{
						continue;
					}
					if (HasNamesMissingFrom(Old.RequiresPaks, CleanList(Match->RequiresPaks, true)))
					{
						Lost += FString::Printf(TEXT("    %s: requires_paks %s\n"), *ShortName(Old.Receiving), *ListText(Old.RequiresPaks));
					}
					if (Old.AdoptPaths.Num() > 0 && Match->AdoptPaths.Num() == 0 && Match->Method == EEndSkelCompatMethod::Animations)
					{
						Lost += FString::Printf(TEXT("    %s: adopt_paths %s\n"), *ShortName(Old.Receiving), *ListText(Old.AdoptPaths));
					}
					// Data objects made before Method existed load as Animations; a file set to another method by hand would flip back.
					if (Old.bHasMethod && Old.Method != EEndSkelCompatMethod::Animations && Match->Method == EEndSkelCompatMethod::Animations)
					{
						Lost += FString::Printf(TEXT("    %s: method %s (this data object says Animations)\n"), *ShortName(Old.Receiving), MethodText(Old.Method));
					}
					if (Old.bHasCarrySockets && !Old.bCarrySockets && Match->bCarrySockets)
					{
						Lost += FString::Printf(TEXT("    %s: carry_sockets false\n"), *ShortName(Old.Receiving));
					}
				}
			}
			if (Lost.IsEmpty())
			{
				Write(GameFile);
			}
			else
			{
				OutReport += TEXT("NOT written: ") + GameFile + TEXT("\n  It has settings this data object does not have, which the export would remove or change:\n") + Lost +
					TEXT("  Press Import From Game Json to take them over (or set them on the pair), then Export Json again. To drop them on purpose, delete that file first.\n");
				bOk = false;
			}
		}
	}
	OutReport += TEXT("\n") + Json;
	return bOk;
}

bool UEndSkeletonCompatDataObject::ImportRuntimeJson(FString& OutReport)
{
	OutReport.Reset();
	const FString GameFile = ImportFile.FilePath.TrimStartAndEnd().IsEmpty() ? GameCompatFile() : FPaths::ConvertRelativePathToFull(ImportFile.FilePath.TrimStartAndEnd());
	if (GameFile.IsEmpty() || !IFileManager::Get().FileExists(*GameFile))
	{
		OutReport += TEXT("No game JSON for this data object: ") + (GameFile.IsEmpty() ? FString(TEXT("Game Directory is empty")) : GameFile) +
			TEXT(" (set Import File to read another one)\n");
		return false;
	}
	TArray<FFilePair> FilePairs;
	TArray<FEndAnimSetRow> FileRows;
	TArray<FEndWeaponSwap> FileSwaps;
	TArray<FEndCharacterSwap> FileCharacters;
	FString Error;
	if (!ReadPairsFile(GameFile, FilePairs, Error, &FileRows, &FileSwaps, &FileCharacters))
	{
		OutReport += GameFile + TEXT(" ") + Error + TEXT("\n");
		return false;
	}
	const FScopedTransaction Transaction(NSLOCTEXT("RebirthSkelCompat", "ImportFromGameJson", "Import From Game Json"));
	Modify();
	bool bChanged = false;
	for (int32 Index = 0; Index < Pairs.Num(); ++Index)
	{
		FEndSkeletonCompatPair& Pair = Pairs[Index];
		if (Pair.ReceivingSkeleton.IsNull())
		{
			continue;
		}
		const FFilePair* From = FilePairs.FindByPredicate([&](const FFilePair& Candidate) { return SamePath(Candidate.Receiving, SoftPath(Pair.ReceivingSkeleton)); });
		if (!From)
		{
			OutReport += FString::Printf(TEXT("Pair %d: not in %s\n"), Index, *FPaths::GetCleanFilename(GameFile));
			continue;
		}
		FString Changes;
		// The file's method is what the mod uses: without "method" that is the animations method.
		if (Pair.Method != From->Method)
		{
			Pair.Method = From->Method;
			Changes += FString::Printf(TEXT(" method %s;"), MethodText(Pair.Method));
		}
		const TArray<FString> Requires = CleanList(Pair.RequiresPaks, true);
		if (HasNamesMissingFrom(From->RequiresPaks, Requires))
		{
			TArray<FString> Merged = Requires;
			for (const FString& Name : From->RequiresPaks)
			{
				Merged.AddUnique(Name);
			}
			Pair.RequiresPaks = Merged;
			Changes += TEXT(" Requires Paks ") + ListText(Merged) + TEXT(";");
		}
		const TArray<FString> Adopt = CleanList(Pair.AdoptPaths, false);
		if (HasNamesMissingFrom(From->AdoptPaths, Adopt))
		{
			TArray<FString> Merged = Adopt;
			for (const FString& Path : From->AdoptPaths)
			{
				Merged.AddUnique(Path);
			}
			Pair.AdoptPaths = Merged;
			Changes += TEXT(" Adopt Paths ") + ListText(Merged) + TEXT(";");
		}
		if (Pair.Method == EEndSkelCompatMethod::Family)
		{
			// Members the file lists that this pair does not.
			for (const FString& Member : From->Animation)
			{
				const bool bListed = SamePath(Member, SoftPath(Pair.ReceivingSkeleton)) ||
					Pair.AnimationSkeletons.ContainsByPredicate([&](const TSoftObjectPtr<USkeleton>& Soft) { return SamePath(SoftPath(Soft), Member); }) ||
					Pair.MoreReceivingSkeletons.ContainsByPredicate([&](const TSoftObjectPtr<USkeleton>& Soft) { return SamePath(SoftPath(Soft), Member); });
				if (!bListed)
				{
					Pair.AnimationSkeletons.Add(TSoftObjectPtr<USkeleton>(FSoftObjectPath(Member)));
					Changes += TEXT(" member ") + ShortName(Member) + TEXT(";");
				}
			}
		}
		if (From->bHasFixHierarchy && Pair.bFixHierarchy != From->bFixHierarchy)
		{
			Pair.bFixHierarchy = From->bFixHierarchy;
			Changes += Pair.bFixHierarchy ? TEXT(" Fix Hierarchy on;") : TEXT(" Fix Hierarchy off;");
		}
		if (From->bHasRepairLiveComponents && Pair.bRepairLiveComponents != From->bRepairLiveComponents)
		{
			Pair.bRepairLiveComponents = From->bRepairLiveComponents;
			Changes += Pair.bRepairLiveComponents ? TEXT(" Repair Live Components on;") : TEXT(" Repair Live Components off;");
		}
		if (From->bHasCarrySockets && Pair.bCarrySockets != From->bCarrySockets)
		{
			Pair.bCarrySockets = From->bCarrySockets;
			Changes += Pair.bCarrySockets ? TEXT(" Carry Sockets on;") : TEXT(" Carry Sockets off;");
		}
		if (From->bHasKeepProportions && Pair.bKeepProportions != From->bKeepProportions)
		{
			Pair.bKeepProportions = From->bKeepProportions;
			Changes += Pair.bKeepProportions ? TEXT(" Keep Proportions on;") : TEXT(" Keep Proportions off;");
		}
		if (From->bHasProportionBones && CleanList(Pair.ProportionBones, false) != From->ProportionBones)   // (1.14)
		{
			Pair.ProportionBones = From->ProportionBones;
			Changes += TEXT(" Proportion Bones;");
		}
		OutReport += FString::Printf(TEXT("Pair %d (%s):%s\n"), Index, *ShortName(SoftPath(Pair.ReceivingSkeleton)),
			Changes.IsEmpty() ? TEXT(" already matches the file") : *Changes);
		bChanged |= !Changes.IsEmpty();
	}
	// Pairs and families of the file this data object does not have.
	for (const FFilePair& From : FilePairs)
	{
		if (From.Receiving.IsEmpty() || Pairs.ContainsByPredicate([&](const FEndSkeletonCompatPair& Pair) {
				return !Pair.ReceivingSkeleton.IsNull() && SamePath(SoftPath(Pair.ReceivingSkeleton), From.Receiving);
			}))
		{
			continue;
		}
		FEndSkeletonCompatPair Pair;
		Pair.bEnabled = From.bEnabled;
		Pair.Method = From.Method;
		Pair.ReceivingSkeleton = TSoftObjectPtr<USkeleton>(FSoftObjectPath(From.Receiving));
		for (const FString& Skeleton : From.Animation)
		{
			Pair.AnimationSkeletons.Add(TSoftObjectPtr<USkeleton>(FSoftObjectPath(Skeleton)));
		}
		Pair.RequiresPaks = From.RequiresPaks;
		Pair.AdoptPaths = From.AdoptPaths;
		if (From.bHasFixHierarchy) { Pair.bFixHierarchy = From.bFixHierarchy; }
		if (From.bHasRepairLiveComponents) { Pair.bRepairLiveComponents = From.bRepairLiveComponents; }
		if (From.bHasCarrySockets) { Pair.bCarrySockets = From.bCarrySockets; }
		if (From.bHasKeepProportions) { Pair.bKeepProportions = From.bKeepProportions; }
		if (From.bHasProportionBones) { Pair.ProportionBones = From.ProportionBones; }   // (1.14)
		Pairs.Add(Pair);
		OutReport += FString::Printf(TEXT("Pair %d (%s, %s): added from the file\n"), Pairs.Num() - 1, *ShortName(From.Receiving), MethodLabel(From.Method));
		bChanged = true;
	}
	// Animation set rows, matched by character: what the file has and the row does not is added; a character this data
	// object has no row for gets the file's row.
	for (const FEndAnimSetRow& From : FileRows)
	{
		FEndAnimSetRow* Row = AnimationSets.FindByPredicate([&](const FEndAnimSetRow& Candidate) {
			return Candidate.Characters.ContainsByPredicate([&](const FString& Mine) {
				return From.Characters.ContainsByPredicate([&](const FString& Theirs) { return CharaSpecRowName(Mine).Equals(CharaSpecRowName(Theirs), ESearchCase::IgnoreCase); });
			});
		});
		if (!Row)
		{
			AnimationSets.Add(From);
			OutReport += FString::Printf(TEXT("Animation set row for %s: added from the file\n"), *ListText(From.Characters));
			bChanged = true;
			continue;
		}
		FString Changes;
		for (const TArray<FEndAnimSetSource>* List : {&From.Battle, &From.Field})
		{
			TArray<FEndAnimSetSource>& Ours = List == &From.Battle ? Row->Battle : Row->Field;
			for (const FEndAnimSetSource& Source : *List)
			{
				FEndAnimSetSource* Mine = Ours.FindByPredicate([&](const FEndAnimSetSource& Candidate) { return SamePath(Candidate.Path, Source.Path); });
				if (!Mine)
				{
					Ours.Add(Source);
					Changes += FString::Printf(TEXT(" %s source %s;"), List == &From.Battle ? TEXT("battle") : TEXT("field"), *Source.Path);
				}
				else if (Mine->AutoMatch == EEndAnimSetAutoMatch::Off && Source.AutoMatch != EEndAnimSetAutoMatch::Off)
				{
					Mine->AutoMatch = Source.AutoMatch;
					Mine->OnlyNamesWith = Source.OnlyNamesWith;
					Changes += FString::Printf(TEXT(" auto match for %s;"), *Source.Path);
				}
			}
		}
		FString Kept; // what the file has differently: the data object keeps its own (it is not a change)
		for (const FEndAnimSetMove& Move : From.Moves)
		{
			const FEndAnimSetMove* Mine = Row->Moves.FindByPredicate([&](const FEndAnimSetMove& Candidate) {
				return Candidate.Name.Equals(Move.Name, ESearchCase::IgnoreCase) && Candidate.Set.Equals(Move.Set, ESearchCase::IgnoreCase); });
			if (!Mine)
			{
				Row->Moves.Add(Move);
				Changes += TEXT(" move ") + Move.Name + TEXT(";");
			}
			else if (!SameMove(*Mine, Move))
			{
				Kept += TEXT(" move ") + Move.Name + TEXT(";");
			}
		}
		if (Row->FieldActions.TrimStartAndEnd().IsEmpty() && !From.FieldActions.IsEmpty())
		{
			Row->FieldActions = From.FieldActions;
			Changes += TEXT(" Field Actions ") + From.FieldActions + TEXT(";");
		}
		if (Row->Cutscene.IsNull() && !From.Cutscene.IsNull())
		{
			Row->Cutscene = From.Cutscene;
			Changes += TEXT(" Cutscene ") + ShortName(SoftPath(From.Cutscene)) + TEXT(";");
		}
		if (Row->CharacterSkeleton.IsNull() && !From.CharacterSkeleton.IsNull())
		{
			Row->CharacterSkeleton = From.CharacterSkeleton;
			Changes += TEXT(" Character Skeleton ") + ShortName(SoftPath(From.CharacterSkeleton)) + TEXT(";");
		}
		for (const FEndSocketStandIn& Socket : From.Sockets)
		{
			if (!Row->Sockets.ContainsByPredicate([&](const FEndSocketStandIn& Mine) { return Mine.Socket.Equals(Socket.Socket, ESearchCase::IgnoreCase); }))
			{
				Row->Sockets.Add(Socket);
				Changes += TEXT(" socket ") + Socket.Socket + TEXT(" -> ") + Socket.Use + TEXT(";");
			}
		}
		for (int32 Index = 0; Index < From.LimitBreaks.Num(); ++Index)
		{
			if (From.LimitBreaks[Index].Animation.IsEmpty() || (Row->LimitBreaks.IsValidIndex(Index) && !Row->LimitBreaks[Index].Animation.IsEmpty()))
			{
				continue;
			}
			if (Row->LimitBreaks.Num() <= Index) { Row->LimitBreaks.SetNum(Index + 1); }
			Row->LimitBreaks[Index] = From.LimitBreaks[Index];
			Changes += FString::Printf(TEXT(" limit break %d;"), Index + 1);
		}
		if (!Row->bKeepProportions && From.bKeepProportions)
		{
			Row->bKeepProportions = true;
			Changes += TEXT(" Keep Proportions on;");
		}
		if (!Row->bOverride && From.bOverride)
		{
			Row->bOverride = true;
			Changes += TEXT(" Override on;");
		}
		// 3.3: Player Parameter, the packs' abilities and Preload (what the data object already has wins).
		if (Row->PlayerParameter.TrimStartAndEnd().IsEmpty() && !From.PlayerParameter.IsEmpty())
		{
			Row->PlayerParameter = From.PlayerParameter;
			Changes += TEXT(" Player Parameter ") + From.PlayerParameter + TEXT(";");
		}
		for (const FEndPackAbilities& Pack : From.Abilities)
		{
			if (!Row->Abilities.ContainsByPredicate([&](const FEndPackAbilities& Mine) { return Mine.Pack.TrimStartAndEnd().Equals(Pack.Pack.TrimStartAndEnd(), ESearchCase::IgnoreCase); }))
			{
				Row->Abilities.Add(Pack);
				Changes += TEXT(" abilities of pack ") + Pack.Pack + TEXT(";");
			}
		}
		for (const FString& Path : From.Preload)
		{
			if (!Row->Preload.ContainsByPredicate([&](const FString& Mine) { return SamePath(Mine, Path); }))
			{
				Row->Preload.Add(Path);
				Changes += TEXT(" preload ") + ShortName(Path) + TEXT(";");
			}
		}
		for (const FString& Path : From.PackAssets)
		{
			if (!Row->PackAssets.ContainsByPredicate([&](const FString& Mine) { return SamePath(Mine, Path); }))
			{
				Row->PackAssets.Add(Path);
				Changes += TEXT(" pack asset ") + ShortName(Path) + TEXT(";");
			}
		}
		if (!From.bRefreshAbilities && Row->bRefreshAbilities)
		{
			Row->bRefreshAbilities = false;
			Changes += TEXT(" Refresh Abilities off;");
		}
		// 3.6: the forms (the data object's own win when it has some).
		if (Row->Forms.List.Num() == 0 && From.Forms.List.Num() > 0)
		{
			Row->Forms = From.Forms;
			Changes += FString::Printf(TEXT(" %d form(s);"), From.Forms.List.Num());
		}
		else if (From.Forms.List.Num() > 0 && Row->Forms.List.Num() != From.Forms.List.Num())
		{
			Kept += FString::Printf(TEXT(" Forms (%d; the file has %d);"), Row->Forms.List.Num(), From.Forms.List.Num());
		}
		// (1.14) a form of the data object takes the newer settings its namesake in the file has and it lacks
		for (FEndCharacterForm& Mine : Row->Forms.List)
		{
			const FEndCharacterForm* Theirs = From.Forms.List.FindByPredicate([&](const FEndCharacterForm& F) { return F.Name.TrimStartAndEnd().Equals(Mine.Name.TrimStartAndEnd(), ESearchCase::IgnoreCase); });
			if (!Theirs)
			{
				continue;
			}
			FString FormChanges;
			if (!Mine.bAsLook && Theirs->bAsLook) { Mine.bAsLook = true; FormChanges += TEXT(" As Look"); }
			if (Mine.Weapon.TrimStartAndEnd().IsEmpty() && !Theirs->Weapon.IsEmpty()) { Mine.Weapon = Theirs->Weapon; FormChanges += TEXT(" Weapon"); }
			if (Mine.Sets.Num() == 0 && Theirs->Sets.Num() > 0) { Mine.Sets = Theirs->Sets; FormChanges += TEXT(" Sets"); }
			if (Mine.Voice.TrimStartAndEnd().IsEmpty() && !Theirs->Voice.IsEmpty()) { Mine.Voice = Theirs->Voice; Mine.VoiceReplaces = Theirs->VoiceReplaces; FormChanges += TEXT(" Voice"); }
			if (Mine.CameraJson.TrimStartAndEnd().IsEmpty() && !Theirs->CameraJson.IsEmpty()) { Mine.CameraJson = Theirs->CameraJson; FormChanges += TEXT(" Camera"); }
			if (Mine.AbilityCamerasJson.TrimStartAndEnd().IsEmpty() && !Theirs->AbilityCamerasJson.IsEmpty()) { Mine.AbilityCamerasJson = Theirs->AbilityCamerasJson; FormChanges += TEXT(" Ability Cameras"); }
			if (Mine.EntranceJson.TrimStartAndEnd().IsEmpty() && !Theirs->EntranceJson.IsEmpty()) { Mine.EntranceJson = Theirs->EntranceJson; FormChanges += TEXT(" Entrance"); }
			if (Mine.ShooterJson.TrimStartAndEnd().IsEmpty() && !Theirs->ShooterJson.IsEmpty()) { Mine.ShooterJson = Theirs->ShooterJson; FormChanges += TEXT(" Shooter"); }
			if (!FormChanges.IsEmpty())
			{
				Changes += TEXT(" form ") + Mine.Name + TEXT(":") + FormChanges + TEXT(";");
			}
		}
		// (1.14) the newer row settings (the data object's own win)
		if (Row->Voice.TrimStartAndEnd().IsEmpty() && !From.Voice.IsEmpty())
		{
			Row->Voice = From.Voice;
			Row->VoiceReplaces = From.VoiceReplaces;
			Changes += TEXT(" Voice ") + ShortName(From.Voice) + TEXT(";");
		}
		if (Row->LooksFrom.TrimStartAndEnd().IsEmpty() && !From.LooksFrom.IsEmpty())
		{
			Row->LooksFrom = From.LooksFrom;
			Changes += TEXT(" Looks From ") + ShortName(From.LooksFrom) + TEXT(";");
		}
		if (Row->AnimBlueprintsFrom.IsNull() && !From.AnimBlueprintsFrom.IsNull())
		{
			Row->AnimBlueprintsFrom = From.AnimBlueprintsFrom;
			Changes += TEXT(" AnimBlueprints From ") + ShortName(SoftPath(From.AnimBlueprintsFrom)) + TEXT(";");
		}
		if (Row->CutsceneWeaponSocket.TrimStartAndEnd().IsEmpty() && !From.CutsceneWeaponSocket.IsEmpty())
		{
			Row->CutsceneWeaponSocket = From.CutsceneWeaponSocket;
			Changes += TEXT(" Cutscene Weapon Socket ") + From.CutsceneWeaponSocket + TEXT(";");
		}
		if (Row->ShooterJson.TrimStartAndEnd().IsEmpty() && !From.ShooterJson.IsEmpty())
		{
			Row->ShooterJson = From.ShooterJson;
			Changes += TEXT(" Shooter;");
		}
		if (Row->BuildFolder.TrimStartAndEnd().IsEmpty() && !From.BuildFolder.IsEmpty())
		{
			Row->BuildFolder = From.BuildFolder;
			Changes += TEXT(" Build Folder ") + From.BuildFolder + TEXT(";");
		}
		else if (!From.BuildFolder.IsEmpty() && !BuildFolderOf(*Row).Equals(BuildFolderOf(From), ESearchCase::IgnoreCase))
		{
			Kept += TEXT(" Build Folder ") + BuildFolderOf(*Row) + TEXT(" (the file has ") + BuildFolderOf(From) + TEXT(");");
		}
		if (Row->ShotEffects.MuzzleEffect.TrimStartAndEnd().IsEmpty() && Row->ShotEffects.SoundBank.TrimStartAndEnd().IsEmpty() &&
			(!From.ShotEffects.MuzzleEffect.IsEmpty() || !From.ShotEffects.SoundBank.IsEmpty()))
		{
			Row->ShotEffects = From.ShotEffects;
			Changes += TEXT(" Shot Effects;");
		}
		for (const FString& Name : From.MoreSetNames)
		{
			if (!Row->MoreSetNames.Contains(Name))
			{
				Row->MoreSetNames.Add(Name);
				Changes += TEXT(" set name ") + Name + TEXT(";");
			}
		}
		const TArray<FString> Requires = CleanList(Row->RequiresPaks, true);
		if (HasNamesMissingFrom(From.RequiresPaks, Requires))
		{
			TArray<FString> Merged = Requires;
			for (const FString& Name : From.RequiresPaks)
			{
				Merged.AddUnique(Name);
			}
			Row->RequiresPaks = Merged;
			Changes += TEXT(" Requires Paks ") + ListText(Merged) + TEXT(";");
		}
		OutReport += FString::Printf(TEXT("Animation set row for %s:%s\n"), *ListText(Row->Characters),
			!Changes.IsEmpty() ? *Changes : (Kept.IsEmpty() ? TEXT(" already matches the file") : TEXT(" nothing added")));
		if (!Kept.IsEmpty())
		{
			OutReport += TEXT("    kept as this data object has them, the file's differ:") + Kept +
						 TEXT("\n    (to take the file's: change them here by hand, or import into a new data object)\n");
		}
		bChanged |= !Changes.IsEmpty();
	}
	// Weapon swaps, matched by new weapon: the file's weapons, Requires Paks and skeletons this data object lacks are added.
	for (const FEndWeaponSwap& From : FileSwaps)
	{
		const FString FromNew = CharaSpecRowName(From.NewWeapon);
		FEndWeaponSwap* Swap = WeaponSwaps.FindByPredicate([&](const FEndWeaponSwap& Candidate) {
			return CharaSpecRowName(Candidate.NewWeapon).Equals(FromNew, ESearchCase::IgnoreCase);
		});
		if (!Swap)
		{
			WeaponSwaps.Add(From);
			OutReport += FString::Printf(TEXT("Weapon swap to %s: added from the file\n"), *FromNew);
			bChanged = true;
			continue;
		}
		FString Changes;
		for (const FString& Weapon : From.Weapons)
		{
			if (!CleanList(Swap->Weapons, false).Contains(Weapon))
			{
				Swap->Weapons.Add(Weapon);
				Changes += TEXT(" weapon ") + Weapon + TEXT(";");
			}
		}
		const TArray<FString> Requires = CleanList(Swap->RequiresPaks, true);
		if (HasNamesMissingFrom(From.RequiresPaks, Requires))
		{
			TArray<FString> Merged = Requires;
			for (const FString& Name : From.RequiresPaks)
			{
				Merged.AddUnique(Name);
			}
			Swap->RequiresPaks = Merged;
			Changes += TEXT(" Requires Paks ") + ListText(Merged) + TEXT(";");
		}
		if (Swap->WeaponSkeleton.IsNull() && !From.WeaponSkeleton.IsNull())
		{
			Swap->WeaponSkeleton = From.WeaponSkeleton;
			Changes += TEXT(" Weapon Skeleton ") + ShortName(SoftPath(From.WeaponSkeleton)) + TEXT(";");
		}
		if (Swap->NewWeaponSkeleton.IsNull() && !From.NewWeaponSkeleton.IsNull())
		{
			Swap->NewWeaponSkeleton = From.NewWeaponSkeleton;
			Changes += TEXT(" New Weapon Skeleton ") + ShortName(SoftPath(From.NewWeaponSkeleton)) + TEXT(";");
		}
		for (const FEndSocketStandIn& Socket : From.Sockets)
		{
			if (!Swap->Sockets.ContainsByPredicate([&](const FEndSocketStandIn& Mine) { return Mine.Socket.TrimStartAndEnd().Equals(Socket.Socket, ESearchCase::IgnoreCase); }))
			{
				Swap->Sockets.Add(Socket);
				Changes += TEXT(" socket ") + Socket.Socket + TEXT(" -> ") + Socket.Use + TEXT(";");
			}
		}
		OutReport += FString::Printf(TEXT("Weapon swap to %s:%s\n"), *FromNew, Changes.IsEmpty() ? TEXT(" already matches the file") : *Changes);
		bChanged |= !Changes.IsEmpty();
	}
	// Character swaps, matched by new character and replaced rows: the file's rows, Requires Paks and the settings this
	// data object leaves empty are added.
	for (const FEndCharacterSwap& From : FileCharacters)
	{
		FEndCharacterSwap* Swap = CharacterSwaps.FindByPredicate([&](const FEndCharacterSwap& Candidate) { return SameCharacterSwap(Candidate, From); });
		if (!Swap)
		{
			CharacterSwaps.Add(From);
			OutReport += FString::Printf(TEXT("Character swap %s -> %s: added from the file\n"), *ListText(From.Characters), *From.NewCharacter);
			bChanged = true;
			continue;
		}
		FString Changes;
		FString Kept;
		for (const FString& Character : From.Characters)
		{
			if (!CleanList(Swap->Characters, false).Contains(Character))
			{
				Swap->Characters.Add(Character);
				Changes += TEXT(" character ") + Character + TEXT(";");
			}
		}
		const TArray<FString> Requires = CleanList(Swap->RequiresPaks, true);
		if (HasNamesMissingFrom(From.RequiresPaks, Requires))
		{
			TArray<FString> Merged = Requires;
			for (const FString& Name : From.RequiresPaks)
			{
				Merged.AddUnique(Name);
			}
			Swap->RequiresPaks = Merged;
			Changes += TEXT(" Requires Paks ") + ListText(Merged) + TEXT(";");
		}
		const auto Take = [&](FString& Mine, const FString& Theirs, const TCHAR* Name)
		{
			if (Mine.TrimStartAndEnd().IsEmpty() && !Theirs.IsEmpty())
			{
				Mine = Theirs;
				Changes += FString::Printf(TEXT(" %s %s;"), Name, *Theirs);
			}
			else if (!Theirs.IsEmpty() && !Mine.TrimStartAndEnd().Equals(Theirs, ESearchCase::IgnoreCase))
			{
				Kept += FString::Printf(TEXT(" %s %s (the file has %s);"), Name, *Mine.TrimStartAndEnd(), *Theirs);
			}
		};
		Take(Swap->Voice, From.Voice, TEXT("Voice"));
		Take(Swap->WeaponSocket, From.WeaponSocket, TEXT("Weapon Socket"));
		if (Swap->Moveset != From.Moveset)
		{
			Kept += FString::Printf(TEXT(" Moveset %s (the file has %s);"), MovesetText(Swap->Moveset), MovesetText(From.Moveset));
		}
		if (Swap->bKeepProportions != From.bKeepProportions)
		{
			Kept += FString::Printf(TEXT(" Keep Proportions %s (the file has %s);"), Swap->bKeepProportions ? TEXT("on") : TEXT("off"), From.bKeepProportions ? TEXT("on") : TEXT("off"));
		}
		if (Swap->ReplacedSkeleton.IsNull() && !From.ReplacedSkeleton.IsNull())
		{
			Swap->ReplacedSkeleton = From.ReplacedSkeleton;
			Changes += TEXT(" Replaced Skeleton ") + ShortName(SoftPath(From.ReplacedSkeleton)) + TEXT(";");
		}
		if (Swap->NewSkeleton.IsNull() && !From.NewSkeleton.IsNull())
		{
			Swap->NewSkeleton = From.NewSkeleton;
			Changes += TEXT(" New Skeleton ") + ShortName(SoftPath(From.NewSkeleton)) + TEXT(";");
		}
		OutReport += FString::Printf(TEXT("Character swap to %s:%s\n"), *From.NewCharacter, Changes.IsEmpty() ? (Kept.IsEmpty() ? TEXT(" already matches the file") : TEXT(" nothing added")) : *Changes);
		if (!Kept.IsEmpty())
		{
			OutReport += TEXT("    kept as this data object has them, the file's differ:") + Kept + TEXT("\n");
		}
		bChanged |= !Changes.IsEmpty();
	}
	if (bChanged)
	{
		PostEditChange();
		MarkPackageDirty();
		OutReport += TEXT("\nSave this data object to keep the changes.\n");
	}
	return true;
}

bool UEndSkeletonCompatDataObject::ApplyPairsToSkeletons(bool bRemove, FString& OutReport)
{
	OutReport.Reset();
	TArray<UPackage*> Dirty;
	UClass* Carrier = FindOrCreateCarrier(!bRemove, Dirty, OutReport);
	if (!Carrier)
	{
		return bRemove;
	}
	// Several pairs may name the same receiving skeleton: one list per skeleton, merged like the mod merges JSON.
	// Only Mesh rebind pairs travel this way; skeletons left without one lose a list stamped earlier.
	struct FMerged
	{
		bool bEnabled = false;
		bool bAllMeshes = false;
		TArray<FSoftObjectPath> Animation;
		TArray<FSoftObjectPath> Meshes;
	};
	TArray<USkeleton*> Order;
	TMap<USkeleton*, FMerged> Merged;
	bool bOk = true;
	for (int32 Index = 0; Index < Pairs.Num(); ++Index)
	{
		const FEndSkeletonCompatPair& Pair = Pairs[Index];
		if (Pair.ReceivingSkeleton.IsNull())
		{
			continue;
		}
		if (Pair.Method == EEndSkelCompatMethod::Family)
		{
			if (bRemove || !Pair.bEnabled)
			{
				continue;
			}
			OutReport += FString::Printf(TEXT("Pair %d (%s): families reach the game only as JSON; use Export Json.\n"), Index, *ShortName(SoftPath(Pair.ReceivingSkeleton)));
			USkeleton* Hub = Pair.ReceivingSkeleton.LoadSynchronous();
			if (!bRegisterForEditorPreview || !Hub)
			{
				continue;
			}
			TArray<TSoftObjectPtr<USkeleton>> Members = Pair.AnimationSkeletons;
			Members.Append(Pair.MoreReceivingSkeletons);
			for (const TSoftObjectPtr<USkeleton>& Soft : Members)
			{
				USkeleton* Member = Soft.IsNull() ? nullptr : Soft.LoadSynchronous();
				if (!Member || Member == Hub)
				{
					continue;
				}
				FString ToHub, FromHub;
				const bool bOne = RegisterForEditorPreview(Hub, Member, ToHub);
				const bool bTwo = RegisterForEditorPreview(Member, Hub, FromHub);
				OutReport += FString::Printf(TEXT("    editor preview %s <-> %s: %s%s%s\n"), *Hub->GetName(), *Member->GetName(),
					bOne && bTwo ? TEXT("registered both ways") : (bOne || bTwo ? TEXT("registered one way") : TEXT("not registered")),
					ToHub.IsEmpty() ? TEXT("") : TEXT(" - "), *ToHub);
			}
			continue;
		}
		TArray<TSoftObjectPtr<USkeleton>> Receivers;
		Receivers.Add(Pair.ReceivingSkeleton);
		for (const TSoftObjectPtr<USkeleton>& Soft : Pair.MoreReceivingSkeletons)
		{
			if (!Soft.IsNull())
			{
				Receivers.AddUnique(Soft);
			}
		}
		for (const TSoftObjectPtr<USkeleton>& ReceivingSoft : Receivers)
		{
			USkeleton* Receiving = ReceivingSoft.LoadSynchronous();
			if (!Receiving)
			{
				OutReport += FString::Printf(TEXT("Pair %d: ERROR: %s not found\n"), Index, *ReceivingSoft.ToString());
				bOk = false;
				continue;
			}
			FMerged& Entry = Merged.FindOrAdd(Receiving);
			Order.AddUnique(Receiving);
			if (bRemove || !Pair.bEnabled)
			{
				continue;
			}
			if (Pair.Method != EEndSkelCompatMethod::Mesh)
			{
				OutReport += FString::Printf(TEXT("Pair %d (%s): Animations pairs reach the game only as JSON; use Export Json. Apply To Skeletons carries Mesh rebind pairs.\n"),
					Index, *Receiving->GetName());
				continue;
			}
			if (!Pair.bFixHierarchy)
			{
				OutReport += FString::Printf(TEXT("Pair %d: note: Fix Hierarchy off is not stored on the skeleton (the mod keeps it on); use Export Json to switch it off\n"), Index);
			}
			if (!Pair.bCarrySockets)
			{
				OutReport += FString::Printf(TEXT("Pair %d: note: Carry Sockets off is not stored on the skeleton (the mod keeps it on); use Export Json to switch it off\n"), Index);
			}
			Entry.bEnabled = true;
			for (const TSoftObjectPtr<USkeleton>& Soft : Pair.AnimationSkeletons)
			{
				if (!Soft.IsNull() && Soft.ToSoftObjectPath() != ReceivingSoft.ToSoftObjectPath())
				{
					Entry.Animation.AddUnique(Soft.ToSoftObjectPath());
				}
			}
			int32 Listed = 0;
			for (const TSoftObjectPtr<USkeletalMesh>& Soft : Pair.ReceivingMeshes)
			{
				if (!Soft.IsNull())
				{
					Entry.Meshes.AddUnique(Soft.ToSoftObjectPath());
					++Listed;
				}
			}
			Entry.bAllMeshes |= Listed == 0;
		}
	}

	for (USkeleton* Receiving : Order)
	{
		FMerged& Entry = Merged[Receiving];
		if (IsCookedAsset(Receiving))
		{
			if (Entry.bEnabled)
			{
				OutReport += FString::Printf(TEXT("%s: NOT changed. It is a cooked game asset, and saving it from the editor would replace it with an editor copy. Use Export Json, or make the receiving skeleton your own skeleton asset.\n"), *Receiving->GetName());
				bOk = false;
			}
			continue;
		}
		if (!Entry.bEnabled)
		{
			if (Receiving->GetAssetUserDataOfClass(Carrier))
			{
				Receiving->Modify();
				Receiving->RemoveUserDataOfClass(Carrier);
				Receiving->MarkPackageDirty();
				Dirty.AddUnique(Receiving->GetOutermost());
				OutReport += FString::Printf(TEXT("%s: list removed\n"), *Receiving->GetName());
			}
			continue;
		}
		if (Entry.Animation.Num() == 0)
		{
			OutReport += FString::Printf(TEXT("%s: ERROR: no animation skeleton\n"), *Receiving->GetName());
			bOk = false;
			continue;
		}
		if (Entry.bAllMeshes)
		{
			Entry.Meshes.Reset();
		}
		Receiving->Modify();
		UAssetUserData* Data = Receiving->GetAssetUserDataOfClass(Carrier);
		if (!Data)
		{
			Data = NewObject<UAssetUserData>(Receiving, Carrier, NAME_None, RF_Transactional);
			Receiving->AddAssetUserData(Data);
		}
		Data->Modify();
		if (!SetPathArray(Data, AnimationSkeletonsVariable, Entry.Animation) || !SetPathArray(Data, ReceivingMeshesVariable, Entry.Meshes))
		{
			OutReport += FString::Printf(TEXT("%s: ERROR: %s has unexpected variables\n"), *Receiving->GetName(), CarrierName);
			bOk = false;
			continue;
		}
		Receiving->MarkPackageDirty();
		Dirty.AddUnique(Receiving->GetOutermost());
		OutReport += FString::Printf(TEXT("%s: lists %d animation skeleton(s), %s\n"), *Receiving->GetName(), Entry.Animation.Num(),
			Entry.Meshes.Num() ? *FString::Printf(TEXT("%d mesh(es)"), Entry.Meshes.Num()) : TEXT("all its meshes"));
		if (bRegisterForEditorPreview)
		{
			for (const FSoftObjectPath& Path : Entry.Animation)
			{
				FString Diagnostic;
				USkeleton* AnimationSkeleton = Cast<USkeleton>(Path.TryLoad());
				const bool bRegistered = AnimationSkeleton && RegisterForEditorPreview(Receiving, AnimationSkeleton, Diagnostic);
				OutReport += FString::Printf(TEXT("    editor preview with %s: %s%s%s\n"), *Path.GetAssetName(),
					bRegistered ? TEXT("registered") : TEXT("not registered"), Diagnostic.IsEmpty() ? TEXT("") : TEXT(" - "), *Diagnostic);
			}
		}
	}
	if (Dirty.Num() > 0)
	{
		FEditorFileUtils::PromptForCheckoutAndSave(Dirty, false, true);
		OutReport += TEXT("\nSave the changed packages (you were prompted), then cook and pak them with your mod. ")
			TEXT("BP_SkelCompatUserData cooks along with the skeleton; the game reads the list from it.\n");
	}
	return bOk;
}

bool UEndSkeletonCompatDataObject::ApplyRowsToCharaSpec(FString& OutReport)
{
	OutReport.Reset();
	const FCharaSpecTable Table(CharaSpecTable);
	if (!Table.bAvailable)
	{
		OutReport += TEXT("The Rebirth data object tools (Rebirth Cooked Asset Preview plugin) are not loaded, so the CharaSpec table cannot be edited here.\n");
		return false;
	}
	if (Table.Rows.Num() == 0)
	{
		OutReport += Table.Package + TEXT(" has no rows. Set CharaSpec Table (Advanced) to your project's editable CharaSpec.\n");
		return false;
	}
	bool bOk = true;
	bool bChanged = false;
	TSet<FString> Handled; // rows a swap writes (Fix Pack Models leaves them to it)
	const auto Set = [&](const FString& Row, const TCHAR* Field, const FString& Value, const FString& Why) {
		FString Message;
		if (Table.SetField(Row, Field, Value, Message))
		{
			OutReport += FString::Printf(TEXT("%s: %s = %s (%s)\n"), *Row, Field, *Value, *Why);
			bChanged = true;
		}
		else
		{
			OutReport += FString::Printf(TEXT("%s: ERROR: %s not set: %s\n"), *Row, Field, *Message);
			bOk = false;
		}
	};
	// A row's changes from a swap; a Shared CharaSpec List that would make specs load each other in a loop is left out.
	const auto Write = [&](const FString& Row, const TArray<FFieldChange>& Changes, const FString& Why) {
		for (const FFieldChange& Change : Changes)
		{
			if (FCString::Strcmp(Change.Field, TEXT("SharedCharaSpecList_Array")) == 0)
			{
				TMap<FString, TArray<FString>> One;
				One.Add(Row, NamesInText(Change.Value));
				const TArray<FString> Loops = SharedLoops(Table, One);
				if (Loops.Num() > 0)
				{
					OutReport += FString::Printf(TEXT("%s: ERROR: SharedCharaSpecList_Array left as it is: %s would load each other in a loop (%s)\n"), *Row,
						*FieldShown(Change.Field, Change.Value), *Loops[0]);
					bOk = false;
					continue;
				}
			}
			Set(Row, Change.Field, Change.Value, Why + TEXT(", was ") + FieldShown(Change.Field, Change.Current));
		}
	};

	// 1. The swaps' packs (Apply To Packs): the blueprint they spawn, a character's voice, a weapon's effects.
	TArray<UPackage*> DirtyPacks;
	TSet<FString> FailedPacks; // their rows are left alone: they would describe what the pack does not spawn
	TArray<FCharacterSwapPlan> CharacterPlans;
	for (const FEndCharacterSwap& Swap : CharacterSwaps)
	{
		CharacterPlans.Add(Swap.bEnabled ? PlanCharacterSwap(Swap, Table, true, bApplyToPacks) : FCharacterSwapPlan());
		for (const FCharacterRowPlan& Row : CharacterPlans.Last().Rows)
		{
			if (Row.Problem.IsEmpty() && Row.Pack.bInProject && Row.Edit.HasWork() && !ApplyPackEdit(Row.Row, Row.Edit, DirtyPacks, OutReport))
			{
				FailedPacks.Add(Row.Row);
				bOk = false;
			}
		}
	}
	TArray<FWeaponSwapPlan> WeaponPlans;
	for (const FEndWeaponSwap& Swap : WeaponSwaps)
	{
		WeaponPlans.Add(Swap.bEnabled ? PlanWeaponSwap(Swap, Table, true, bApplyToPacks) : FWeaponSwapPlan());
		for (const FWeaponRowPlan& Row : WeaponPlans.Last().Rows)
		{
			if (!LeftOut(Row) && Row.Pack.bInProject && Row.Edit.HasWork() && !ApplyPackEdit(Row.Row, Row.Edit, DirtyPacks, OutReport))
			{
				FailedPacks.Add(Row.Row);
				bOk = false;
			}
		}
	}
	if (DirtyPacks.Num() > 0)
	{
		if (FEditorFileUtils::PromptForCheckoutAndSave(DirtyPacks, false, false) == FEditorFileUtils::PR_Success)
		{
			OutReport += FString::Printf(TEXT("Saved %d pack(s). Cook them with your mod.\n\n"), DirtyPacks.Num());
		}
		else
		{
			OutReport += TEXT("ERROR: the changed packs were not all saved (save them by hand)\n\n");
			bOk = false;
		}
	}

	// 2. Animation set rows: field actions and references to rows that are not in the table.
	for (int32 Index = 0; Index < AnimationSets.Num(); ++Index)
	{
		const FEndAnimSetRow& Row = AnimationSets[Index];
		if (!Row.bEnabled)
		{
			continue;
		}
		const FString Folder = Row.FieldActions.TrimStartAndEnd();
		for (const FString& Character : CleanList(Row.Characters, false))
		{
			const FString Name = CharaSpecRowName(Character);
			if (Name.IsEmpty() || !Table.Has(Name))
			{
				OutReport += FString::Printf(TEXT("Row %d: %s is not a row of %s\n"), Index, *Character, *Table.Package);
				bOk = false;
				continue;
			}
			if (!Folder.IsEmpty())
			{
				const FString Current = Table.Field(Name, TEXT("AnimationSetParentFolder"));
				if (Current.Equals(Folder, ESearchCase::IgnoreCase))
				{
					OutReport += FString::Printf(TEXT("%s: AnimationSetParentFolder is already %s\n"), *Name, *Folder);
				}
				else
				{
					Set(Name, TEXT("AnimationSetParentFolder"), Folder, TEXT("field actions, was ") + (Current.IsEmpty() ? FString(TEXT("empty")) : Current));
				}
			}
			if (bFixMissingRowReferences)
			{
				for (const TCHAR* Field : {TEXT("NoBattleCharaSpec"), TEXT("ReserveCharaSpec")})
				{
					const FString Current = Table.Field(Name, Field);
					if (!Current.IsEmpty() && !Current.Equals(TEXT("None"), ESearchCase::IgnoreCase) && !Table.Has(Current))
					{
						Set(Name, Field, Name, Current + TEXT(" is not in the table"));
					}
				}
			}
		}
	}

	// 3. Character swaps: each replaced row describes what its pack spawns and loads. A row whose pack is the game's own,
	// or still spawns someone else, is left alone: describing a character the pack does not spawn keeps the game loading.
	for (int32 Index = 0; Index < CharacterSwaps.Num(); ++Index)
	{
		if (!CharacterSwaps[Index].bEnabled)
		{
			continue;
		}
		const FCharacterSwapPlan& Plan = CharacterPlans[Index];
		if (!Plan.Error.IsEmpty())
		{
			OutReport += FString::Printf(TEXT("Character swap %d: ERROR: %s\n"), Index, *Plan.Error);
			bOk = false;
			continue;
		}
		for (const FString& Item : Plan.Unknown)
		{
			OutReport += FString::Printf(TEXT("Character swap %d: %s names no row of %s\n"), Index, *Item, *Table.Package);
		}
		if (Plan.Rows.Num() == 0)
		{
			OutReport += FString::Printf(TEXT("Character swap %d: ERROR: no rows to replace\n"), Index);
			bOk = false;
		}
		if (!Plan.NewSpecNote.IsEmpty())
		{
			OutReport += FString::Printf(TEXT("Character swap %d: note: %s\n"), Index, *Plan.NewSpecNote);
		}
		for (const FCharacterRowPlan& Row : Plan.Rows)
		{
			if (LeftOut(Row))
			{
				OutReport += FString::Printf(TEXT("%s: left out (its pack is the game's own, so it stays the old character)\n"), *Row.Row);
				continue;
			}
			for (const FString& Note : Row.Notes)
			{
				OutReport += FString::Printf(TEXT("%s: note: %s\n"), *Row.Row, *Note);
			}
			if (!Row.Problem.IsEmpty() || FailedPacks.Contains(Row.Row))
			{
				OutReport += FString::Printf(TEXT("%s: NOT changed: %s\n"), *Row.Row, Row.Problem.IsEmpty() ? TEXT("its pack could not be changed (above)") : *Row.Problem);
				bOk = false;
				continue;
			}
			Handled.Add(Row.Row);
			if (Row.Changes.Num() == 0)
			{
				OutReport += FString::Printf(TEXT("%s: already describes %s\n"), *Row.Row, *ListText(Row.After.Blueprints));
				continue;
			}
			Write(Row.Row, Row.Changes, TEXT("character swap to ") + Plan.NewCharacter);
		}
	}

	// 4. Weapon swaps: each replaced weapon's row describes the weapon its pack spawns. A row whose pack still spawns the old
	// weapon (or is the game's own) is left alone: describing a weapon the pack does not spawn is the same mismatch.
	for (int32 Index = 0; Index < WeaponSwaps.Num(); ++Index)
	{
		if (!WeaponSwaps[Index].bEnabled)
		{
			continue;
		}
		const FWeaponSwapPlan& Plan = WeaponPlans[Index];
		if (!Plan.Error.IsEmpty())
		{
			OutReport += FString::Printf(TEXT("Weapon swap %d: ERROR: %s\n"), Index, *Plan.Error);
			bOk = false;
			continue;
		}
		for (const FString& Item : Plan.Unknown)
		{
			OutReport += FString::Printf(TEXT("Weapon swap %d: %s names no row of %s\n"), Index, *Item, *Table.Package);
		}
		if (Plan.Rows.Num() == 0)
		{
			OutReport += FString::Printf(TEXT("Weapon swap %d: ERROR: no weapon rows to replace\n"), Index);
			bOk = false;
		}
		for (const FWeaponRowPlan& Row : Plan.Rows)
		{
			if (LeftOut(Row))
			{
				OutReport += FString::Printf(TEXT("%s: left out (its pack is the game's own, so it stays the old weapon)\n"), *Row.Row);
				continue;
			}
			for (const FString& Note : Row.Notes)
			{
				OutReport += FString::Printf(TEXT("%s: note: %s\n"), *Row.Row, *Note);
			}
			const FString Problem = FailedPacks.Contains(Row.Row) ? FString(TEXT("its pack could not be changed (above)")) : WeaponRowProblem(Row, Plan.NewWeapon);
			if (!Problem.IsEmpty())
			{
				OutReport += FString::Printf(TEXT("%s: NOT changed: %s\n"), *Row.Row, *Problem);
				bOk = false;
				continue;
			}
			Handled.Add(Row.Row);
			if (Row.Changes.Num() == 0)
			{
				OutReport += FString::Printf(TEXT("%s: already describes %s\n"), *Row.Row, *Plan.NewWeapon);
				continue;
			}
			Write(Row.Row, Row.Changes, TEXT("weapon swap to ") + Plan.NewWeapon);
		}
	}

	// 5. Fix Pack Models: every other pack of this project gets a row whose model is the blueprint it spawns.
	if (bFixPackModels)
	{
		for (const FPackCheck& Check : CheckProjectPacks(Table))
		{
			if (Check.Spawns.IsEmpty() || Check.Spawns.Equals(Check.Model, ESearchCase::IgnoreCase) || Handled.Contains(Check.Row))
			{
				continue;
			}
			if (!Table.Has(Check.Spawns))
			{
				OutReport += FString::Printf(TEXT("%s: note: its pack spawns %s, which is not a row of the table, so its model is left as %s\n"), *Check.Row, *Check.Spawns, *Check.Model);
				continue;
			}
			Set(Check.Row, TEXT("ContentsModel"), Check.Spawns, TEXT("Fix Pack Models: the blueprint its pack spawns, was ") + Check.Model);
		}
	}

	if (bChanged)
	{
		FString Message;
		if (Table.Save(Message))
		{
			OutReport += TEXT("\nSaved ") + Table.Package + TEXT(". Cook it with your mod (it replaces the game's CharaSpec).\n");
		}
		else
		{
			OutReport += TEXT("\nERROR: ") + Table.Package + TEXT(" not saved: ") + Message + TEXT("\n");
			bOk = false;
		}
	}
	else if (bOk && DirtyPacks.Num() == 0)
	{
		OutReport += TEXT("\nNothing to change.\n");
	}
	if (CharacterSwaps.ContainsByPredicate([](const FEndCharacterSwap& Swap) { return Swap.bEnabled; }) ||
		WeaponSwaps.ContainsByPredicate([](const FEndWeaponSwap& Swap) { return Swap.bEnabled && Swap.Sockets.Num() > 0; }))
	{
		OutReport += TEXT("Press Export Json too: the swaps' families, moves and socket stand-ins reach the game through it.\n");
	}
	return bOk;
}

void UEndSkeletonCompatDataObject::ApplyToCharaSpec()
{
	FString Report;
	const bool bOk = ApplyRowsToCharaSpec(Report);
	ShowResult(TEXT("Apply To CharaSpec"), Report, bOk);
}

void UEndSkeletonCompatDataObject::ShowResult(const FString& Title, const FString& Report, bool bOk)
{
	LastResult = Title + (bOk ? TEXT(": OK\n\n") : TEXT(": PROBLEMS\n\n")) + Report;
	UE_LOG(LogRebirthSkelCompat, Log, TEXT("%s"), *LastResult);
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(LastResult.Left(6000)));
}

void UEndSkeletonCompatDataObject::Validate()
{
	FString Report;
	const bool bOk = ValidatePairs(Report);
	ShowResult(TEXT("Validate"), Report, bOk);
}

void UEndSkeletonCompatDataObject::ApplyToSkeletons()
{
	FString Report;
	bool bOk = true;
	if (Pairs.Num() > 0)
	{
		bOk = ApplyPairsToSkeletons(false, Report);
	}
	else
	{
		Report += TEXT("No skeleton compatibility pairs.\n");
	}
	// The CharaSpec part (field actions, weapon rows) cooks with the pak too, so it is applied here as well.
	if (HasCharaSpecWork(AnimationSets, WeaponSwaps, CharacterSwaps, bFixMissingRowReferences))
	{
		FString Rows;
		bOk &= ApplyRowsToCharaSpec(Rows);
		Report += TEXT("\nCharaSpec table (Apply To CharaSpec):\n") + Rows;
	}
	if (WeaponSwaps.ContainsByPredicate([](const FEndWeaponSwap& Swap) { return Swap.bEnabled && Swap.bCutsceneFamily; }) ||
		CharacterSwaps.ContainsByPredicate([](const FEndCharacterSwap& Swap) { return Swap.bEnabled; }) ||
		Pairs.ContainsByPredicate([](const FEndSkeletonCompatPair& Pair) { return Pair.bEnabled && Pair.Method != EEndSkelCompatMethod::Mesh; }))
	{
		Report += TEXT("\nFamilies, Animations pairs and the swaps' families and moves reach the game through Export Json.\n");
	}
	ShowResult(TEXT("Apply To Skeletons"), Report, bOk);
}

void UEndSkeletonCompatDataObject::RemoveFromSkeletons()
{
	FString Report;
	const bool bOk = ApplyPairsToSkeletons(true, Report);
	ShowResult(TEXT("Remove From Skeletons"), Report, bOk);
}

void UEndSkeletonCompatDataObject::ExportJson()
{
	FString Report;
	const bool bOk = WriteRuntimeJson(Report);
	ShowResult(TEXT("Export Json"), Report, bOk);
}

void UEndSkeletonCompatDataObject::ImportFromGameJson()
{
	FString Report;
	const bool bOk = ImportRuntimeJson(Report);
	ShowResult(TEXT("Import From Game Json"), Report, bOk);
}

bool UEndSkeletonCompatDataObject::BuildMoveAnimations(FString& OutReport)
{
	return BuildMovesWhere([](int32, const FEndAnimSetMove&) { return true; }, OutReport);
}

bool UEndSkeletonCompatDataObject::BuildOneMove(int32 RowIndex, const FString& Name, const FString& Set, FString& OutReport)
{
	if (!AnimationSets.IsValidIndex(RowIndex))
	{
		OutReport = FString::Printf(TEXT("ERROR: this data object has no animation set row %d\n"), RowIndex);
		return false;
	}
	const FString WantName = Name.TrimStartAndEnd();
	const FString WantSet = Set.TrimStartAndEnd();
	const bool bOk = BuildMovesWhere([&](int32 Row, const FEndAnimSetMove& Move)
	{
		return Row == RowIndex && Move.Name.TrimStartAndEnd().Equals(WantName, ESearchCase::IgnoreCase) &&
			   Move.Set.TrimStartAndEnd().Equals(WantSet, ESearchCase::IgnoreCase);
	}, OutReport);
	// (scripts: the report as Last Result, as Python returns only the return value of this call)
	LastResult = OutReport;
	return bOk;
}

bool UEndSkeletonCompatDataObject::BuildMovesWhere(TFunctionRef<bool(int32, const FEndAnimSetMove&)> Pick, FString& OutReport)
{
	OutReport.Reset();
	bool bOk = true;
	int32 Asked = 0;
	int32 Built = 0;
	TArray<UPackage*> ToSave;
	TArray<UAnimSequence*> BuiltSequences;
	TMap<FString, TArray<UObject*>> ByFolder;
	for (int32 RowIndex = 0; RowIndex < AnimationSets.Num(); ++RowIndex)
	{
		const FEndAnimSetRow& Row = AnimationSets[RowIndex];
		if (!Row.bEnabled)
		{
			continue;
		}
		int32 RowMoves = 0;
		for (const FEndAnimSetMove& Move : Row.Moves)
		{
			RowMoves += Move.bBuild && Pick(RowIndex, Move) ? 1 : 0;
		}
		if (RowMoves == 0)
		{
			continue;
		}
		// A folder the project never cooks would build animations that are never packaged.
		const FString NeverCook = NeverCookDirectoryOf(BuildFolderOf(Row));
		if (!NeverCook.IsEmpty())
		{
			Asked += RowMoves;
			OutReport += FString::Printf(TEXT("ERROR: %d move(s) not built: Build Folder %s is in %s, which Project Settings > Packaging > Directories To Never Cook lists, ")
										 TEXT("so they would never be packaged. Set Build Folder outside it (for example /Game/RebirthSkelCompat/Built/<Character>).\n"),
				RowMoves, *BuildFolderOf(Row), *NeverCook);
			bOk = false;
			continue;
		}
		// The skeleton the moves are built on: the character's own (an animation of another skeleton is put on it).
		USkeleton* CharacterSkeleton = Row.CharacterSkeleton.IsNull() ? nullptr : Row.CharacterSkeleton.LoadSynchronous();
		if (!Row.CharacterSkeleton.IsNull() && !CharacterSkeleton)
		{
			OutReport += FString::Printf(TEXT("ERROR: %d move(s) not built: Character Skeleton %s does not load\n"), RowMoves, *SoftPath(Row.CharacterSkeleton));
			Asked += RowMoves;
			bOk = false;
			continue;
		}
		for (const FEndAnimSetMove& Move : Row.Moves)
		{
			if (!Move.bBuild || !Pick(RowIndex, Move))
			{
				continue;
			}
			++Asked;
			const FString Name = Move.Name.TrimStartAndEnd();
			const FString Label = (Move.Set.TrimStartAndEnd().IsEmpty() ? FString() : Move.Set.TrimStartAndEnd() + TEXT("/")) + Name;
			const FString SourcePath = Move.Animation.TrimStartAndEnd();
			UAnimSequence* Source = SourcePath.IsEmpty() ? nullptr : Cast<UAnimSequence>(FSoftObjectPath(NormalizedObjectPath(SourcePath)).TryLoad());
			if (Name.IsEmpty() || !Source)
			{
				OutReport += FString::Printf(TEXT("%s: ERROR: %s\n"), *Label,
					Name.IsEmpty() ? TEXT("the move has no Name") : *(TEXT("Animation ") + SourcePath + TEXT(" is not an Anim Sequence that loads in this editor")));
				bOk = false;
				continue;
			}
			USkeleton* Target = CharacterSkeleton ? CharacterSkeleton : Source->GetSkeleton();
			// 3.6: a move of a form that wears another model is built on that model's skeleton. A model of the game's that is
			// not in this project (only its skeleton and animations are): the move is built on its animation's skeleton,
			// which is the model's when the animation is one of the model's own (1.12: or on its Base's, an animation of the
			// model's own under a move made of another skeleton's animation).
			FString FormModel;
			FString ModelNote;
			if (USkeleton* FormSkeleton = FormModelSkeleton(Row, Move.Set, &FormModel))
			{
				Target = FormSkeleton;
			}
			else if (!FormModel.IsEmpty())
			{
				USkeleton* BaseSkeleton = BaseSkeletonOf(Move);
				Target = BaseSkeleton ? BaseSkeleton : Source->GetSkeleton();
				ModelNote = FString::Printf(TEXT("; the form's model %s is not in this project, so it is built on its %s's skeleton %s (use an animation of the model's own)"),
					*ShortName(FormModel), BaseSkeleton ? TEXT("Base") : TEXT("animation"), Target ? *Target->GetName() : TEXT("?"));
			}
			FString NotifyPath;
			UAnimSequenceBase* From = FindNotifySource(Row, Move, NotifyPath);
			const bool bHitsNameDamage = Move.Hits.ContainsByPredicate([](const FEndMoveHit& Hit) { return !Hit.DamageSourceID.TrimStartAndEnd().IsEmpty(); });
			if (!From && !bHitsNameDamage)
			{
				OutReport += FString::Printf(TEXT("%s: ERROR: no animation to take the gameplay notifies from (%s is not in this project). Set Notifies From to a move of the character that hits the way this one should, or give each hit a Damage Source ID\n"),
					*Label, *NotifyPath);
				bOk = false;
				continue;
			}
			const FString Package = BuiltPackageOf(Row, Move);
			if (!FPackageName::IsValidLongPackageName(Package))
			{
				OutReport += FString::Printf(TEXT("%s: ERROR: %s is not in a content folder (Build Folder must start with /Game/ or a plugin's folder)\n"), *Label, *Package);
				bOk = false;
				continue;
			}
			// An earlier build is made anew, without loading it or deleting it as an asset (see ReplaceEarlierAsset).
			FString Why;
			if (ReplaceEarlierAsset(Package, Name, UAnimSequence::StaticClass(), Why) == EEarlierAsset::Refused)
			{
				OutReport += FString::Printf(TEXT("%s: ERROR: %s %s, so it is not replaced; choose another Build Folder\n"), *Label, *Package, *Why);
				bOk = false;
				continue;
			}
			// Made new, not duplicated (duplicating an Anim Sequence crashes this engine), and not put in the undo history
			// (undoing it would read it back the same broken way). An animation of another skeleton, or one of the game's
			// (only compressed data in this project), is sampled onto the character's skeleton.
			FString Error;
			FBakeResult Bake;
			// (1.12) the character's own animation under the move
			UAnimSequence* Base = nullptr;
			const FString BasePath = Move.Base.TrimStartAndEnd();
			if (!BasePath.IsEmpty())
			{
				Base = Cast<UAnimSequence>(FSoftObjectPath(NormalizedObjectPath(BasePath)).TryLoad());
				if (!Base)
				{
					OutReport += FString::Printf(TEXT("%s: ERROR: its Base %s is not an Anim Sequence that loads in this editor\n"), *Label, *BasePath);
					bOk = false;
					continue;
				}
			}
			// (1.12) the pose of the animation's skeleton its motion is taken from ("Keep the character's own pose" with a Base)
			UAnimSequence* MotionFrom = nullptr;
			const FString MotionFromPath = Move.MotionFrom.TrimStartAndEnd();
			if (!MotionFromPath.IsEmpty() && Base && Move.Retarget == EEndMoveRetarget::Motion)
			{
				MotionFrom = Cast<UAnimSequence>(FSoftObjectPath(NormalizedObjectPath(MotionFromPath)).TryLoad());
				if (!MotionFrom)
				{
					OutReport += FString::Printf(TEXT("%s: ERROR: its Motion From %s is not an Anim Sequence that loads in this editor\n"), *Label, *MotionFromPath);
					bOk = false;
					continue;
				}
			}
			const bool bClipped = Move.ClipStart > 0.f || Move.ClipEnd > 0.f || !FMath::IsNearlyEqual(Move.Speed, 1.f, 0.0005f);
			if (Move.Retarget == EEndMoveRetarget::Lean && !Base)
			{
				OutReport += FString::Printf(TEXT("%s: ERROR: Retarget \"leaning into the animation's root motion\" needs a Base (the character's own idle)\n"), *Label);
				bOk = false;
				continue;
			}
			// (1.12.1) the form's model turned and lifted in its moves
			const FEndCharacterForm* MoveForm = FormOfPack(Row, Move.Set);
			const float ModelTurn = MoveForm ? MoveForm->ModelTurn : 0.f;
			const float ModelLift = MoveForm ? MoveForm->ModelLift : 0.f;
			const bool bStand = !FMath::IsNearlyZero(ModelTurn) || !FMath::IsNearlyZero(ModelLift);
			// (1.12.2) a form's model at a size of its own moves by its root's motion times that size: its moves' root
			// motion (a person's walks and runs, over the model's own idle) goes that much farther
			const float MotionScale = MoveForm && MoveForm->Scale > KINDA_SMALL_NUMBER ? 1.f / MoveForm->Scale : 1.f;
			const bool bSample = Target != Source->GetSkeleton() || IsCookedAsset(Source) || Source->GetRawAnimationData().Num() == 0 || bClipped || Base ||
								 Move.Retarget == EEndMoveRetarget::Motion || Move.Retarget == EEndMoveRetarget::Lean || bStand;
			UAnimSequence* Sequence = bSample ? MakeAnimationBySampling(Source, Target, Package, Name, Move.Retarget, Move.bKeepSourceEffects, Bake, Error,
													Move.ClipStart, Move.ClipEnd, Move.Speed, Base, Move.bBaseLoop, MotionFrom, Move.LeanBone, Move.Lean,
													ModelTurn, ModelLift, MotionScale, Move.BoneMap, Move.SourceTurn, Move.bKeepBaseRoot,
													Move.bKeepSourceEffects && Move.bSourceSoundsOnly)
											  : MakeAnimationFrom(Source, Package, Name, Error, Bake.EffectParameters, Bake.NotifiesLeftOut);
			if (!Sequence)
			{
				OutReport += FString::Printf(TEXT("%s: ERROR: %s could not be made: %s\n"), *Label, *Package, *Error);
				bOk = false;
				continue;
			}
			FString Notes = ModelNote;
			if (CleanList(Move.ThenPlay, false).Num() > 0)
			{
				Notes += TEXT("; Then Play is not built (only Animation)");
			}
			const FBuildResult Result = BuildNotifies(Sequence, From, Move, Row.ShotEffects, Notes);
			CopyPlaySettings(From ? From : static_cast<UAnimSequenceBase*>(Source), Sequence);
			Sequence->RefreshCacheData();
			Sequence->PostEditChange();
			// Compressed now, so the report can say which codec it got: the game decompresses with GameBoneCodec only.
			Sequence->RequestSyncAnimRecompression(false);
			const UAnimBoneCompressionCodec* Codec = Sequence->CompressedData.BoneCompressionCodec;
			const FString CodecName = Codec ? Codec->GetCodecDDCHandle() : FString(TEXT("no codec"));
			if (!CodecName.Equals(GameBoneCodec, ESearchCase::IgnoreCase))
			{
				Notes += FString::Printf(TEXT("; ERROR: compressed with %s, but the game reads it with %s (it would not play right; ACL's safety fallback, which editor 1.11.1 turns off)"), *CodecName, GameBoneCodec);
				bOk = false;
			}
			Sequence->MarkPackageDirty();
			ToSave.AddUnique(Sequence->GetOutermost());
			BuiltSequences.Add(Sequence);
			ByFolder.FindOrAdd(BuildFolderOf(Row)).Add(Sequence);
			++Built;
			OutReport += FString::Printf(TEXT("%s: built %s from %s (%.2f s)"), *Label, *Package, *Source->GetName(), Sequence->SequenceLength);
			if (bClipped)
			{
				OutReport += FString::Printf(TEXT(", its %.2f - %.2f s at %.2fx"), Move.ClipStart, Move.ClipEnd > 0.f ? Move.ClipEnd : Source->SequenceLength, Move.Speed);
			}
			if (bSample)
			{
				OutReport += Bake.bRetargeted
					? FString::Printf(TEXT(", put on %s from %s (%s; %d bone(s), %d the character lacks left out, %d curve(s))"), *Target->GetName(), *Source->GetSkeleton()->GetName(),
						  RetargetText(Move.Retarget), Bake.Bones, Bake.Dropped, Bake.Curves)
					: FString::Printf(TEXT(", sampled from the game animation (%d bone(s), %d curve(s))"), Bake.Bones, Bake.Curves);
				if (Move.Retarget == EEndMoveRetarget::Motion && !Move.BoneMap.TrimStartAndEnd().IsEmpty())
				{
					OutReport += FString::Printf(TEXT(", its Bone Map's %d bone(s)%s%s, its curves left out"), Bake.Bones,
						Bake.MappedAnchor.IsNone() ? TEXT("") : *FString::Printf(TEXT(" (relative to %s)"), *Bake.MappedAnchor.ToString()),
						FMath::IsNearlyZero(Move.SourceTurn) ? TEXT("") : *FString::Printf(TEXT(", its skeleton turned %.0f degrees"), Move.SourceTurn));
				}
				if (Base)
				{
					OutReport += FString::Printf(TEXT(", over %s (%d bone(s) only it moves)"), *Base->GetName(), Bake.BaseBones);
					if (Move.Retarget == EEndMoveRetarget::Motion)
					{
						OutReport += MotionFrom ? FString::Printf(TEXT(", its motion from %s's first frame"), *MotionFrom->GetName())
												: FString(TEXT(", its motion from its own first frame (no Motion From)"));
					}
					if (Move.bKeepBaseRoot)
					{
						OutReport += TEXT(", where Base puts it (no root motion)");
					}
					else if (Move.Retarget == EEndMoveRetarget::Lean)
					{
						OutReport += FString::Printf(TEXT(", %s leaning up to %.1f degrees and turning up to %.1f into its turns"), *Bake.LeanBone.ToString(), Bake.MostLean, Bake.MostTwist);
					}
					if (Move.bBaseLoop)
					{
						OutReport += FString::Printf(TEXT(", a loop of %.2f s with the animation %d time(s)"), Sequence->SequenceLength, Bake.Loops);
					}
					if (Bake.RootMotionScale > 0.f)
					{
						OutReport += FString::Printf(TEXT(", moving the character as %s's root does%s"), *Source->GetName(),
							FMath::IsNearlyEqual(Bake.RootMotionScale, 1.f) ? TEXT("") : *FString::Printf(TEXT(" (%.2f times as far: the form's model is at %.2f)"), Bake.RootMotionScale, 1.f / Bake.RootMotionScale));
					}
				}
				if (bStand)
				{
					OutReport += FString::Printf(TEXT(", the model turned %.0f degrees and lifted %.0f (its root held at its reference pose)"), ModelTurn, ModelLift);
				}
				if (Bake.SourceEffects > 0)
				{
					if (Move.bSourceSoundsOnly)
					{
						OutReport += FString::Printf(TEXT(", %d of its own sounds kept (not its effects)"), Bake.SourceEffects);
					}
					else
					{
						OutReport += FString::Printf(TEXT(", %d of its own sounds and effects kept"), Bake.SourceEffects);
					}
				}
				if (Bake.CurvesDropped > 0)
				{
					OutReport += FString::Printf(TEXT(", %d curve(s) the character's skeleton has no name for left out"), Bake.CurvesDropped);
				}
			}
			// (1.12.4) CopyNotifyObject
			const int32 EffectParameters = Bake.EffectParameters + Result.EffectParameters;
			const int32 NotifiesLeftOut = Bake.NotifiesLeftOut + Result.NotifiesLeftOut;
			if (EffectParameters > 0)
			{
				OutReport += FString::Printf(TEXT(", %d effect parameter(s) of the game's that this editor cannot write taken out of the effects copied (they play with their own values)"), EffectParameters);
			}
			if (NotifiesLeftOut > 0)
			{
				OutReport += FString::Printf(TEXT(", %d notify(s) not copied (effect parameters of the game's that this editor cannot write)"), NotifiesLeftOut);
			}
			if (From)
			{
				OutReport += FString::Printf(TEXT(", %d gameplay notifies from %s (%.2f s)"), Result.Copied, *From->GetName(), From->SequenceLength);
			}
			if (Result.OldHit >= 0.f)
			{
				OutReport += FString::Printf(TEXT(", first hit %.2f s -> %.2f s (%d hit(s))"), Result.OldHit, Result.NewHit, Result.Hits);
			}
			else if (Result.HitsMade > 0)
			{
				OutReport += FString::Printf(TEXT(", %d new hit(s) with their Damage Source IDs"), Result.HitsMade);
			}
			else if (From)
			{
				OutReport += TEXT(", the original has no hit");
			}
			if (Result.HitsRepeated > 0)
			{
				OutReport += FString::Printf(TEXT(", %d more hit(s) made from its last one"), Result.HitsRepeated);
			}
			if (Result.HitsLeftOut > 0)
			{
				OutReport += FString::Printf(TEXT(", its last %d hit(s) left out (the move has fewer)"), Result.HitsLeftOut);
			}
			if (Result.Effects > 0)
			{
				OutReport += FString::Printf(TEXT(", %d hit effect(s) and sound(s)"), Result.Effects);
			}
			if (Result.Shots > 0)
			{
				OutReport += FString::Printf(TEXT(", %d shot(s) with muzzle flash and gunshot"), Result.Shots);
			}
			if (Result.Left > 0)
			{
				OutReport += FString::Printf(TEXT("; left out %d of the original's own sounds and effects (%s)"), Result.Left, *FString::Join(Result.LeftClasses, TEXT(", ")));
			}
			OutReport += Notes + TEXT("\n");
		}
	}
	if (Asked == 0)
	{
		OutReport += TEXT("No move with Build on to build. Turn on Build on the moves to make (Animation: the animation to make each from).\n");
		return false;
	}
	if (BuildChunk > 0)
	{
		for (const TPair<FString, TArray<UObject*>>& Folder : ByFolder)
		{
			LabelForChunk(Folder.Key, BuildChunk, Folder.Value, ToSave, OutReport);
		}
	}
	if (ToSave.Num() > 0)
	{
		// The data object too, when its moves changed (the Move Maker's Build), so the build and its settings stay together.
		if (GetOutermost()->IsDirty())
		{
			ToSave.AddUnique(GetOutermost());
		}
		int32 Broken = 0;
		const TArray<UPackage*> Failed = SaveAnimationPackages(ToSave, BuiltSequences, Broken, OutReport);
		Built -= Broken;
		OutReport += FString::Printf(TEXT("\n%d of %d move(s) built and saved%s. Package the project: they go in pakchunk%d. Export Json points the moves at them.\n"),
			Built, Asked, Failed.Num() > 0 ? *FString::Printf(TEXT(" (%d package(s) NOT saved)"), Failed.Num()) : TEXT(""), BuildChunk);
		bOk &= Failed.Num() == 0;
	}
	return bOk && Built == Asked;
}

// ------------------------------------------------------------------------------------------------
// The Move Maker's view of this data object (editor 1.8)
// ------------------------------------------------------------------------------------------------
void UEndSkeletonCompatDataObject::OpenMoveMaker()
{
	RebirthSkelCompatEditor::OpenMoveMakerTab(this);
}

TArray<FString> UEndSkeletonCompatDataObject::MoveMakerRowLabels() const
{
	TArray<FString> Labels;
	for (int32 Index = 0; Index < AnimationSets.Num(); ++Index)
	{
		const TArray<FString> Characters = CleanList(AnimationSets[Index].Characters, false);
		Labels.Add(FString::Printf(TEXT("%d: %s"), Index, Characters.Num() > 0 ? *ListText(Characters) : TEXT("(no character yet)")));
	}
	return Labels;
}

TArray<FString> UEndSkeletonCompatDataObject::MoveMakerSlots(int32 RowIndex, EEndMoveSlotKind Kind) const
{
	TArray<FString> Out;
	if (!AnimationSets.IsValidIndex(RowIndex))
	{
		return Out;
	}
	const FEndAnimSetRow& Row = AnimationSets[RowIndex];
	TMap<FString, float> Lengths;
	const auto Take = [&Lengths](UObject* Set)
	{
		FSetContents Contents;
		if (!Set || !ReadEndAnimSet(Set, Contents))
		{
			return;
		}
		for (const SkelCompat::MatchAnim& Anim : Contents.Anims)
		{
			const FString Name = FromWide(Anim.Name);
			if (!Lengths.Contains(Name))
			{
				Lengths.Add(Name, Anim.Length);
			}
		}
	};
	// The battle sets the character plays: the row's battle sources, the slot owner's (last) first, then the packs' own.
	static const TCHAR* const SetNames[] = {TEXT("Battle00"), TEXT("Battle01"), TEXT("Battle02"), TEXT("Battle00_Comp"), TEXT("Battle01_Comp")};
	for (int32 K = Row.Battle.Num() - 1; K >= 0; --K)
	{
		SkelCompat::SetSource Parsed;
		if (!SkelCompat::ParseSetSource(Wide(Row.Battle[K].Path), Parsed))
		{
			continue;
		}
		if (Parsed.Folder)
		{
			for (const TCHAR* SetName : SetNames)
			{
				const FString Path = FromWide(Parsed.Path) + TEXT("/") + SetName + TEXT(".") + SetName;
				if (InProject(Path))
				{
					Take(LoadObject<UObject>(nullptr, *Path));
				}
			}
		}
		else if (InProject(FromWide(Parsed.Path)))
		{
			Take(LoadObject<UObject>(nullptr, *FromWide(Parsed.Path)));
		}
	}
	for (const FString& Character : CleanList(Row.Characters, false))
	{
		const FString Pack = FromWide(SkelCompat::CharacterPackPath(Wide(Character)));
		for (const TCHAR* SetName : SetNames)
		{
			Take(PackOwnSet(Pack, SetName));
		}
	}
	// The row's own moves (names the sets do not have included).
	for (const FEndAnimSetMove& Move : Row.Moves)
	{
		const FString Name = Move.Name.TrimStartAndEnd();
		if (!Name.IsEmpty() && !Lengths.Contains(Name))
		{
			Lengths.Add(Name, 0.f);
		}
	}
	TArray<FString> Names;
	Lengths.GetKeys(Names);
	Names.Sort();
	for (const FString& Name : Names)
	{
		if (!SlotIsKind(Name, Kind))
		{
			continue;
		}
		const float Length = Lengths[Name];
		Out.Add(Length > 0.f ? FString::Printf(TEXT("%s (%.2f s)"), *Name, Length) : Name);
	}
	return Out;
}

int32 UEndSkeletonCompatDataObject::FindMove(int32 RowIndex, const FString& Name, const FString& Set) const
{
	if (!AnimationSets.IsValidIndex(RowIndex))
	{
		return INDEX_NONE;
	}
	const TArray<FEndAnimSetMove>& Moves = AnimationSets[RowIndex].Moves;
	for (int32 Index = 0; Index < Moves.Num(); ++Index)
	{
		if (Moves[Index].Name.TrimStartAndEnd().Equals(Name.TrimStartAndEnd(), ESearchCase::IgnoreCase) &&
			Moves[Index].Set.TrimStartAndEnd().Equals(Set.TrimStartAndEnd(), ESearchCase::IgnoreCase))
		{
			return Index;
		}
	}
	return INDEX_NONE;
}

const FEndAnimSetMove* UEndSkeletonCompatDataObject::GetMove(int32 RowIndex, int32 MoveIndex) const
{
	return AnimationSets.IsValidIndex(RowIndex) && AnimationSets[RowIndex].Moves.IsValidIndex(MoveIndex) ? &AnimationSets[RowIndex].Moves[MoveIndex] : nullptr;
}

void UEndSkeletonCompatDataObject::SetMove(int32 RowIndex, const FEndAnimSetMove& Move)
{
	if (!AnimationSets.IsValidIndex(RowIndex) || Move.Name.TrimStartAndEnd().IsEmpty())
	{
		return;
	}
	Modify();
	const int32 Index = FindMove(RowIndex, Move.Name, Move.Set);
	if (Index == INDEX_NONE)
	{
		AnimationSets[RowIndex].Moves.Add(Move);
	}
	else
	{
		AnimationSets[RowIndex].Moves[Index] = Move;
	}
	PostEditChange();
	MarkPackageDirty();
}

FString UEndSkeletonCompatDataObject::BuiltMoveObjectPath(int32 RowIndex, const FEndAnimSetMove& Move) const
{
	return AnimationSets.IsValidIndex(RowIndex) && !Move.Name.TrimStartAndEnd().IsEmpty() ? BuiltObjectPathOf(AnimationSets[RowIndex], Move) : FString();
}

FString UEndSkeletonCompatDataObject::MoveNotifySourcePath(int32 RowIndex, const FEndAnimSetMove& Move, FString& OutLookedFor) const
{
	OutLookedFor.Reset();
	if (!AnimationSets.IsValidIndex(RowIndex) || (Move.Name.TrimStartAndEnd().IsEmpty() && Move.NotifiesFrom.TrimStartAndEnd().IsEmpty()))
	{
		return FString();
	}
	const UAnimSequenceBase* From = FindNotifySource(AnimationSets[RowIndex], Move, OutLookedFor);
	return From ? From->GetPathName() : FString();
}

USkeleton* UEndSkeletonCompatDataObject::CharacterSkeletonOf(int32 RowIndex) const
{
	return AnimationSets.IsValidIndex(RowIndex) && !AnimationSets[RowIndex].CharacterSkeleton.IsNull() ? AnimationSets[RowIndex].CharacterSkeleton.LoadSynchronous() : nullptr;
}

bool UEndSkeletonCompatDataObject::ApplySocketStandInsToMeshes(bool bRemove, FString& OutReport)
{
	OutReport.Reset();
	bool bOk = true;
	TArray<UPackage*> Dirty;
	const FString Prefix = TEXT("SkelCompatStandIn_");
	for (int32 Index = 0; Index < AnimationSets.Num(); ++Index)
	{
		const FEndAnimSetRow& Row = AnimationSets[Index];
		if (!Row.bEnabled || Row.Sockets.Num() == 0)
		{
			continue;
		}
		USkeleton* Own = Row.CharacterSkeleton.IsNull() ? nullptr : Row.CharacterSkeleton.LoadSynchronous();
		if (!Own)
		{
			OutReport += FString::Printf(TEXT("Row %d: ERROR: Sockets need Character Skeleton\n"), Index);
			bOk = false;
			continue;
		}
		for (USkeletalMesh* Mesh : MeshesFor(Own, {}, TEXT("    "), OutReport))
		{
			if (IsCookedAsset(Mesh))
			{
				OutReport += FString::Printf(TEXT("%s: cooked game mesh, not changed (the game mod adds the stand-ins while it loads)\n"), *Mesh->GetName());
				continue;
			}
			FString Line;
			bool bChanged = false;
			TArray<USkeletalMeshSocket*>& List = Mesh->GetMeshOnlySocketList();
			for (const FEndSocketStandIn& Socket : Row.Sockets)
			{
				const FName Wanted(*Socket.Socket.TrimStartAndEnd());
				const FName Use(*Socket.Use.TrimStartAndEnd());
				if (Wanted.IsNone() || Use.IsNone())
				{
					continue;
				}
				const int32 At = List.IndexOfByPredicate([&](const USkeletalMeshSocket* One) { return One && One->SocketName == Wanted; });
				const bool bOurs = At != INDEX_NONE && List[At]->GetName().StartsWith(Prefix);
				if (bRemove)
				{
					if (bOurs)
					{
						Mesh->Modify();
						List.RemoveAt(At);
						bChanged = true;
						Line += TEXT(" ") + Wanted.ToString() + TEXT(" removed;");
					}
					continue;
				}
				if (At != INDEX_NONE && !bOurs)
				{
					Line += TEXT(" has its own ") + Wanted.ToString() + TEXT(", left as it is;");
					continue;
				}
				// A copy of the Use socket (mesh, then skeleton), else a socket on the Use bone.
				const USkeletalMeshSocket* Model = Mesh->FindSocket(Use);
				const FName Bone = Model ? Model->BoneName : (Mesh->RefSkeleton.FindBoneIndex(Use) != INDEX_NONE ? Use : NAME_None);
				if (Bone.IsNone())
				{
					Line += TEXT(" ") + Wanted.ToString() + TEXT(": NO socket or bone ") + Use.ToString() + TEXT(";");
					bOk = false;
					continue;
				}
				Mesh->Modify();
				USkeletalMeshSocket* StandIn = bOurs ? List[At]
					: NewObject<USkeletalMeshSocket>(Mesh, MakeUniqueObjectName(Mesh, USkeletalMeshSocket::StaticClass(), FName(*(Prefix + Wanted.ToString()))), RF_Transactional);
				StandIn->Modify();
				StandIn->SocketName = Wanted;
				StandIn->BoneName = Bone;
				StandIn->RelativeLocation = Model ? Model->RelativeLocation : FVector::ZeroVector;
				StandIn->RelativeRotation = Model ? Model->RelativeRotation : FRotator::ZeroRotator;
				StandIn->RelativeScale = Model ? Model->RelativeScale : FVector::OneVector;
				StandIn->bForceAlwaysAnimated = Model ? Model->bForceAlwaysAnimated : false;
				if (!bOurs)
				{
					List.Add(StandIn);
				}
				bChanged = true;
				Line += FString::Printf(TEXT(" %s -> %s (bone %s);"), *Wanted.ToString(), *Use.ToString(), *Bone.ToString());
			}
			if (bChanged)
			{
				Mesh->RebuildSocketMap();
				Mesh->MarkPackageDirty();
				Dirty.AddUnique(Mesh->GetOutermost());
			}
			OutReport += Mesh->GetName() + TEXT(":") + (Line.IsEmpty() ? FString(TEXT(" nothing to do")) : Line) + TEXT("\n");
		}
	}
	if (Dirty.Num() > 0)
	{
		FEditorFileUtils::PromptForCheckoutAndSave(Dirty, false, true);
		OutReport += TEXT("\nSave the changed meshes (you were prompted), then cook them with your mod.\n");
	}
	else if (OutReport.IsEmpty())
	{
		OutReport += TEXT("No row has Sockets.\n");
	}
	return bOk;
}

bool UEndSkeletonCompatDataObject::MakeChainAnimComposites(FString& OutReport)
{
	OutReport.Reset();
	bool bOk = true;
	int32 Made = 0;
	TArray<UPackage*> ToSave;
	FString Folder = ChainFolder.TrimStartAndEnd().Replace(TEXT("\\"), TEXT("/"));
	while (Folder.EndsWith(TEXT("/")))
	{
		Folder.LeftChopInline(1);
	}
	if (!FPackageName::IsValidLongPackageName(Folder + TEXT("/Chain")))
	{
		OutReport += TEXT("ERROR: Chain Folder must be a content folder, e.g. /Game/RebirthSkelCompat/Chains\n");
		return false;
	}
	for (int32 Index = 0; Index < AnimationSets.Num(); ++Index)
	{
		const FEndAnimSetRow& Row = AnimationSets[Index];
		if (!Row.bEnabled)
		{
			continue;
		}
		const TArray<FString> Characters = CleanList(Row.Characters, false);
		const FString Character = Characters.Num() > 0 ? CharaSpecRowName(Characters[0]) : FString::Printf(TEXT("Row%d"), Index);
		struct FChain
		{
			FString Key;
			TArray<FString> Paths;
		};
		TArray<FChain> Chains;
		for (const FEndAnimSetMove& Move : Row.Moves)
		{
			const TArray<FString> Then = CleanList(Move.ThenPlay, false);
			if (Then.Num() > 0 && !Move.bBuild)
			{
				FChain Chain;
				Chain.Key = (Move.Set.TrimStartAndEnd().IsEmpty() ? FString() : Move.Set.TrimStartAndEnd() + TEXT("_")) + Move.Name.TrimStartAndEnd();
				Chain.Paths.Add(Move.Animation.TrimStartAndEnd());
				Chain.Paths.Append(Then);
				Chains.Add(Chain);
			}
		}
		for (int32 Limit = 0; Limit < Row.LimitBreaks.Num(); ++Limit)
		{
			const TArray<FString> Then = CleanList(Row.LimitBreaks[Limit].ThenPlay, false);
			if (Then.Num() > 0 && !Row.LimitBreaks[Limit].Animation.TrimStartAndEnd().IsEmpty())
			{
				FChain Chain;
				Chain.Key = FString::Printf(TEXT("B_AtkLimit%02d_0"), Limit + 1);
				Chain.Paths.Add(Row.LimitBreaks[Limit].Animation.TrimStartAndEnd());
				Chain.Paths.Append(Then);
				Chains.Add(Chain);
			}
		}
		for (const FChain& Chain : Chains)
		{
			TArray<UAnimSequenceBase*> Pieces;
			FString Missing;
			for (const FString& Path : Chain.Paths)
			{
				UAnimSequenceBase* Piece = InProject(Path) ? Cast<UAnimSequenceBase>(FSoftObjectPath(NormalizedObjectPath(Path)).TryLoad()) : nullptr;
				if (!Piece)
				{
					Missing += (Missing.IsEmpty() ? TEXT("") : TEXT(", ")) + ShortSource(Path);
				}
				Pieces.Add(Piece);
			}
			if (!Missing.IsEmpty())
			{
				OutReport += FString::Printf(TEXT("%s %s: NOT made, not in this project: %s (the game still builds it)\n"), *Character, *Chain.Key, *Missing);
				bOk = false;
				continue;
			}
			USkeleton* Skeleton = Pieces[0]->GetSkeleton();
			if (Pieces.ContainsByPredicate([&](const UAnimSequenceBase* Piece) { return Piece->GetSkeleton() != Skeleton; }))
			{
				OutReport += FString::Printf(TEXT("%s %s: NOT made, its animations are on different skeletons\n"), *Character, *Chain.Key);
				bOk = false;
				continue;
			}
			const FString Name = TEXT("AC_") + Chain.Key;
			const FString Package = Folder + TEXT("/") + Character + TEXT("/") + Name;
			// An earlier one is made anew, without deleting it as an asset (which would break the Anim Sequences in memory,
			// see ReplaceEarlierAsset).
			FString Why;
			if (ReplaceEarlierAsset(Package, Name, UAnimComposite::StaticClass(), Why) == EEarlierAsset::Refused)
			{
				OutReport += FString::Printf(TEXT("%s %s: NOT made, %s %s, so it is not replaced\n"), *Character, *Chain.Key, *Package, *Why);
				bOk = false;
				continue;
			}
			UPackage* Outer = CreatePackage(*Package);
			UAnimComposite* Composite = NewObject<UAnimComposite>(Outer, *Name, RF_Public | RF_Standalone | RF_Transactional);
			Composite->SetSkeleton(Skeleton);
			float Position = 0.f;
			for (UAnimSequenceBase* Piece : Pieces)
			{
				FAnimSegment Segment;
				Segment.AnimReference = Piece;
				Segment.StartPos = Position;
				Segment.AnimStartTime = 0.f;
				Segment.AnimEndTime = Piece->SequenceLength;
				Segment.AnimPlayRate = 1.f;
				Segment.LoopingCount = 1;
				Segment.AnimBlendTime = 0.f;
				Segment.bTriggerAnimReferenceNotify = true; // the pieces' sounds and effects still play
				Composite->AnimationTrack.AnimSegments.Add(Segment);
				Position += Segment.GetLength();
			}
			Composite->SequenceLength = Position;
			FAssetRegistryModule::AssetCreated(Composite);
			Composite->MarkPackageDirty();
			ToSave.Add(Outer);
			++Made;
			OutReport += FString::Printf(TEXT("%s %s: %s, %d animations, %.2f s\n"), *Character, *Chain.Key, *Package, Pieces.Num(), Position);
		}
	}
	if (ToSave.Num() > 0)
	{
		FEditorFileUtils::PromptForCheckoutAndSave(ToSave, false, true);
		OutReport += TEXT("\nTo play an edited one in game: set the move's Animation to it, clear Then Play, and cook it with your mod.\n");
	}
	else if (Made == 0 && bOk)
	{
		OutReport += TEXT("No move or limit break has Then Play.\n");
	}
	return bOk;
}

void UEndSkeletonCompatDataObject::BuildMoves()
{
	FString Report;
	const bool bOk = BuildMoveAnimations(Report);
	ShowResult(TEXT("Build Moves"), Report, bOk);
}

void UEndSkeletonCompatDataObject::ApplySocketStandIns()
{
	FString Report;
	const bool bOk = ApplySocketStandInsToMeshes(false, Report);
	ShowResult(TEXT("Apply Socket Stand-ins"), Report, bOk);
}

void UEndSkeletonCompatDataObject::RemoveSocketStandIns()
{
	FString Report;
	const bool bOk = ApplySocketStandInsToMeshes(true, Report);
	ShowResult(TEXT("Remove Socket Stand-ins"), Report, bOk);
}

void UEndSkeletonCompatDataObject::MakeChainAssets()
{
	FString Report;
	const bool bOk = MakeChainAnimComposites(Report);
	ShowResult(TEXT("Make Chain Assets"), Report, bOk);
}

// ------------------------------------------------------------------------------------------------
// Key animations (editor 1.10): animations made from key files the Create a Character System tools write (.cacanim:
// every bone's local translation, rotation and scale per frame, already in Unreal's axes and on the skeleton's bone
// names). For animations from other games whose FBX does not import cleanly onto a game skeleton (a Blender export's
// Armature root turns them around, bones the skeleton lacks, hips left at standing height by a retarget).
//   'CACANIM1', uint32 version (1), float frame rate, int32 frames, uint32 flags (1: loops), int32 tracks, then per track
//   uint16 name length, the name (ASCII), int32 keys (1 for a still track, else frames), keys x 10 floats
//   (translation xyz, rotation quaternion xyzw, scale xyz).
// ------------------------------------------------------------------------------------------------
namespace
{
struct FKeyAnimationTrack
{
	FName Bone;
	TArray<FVector> Positions;
	TArray<FQuat> Rotations;
	TArray<FVector> Scales;
};

struct FKeyAnimation
{
	float FrameRate = 30.f;
	int32 Frames = 0;
	bool bLoop = false;
	TArray<FKeyAnimationTrack> Tracks;
};

class FKeyAnimationReader
{
public:
	explicit FKeyAnimationReader(const TArray<uint8>& InData) : Data(InData) {}

	bool Bytes(void* Out, int64 Size)
	{
		if (Size < 0 || Offset + Size > static_cast<int64>(Data.Num()))
		{
			return false;
		}
		FMemory::Memcpy(Out, Data.GetData() + Offset, Size);
		Offset += Size;
		return true;
	}

	template <typename T>
	bool Read(T& Out) { return Bytes(&Out, sizeof(T)); }

	bool AtEnd() const { return Offset == static_cast<int64>(Data.Num()); }

private:
	const TArray<uint8>& Data;
	int64 Offset = 0;
};

bool ReadKeyAnimation(const FString& File, FKeyAnimation& Out, FString& Error)
{
	TArray<uint8> Data;
	if (!FFileHelper::LoadFileToArray(Data, *File))
	{
		Error = TEXT("could not be read");
		return false;
	}
	FKeyAnimationReader Reader(Data);
	ANSICHAR Magic[8];
	uint32 Version = 0;
	uint32 Flags = 0;
	int32 NumTracks = 0;
	if (!Reader.Bytes(Magic, sizeof(Magic)) || FMemory::Memcmp(Magic, "CACANIM1", sizeof(Magic)) != 0)
	{
		Error = TEXT("is not a key animation (no CACANIM1 header)");
		return false;
	}
	if (!Reader.Read(Version) || !Reader.Read(Out.FrameRate) || !Reader.Read(Out.Frames) || !Reader.Read(Flags) || !Reader.Read(NumTracks))
	{
		Error = TEXT("ends inside its header");
		return false;
	}
	if (Version != 1)
	{
		Error = FString::Printf(TEXT("is version %u (this editor reads version 1)"), Version);
		return false;
	}
	if (Out.Frames < 2 || Out.Frames > 100000 || !(Out.FrameRate > 0.f && Out.FrameRate <= 1000.f) || NumTracks < 1 || NumTracks > 8192)
	{
		Error = FString::Printf(TEXT("has a bad header (%d frames at %g fps, %d tracks)"), Out.Frames, Out.FrameRate, NumTracks);
		return false;
	}
	Out.bLoop = (Flags & 1u) != 0;
	for (int32 TrackIndex = 0; TrackIndex < NumTracks; ++TrackIndex)
	{
		uint16 NameLength = 0;
		if (!Reader.Read(NameLength) || NameLength == 0 || NameLength > 512)
		{
			Error = FString::Printf(TEXT("has a broken name in track %d"), TrackIndex);
			return false;
		}
		TArray<ANSICHAR> Name;
		Name.SetNumZeroed(NameLength + 1);
		int32 Keys = 0;
		if (!Reader.Bytes(Name.GetData(), NameLength) || !Reader.Read(Keys) || (Keys != 1 && Keys != Out.Frames))
		{
			Error = FString::Printf(TEXT("has a broken track %d (%s)"), TrackIndex, ANSI_TO_TCHAR(Name.GetData()));
			return false;
		}
		FKeyAnimationTrack& Track = Out.Tracks.AddDefaulted_GetRef();
		Track.Bone = FName(ANSI_TO_TCHAR(Name.GetData()));
		Track.Positions.Reserve(Keys);
		Track.Rotations.Reserve(Keys);
		Track.Scales.Reserve(Keys);
		for (int32 Key = 0; Key < Keys; ++Key)
		{
			float V[10];
			if (!Reader.Bytes(V, sizeof(V)))
			{
				Error = FString::Printf(TEXT("ends inside track %s"), *Track.Bone.ToString());
				return false;
			}
			Track.Positions.Add(FVector(V[0], V[1], V[2]));
			Track.Rotations.Add(FQuat(V[3], V[4], V[5], V[6]).GetNormalized());
			Track.Scales.Add(FVector(V[7], V[8], V[9]));
		}
	}
	if (!Reader.AtEnd())
	{
		Error = TEXT("has data after its last track");
		return false;
	}
	return true;
}
} // namespace

bool UEndSkeletonCompatDataObject::ImportKeyAnimations(const FString& Folder, const FString& SkeletonPath, const FString& Destination, FString& OutReport)
{
	OutReport.Reset();
	USkeleton* Skeleton = Cast<USkeleton>(FSoftObjectPath(NormalizedObjectPath(SkeletonPath)).TryLoad());
	if (!Skeleton)
	{
		OutReport = FString::Printf(TEXT("ERROR: the skeleton %s does not load in this editor\n"), *SkeletonPath);
		return false;
	}
	FString Root = Destination.TrimStartAndEnd();
	Root.ReplaceInline(TEXT("\\"), TEXT("/"));
	while (Root.EndsWith(TEXT("/")))
	{
		Root.LeftChopInline(1);
	}
	if (!FPackageName::IsValidLongPackageName(Root + TEXT("/Animation")))
	{
		OutReport = FString::Printf(TEXT("ERROR: %s is not a content folder (Destination must start with /Game/)\n"), *Destination);
		return false;
	}
	UAnimBoneCompressionSettings* BoneCompression = LoadObject<UAnimBoneCompressionSettings>(nullptr, GameBoneCompression, nullptr, LOAD_NoWarn | LOAD_Quiet);
	TurnOffAclSafetyFallback(BoneCompression);
	UAnimCurveCompressionSettings* CurveCompression = LoadObject<UAnimCurveCompressionSettings>(nullptr, GameCurveCompression, nullptr, LOAD_NoWarn | LOAD_Quiet);
	if (!BoneCompression || !CurveCompression)
	{
		OutReport = FString::Printf(TEXT("ERROR: the game's animation compression settings are not in this project (%s, %s): the game reads every animation with them\n"),
			BoneCompression ? TEXT("bone settings found") : GameBoneCompression, CurveCompression ? TEXT("curve settings found") : GameCurveCompression);
		return false;
	}
	TArray<FString> Files;
	IFileManager::Get().FindFiles(Files, *FPaths::Combine(Folder, TEXT("*.cacanim")), true, false);
	Files.Sort();
	if (Files.Num() == 0)
	{
		OutReport = FString::Printf(TEXT("ERROR: no key animation (.cacanim) in %s\n"), *Folder);
		return false;
	}
	const FReferenceSkeleton& Reference = Skeleton->GetReferenceSkeleton();
	TArray<UPackage*> ToSave;
	TArray<UAnimSequence*> Sequences;
	int32 Made = 0;
	bool bOk = true;
	for (const FString& FileName : Files)
	{
		const FString Name = FPaths::GetBaseFilename(FileName);
		const FString Package = Root + TEXT("/") + Name;
		if (!FPackageName::IsValidLongPackageName(Package))
		{
			OutReport += FString::Printf(TEXT("%s: ERROR: %s is not a valid package name\n"), *FileName, *Package);
			bOk = false;
			continue;
		}
		FKeyAnimation Keys;
		FString Error;
		if (!ReadKeyAnimation(FPaths::Combine(Folder, FileName), Keys, Error))
		{
			OutReport += FString::Printf(TEXT("%s: ERROR: the file %s\n"), *FileName, *Error);
			bOk = false;
			continue;
		}
		// An earlier import is made anew, without loading it (this engine may have saved it broken, and loading that stops
		// the editor) or deleting it as an asset (see ReplaceEarlierAsset).
		FString Why;
		if (ReplaceEarlierAsset(Package, Name, UAnimSequence::StaticClass(), Why) == EEarlierAsset::Refused)
		{
			OutReport += FString::Printf(TEXT("%s: ERROR: %s %s, so it is not replaced; choose another Destination\n"), *FileName, *Package, *Why);
			bOk = false;
			continue;
		}
		UPackage* Outer = CreatePackage(*Package);
		if (!Outer)
		{
			OutReport += FString::Printf(TEXT("%s: ERROR: %s could not be made\n"), *FileName, *Package);
			bOk = false;
			continue;
		}
		Outer->FullyLoad();
		if (StaticFindObjectFast(nullptr, Outer, FName(*Name)))
		{
			OutReport += FString::Printf(TEXT("%s: ERROR: %s is still loaded (close it, then import again)\n"), *FileName, *Package);
			bOk = false;
			continue;
		}
		// Made new (an Anim Sequence is never duplicated in this engine) with the raw keys as they are.
		UAnimSequence* Sequence = NewObject<UAnimSequence>(Outer, FName(*Name), RF_Public | RF_Standalone | RF_Transactional);
		Sequence->SetSkeleton(Skeleton);
		Sequence->BoneCompressionSettings = BoneCompression;
		Sequence->CurveCompressionSettings = CurveCompression;
		Sequence->SequenceLength = static_cast<float>(Keys.Frames - 1) / Keys.FrameRate;
		Sequence->SetRawNumberOfFrame(Keys.Frames);
		int32 Added = 0;
		int32 Missing = 0;
		for (const FKeyAnimationTrack& Track : Keys.Tracks)
		{
			if (Reference.FindBoneIndex(Track.Bone) == INDEX_NONE)
			{
				++Missing;
				continue;
			}
			FRawAnimSequenceTrack Raw;
			Raw.PosKeys = Track.Positions;
			Raw.RotKeys = Track.Rotations;
			Raw.ScaleKeys = Track.Scales;
			if (Sequence->AddNewRawTrack(Track.Bone, &Raw) != INDEX_NONE)
			{
				++Added;
			}
		}
		if (Added == 0)
		{
			Sequence->ClearFlags(RF_Public | RF_Standalone);
			Sequence->MarkPendingKill();
			OutReport += FString::Printf(TEXT("%s: ERROR: none of its %d bone(s) is in %s\n"), *FileName, Keys.Tracks.Num(), *Skeleton->GetName());
			bOk = false;
			continue;
		}
		Sequence->MarkRawDataAsModified();
		Sequence->OnRawDataChanged();
		Sequence->RefreshCacheData();
		Sequence->PostEditChange();
		Sequence->RequestSyncAnimRecompression(false);
		FAssetRegistryModule::AssetCreated(Sequence);
		Sequence->MarkPackageDirty();
		ToSave.AddUnique(Outer);
		Sequences.Add(Sequence);
		++Made;
		OutReport += FString::Printf(TEXT("%s: %d frames at %.0f fps (%.2f s), %d bone track(s)"), *Package, Keys.Frames, Keys.FrameRate, Sequence->SequenceLength, Added);
		if (Missing > 0)
		{
			OutReport += FString::Printf(TEXT(", %d bone(s) %s lacks left out"), Missing, *Skeleton->GetName());
		}
		OutReport += TEXT("\n");
	}
	int32 NotSaved = 0;
	if (ToSave.Num() > 0)
	{
		int32 Broken = 0;
		NotSaved = SaveAnimationPackages(ToSave, Sequences, Broken, OutReport).Num();
		Made -= Broken;
		bOk = bOk && NotSaved == 0;
	}
	OutReport += FString::Printf(TEXT("\n%d of %d key animation(s) made in %s on %s%s.\n"), Made, Files.Num(), *Root, *Skeleton->GetName(),
		NotSaved > 0 ? *FString::Printf(TEXT(" (%d package(s) NOT saved)"), NotSaved) : TEXT(""));
	return bOk && Made == Files.Num();
}

// ------------------------------------------------------------------------------------------------
// Flatten Root (editor 1.13.1): a skeleton's root bone made to rest unturned (no rotation, a scale of 1), the root's
// children taking its old turn into their own rest, on the skeleton, its meshes and its animations, so every pose stays
// where it was. See the header.
// ------------------------------------------------------------------------------------------------
namespace
{
const FName FlattenOldRootKey(TEXT("CaC.FlattenRoot.OldRoot"));
const FName FlattenRenamesKey(TEXT("CaC.FlattenRoot.Renames"));
const FName FlattenDoneKey(TEXT("CaC.FlattenRoot.Done"));

FString FlattenTransformText(const FTransform& Transform)
{
	const FQuat Q = Transform.GetRotation();
	const FVector P = Transform.GetTranslation();
	const FVector S = Transform.GetScale3D();
	return FString::Printf(TEXT("%.9g %.9g %.9g %.9g %.9g %.9g %.9g %.9g %.9g %.9g"), Q.X, Q.Y, Q.Z, Q.W, P.X, P.Y, P.Z, S.X, S.Y, S.Z);
}

bool FlattenTransformFromText(const FString& Text, FTransform& Out)
{
	TArray<FString> Parts;
	Text.ParseIntoArrayWS(Parts);
	if (Parts.Num() != 10)
	{
		return false;
	}
	float V[10];
	for (int32 Index = 0; Index < 10; ++Index)
	{
		V[Index] = FCString::Atof(*Parts[Index]);
	}
	Out = FTransform(FQuat(V[0], V[1], V[2], V[3]).GetNormalized(), FVector(V[4], V[5], V[6]), FVector(V[7], V[8], V[9]));
	return true;
}

FString FlattenRenamesText(const TMap<FName, FName>& Renames)
{
	FString Text;
	for (const TPair<FName, FName>& Pair : Renames)
	{
		Text += FString::Printf(TEXT("%s%s=%s"), Text.IsEmpty() ? TEXT("") : TEXT(";"), *Pair.Key.ToString(), *Pair.Value.ToString());
	}
	return Text;
}

TMap<FName, FName> FlattenRenamesFromText(const FString& Text)
{
	TMap<FName, FName> Renames;
	TArray<FString> Pairs;
	Text.ParseIntoArray(Pairs, TEXT(";"));
	for (const FString& Pair : Pairs)
	{
		FString From;
		FString To;
		if (Pair.Split(TEXT("="), &From, &To) && !From.IsEmpty() && !To.IsEmpty())
		{
			Renames.Add(FName(*From), FName(*To));
		}
	}
	return Renames;
}

// The rest the root takes: no turn and a scale of 1, standing where it stood.
FTransform FlatRoot(const FTransform& OldRoot)
{
	return FTransform(FQuat::Identity, OldRoot.GetTranslation(), FVector::OneVector);
}

bool RestsFlat(const FTransform& Root)
{
	return Root.GetRotation().AngularDistance(FQuat::Identity) < 1e-4f && Root.GetScale3D().Equals(FVector::OneVector, 1e-5f);
}

// Old's bones with the root resting at NewRoot (each child of the root taking the root's old rest into its own) and the
// bones in Renames renamed.
FReferenceSkeleton FlattenedRefSkeleton(const FReferenceSkeleton& Old, const USkeleton* Skeleton, const FTransform& NewRoot, const TMap<FName, FName>& Renames)
{
	FReferenceSkeleton New;
	const TArray<FMeshBoneInfo>& Info = Old.GetRawRefBoneInfo();
	const TArray<FTransform>& Pose = Old.GetRawRefBonePose();
	{
		FReferenceSkeletonModifier Modifier(New, Skeleton);
		for (int32 Bone = 0; Bone < Info.Num(); ++Bone)
		{
			FMeshBoneInfo Renamed = Info[Bone];
			if (const FName* To = Renames.Find(Info[Bone].Name))
			{
				Renamed.Name = *To;
#if WITH_EDITORONLY_DATA
				Renamed.ExportName = To->ToString();
#endif
			}
			FTransform Rest = Pose[Bone];
			if (Bone == 0)
			{
				Rest = NewRoot;
			}
			else if (Info[Bone].ParentIndex == 0)
			{
				Rest = (Pose[Bone] * Pose[0]).GetRelativeTransform(NewRoot);
			}
			Modifier.Add(Renamed, Rest);
		}
	}
	return New;
}

// A socket on the root keeps its place in component space; a socket on a renamed bone follows the new name.
void FlattenSocket(USkeletalMeshSocket* Socket, const FName OldRootName, const FTransform& OldRoot, const FTransform& NewRoot, const TMap<FName, FName>& Renames, const FString& Owner, FString& Report)
{
	if (!Socket)
	{
		return;
	}
	if (Socket->BoneName == OldRootName)
	{
		const FTransform Relative(Socket->RelativeRotation, Socket->RelativeLocation, Socket->RelativeScale);
		const FTransform Moved = (Relative * OldRoot).GetRelativeTransform(NewRoot);
		Socket->Modify();
		Socket->RelativeLocation = Moved.GetTranslation();
		Socket->RelativeRotation = Moved.Rotator();
		Socket->RelativeScale = Moved.GetScale3D();
		Report += FString::Printf(TEXT("  %s socket %s (on the root) keeps its place: location %s, rotation %s\n"), *Owner, *Socket->SocketName.ToString(),
			*Socket->RelativeLocation.ToString(), *Socket->RelativeRotation.ToString());
	}
	if (const FName* To = Renames.Find(Socket->BoneName))
	{
		Socket->Modify();
		Report += FString::Printf(TEXT("  %s socket %s now on %s (was %s)\n"), *Owner, *Socket->SocketName.ToString(), *To->ToString(), *Socket->BoneName.ToString());
		Socket->BoneName = *To;
	}
}

// A raw track of a child of the root, from under the old root to under the new one: each key times Delta (the old root
// relative to the new one). Rotation, translation and scale keys each change on their own.
void FlattenTrackKeys(FRawAnimSequenceTrack& Raw, const FTransform& Delta)
{
	const FQuat Turn = Delta.GetRotation();
	for (FQuat& Key : Raw.RotKeys)
	{
		Key = (Turn * Key).GetNormalized();
	}
	for (FVector& Key : Raw.PosKeys)
	{
		Key = Delta.TransformPosition(Key);
	}
	const FVector Scale = Delta.GetScale3D();
	for (FVector& Key : Raw.ScaleKeys)
	{
		Key = Key * Scale;
	}
}

bool IsFlattenedAnimation(const UAnimSequence* Sequence)
{
	return Sequence && Sequence->GetOutermost()->GetMetaData()->HasValue(Sequence, FlattenDoneKey);
}
} // namespace

FString UEndSkeletonCompatDataObject::FlattenSkeletonRoot(const FString& SkeletonPath, const TMap<FString, FString>& BoneRenames, bool bAnimations, int32 First, int32 Count)
{
	FString Report;
	USkeleton* Skeleton = Cast<USkeleton>(FSoftObjectPath(NormalizedObjectPath(SkeletonPath)).TryLoad());
	if (!Skeleton)
	{
		return FString::Printf(TEXT("ERROR: the skeleton %s does not load in this editor\n"), *SkeletonPath);
	}
	UPackage* SkeletonPackage = Skeleton->GetOutermost();
	if (SkeletonPackage->HasAnyPackageFlags(PKG_Cooked))
	{
		return FString::Printf(TEXT("ERROR: %s is a cooked game asset: only a skeleton of this project can be flattened\n"), *Skeleton->GetPathName());
	}
	UMetaData* SkeletonMeta = SkeletonPackage->GetMetaData();
	const FString SkeletonTag = FAssetData(Skeleton).GetExportTextName();
	IAssetRegistry& Registry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();
	UAssetEditorSubsystem* Editors = GEditor ? GEditor->GetEditorSubsystem<UAssetEditorSubsystem>() : nullptr;

	if (!bAnimations)
	{
		// ---- the skeleton and its meshes
		if (SkeletonMeta->HasValue(Skeleton, FlattenOldRootKey))
		{
			return FString::Printf(TEXT("%s is flattened already (its root rested at %s): now run Flatten Root with bAnimations on.\n"),
				*Skeleton->GetPathName(), *SkeletonMeta->GetValue(Skeleton, FlattenOldRootKey));
		}
		const FReferenceSkeleton& SkeletonRef = Skeleton->GetReferenceSkeleton();
		TMap<FName, FName> Renames;
		for (const TPair<FString, FString>& Pair : BoneRenames)
		{
			const FName From(*Pair.Key.TrimStartAndEnd());
			const FName To(*Pair.Value.TrimStartAndEnd());
			if (From.IsNone() || To.IsNone() || From == To)
			{
				continue;
			}
			if (SkeletonRef.FindRawBoneIndex(From) == INDEX_NONE)
			{
				return FString::Printf(TEXT("ERROR: %s has no bone %s to rename\n"), *Skeleton->GetName(), *From.ToString());
			}
			if (SkeletonRef.FindRawBoneIndex(To) != INDEX_NONE)
			{
				return FString::Printf(TEXT("ERROR: %s already has a bone named %s (names are the same whatever their case)\n"), *Skeleton->GetName(), *To.ToString());
			}
			for (const TPair<FName, FName>& Earlier : Renames)
			{
				if (Earlier.Value == To)
				{
					return FString::Printf(TEXT("ERROR: two bones would be renamed %s\n"), *To.ToString());
				}
			}
			Renames.Add(From, To);
		}
		for (const FVirtualBone& Virtual : Skeleton->GetVirtualBones())
		{
			if (Renames.Contains(Virtual.SourceBoneName) || Renames.Contains(Virtual.TargetBoneName))
			{
				return FString::Printf(TEXT("ERROR: the virtual bone %s is made from a bone to rename: remove it first\n"), *Virtual.VirtualBoneName.ToString());
			}
		}
		// the meshes of this skeleton in this project: the same bones as the skeleton, in the same order
		FARFilter MeshFilter;
		MeshFilter.ClassNames.Add(USkeletalMesh::StaticClass()->GetFName());
		MeshFilter.bRecursiveClasses = true;
		MeshFilter.TagsAndValues.Add(TEXT("Skeleton"), SkeletonTag);
		TArray<FAssetData> MeshData;
		Registry.GetAssets(MeshFilter, MeshData);
		TArray<USkeletalMesh*> Meshes;
		for (const FAssetData& Data : MeshData)
		{
			USkeletalMesh* Mesh = Cast<USkeletalMesh>(Data.GetAsset());
			if (!Mesh || Mesh->Skeleton != Skeleton)
			{
				continue;
			}
			if (Mesh->GetOutermost()->HasAnyPackageFlags(PKG_Cooked))
			{
				return FString::Printf(TEXT("ERROR: the mesh %s is a cooked game asset and cannot be changed\n"), *Mesh->GetPathName());
			}
			const FReferenceSkeleton& MeshRef = Mesh->RefSkeleton;
			if (MeshRef.GetRawBoneNum() != SkeletonRef.GetRawBoneNum())
			{
				return FString::Printf(TEXT("ERROR: the mesh %s has %d bones and %s %d: they have to be the same bones\n"), *Mesh->GetPathName(),
					MeshRef.GetRawBoneNum(), *Skeleton->GetName(), SkeletonRef.GetRawBoneNum());
			}
			for (int32 Bone = 0; Bone < MeshRef.GetRawBoneNum(); ++Bone)
			{
				if (MeshRef.GetBoneName(Bone) != SkeletonRef.GetBoneName(Bone) || MeshRef.GetParentIndex(Bone) != SkeletonRef.GetParentIndex(Bone))
				{
					return FString::Printf(TEXT("ERROR: bone %d of the mesh %s is %s, of %s %s: they have to be the same bones in the same order\n"), Bone,
						*Mesh->GetPathName(), *MeshRef.GetBoneName(Bone).ToString(), *Skeleton->GetName(), *SkeletonRef.GetBoneName(Bone).ToString());
				}
			}
			Meshes.Add(Mesh);
		}
		if (Meshes.Num() == 0)
		{
			return FString::Printf(TEXT("ERROR: no mesh of this project is on %s\n"), *Skeleton->GetPathName());
		}
		// The game rests a character's root as its mesh has it: that rest is what the animations' keys are under.
		const FTransform OldRoot = Meshes[0]->RefSkeleton.GetRawRefBonePose()[0];
		for (USkeletalMesh* Mesh : Meshes)
		{
			if (!Mesh->RefSkeleton.GetRawRefBonePose()[0].Equals(OldRoot, 1e-4f))
			{
				return FString::Printf(TEXT("ERROR: the meshes %s and %s rest their roots differently\n"), *Meshes[0]->GetPathName(), *Mesh->GetPathName());
			}
		}
		const FTransform SkeletonOldRoot = SkeletonRef.GetRawRefBonePose()[0];
		if (RestsFlat(OldRoot) && RestsFlat(SkeletonOldRoot) && Renames.Num() == 0)
		{
			return FString::Printf(TEXT("%s already rests its root flat: nothing to do.\n"), *Skeleton->GetPathName());
		}
		const FName OldRootName = SkeletonRef.GetBoneName(0);
		const FTransform NewRoot = FlatRoot(OldRoot);
		Report += FString::Printf(TEXT("%s: the root %s rested at rotation %s (%s), scale %s; now no rotation, scale 1.\n"), *Skeleton->GetPathName(),
			*OldRootName.ToString(), *OldRoot.GetRotation().ToString(), *OldRoot.Rotator().ToString(), *OldRoot.GetScale3D().ToString());
		for (const TPair<FName, FName>& Pair : Renames)
		{
			Report += FString::Printf(TEXT("  bone %s renamed %s\n"), *Pair.Key.ToString(), *Pair.Value.ToString());
		}
		if (Editors)
		{
			Editors->CloseAllEditorsForAsset(Skeleton);
			for (USkeletalMesh* Mesh : Meshes)
			{
				Editors->CloseAllEditorsForAsset(Mesh);
			}
		}
		TArray<UPackage*> ToSave;
		for (USkeletalMesh* Mesh : Meshes)
		{
			FSkinnedMeshComponentRecreateRenderStateContext Recreate(Mesh, false);
			Mesh->Modify();
			const FTransform MeshRoot = Mesh->RefSkeleton.GetRawRefBonePose()[0];
#if WITH_EDITORONLY_DATA
			// the Retarget Manager's base pose, when the mesh has one, the same way
			if (Mesh->RetargetBasePose.Num() == Mesh->RefSkeleton.GetRawBoneNum())
			{
				TArray<FTransform> Base = Mesh->RetargetBasePose;
				const FTransform BaseRoot = Base[0];
				for (int32 Bone = 1; Bone < Base.Num(); ++Bone)
				{
					if (Mesh->RefSkeleton.GetParentIndex(Bone) == 0)
					{
						Base[Bone] = (Base[Bone] * BaseRoot).GetRelativeTransform(FlatRoot(BaseRoot));
					}
				}
				Base[0] = FlatRoot(BaseRoot);
				Mesh->RetargetBasePose = Base;
			}
#endif
			Mesh->RefSkeleton = FlattenedRefSkeleton(Mesh->RefSkeleton, Skeleton, NewRoot, Renames);
			Mesh->CalculateInvRefMatrices();
			for (USkeletalMeshSocket* Socket : Mesh->GetMeshOnlySocketList())
			{
				FlattenSocket(Socket, OldRootName, MeshRoot, NewRoot, Renames, Mesh->GetName(), Report);
			}
			Mesh->MarkPackageDirty();
			ToSave.AddUnique(Mesh->GetOutermost());
			Report += FString::Printf(TEXT("  mesh %s: rest pose flattened\n"), *Mesh->GetPathName());
		}
		// the skeleton (its own copy of the rest pose; its Guid stays, so its animations keep their tracks as they are)
		Skeleton->Modify();
		FReferenceSkeleton& Ref = const_cast<FReferenceSkeleton&>(Skeleton->GetReferenceSkeleton());
		Ref = FlattenedRefSkeleton(Ref, Skeleton, FlatRoot(SkeletonOldRoot), Renames);
		for (USkeletalMeshSocket* Socket : Skeleton->Sockets)
		{
			FlattenSocket(Socket, OldRootName, OldRoot, NewRoot, Renames, Skeleton->GetName(), Report);
		}
		if (Skeleton->AnimRetargetSources.Num() > 0)
		{
			Report += FString::Printf(TEXT("  NOTE: %d retarget source pose(s) of the skeleton keep the old root: update them in the Retarget Manager\n"), Skeleton->AnimRetargetSources.Num());
		}
		SkeletonMeta->SetValue(Skeleton, FlattenOldRootKey, *FlattenTransformText(OldRoot));
		SkeletonMeta->SetValue(Skeleton, FlattenRenamesKey, *FlattenRenamesText(Renames));
		Skeleton->ClearCacheData();
		Skeleton->MarkPackageDirty();
		ToSave.AddUnique(SkeletonPackage);
		TArray<UPackage*> Failed;
		FEditorFileUtils::PromptForCheckoutAndSave(ToSave, false, false, &Failed);
		for (UPackage* Package : Failed)
		{
			Report += FString::Printf(TEXT("ERROR: %s was not saved\n"), *Package->GetName());
		}
		FARFilter AnimFilter;
		AnimFilter.ClassNames.Add(UAnimSequence::StaticClass()->GetFName());
		AnimFilter.bRecursiveClasses = true;
		AnimFilter.TagsAndValues.Add(TEXT("Skeleton"), SkeletonTag);
		TArray<FAssetData> Anims;
		Registry.GetAssets(AnimFilter, Anims);
		Report += FString::Printf(TEXT("%s and %d mesh(es) saved%s. Now run Flatten Root with bAnimations on for its %d animation(s), a batch at a time.\n"),
			*Skeleton->GetName(), Meshes.Num(), Failed.Num() > 0 ? TEXT(" (NOT all)") : TEXT(""), Anims.Num());
		UE_LOG(LogTemp, Display, TEXT("Flatten Root: %s"), *Report);
		return Report;
	}

	// ---- the animations of the skeleton, from First, Count of them
	FTransform OldRoot;
	if (!SkeletonMeta->HasValue(Skeleton, FlattenOldRootKey) || !FlattenTransformFromText(SkeletonMeta->GetValue(Skeleton, FlattenOldRootKey), OldRoot))
	{
		return FString::Printf(TEXT("ERROR: %s is not flattened yet: run Flatten Root with bAnimations off first\n"), *Skeleton->GetPathName());
	}
	const TMap<FName, FName> Renames = FlattenRenamesFromText(SkeletonMeta->GetValue(Skeleton, FlattenRenamesKey));
	const FTransform Delta = OldRoot.GetRelativeTransform(FlatRoot(OldRoot));
	TurnOffAclSafetyFallback(nullptr); // compressed again with what the game reads (see TurnOffAclSafetyFallback)
	const FReferenceSkeleton& Ref = Skeleton->GetReferenceSkeleton();
	FARFilter Filter;
	Filter.ClassNames.Add(UAnimSequence::StaticClass()->GetFName());
	Filter.bRecursiveClasses = true;
	Filter.TagsAndValues.Add(TEXT("Skeleton"), SkeletonTag);
	TArray<FAssetData> Found;
	Registry.GetAssets(Filter, Found);
	// additive ones after the others (their compression takes the pose of their base animation)
	const auto IsAdditive = [](const FAssetData& Data)
	{
		const FString Type = Data.GetTagValueRef<FString>(TEXT("AdditiveAnimType"));
		return !Type.IsEmpty() && Type != TEXT("AAT_None");
	};
	Found.Sort([&IsAdditive](const FAssetData& A, const FAssetData& B)
	{
		const bool AddA = IsAdditive(A);
		const bool AddB = IsAdditive(B);
		if (AddA != AddB)
		{
			return !AddA;
		}
		return A.ObjectPath.LexicalLess(B.ObjectPath);
	});
	First = FMath::Max(First, 0);
	const int32 End = FMath::Min(First + FMath::Max(Count, 0), Found.Num());
	TArray<UPackage*> ToSave;
	TArray<UAnimSequence*> Sequences;
	int32 Already = 0;
	int32 Waiting = 0;
	int32 Errors = 0;
	for (int32 Index = First; Index < End; ++Index)
	{
		UAnimSequence* Sequence = Cast<UAnimSequence>(Found[Index].GetAsset());
		if (!Sequence)
		{
			Report += FString::Printf(TEXT("ERROR: %s does not load\n"), *Found[Index].ObjectPath.ToString());
			++Errors;
			continue;
		}
		UPackage* Package = Sequence->GetOutermost();
		if (Package->HasAnyPackageFlags(PKG_Cooked))
		{
			continue;
		}
		if (IsFlattenedAnimation(Sequence))
		{
			++Already;
			continue;
		}
		if (Sequence->HasSourceRawData())
		{
			Report += FString::Printf(TEXT("ERROR: %s has baked transform curves (source raw data): not changed\n"), *Sequence->GetPathName());
			++Errors;
			continue;
		}
		if (Sequence->IsValidAdditive() && Sequence->RefPoseSeq && Sequence->RefPoseSeq->GetSkeleton() == Skeleton && !IsFlattenedAnimation(Sequence->RefPoseSeq))
		{
			Report += FString::Printf(TEXT("%s waits for its base %s\n"), *Sequence->GetPathName(), *Sequence->RefPoseSeq->GetPathName());
			++Waiting;
			continue;
		}
		if (Editors)
		{
			Editors->CloseAllEditorsForAsset(Sequence);
		}
		Sequence->Modify();
		// a renamed bone's track under its new name
		const TArray<FName> Names = Sequence->GetAnimationTrackNames();
		for (const FName& Name : Names)
		{
			const FName* To = Renames.Find(Name);
			if (!To)
			{
				continue;
			}
			const int32 TrackIndex = Sequence->GetAnimationTrackNames().Find(Name);
			if (TrackIndex == INDEX_NONE)
			{
				continue;
			}
			FRawAnimSequenceTrack Data = Sequence->GetRawAnimationTrack(TrackIndex);
			UAnimationBlueprintLibrary::RemoveBoneAnimation(Sequence, Name, false, false);
			if (Sequence->AddNewRawTrack(*To, &Data) == INDEX_NONE)
			{
				Report += FString::Printf(TEXT("ERROR: %s: the track of %s could not be put on %s\n"), *Sequence->GetPathName(), *Name.ToString(), *To->ToString());
				++Errors;
			}
		}
		// the root's children's keys under the flat root
		int32 Moved = 0;
		const TArray<FName>& Tracks = Sequence->GetAnimationTrackNames();
		for (int32 TrackIndex = 0; TrackIndex < Tracks.Num(); ++TrackIndex)
		{
			const int32 Bone = Ref.FindBoneIndex(Tracks[TrackIndex]);
			if (Bone > 0 && Ref.GetParentIndex(Bone) == 0)
			{
				FlattenTrackKeys(Sequence->GetRawAnimationTrack(TrackIndex), Delta);
				++Moved;
			}
		}
		Sequence->MarkRawDataAsModified();
		Package->GetMetaData()->SetValue(Sequence, FlattenDoneKey, *FlattenTransformText(OldRoot));
		Sequence->MarkPackageDirty();
		ToSave.AddUnique(Package);
		Sequences.Add(Sequence);
		if (Moved == 0)
		{
			Report += FString::Printf(TEXT("%s: no track under the root (its pose was already the rest pose's there)\n"), *Sequence->GetPathName());
		}
	}
	// saved; a file this engine saves broken is saved once more, and if it is still broken it is reported (never deleted
	// here: put its backup back)
	int32 Saved = 0;
	if (ToSave.Num() > 0)
	{
		for (UAnimSequence* Sequence : Sequences)
		{
			ReadyAnimationToSave(Sequence);
		}
		TArray<UPackage*> Failed;
		FEditorFileUtils::PromptForCheckoutAndSave(ToSave, false, false, &Failed);
		for (UAnimSequence* Sequence : Sequences)
		{
			UPackage* Package = Sequence->GetOutermost();
			if (Failed.Contains(Package))
			{
				Report += FString::Printf(TEXT("ERROR: %s was not saved\n"), *Package->GetName());
				++Errors;
				continue;
			}
			FString Problem = SavedAnimationProblem(Package->GetName());
			if (!Problem.IsEmpty())
			{
				ReadyAnimationToSave(Sequence);
				TArray<UPackage*> Again;
				Again.Add(Package);
				TArray<UPackage*> FailedAgain;
				FEditorFileUtils::PromptForCheckoutAndSave(Again, false, false, &FailedAgain);
				Problem = FailedAgain.Num() > 0 ? FString(TEXT("could not be saved again")) : SavedAnimationProblem(Package->GetName());
			}
			if (!Problem.IsEmpty())
			{
				Report += FString::Printf(TEXT("ERROR: %s: %s (put its backup back before cooking)\n"), *Package->GetName(), *Problem);
				++Errors;
				continue;
			}
			++Saved;
		}
	}
	Report += FString::Printf(TEXT("Animations %d to %d of %d: %d flattened and saved, %d done before, %d waiting for their base, %d error(s). %s\n"),
		First, End - 1, Found.Num(), Saved, Already, Waiting, Errors,
		End < Found.Num() ? *FString::Printf(TEXT("Next: First %d (%d left)."), End, Found.Num() - End) : TEXT("That was the last batch."));
	UE_LOG(LogTemp, Display, TEXT("Flatten Root: %s"), *Report.Right(400));
	return Report;
}

// ------------------------------------------------------------------------------------------------
// Cook For Game (editor 1.13.1). This engine keeps an Anim Sequence's compressed bytes as last loaded or saved
// (FCompressedAnimSequence::SerializedData) and checks, as it writes them, that the bytes it writes count as many as its
// byte stream: when the stream was compressed again in the session (shorter than before) and nothing loaded or saved the
// bytes since, that check stops the editor. So each animation is compressed (from the derived data cache when it has it)
// and its bytes are written out afresh right before the package is saved.
// ------------------------------------------------------------------------------------------------
namespace
{
void ReadyAnimationForCook(UAnimSequence* Sequence)
{
	if (!IsValid(Sequence))
	{
		return;
	}
	Sequence->WaitOnExistingCompression(true);
	ReadyAnimationToSave(Sequence);
	FCompressedAnimSequence& Data = Sequence->CompressedData;
	if (Data.BoneCompressionCodec && Data.CompressedDataStructure.IsValid())
	{
		Data.SerializedData.Reset();
		FMemoryWriter Writer(Data.SerializedData, true);
		Data.BoneCompressionCodec->ByteSwapOut(*Data.CompressedDataStructure, Data.CompressedByteStream, Writer);
	}
}
} // namespace

FString UEndSkeletonCompatDataObject::CookPackagesForGame(const TArray<FString>& PackageNames, const FString& OutContentDir)
{
	FString Report;
	const ITargetPlatform* Platform = GetTargetPlatformManagerRef().FindTargetPlatform(TEXT("WindowsNoEditor"));
	if (!Platform)
	{
		return TEXT("ERROR: the WindowsNoEditor target platform is not available in this editor\n");
	}
	TurnOffAclSafetyFallback(nullptr);
	int32 Cooked = 0;
	int32 Failed = 0;
	int32 Animations = 0;
	for (const FString& Name : PackageNames)
	{
		FString PackageName = Name.TrimStartAndEnd();
		if (PackageName.Contains(TEXT(".")))
		{
			PackageName = FPackageName::ObjectPathToPackageName(PackageName);
		}
		if (!PackageName.StartsWith(TEXT("/Game/")))
		{
			Report += FString::Printf(TEXT("ERROR: %s is not under /Game/\n"), *Name);
			++Failed;
			continue;
		}
		UPackage* Package = LoadPackage(nullptr, *PackageName, LOAD_None);
		if (!Package)
		{
			Report += FString::Printf(TEXT("ERROR: %s does not load\n"), *PackageName);
			++Failed;
			continue;
		}
		Package->FullyLoad();
		TArray<UObject*> Objects;
		GetObjectsWithOuter(Package, Objects, false);
		for (UObject* Object : Objects)
		{
			if (UAnimSequence* Sequence = Cast<UAnimSequence>(Object))
			{
				ReadyAnimationForCook(Sequence);
				++Animations;
			}
		}
		const FString Filename = FPaths::ConvertRelativePathToFull(OutContentDir / PackageName.RightChop(6) + TEXT(".uasset"));
		IPlatformFile::GetPlatformPhysical().CreateDirectoryTree(*FPaths::GetPath(Filename));
		const uint32 Flags = Package->GetPackageFlags();
		Package->SetPackageFlags(PKG_FilterEditorOnly);
		const bool bSaved = UPackage::SavePackage(Package, nullptr, RF_Public, *Filename, GError, nullptr, false, true,
			SAVE_NoError | SAVE_KeepGUID | SAVE_Unversioned, Platform);
		Package->SetPackageFlagsTo(Flags);
		if (bSaved)
		{
			++Cooked;
		}
		else
		{
			Report += FString::Printf(TEXT("ERROR: %s could not be cooked to %s\n"), *PackageName, *Filename);
			++Failed;
		}
	}
	Report += FString::Printf(TEXT("%d of %d package(s) cooked into %s (%d animation(s) readied), %d failed.\n"), Cooked, PackageNames.Num(),
		*OutContentDir, Animations, Failed);
	return Report;
}

// ------------------------------------------------------------------------------------------------
// Describe Animations (editor 1.10.2): what an animation (or an animation pack) has, for planning moves from it.
// ------------------------------------------------------------------------------------------------
FString UEndSkeletonCompatDataObject::DescribeAnimations(const TArray<FString>& AnimationPaths)
{
	TArray<TSharedPtr<FJsonValue>> List;
	for (const FString& Path : AnimationPaths)
	{
		TSharedRef<FJsonObject> Item = MakeShared<FJsonObject>();
		Item->SetStringField(TEXT("path"), Path);
		UObject* Object = FSoftObjectPath(NormalizedObjectPath(Path)).TryLoad();
		if (!Object)
		{
			Item->SetStringField(TEXT("error"), TEXT("does not load in this editor"));
			List.Add(MakeShared<FJsonValueObject>(Item));
			continue;
		}
		Item->SetStringField(TEXT("class"), Object->GetClass()->GetName());
		// An animation pack (UEndAnimSet): its animations by name.
		if (FMapProperty* Map = FindFProperty<FMapProperty>(Object->GetClass(), TEXT("AnimationAssets")))
		{
			FObjectPropertyBase* Value = CastField<FObjectPropertyBase>(Map->ValueProp);
			if (CastField<FNameProperty>(Map->KeyProp) && Value)
			{
				TSharedRef<FJsonObject> Entries = MakeShared<FJsonObject>();
				FScriptMapHelper Helper(Map, Map->ContainerPtrToValuePtr<void>(Object));
				for (int32 Index = 0; Index < Helper.GetMaxIndex(); ++Index)
				{
					if (Helper.IsValidIndex(Index))
					{
						const FName Key = *reinterpret_cast<const FName*>(Helper.GetKeyPtr(Index));
						Entries->SetStringField(Key.ToString(), PathOf(Value->GetObjectPropertyValue(Helper.GetValuePtr(Index))));
					}
				}
				Item->SetObjectField(TEXT("animations"), Entries);
			}
		}
		UAnimSequenceBase* Anim = Cast<UAnimSequenceBase>(Object);
		if (!Anim)
		{
			List.Add(MakeShared<FJsonValueObject>(Item));
			continue;
		}
		Item->SetNumberField(TEXT("length"), Anim->SequenceLength);
		Item->SetNumberField(TEXT("rate_scale"), Anim->RateScale);
		if (const USkeleton* Skeleton = Anim->GetSkeleton())
		{
			Item->SetStringField(TEXT("skeleton"), Skeleton->GetPathName());
		}
		if (const UAnimSequence* Sequence = Cast<UAnimSequence>(Anim))
		{
			Item->SetNumberField(TEXT("frames"), Sequence->GetRawNumberOfFrames());
			Item->SetBoolField(TEXT("root_motion"), Sequence->bEnableRootMotion);
			Item->SetNumberField(TEXT("root_lock"), static_cast<int32>(Sequence->RootMotionRootLock.GetValue()));
			Item->SetBoolField(TEXT("force_root_lock"), Sequence->bForceRootLock);
			Item->SetBoolField(TEXT("additive"), Sequence->IsValidAdditive());
		}
		if (const UAnimComposite* Composite = Cast<UAnimComposite>(Anim))
		{
			TArray<TSharedPtr<FJsonValue>> Segments;
			for (const FAnimSegment& Segment : Composite->AnimationTrack.AnimSegments)
			{
				TSharedRef<FJsonObject> S = MakeShared<FJsonObject>();
				S->SetStringField(TEXT("animation"), PathOf(Segment.AnimReference));
				S->SetNumberField(TEXT("start"), Segment.StartPos);
				S->SetNumberField(TEXT("from"), Segment.AnimStartTime);
				S->SetNumberField(TEXT("to"), Segment.AnimEndTime);
				S->SetNumberField(TEXT("rate"), Segment.AnimPlayRate);
				S->SetNumberField(TEXT("loops"), Segment.LoopingCount);                               // (1.12.3)
				S->SetBoolField(TEXT("its_notifies"), Segment.bTriggerAnimReferenceNotify);
				Segments.Add(MakeShared<FJsonValueObject>(S));
			}
			Item->SetArrayField(TEXT("segments"), Segments);
		}
		TArray<TSharedPtr<FJsonValue>> Notifies;
		for (const FAnimNotifyEvent& Event : Anim->Notifies)
		{
			TSharedRef<FJsonObject> N = MakeShared<FJsonObject>();
			N->SetNumberField(TEXT("time"), Event.GetTime());
			N->SetNumberField(TEXT("duration"), Event.GetDuration());
			N->SetNumberField(TEXT("track"), Event.TrackIndex);
			if (!Event.NotifyName.IsNone())
			{
				N->SetStringField(TEXT("name"), Event.NotifyName.ToString());
			}
			if (UObject* Notify = NotifyObject(Event))
			{
				N->SetStringField(TEXT("class"), Notify->GetClass()->GetName());
				N->SetBoolField(TEXT("hit"), IsHitNotify(Notify));
				N->SetBoolField(TEXT("motion"), IsMotionNotify(Notify));
				TSharedRef<FJsonObject> Settings = MakeShared<FJsonObject>();
				const UObject* Default = Notify->GetClass()->GetDefaultObject();
				for (TFieldIterator<FProperty> It(Notify->GetClass()); It; ++It)
				{
					const FProperty* Property = *It;
					if (Property->HasAnyPropertyFlags(CPF_Transient | CPF_DuplicateTransient) || Property->Identical_InContainer(Notify, Default))
					{
						continue;
					}
					FString Text;
					Property->ExportTextItem(Text, Property->ContainerPtrToValuePtr<void>(Notify), nullptr, Notify, PPF_None);
					Settings->SetStringField(Property->GetName(), Text.Left(600));
				}
				N->SetObjectField(TEXT("settings"), Settings);
			}
			Notifies.Add(MakeShared<FJsonValueObject>(N));
		}
		Item->SetArrayField(TEXT("notifies"), Notifies);
		TArray<TSharedPtr<FJsonValue>> Hits;
		for (const float Time : HitGroupTimes(PlayedNotifies(Anim)))
		{
			Hits.Add(MakeShared<FJsonValueNumber>(Time));
		}
		Item->SetArrayField(TEXT("hits"), Hits);
		List.Add(MakeShared<FJsonValueObject>(Item));
	}
	FString Out;
	const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out);
	FJsonSerializer::Serialize(List, Writer);
	return Out;
}

// ------------------------------------------------------------------------------------------------
// (editor 1.13) Notifies as they are, onto animations made frame for frame from another character's (retargeted key
// animations): every notify, sync marker and curve of the original, with all its settings.
// ------------------------------------------------------------------------------------------------
namespace
{
// A notify's copy for another animation: a new object of its class made with the original as its template, so every
// setting comes over as it is, links to sound banks and effects this project does not have and values the editor's types
// have no name for included (DuplicateObject writes the object and reads it back, which keeps neither). Effect parameters
// of the game's this editor cannot write come out (UnwritableNiagara), as in Build Moves; one it cannot take them out of is
// left out (nullptr).
template <class T>
T* CopyNotifyAsIs(T* Original, UObject* Outer, int32& EffectParameters, int32& NotifiesLeftOut)
{
	if (!Original)
	{
		return nullptr;
	}
	T* Copy = NewObject<T>(Outer, Original->GetClass(), NAME_None, RF_Transactional, Original);
	if (UnwritableNiagara::CountIn(Copy) > 0)
	{
		EffectParameters += UnwritableNiagara::DropInStruct(Copy->GetClass(), Copy, Copy, 0);
		if (UnwritableNiagara::CountIn(Copy) > 0)
		{
			Copy->Rename(nullptr, GetTransientPackage(), REN_DontCreateRedirectors | REN_NonTransactional | REN_ForceNoResetLoaders);
			Copy->MarkPendingKill();
			++NotifiesLeftOut;
			return nullptr;
		}
	}
	return Copy;
}

void LetGo(UObject* Object)
{
	if (Object && Object->GetOuter() != GetTransientPackage())
	{
		Object->Rename(nullptr, GetTransientPackage(), REN_DontCreateRedirectors | REN_NonTransactional | REN_ForceNoResetLoaders);
		Object->MarkPendingKill();
	}
}
} // namespace

FString UEndSkeletonCompatDataObject::CopyNotifiesOnto(const TArray<FString>& FromPaths, const TArray<FString>& ToPaths, bool bReplace)
{
	FString Report;
	TArray<UPackage*> ToSave;
	TArray<UAnimSequence*> Sequences;
	TArray<USkeleton*> SkeletonsChanged;
	int32 Pairs = 0, Copied = 0, EffectParameters = 0, LeftOut = 0, Markers = 0, Curves = 0, CurvesLeft = 0, Problems = 0;
	for (int32 Index = 0; Index < FromPaths.Num(); ++Index)
	{
		const FString& FromPath = FromPaths[Index];
		const FString ToPath = ToPaths.IsValidIndex(Index) ? ToPaths[Index] : FString();
		UAnimSequenceBase* From = Cast<UAnimSequenceBase>(FSoftObjectPath(NormalizedObjectPath(FromPath)).TryLoad());
		UAnimSequence* To = ToPath.IsEmpty() ? nullptr : Cast<UAnimSequence>(FSoftObjectPath(NormalizedObjectPath(ToPath)).TryLoad());
		if (!From || !To || From == To)
		{
			Report += FString::Printf(TEXT("%s -> %s: %s\n"), *FromPath, *ToPath, !From ? TEXT("the original does not load") : !To ? TEXT("not an Anim Sequence of this project") : TEXT("the same animation"));
			++Problems;
			continue;
		}
		UPackage* Package = To->GetOutermost();
		if (Package->HasAnyPackageFlags(PKG_Cooked | PKG_FilterEditorOnly))
		{
			Report += FString::Printf(TEXT("%s: one of the game's (cooked), not changed\n"), *ToPath);
			++Problems;
			continue;
		}
		To->Modify();
		if (bReplace)
		{
			for (FAnimNotifyEvent& Old : To->Notifies)
			{
				LetGo(Old.Notify);
				LetGo(Old.NotifyStateClass);
			}
			To->Notifies.Reset();
			To->AuthoredSyncMarkers.Reset();
			To->RawCurveData.FloatCurves.Reset();
#if WITH_EDITORONLY_DATA
			To->AnimNotifyTracks.Reset();
#endif
		}
		const float Scale = From->SequenceLength > KINDA_SMALL_NUMBER ? To->SequenceLength / From->SequenceLength : 1.f;
		const UAnimSequence* FromSequence = Cast<UAnimSequence>(From);
#if WITH_EDITORONLY_DATA
		int32 MostTrack = 0;
		for (const FAnimNotifyEvent& Event : From->Notifies)
		{
			MostTrack = FMath::Max(MostTrack, Event.TrackIndex);
		}
		if (FromSequence)
		{
			for (const FAnimSyncMarker& Marker : FromSequence->AuthoredSyncMarkers)
			{
				MostTrack = FMath::Max(MostTrack, Marker.TrackIndex);
			}
		}
		while (To->AnimNotifyTracks.Num() <= MostTrack)
		{
			const int32 Track = To->AnimNotifyTracks.Num();
			const bool bHas = From->AnimNotifyTracks.IsValidIndex(Track);
			To->AnimNotifyTracks.Add(FAnimNotifyTrack(bHas ? From->AnimNotifyTracks[Track].TrackName : FName(*FString::FromInt(Track + 1)),
													  bHas ? From->AnimNotifyTracks[Track].TrackColor : FLinearColor::White));
		}
#endif
		for (const FAnimNotifyEvent& Original : From->Notifies)
		{
			FAnimNotifyEvent Event = Original;
			if (Original.Notify)
			{
				Event.Notify = CopyNotifyAsIs<UAnimNotify>(Original.Notify, To, EffectParameters, LeftOut);
				if (!Event.Notify)
				{
					continue;
				}
			}
			if (Original.NotifyStateClass)
			{
				Event.NotifyStateClass = CopyNotifyAsIs<UAnimNotifyState>(Original.NotifyStateClass, To, EffectParameters, LeftOut);
				if (!Event.NotifyStateClass)
				{
					continue;
				}
			}
			const float Start = FMath::Max(Original.GetTime() * Scale, 0.f);
			Event.Link(To, Start);
			Event.TriggerTimeOffset = GetTriggerTimeOffsetForType(To->CalculateOffsetForNotify(Start));
			if (Event.NotifyStateClass)
			{
				// a window that runs past the end stays so (the game's own animations have them)
				const float End = Start + FMath::Max(Original.GetDuration() * Scale, 0.f);
				Event.EndLink.Link(To, End);
				Event.SetDuration(End - Start);
				Event.EndTriggerTimeOffset = GetTriggerTimeOffsetForType(To->CalculateOffsetForNotify(End));
			}
			else
			{
				Event.EndLink.Link(To, Start);
				Event.Duration = 0.f;
				Event.EndTriggerTimeOffset = 0.f;
			}
#if WITH_EDITORONLY_DATA
			Event.TrackIndex = FMath::Max(Original.TrackIndex, 0);
			Event.Guid = FGuid::NewGuid();
#endif
			To->Notifies.Add(Event);
			++Copied;
		}
		if (FromSequence)
		{
			for (const FAnimSyncMarker& Marker : FromSequence->AuthoredSyncMarkers)
			{
				FAnimSyncMarker New = Marker;
				New.Time = FMath::Clamp(Marker.Time * Scale, 0.f, To->SequenceLength);
#if WITH_EDITORONLY_DATA
				New.Guid = FGuid::NewGuid();
#endif
				To->AuthoredSyncMarkers.Add(New);
				++Markers;
			}
			// Curves by name: the target's skeleton gets the names it lacks when it is one of this project's.
			USkeleton* Skeleton = To->GetSkeleton();
			const bool bOwnSkeleton = Skeleton && !Skeleton->GetOutermost()->HasAnyPackageFlags(PKG_Cooked | PKG_FilterEditorOnly);
			bool bCurvesChanged = false;
			const auto CurveOf = [&](const FName& CurveName, int32 Flags) -> FFloatCurve*
			{
				FSmartName Smart;
				if (!Skeleton || !Skeleton->GetSmartNameByName(USkeleton::AnimCurveMappingName, CurveName, Smart))
				{
					if (!bOwnSkeleton || !Skeleton->AddSmartNameAndModify(USkeleton::AnimCurveMappingName, CurveName, Smart))
					{
						++CurvesLeft;
						return nullptr;
					}
					SkeletonsChanged.AddUnique(Skeleton);
				}
				To->RawCurveData.AddCurveData(Smart, Flags);
				bCurvesChanged = true;
				return static_cast<FFloatCurve*>(To->RawCurveData.GetCurveData(Smart.UID, ERawCurveTrackTypes::RCT_Float));
			};
			const int32 Frames = FMath::Max(To->GetRawNumberOfFrames(), 2);
			const float Step = To->SequenceLength / (Frames - 1);
			if (FromSequence->RawCurveData.FloatCurves.Num() > 0)
			{
				for (const FFloatCurve& Curve : FromSequence->RawCurveData.FloatCurves)
				{
					if (FFloatCurve* New = CurveOf(Curve.Name.DisplayName, Curve.GetCurveTypeFlags()))
					{
						for (int32 Frame = 0; Frame < Frames; ++Frame)
						{
							const float Time = FMath::Min(Frame * Step, To->SequenceLength);
							New->UpdateOrAddKey(Curve.FloatCurve.Eval(Time / Scale), Time);
						}
						++Curves;
					}
				}
			}
			else if (const UAnimCurveCompressionCodec* Codec = FromSequence->CompressedData.CurveCompressionCodec)
			{
				for (const FSmartName& CurveName : FromSequence->CompressedData.CompressedCurveNames)
				{
					if (FFloatCurve* New = CurveOf(CurveName.DisplayName, AACF_DefaultCurve))
					{
						for (int32 Frame = 0; Frame < Frames; ++Frame)
						{
							const float Time = FMath::Min(Frame * Step, To->SequenceLength);
							New->UpdateOrAddKey(Codec->DecompressCurve(FromSequence->CompressedData, CurveName.UID, Time / Scale), Time);
						}
						++Curves;
					}
				}
			}
			if (bCurvesChanged || bReplace)
			{
				To->MarkRawDataAsModified();
			}
		}
		To->SortSyncMarkers();
		To->RefreshSyncMarkerDataFromAuthored();
		To->RefreshCacheData();
		To->PostEditChange();
		To->MarkPackageDirty();
		ToSave.AddUnique(Package);
		Sequences.Add(To);
		++Pairs;
	}
	for (USkeleton* Skeleton : SkeletonsChanged)
	{
		Skeleton->MarkPackageDirty();
		ToSave.AddUnique(Skeleton->GetOutermost());
	}
	int32 Broken = 0;
	const int32 NotSaved = ToSave.Num() > 0 ? SaveAnimationPackages(ToSave, Sequences, Broken, Report).Num() : 0;
	Report += FString::Printf(TEXT("%d animation(s): %d notifies, %d sync marker(s), %d curve(s) copied"), Pairs, Copied, Markers, Curves);
	if (CurvesLeft > 0)
	{
		Report += FString::Printf(TEXT(", %d curve(s) left out (the target's skeleton is the game's and has no such name)"), CurvesLeft);
	}
	if (EffectParameters > 0)
	{
		Report += FString::Printf(TEXT(", %d effect parameter(s) of the game's that this editor cannot write taken out (they play with their own values)"), EffectParameters);
	}
	if (LeftOut > 0)
	{
		Report += FString::Printf(TEXT(", %d notify(ies) left out (effect parameters that could not be taken out)"), LeftOut);
	}
	if (SkeletonsChanged.Num() > 0)
	{
		Report += FString::Printf(TEXT(", curve names added to %d skeleton(s)"), SkeletonsChanged.Num());
	}
	if (Problems > 0)
	{
		Report += FString::Printf(TEXT(", %d pair(s) not copied"), Problems);
	}
	if (NotSaved > 0)
	{
		Report += FString::Printf(TEXT(", %d package(s) NOT saved"), NotSaved);
	}
	Report += TEXT(".\n");
	return Report;
}
