#include "RebirthMaterialInstanceOverrides.h"

#include "Editor.h"
#include "Engine/Texture.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceConstant.h"
#include "ScopedTransaction.h"
#include "UObject/Package.h"
#include "UObject/UnrealType.h"

namespace
{
	constexpr int32 MaxParametersPerKind = 4096;
	constexpr int32 MaxParentDepth = 64;

	bool ValidInfo(const FMaterialParameterInfo& Info)
	{
		const int32 Association = static_cast<int32>(Info.Association.GetValue());
		return !Info.Name.IsNone() && Association >= LayerParameter && Association <= GlobalParameter &&
			((Association == GlobalParameter && Info.Index == INDEX_NONE) ||
			 (Association != GlobalParameter && Info.Index >= 0 && Info.Index < MaxParametersPerKind));
	}

	template<typename EntryType>
	FMaterialParameterInfo GetInfo(const EntryType& Entry)
	{
		return FMaterialParameterInfo(Entry.Name, Entry.Association.GetValue(), Entry.Index);
	}

	bool ValidValue(float Value) { return FMath::IsFinite(Value); }
	bool ValidValue(const FLinearColor& Value)
	{
		return FMath::IsFinite(Value.R) && FMath::IsFinite(Value.G) && FMath::IsFinite(Value.B) && FMath::IsFinite(Value.A);
	}
	bool ValidValue(UTexture* Value)
	{
		return Value == nullptr || (IsValid(Value) && !Value->HasAnyFlags(RF_BeginDestroyed | RF_FinishDestroyed | RF_NeedLoad | RF_NeedPostLoad | RF_NeedPostLoadSubobjects));
	}

	template<typename NativeType>
	const NativeType* FindOwn(const TArray<NativeType>& Own, const FMaterialParameterInfo& Info, int32& OutCount)
	{
		const NativeType* Found = nullptr;
		OutCount = 0;
		for (const NativeType& Candidate : Own)
		{
			if (Candidate.ParameterInfo == Info)
			{
				Found = &Candidate;
				++OutCount;
			}
		}
		return Found;
	}

	template<typename EntryType, typename NativeType, typename GetterType>
	bool BuildEntries(const TArray<FMaterialParameterInfo>& Advertised, const TArray<NativeType>& Own,
		TArray<FMaterialParameterInfo>& OutInfos, TArray<EntryType>& OutEntries, GetterType Getter,
		bool bAllowUnsetValue, FString& OutError)
	{
		if (Advertised.Num() > MaxParametersPerKind || Own.Num() > MaxParametersPerKind)
		{
			OutError = TEXT("parameter_count_limit");
			return false;
		}
		TSet<FHashedMaterialParameterInfo> Seen;
		for (const FMaterialParameterInfo& Info : Advertised)
		{
			if (!ValidInfo(Info))
			{
				OutError = TEXT("invalid_runtime_parameter_identity");
				return false;
			}
			const FHashedMaterialParameterInfo HashedInfo(Info);
			if (Seen.Contains(HashedInfo))
			{
				continue;
			}
			Seen.Add(HashedInfo);
			int32 OwnCount = 0;
			const NativeType* OwnValue = FindOwn(Own, Info, OwnCount);
			if (OwnCount > 1)
			{
				OutError = FString::Printf(TEXT("ambiguous_duplicate_own_override:%s"), *Info.Name.ToString());
				return false;
			}
			EntryType Entry;
			Entry.Name = Info.Name;
			Entry.Association = Info.Association;
			Entry.Index = Info.Index;
			Entry.bOverride = OwnValue != nullptr;
			const bool bResolved = Getter(HashedInfo, Entry.Value);
			if (OwnValue)
			{
				// Keep exact own values, including a legitimate null texture entry.
				Entry.Value = OwnValue->ParameterValue;
			}
			else if (!bResolved && !bAllowUnsetValue)
			{
				OutError = FString::Printf(TEXT("runtime_parameter_value_unavailable:%s"), *Info.Name.ToString());
				return false;
			}
			if (!ValidValue(Entry.Value))
			{
				OutError = FString::Printf(TEXT("invalid_runtime_parameter_value:%s"), *Info.Name.ToString());
				return false;
			}
			OutInfos.Add(Info);
			OutEntries.Add(Entry);
		}
		return true;
	}

	template<typename EntryType, typename NativeType>
	bool PlanChanges(const TArray<EntryType>& Entries, const TArray<EntryType>& Baseline,
		const TArray<FMaterialParameterInfo>& Infos, TArray<NativeType>& Planned, bool& bChanged, FString& OutError)
	{
		if (Entries.Num() != Infos.Num() || Baseline.Num() != Infos.Num() || Entries.Num() > MaxParametersPerKind)
		{
			OutError = TEXT("model_parameter_list_changed_refresh_required");
			return false;
		}
		for (int32 Index = 0; Index < Entries.Num(); ++Index)
		{
			const EntryType& Entry = Entries[Index];
			const EntryType& Before = Baseline[Index];
			const FMaterialParameterInfo& Info = Infos[Index];
			if (GetInfo(Entry) != Info || GetInfo(Before) != Info)
			{
				OutError = TEXT("readonly_parameter_identity_changed");
				return false;
			}
			if (Entry.bOverride == Before.bOverride && (!Entry.bOverride || Entry.Value == Before.Value))
			{
				continue; // An inherited value is display data, never an implicit override.
			}
			if (Entry.bOverride && !ValidValue(Entry.Value))
			{
				OutError = TEXT("invalid_edited_parameter_value");
				return false;
			}
			int32 OwnCount = 0;
			const NativeType* Own = FindOwn(Planned, Info, OwnCount);
			if (OwnCount > 1)
			{
				OutError = TEXT("ambiguous_duplicate_own_override_refresh_required");
				return false;
			}
			const bool bAlreadyRequested = Entry.bOverride ? Own && Own->ParameterValue == Entry.Value : Own == nullptr;
			if (bAlreadyRequested)
			{
				continue;
			}
			if ((Own != nullptr) != Before.bOverride || (Own && Own->ParameterValue != Before.Value))
			{
				OutError = FString::Printf(TEXT("source_override_changed_refresh_required:%s"), *Info.Name.ToString());
				return false;
			}
			if (!Entry.bOverride)
			{
				Planned.RemoveAll([&Info](const NativeType& Candidate) { return Candidate.ParameterInfo == Info; });
			}
			else
			{
				NativeType* Destination = Planned.FindByPredicate([&Info](const NativeType& Candidate) { return Candidate.ParameterInfo == Info; });
				if (!Destination)
				{
					if (Planned.Num() >= MaxParametersPerKind)
					{
						OutError = TEXT("own_override_count_limit");
						return false;
					}
					const int32 NewIndex = Planned.AddDefaulted();
					Destination = &Planned[NewIndex];
					Destination->ParameterInfo = Info;
					Destination->ExpressionGUID.Invalidate(); // Same identity policy as native uniform setters.
				}
				// Existing GUIDs, scalar AtlasData, and all other native fields remain untouched.
				Destination->ParameterValue = Entry.Value;
			}
			bChanged = true;
		}
		return true;
	}

	template<typename StaticEntryType>
	bool IsStableStaticArray(const TArray<StaticEntryType>& Entries)
	{
		if (Entries.Num() > MaxParametersPerKind)
		{
			return false;
		}
		for (const StaticEntryType& Entry : Entries)
		{
			if (!Entry.bOverride)
			{
				return false; // Native PostEditChange would otherwise trim this entry.
			}
		}
		return true;
	}
}

URebirthMaterialInstanceOverrides::URebirthMaterialInstanceOverrides()
	: Source(nullptr), InitializedParent(nullptr)
{
	SetFlags(RF_Transactional);
}

bool URebirthMaterialInstanceOverrides::ValidateSource(FString& OutError) const
{
	if (!IsInGameThread() || !IsValid(Source) || Source->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
	{
		OutError = TEXT("editable_material_instance_required_on_game_thread");
		return false;
	}
	if (Source->GetOutermost()->bIsCookedForEditor || Source->GetOutermost()->HasAnyPackageFlags(PKG_Cooked | PKG_FilterEditorOnly))
	{
		OutError = TEXT("cooked_source_is_readonly_create_an_uncooked_child_instance");
		return false;
	}
	if (InitializedParent && Source->Parent != InitializedParent)
	{
		OutError = TEXT("source_parent_changed_reinitialize_required");
		return false;
	}
	TSet<UMaterialInterface*> Seen;
	UMaterialInterface* Current = Source;
	while (Current)
	{
		if (!IsValid(Current) || Current->HasAnyFlags(RF_BeginDestroyed | RF_FinishDestroyed | RF_NeedLoad | RF_NeedPostLoad | RF_NeedPostLoadSubobjects) || Seen.Contains(Current) || Seen.Num() >= MaxParentDepth)
		{
			OutError = TEXT("invalid_incomplete_or_cyclic_material_parent_chain");
			return false;
		}
		Seen.Add(Current);
		if (UMaterialInstance* Instance = Cast<UMaterialInstance>(Current))
		{
			if (Instance->ScalarParameterValues.Num() > MaxParametersPerKind || Instance->VectorParameterValues.Num() > MaxParametersPerKind || Instance->TextureParameterValues.Num() > MaxParametersPerKind)
			{
				OutError = TEXT("parent_own_parameter_count_limit");
				return false;
			}
			Current = Instance->Parent;
		}
		else if (Cast<UMaterial>(Current))
		{
			break;
		}
		else
		{
			OutError = TEXT("unsupported_material_parent_interface");
			return false;
		}
	}
	if (!Current)
	{
		OutError = TEXT("material_parent_chain_has_no_base_material");
		return false;
	}
	const FStaticParameterSet& Static = Source->GetStaticParameters();
	if (!IsStableStaticArray(Static.StaticSwitchParameters) || !IsStableStaticArray(Static.StaticComponentMaskParameters) || !IsStableStaticArray(Static.TerrainLayerWeightParameters) || !IsStableStaticArray(Static.MaterialLayersParameters))
	{
		OutError = TEXT("stale_static_parameters_would_change_during_native_post_edit");
		return false;
	}
	const bool bWantsStaticPermutation = Source->Parent && (!Static.IsEmpty() || Source->HasOverridenBaseProperties());
	if (static_cast<bool>(Source->bHasStaticPermutationResource) != bWantsStaticPermutation)
	{
		OutError = TEXT("inconsistent_static_permutation_state_would_recompile");
		return false;
	}
	return true;
}

bool URebirthMaterialInstanceOverrides::Initialize(UMaterialInstanceConstant* InSource)
{
	TGuardValue<bool> Guard(bSynchronizing, true);
	Source = InSource;
	InitializedParent = nullptr;
	Scalars.Reset(); Vectors.Reset(); Textures.Reset();
	ScalarInfos.Reset(); VectorInfos.Reset(); TextureInfos.Reset();
	ScalarBaseline.Reset(); VectorBaseline.Reset(); TextureBaseline.Reset();
	if (!RefreshFromSource())
	{
		Source = nullptr;
		return false;
	}
	InitializedParent = Source->Parent;
	Source->SetFlags(RF_Transactional);
	return true;
}

bool URebirthMaterialInstanceOverrides::RefreshFromSource()
{
	TGuardValue<bool> Guard(bSynchronizing, true);
	LastError.Reset();
	if (!ValidateSource(LastError))
	{
		return false;
	}
	TArray<FMaterialParameterInfo> AdvertisedScalars, AdvertisedVectors, AdvertisedTextures;
	TArray<FGuid> IgnoredGuids;
	Source->GetAllScalarParameterInfo(AdvertisedScalars, IgnoredGuids);
	Source->GetAllVectorParameterInfo(AdvertisedVectors, IgnoredGuids);
	Source->GetAllTextureParameterInfo(AdvertisedTextures, IgnoredGuids);
	TArray<FMaterialParameterInfo> NewScalarInfos, NewVectorInfos, NewTextureInfos;
	TArray<FRebirthScalarMaterialOverride> NewScalars;
	TArray<FRebirthVectorMaterialOverride> NewVectors;
	TArray<FRebirthTextureMaterialOverride> NewTextures;
	if (!BuildEntries(AdvertisedScalars, Source->ScalarParameterValues, NewScalarInfos, NewScalars,
		[this](const FHashedMaterialParameterInfo& Info, float& Value) { return Source->GetScalarParameterValue(Info, Value); }, false, LastError) ||
		!BuildEntries(AdvertisedVectors, Source->VectorParameterValues, NewVectorInfos, NewVectors,
		[this](const FHashedMaterialParameterInfo& Info, FLinearColor& Value) { return Source->GetVectorParameterValue(Info, Value); }, false, LastError) ||
		!BuildEntries(AdvertisedTextures, Source->TextureParameterValues, NewTextureInfos, NewTextures,
		[this](const FHashedMaterialParameterInfo& Info, UTexture*& Value) { return Source->GetTextureParameterValue(Info, Value); }, true, LastError))
	{
		return false;
	}
	ScalarInfos = MoveTemp(NewScalarInfos); VectorInfos = MoveTemp(NewVectorInfos); TextureInfos = MoveTemp(NewTextureInfos);
	Scalars = MoveTemp(NewScalars); Vectors = MoveTemp(NewVectors); Textures = MoveTemp(NewTextures);
	ScalarBaseline = Scalars; VectorBaseline = Vectors; TextureBaseline = Textures;
	return true;
}

bool URebirthMaterialInstanceOverrides::ApplyKinds(uint8 Kinds)
{
	if (bSynchronizing)
	{
		return true;
	}
	LastError.Reset();
	if (!ValidateSource(LastError))
	{
		return false;
	}
	TArray<FScalarParameterValue> NewScalars = Source->ScalarParameterValues;
	TArray<FVectorParameterValue> NewVectors = Source->VectorParameterValues;
	TArray<FTextureParameterValue> NewTextures = Source->TextureParameterValues;
	bool bScalarsChanged = false, bVectorsChanged = false, bTexturesChanged = false;
	if (((Kinds & ScalarKind) && !PlanChanges(Scalars, ScalarBaseline, ScalarInfos, NewScalars, bScalarsChanged, LastError)) ||
		((Kinds & VectorKind) && !PlanChanges(Vectors, VectorBaseline, VectorInfos, NewVectors, bVectorsChanged, LastError)) ||
		((Kinds & TextureKind) && !PlanChanges(Textures, TextureBaseline, TextureInfos, NewTextures, bTexturesChanged, LastError)))
	{
		return false;
	}
	if (!bScalarsChanged && !bVectorsChanged && !bTexturesChanged)
	{
		return true;
	}
	const FScopedTransaction Transaction(NSLOCTEXT("RebirthMaterialPreview", "EditUniformOverrides", "Edit material instance uniform overrides"), GEditor && !GEditor->IsTransactionActive());
	Modify();
	Source->Modify();
	if (bScalarsChanged) { Source->ScalarParameterValues = MoveTemp(NewScalars); }
	if (bVectorsChanged) { Source->VectorParameterValues = MoveTemp(NewVectors); }
	if (bTexturesChanged) { Source->TextureParameterValues = MoveTemp(NewTextures); }
	Source->MarkPackageDirty();
	Source->PostEditChange();
	return RefreshFromSource();
}

bool URebirthMaterialInstanceOverrides::ApplyChanges()
{
	return ApplyKinds(AllKinds);
}

#if WITH_EDITOR
void URebirthMaterialInstanceOverrides::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (bSynchronizing)
	{
		return;
	}
	const FName MemberName = PropertyChangedEvent.MemberProperty ? PropertyChangedEvent.MemberProperty->GetFName() : NAME_None;
	if (MemberName == GET_MEMBER_NAME_CHECKED(URebirthMaterialInstanceOverrides, Scalars)) { ApplyKinds(ScalarKind); }
	else if (MemberName == GET_MEMBER_NAME_CHECKED(URebirthMaterialInstanceOverrides, Vectors)) { ApplyKinds(VectorKind); }
	else if (MemberName == GET_MEMBER_NAME_CHECKED(URebirthMaterialInstanceOverrides, Textures)) { ApplyKinds(TextureKind); }
}

void URebirthMaterialInstanceOverrides::PostEditUndo()
{
	TGuardValue<bool> Guard(bSynchronizing, true);
	Super::PostEditUndo(); // Calls PostEditChange; the guard prevents writes back into the restored source.
	RefreshFromSource(); // Native transactions restore all records before any PostEditUndo callbacks.
}
#endif
