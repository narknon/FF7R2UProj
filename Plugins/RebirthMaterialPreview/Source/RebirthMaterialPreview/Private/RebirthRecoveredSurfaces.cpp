#include "RebirthRecoveredSurfaces.h"

#include "RebirthPersonaPreviewSupport.h"
#include "Containers/Ticker.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/StaticMesh.h"
#include "Engine/Texture.h"
#include "HAL/IConsoleManager.h"
#include "HAL/PlatformTime.h"
#include "Logging/LogMacros.h"
#include "MaterialCachedData.h"
#include "MaterialExpressionShaderResourceBufferObjectParameter.h"
#include "MaterialShared.h"
#include "RenderingThread.h"
#include "Materials/Material.h"
#include "Materials/MaterialExpressionConstant.h"
#include "Materials/MaterialExpressionCustom.h"
#include "Materials/MaterialExpressionParameter.h"
#include "Materials/MaterialExpressionScalarParameter.h"
#include "Materials/MaterialExpressionStaticSwitchParameter.h"
#include "Materials/MaterialExpressionTextureBase.h"
#include "Materials/MaterialExpressionTextureCoordinate.h"
#include "Materials/MaterialExpressionTextureObjectParameter.h"
#include "Materials/MaterialExpressionTextureSampleParameter.h"
#include "Materials/MaterialExpressionVectorParameter.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Misc/SecureHash.h"
#include "UObject/Package.h"
#include "UObject/StrongObjectPtr.h"
#include "UObject/UObjectGlobals.h"
#include "Misc/PackageName.h"
#include "HAL/PlatformTime.h"
#include "UObject/UObjectHash.h"
#include "UObject/UObjectIterator.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthRecoveredSurfaces, Log, All);

namespace
{
	const TCHAR* const RecoveredRetailSurfacePath = TEXT("/Game/Renderer/Material/RM_Surface.RM_Surface");
	// Bump when the generated master recipe changes: it seeds the deterministic StateIds (and so the DDC keys).
	const TCHAR* const RecoveredRecipeIdentity = TEXT("RebirthRecoveredSurface/4");
	const TCHAR* const RecoveredBlueNoisePath = TEXT("/Engine/EngineResources/SpatiotemporalBlueNoiseVolumeSource.SpatiotemporalBlueNoiseVolumeSource");
	const TCHAR* const RecoveredCoverageSwitchText = TEXT("Coverage_");

	/** RM_Surface's static switches (retail RMI_Surface_* instances and the editable RM_Surface). Declared on every master
	 *  (unconnected unless the family implements it) so the Material Instance Editor keeps an instance's switch overrides. */
	const TCHAR* const RecoveredRetailSwitchNames[] =
	{
		TEXT("AnimateTime_"), TEXT("Color_"), TEXT("Coordinate0_"), TEXT("Coordinate1_"), TEXT("Coordinate2_"), TEXT("Coordinate3_"),
		TEXT("Coverage_"), TEXT("CoverageIdentifier_"), TEXT("CoverageIdentifierCoordinate0_"), TEXT("CoverageIdentifierCoordinate1_"),
		TEXT("CoverageIdentifierCoordinate2_"), TEXT("CoverageIdentifierCoordinate3_"), TEXT("CylindricalNormal_"), TEXT("Deform_"),
		TEXT("Detail_"), TEXT("DetailColor_"), TEXT("DetailCoverage_"), TEXT("DetailFoam_"), TEXT("DetailMetallic_"), TEXT("DetailNormal_"),
		TEXT("DetailOcclusion_"), TEXT("DetailRoughness_"), TEXT("Diffusion_"), TEXT("Emissive_"), TEXT("ExternalEmissive_"), TEXT("Eye_"),
		TEXT("EyeMigration_"), TEXT("Fabric_"), TEXT("Flow_"), TEXT("FlowDetailFoam_"), TEXT("FlowDetailNormal_"), TEXT("FlowDetailRoughness_"),
		TEXT("FlowDirection_"), TEXT("FlowFoam_"), TEXT("FlowNormal_"), TEXT("FlowRoughness_"), TEXT("Foam_"), TEXT("Froth_"),
		TEXT("GazeNormal_"), TEXT("GenericVector_"), TEXT("Gradient_"), TEXT("GradientNormal_"), TEXT("GradientOcclusion_"),
		TEXT("GradientPhase_"), TEXT("GradientRoughness_"), TEXT("Hair_"), TEXT("IrisColor_"), TEXT("IrisEmissive_"), TEXT("IrisNormal_"),
		TEXT("IrisOcclusion_"), TEXT("Isotropy_"), TEXT("Layered_"), TEXT("LayeredColor_"), TEXT("Metallic_"), TEXT("Muddiness_"),
		TEXT("Normal_"), TEXT("Occlusion_"), TEXT("Ocean_"), TEXT("OceanGeometry_"), TEXT("OceanMagnitude_"), TEXT("Opacity_"),
		TEXT("PhaseGCrystal_"), TEXT("PhaseGGlass_"), TEXT("PhaseGWater_"), TEXT("Pool_"), TEXT("Pores_"), TEXT("PositiveTransitionNormal_"),
		TEXT("ReflectanceCrystal_"), TEXT("ReflectanceGlass_"), TEXT("ReflectanceWater_"), TEXT("RigidBody_"), TEXT("Roughness_"),
		TEXT("ScleraNormal_"), TEXT("Segmented_"), TEXT("SegmentLayer0_"), TEXT("SegmentLayer1_"), TEXT("ShadingLayer_"), TEXT("Skin_"),
		TEXT("SkinnedBody_"), TEXT("SoftBody_"), TEXT("Standard_"), TEXT("Thick_"), TEXT("Thickness_"), TEXT("Thin_"), TEXT("Thinness_"),
		TEXT("Transmittance_"), TEXT("TransmittanceCoefficient_"), TEXT("Transparency_"), TEXT("TransparencyCoefficient_"),
		TEXT("VertexExpression_"), TEXT("VertexExpressionBone_"), TEXT("VertexExpressionOcean_"), TEXT("Wetness_"), TEXT("WetnessTrickle_"),
		TEXT("WideBentNormal_"), TEXT("WideFlowDirectivity_"), TEXT("WideFlowPhase_"), TEXT("WideFoamThreshold_"), TEXT("WideOcclusion_"),
	};

	enum class ERecoveredFamily : uint8
	{
		StandardWide,
		StandardWideDetail,
		CoverageWide,
		FabricWide,
		SkinDynamic,
		HairWide,
		EyeMigration,
		Rebuilt,   // RM_Surface itself, rebuilt (editable): every static permutation of the game's, each instance its own switches
	};

	struct FRecoveredFamilySource
	{
		ERecoveredFamily Family;
		const TCHAR* Key;
		const TCHAR* ObjectPath;
		bool bNativeCoverage;   // the family master already applies the retail stochastic coverage
		bool bCoverageCapable;  // the Coverage_ switch adds it
	};

	const FRecoveredFamilySource RecoveredFamilySources[] =
	{
		{ ERecoveredFamily::StandardWide, TEXT("StandardWide"), TEXT("/Game/RebirthCompatibility/EditorPreview/MaterialFamilies/M_RetailStandardWide_b9f4de247751da36FreshV10.M_RetailStandardWide_b9f4de247751da36FreshV10"), false, true },
		{ ERecoveredFamily::StandardWideDetail, TEXT("StandardWideDetail"), TEXT("/Game/RebirthCompatibility/EditorPreview/MaterialFamilies/M_RetailStandardWideDetail_842518d2f9e0abb2FreshV10.M_RetailStandardWideDetail_842518d2f9e0abb2FreshV10"), false, true },
		{ ERecoveredFamily::CoverageWide, TEXT("CoverageWide"), TEXT("/Game/RebirthCompatibility/EditorPreview/MaterialFamilies/M_RetailCoverageWide_e680d1c12a2d687dFreshV10.M_RetailCoverageWide_e680d1c12a2d687dFreshV10"), true, false },
		{ ERecoveredFamily::FabricWide, TEXT("FabricWide"), TEXT("/Game/RebirthCompatibility/EditorPreview/MaterialFamilies/M_RetailFabricWide_c8ed2a5196de2fb7FreshV10.M_RetailFabricWide_c8ed2a5196de2fb7FreshV10"), false, true },
		{ ERecoveredFamily::SkinDynamic, TEXT("SkinDynamic"), TEXT("/Game/RebirthCompatibility/EditorPreview/MaterialFamilies/M_RetailSkinDynamic_0fd6ae139d33d15fFreshV10.M_RetailSkinDynamic_0fd6ae139d33d15fFreshV10"), false, true },
		{ ERecoveredFamily::HairWide, TEXT("HairWide"), TEXT("/Game/RebirthCompatibility/EditorPreview/RecoveredHair/M_RecoveredHairWide.M_RecoveredHairWide"), true, false },
		{ ERecoveredFamily::EyeMigration, TEXT("EyeMigration"), TEXT("/Game/RebirthCompatibility/EditorPreview/RecoveredEye/M_RecoveredEyeMigration.M_RecoveredEyeMigration"), false, false },
		{ ERecoveredFamily::Rebuilt, TEXT("Rebuilt"), TEXT("/Game/Renderer/Material/RM_Surface.RM_Surface"), true, false },
	};

	/** What an instance renders as in game: its effective static switches and base property overrides. */
	struct FRecoveredPermutation
	{
		TSet<FName> Switches;
		bool bBlendMode = false;
		TEnumAsByte<EBlendMode> BlendMode = BLEND_Opaque;
		bool bTwoSided = false;
		bool TwoSided = false;
		bool bClip = false;
		float Clip = 0.3333f;
		bool bDithered = false;
		bool Dithered = false;
		bool bCastMasked = false;
		bool CastMasked = false;
	};

	/**
	 * CookedBridge: a cooked instance cannot compile a static permutation of its own in this editor, so it is pointed at a
	 * transient bridge instance that carries its permutation (and the values it inherited from cooked parents); its own
	 * static parameters are cleared in memory. EditableParent: an editable direct child of RM_Surface keeps everything and
	 * only its parent changes to the family master, which declares every RM_Surface switch; saving puts RM_Surface back.
	 */
	enum class ERecoveredStyle : uint8
	{
		CookedBridge,
		EditableParent,
	};

	struct FRecoveredPlan
	{
		TWeakObjectPtr<UMaterialInstance> Instance;
		TWeakObjectPtr<UMaterial> Retail;
		FRecoveredPermutation Permutation;
		TArray<TWeakObjectPtr<UMaterialInstance>> Ancestors; // original cooked parents below RM_Surface, nearest first
		ERecoveredFamily Family = ERecoveredFamily::StandardWide;
		ERecoveredStyle Style = ERecoveredStyle::CookedBridge;
		bool bCoverage = false;
	};

	struct FRecoveredRecord
	{
		TWeakObjectPtr<UMaterialInterface> OriginalParent;
		TWeakObjectPtr<UMaterialInterface> RedirectParent;
		FStaticParameterSet OriginalStaticParameters;
		FMaterialInstanceBasePropertyOverrides OriginalBasePropertyOverrides;
		bool bNeutralized = false;
		FString Description;
	};

	TAutoConsoleVariable<int32> CVarRecoveredSurfaces(
		TEXT("Rebirth.RecoveredSurfaces"),
		0,
		TEXT("1: in the editor, RM_Surface materials (cooked or editable) render through the recovered retail surface families. ")
		TEXT("In memory only: saved assets keep their real parents and cooks are unchanged. 0 (default): render them with RM_Surface itself (their real parents and switches)."),
		ECVF_Default);

	TAutoConsoleVariable<int32> CVarRecoveredSurfacesRebuilt(
		TEXT("Rebirth.RecoveredSurfaces.Rebuilt"),
		1,
		TEXT("1 (default): when /Game/Renderer/Material/RM_Surface is the rebuilt, editable RM_Surface (all of the game's static ")
		TEXT("permutations, checked against its shaders), cooked RM_Surface instances render through it, each with its own static ")
		TEXT("switches, and editable ones use it directly. 0: the older recovered families. Takes effect for instances redirected ")
		TEXT("afterwards (Rebirth.RecoveredSurfaces.Restore, then reopen)."),
		ECVF_Default);

	/** A blend mode this engine can render: the game's own extra ones (BLEND_AlphaCompositeColored, 7) become the nearest
	 * one it has (BLEND_AlphaComposite). Unmapped, the value draws with no blend state and the renderer asserts. */
	EBlendMode RecoveredSupportedBlend(int32 Value)
	{
		if (Value >= 0 && Value < static_cast<int32>(BLEND_MAX))
		{
			return static_cast<EBlendMode>(Value);
		}
		return BLEND_AlphaComposite;
	}

	TMap<FString, TStrongObjectPtr<UMaterial>> GRecoveredMasters;
	TMap<FString, FString> GRecoveredMasterErrors;
	TMap<FString, TStrongObjectPtr<UMaterialInstanceConstant>> GRecoveredBridges; // one per redirected cooked instance
	TMap<TWeakObjectPtr<UMaterialInstance>, FRecoveredRecord> GRecoveredRecords;
	TSet<TWeakObjectPtr<UMaterialInstance>> GRecoveredPending;
	TSet<TWeakObjectPtr<UMaterialInstance>> GRecoveredSkipped;
	TSet<TWeakObjectPtr<UMaterialInstance>> GRecoveredRefresh; // parents put back by a save; re-applied on the next tick
	TSet<FName> GRecoveredUnknownSwitches;
	TWeakObjectPtr<UMaterial> GRecoveredRetailBase;
	FDelegateHandle GRecoveredAssetLoadedHandle;
	FDelegateHandle GRecoveredObjectSavedHandle;
	FDelegateHandle GRecoveredTickerHandle;
	double GRecoveredNextScanSeconds = 0.0;
	bool bGRecoveredWasEnabled = true;
	TUniquePtr<FAutoConsoleCommand> GRecoveredRestoreCommand;
	TUniquePtr<FAutoConsoleCommand> GRecoveredStatusCommand;

	bool RecoveredIsEnabled()
	{
		return CVarRecoveredSurfaces.GetValueOnGameThread() != 0;
	}

	const FName& RecoveredCoverageSwitchName()
	{
		static const FName Name(RecoveredCoverageSwitchText);
		return Name;
	}

	bool RecoveredIsCookedObject(const UObject* Object)
	{
		const UPackage* Package = Object ? Object->GetOutermost() : nullptr;
		return Package && (Package->bIsCookedForEditor || Package->HasAnyPackageFlags(PKG_Cooked | PKG_FilterEditorOnly));
	}

	FGuid RecoveredGuid(const FString& Text)
	{
		FSHA1 Sha;
		Sha.UpdateWithString(*Text, Text.Len());
		Sha.Final();
		uint32 Hash[5];
		Sha.GetHash(reinterpret_cast<uint8*>(Hash));
		return FGuid(Hash[0], Hash[1], Hash[2], Hash[3]);
	}

	EMaterialSamplerType RecoveredSamplerTypeOf(const UTexture* Texture)
	{
		return UMaterialExpressionTextureBase::GetSamplerTypeForTexture(Texture);
	}

	/** RM_Surface (cooked retail or the project's editable copy), when Material is it. */
	UMaterial* RecoveredRetailSurfaceOf(UMaterialInterface* Material)
	{
		static const FName RetailName(TEXT("RM_Surface"));
		static const FName RetailPackageName(TEXT("/Game/Renderer/Material/RM_Surface"));
		UMaterial* Base = Cast<UMaterial>(Material);
		if (!Base || Base->GetFName() != RetailName || Base->GetOuter() != Base->GetOutermost() ||
			Base->GetOutermost()->GetFName() != RetailPackageName || Base->HasAnyFlags(RF_Transient))
		{
			return nullptr;
		}
		GRecoveredRetailBase = Base;
		return Base;
	}

	bool RecoveredIsMaster(const UMaterialInterface* Material)
	{
		if (!Material) { return false; }
		for (const TPair<FString, TStrongObjectPtr<UMaterial>>& Pair : GRecoveredMasters)
		{
			if (Pair.Value.Get() == Material) { return true; }
		}
		return false;
	}

	const FRecoveredRecord* RecoveredRecordOf(const UMaterialInstance* Instance)
	{
		return Instance ? GRecoveredRecords.Find(TWeakObjectPtr<UMaterialInstance>(const_cast<UMaterialInstance*>(Instance))) : nullptr;
	}

	/** The record of the instance a transient recovered parent was made for (bridges are per instance). */
	const FRecoveredRecord* RecoveredRecordOfRedirectParent(const UMaterialInterface* Parent)
	{
		if (!Parent) { return nullptr; }
		for (const TPair<TWeakObjectPtr<UMaterialInstance>, FRecoveredRecord>& Pair : GRecoveredRecords)
		{
			if (Pair.Value.RedirectParent.Get() == Parent) { return &Pair.Value; }
		}
		return nullptr;
	}

	UMaterialInterface* RecoveredOriginalParent(const UMaterialInstance* Instance)
	{
		const FRecoveredRecord* Record = RecoveredRecordOf(Instance);
		return Record ? Record->OriginalParent.Get() : Instance->Parent;
	}

	const FStaticParameterSet& RecoveredOriginalStatic(const UMaterialInstance* Instance)
	{
		const FRecoveredRecord* Record = RecoveredRecordOf(Instance);
		return Record ? Record->OriginalStaticParameters : Instance->GetStaticParameters();
	}

	const FMaterialInstanceBasePropertyOverrides& RecoveredOriginalOverrides(const UMaterialInstance* Instance)
	{
		const FRecoveredRecord* Record = RecoveredRecordOf(Instance);
		return Record ? Record->OriginalBasePropertyOverrides : Instance->BasePropertyOverrides;
	}

	bool RecoveredHasOverrideFlags(const FMaterialInstanceBasePropertyOverrides& Overrides)
	{
		return Overrides.bOverride_OpacityMaskClipValue || Overrides.bOverride_BlendMode || Overrides.bOverride_ShadingModel ||
			Overrides.bOverride_DitheredLODTransition || Overrides.bOverride_CastDynamicShadowAsMasked || Overrides.bOverride_TwoSided;
	}

	/**
	 * Walks the original chain up to RM_Surface: the nearest override of each static switch and base property wins, as
	 * when the game compiled this instance. False when the chain does not end at RM_Surface.
	 */
	bool RecoveredComputePermutation(UMaterialInstance* Instance, FRecoveredPermutation& Out, UMaterial*& OutRetail,
		TArray<TWeakObjectPtr<UMaterialInstance>>& OutAncestors)
	{
		static TSet<FName> KnownSwitches;
		if (KnownSwitches.Num() == 0)
		{
			for (const TCHAR* SwitchText : RecoveredRetailSwitchNames) { KnownSwitches.Add(FName(SwitchText)); }
		}
		TSet<FName> Decided;
		UMaterialInstance* Level = Instance;
		for (int32 Depth = 0; Level && Depth < 64; ++Depth)
		{
			for (const FStaticSwitchParameter& Switch : RecoveredOriginalStatic(Level).StaticSwitchParameters)
			{
				const FName Name = Switch.ParameterInfo.Name;
				if (!Switch.bOverride || Switch.ParameterInfo.Association != EMaterialParameterAssociation::GlobalParameter || Decided.Contains(Name))
				{
					continue;
				}
				Decided.Add(Name);
				if (Switch.Value) { Out.Switches.Add(Name); }
				if (!KnownSwitches.Contains(Name) && !GRecoveredUnknownSwitches.Contains(Name))
				{
					GRecoveredUnknownSwitches.Add(Name);
					UE_LOG(LogRebirthRecoveredSurfaces, Display, TEXT("Static switch %s (on %s) is not one of the known RM_Surface switches."),
						*Name.ToString(), *Level->GetPathName());
				}
			}
			const FMaterialInstanceBasePropertyOverrides& Overrides = RecoveredOriginalOverrides(Level);
			if (!Out.bBlendMode && Overrides.bOverride_BlendMode) { Out.bBlendMode = true; Out.BlendMode = RecoveredSupportedBlend(static_cast<int32>(Overrides.BlendMode.GetValue())); }
			if (!Out.bTwoSided && Overrides.bOverride_TwoSided) { Out.bTwoSided = true; Out.TwoSided = Overrides.TwoSided != 0; }
			if (!Out.bClip && Overrides.bOverride_OpacityMaskClipValue) { Out.bClip = true; Out.Clip = Overrides.OpacityMaskClipValue; }
			if (!Out.bDithered && Overrides.bOverride_DitheredLODTransition) { Out.bDithered = true; Out.Dithered = Overrides.DitheredLODTransition != 0; }
			if (!Out.bCastMasked && Overrides.bOverride_CastDynamicShadowAsMasked) { Out.bCastMasked = true; Out.CastMasked = Overrides.bCastDynamicShadowAsMasked != 0; }

			UMaterialInterface* Parent = RecoveredOriginalParent(Level);
			if (UMaterial* Retail = RecoveredRetailSurfaceOf(Parent))
			{
				OutRetail = Retail;
				return true;
			}
			UMaterialInstance* Next = Cast<UMaterialInstance>(Parent);
			if (Next) { OutAncestors.Add(Next); }
			Level = Next;
		}
		return false;
	}

	/** RM_Surface in the project is the rebuilt, editable one (not the game's cooked material). */
	bool RecoveredIsRebuiltRetail(const UMaterial& Retail)
	{
		return CVarRecoveredSurfacesRebuilt.GetValueOnGameThread() != 0 && !RecoveredIsCookedObject(&Retail);
	}

	/** Which recovered family renders the retail permutation, and whether it needs the stochastic coverage. */
	void RecoveredChooseFamily(FRecoveredPlan& Plan, const UMaterial& Retail)
	{
		if (RecoveredIsRebuiltRetail(Retail))
		{
			Plan.Family = ERecoveredFamily::Rebuilt; // RM_Surface itself: every switch, the coverage included
			Plan.bCoverage = false;
			return;
		}
		auto Has = [&Plan](const TCHAR* Name) { return Plan.Permutation.Switches.Contains(FName(Name)); };
		const EBlendMode Blend = Plan.Permutation.bBlendMode ? Plan.Permutation.BlendMode.GetValue() : Retail.BlendMode.GetValue();
		const bool bMasked = Blend == BLEND_Masked;
		if (Has(TEXT("Eye_")) || Has(TEXT("EyeMigration_"))) { Plan.Family = ERecoveredFamily::EyeMigration; }
		else if (Has(TEXT("Hair_"))) { Plan.Family = ERecoveredFamily::HairWide; }
		else if (Has(TEXT("Skin_"))) { Plan.Family = ERecoveredFamily::SkinDynamic; }
		else if (Has(TEXT("Fabric_"))) { Plan.Family = ERecoveredFamily::FabricWide; }
		else if (Has(TEXT("Detail_"))) { Plan.Family = ERecoveredFamily::StandardWideDetail; }
		else if (bMasked) { Plan.Family = ERecoveredFamily::CoverageWide; }
		else { Plan.Family = ERecoveredFamily::StandardWide; }
		Plan.bCoverage = bMasked; // a masked retail surface clips through its stochastic coverage
	}

	const FRecoveredFamilySource& RecoveredSourceFor(ERecoveredFamily Family)
	{
		for (const FRecoveredFamilySource& Source : RecoveredFamilySources)
		{
			if (Source.Family == Family) { return Source; }
		}
		return RecoveredFamilySources[0];
	}

	UTexture* RecoveredNeutralTexture(EMaterialSamplerType Wanted, FName ParameterName)
	{
		const FString Name = ParameterName.ToString();
		const bool bBlack = Name.Contains(TEXT("Metallic")) || Name.Contains(TEXT("Emissive")) || Name.Contains(TEXT("Wetness")) || Name.Contains(TEXT("Muddiness"));
		static const TCHAR* const WhiteCandidates[] =
		{
			TEXT("/Game/Renderer/Texture/F4F4F4FF_sRGB.F4F4F4FF_sRGB"),
			TEXT("/Game/Renderer/Texture/FFFFFFFF_BC4.FFFFFFFF_BC4"),
			TEXT("/Game/Renderer/Texture/FFFFFFFF_HDR.FFFFFFFF_HDR"),
			TEXT("/Game/Renderer/Texture/FFFFFFFF.FFFFFFFF"),
			TEXT("/Game/Renderer/Texture/8080FFFF_BC5.8080FFFF_BC5"),
			TEXT("/Engine/EngineMaterials/FlatNormal.FlatNormal"),
			TEXT("/Engine/EngineResources/WhiteSquareTexture.WhiteSquareTexture"),
			TEXT("/Engine/EngineResources/DefaultTexture.DefaultTexture"),
		};
		static const TCHAR* const BlackCandidates[] =
		{
			TEXT("/Game/Renderer/Texture/000000FF_BC4.000000FF_BC4"),
			TEXT("/Game/Renderer/Texture/000000FF_HDR.000000FF_HDR"),
			TEXT("/Game/Renderer/Texture/000000FF_sRGB.000000FF_sRGB"),
			TEXT("/Game/Renderer/Texture/000000FF.000000FF"),
			TEXT("/Engine/EngineResources/Black.Black"),
		};
		auto Pick = [Wanted](const TCHAR* const* Candidates, int32 Count) -> UTexture*
		{
			for (int32 Index = 0; Index < Count; ++Index)
			{
				UTexture* Texture = LoadObject<UTexture>(nullptr, Candidates[Index], nullptr, LOAD_NoWarn | LOAD_Quiet);
				if (Texture && RecoveredSamplerTypeOf(Texture) == Wanted)
				{
					return Texture;
				}
			}
			return nullptr;
		};
		UTexture* Texture = bBlack ? Pick(BlackCandidates, UE_ARRAY_COUNT(BlackCandidates)) : nullptr;
		if (!Texture) { Texture = Pick(WhiteCandidates, UE_ARRAY_COUNT(WhiteCandidates)); }
		if (!Texture && !bBlack) { Texture = Pick(BlackCandidates, UE_ARRAY_COUNT(BlackCandidates)); }
		return Texture;
	}

	const FMaterialCachedParameterEntry& RecoveredRetailEntry(const UMaterial& Retail, EMaterialParameterType Type)
	{
		return Retail.GetCachedExpressionData().Parameters.RuntimeEntries[static_cast<int32>(Type)];
	}

	/** Character-specific defaults of the generated family masters are replaced by RM_Surface defaults. */
	void RecoveredApplyRetailDefaults(UMaterial& Master, const UMaterial& Retail)
	{
		const FMaterialCachedParameters& Parameters = Retail.GetCachedExpressionData().Parameters;
		TMap<FName, UTexture*> TextureDefaults;
		const FMaterialCachedParameterEntry& Textures = RecoveredRetailEntry(Retail, EMaterialParameterType::Texture);
		for (int32 Index = 0; Index < Textures.ParameterInfos.Num(); ++Index)
		{
			if (Parameters.TextureValues.IsValidIndex(Index)) { TextureDefaults.Add(Textures.ParameterInfos[Index].Name, Parameters.TextureValues[Index]); }
		}
		TMap<FName, FLinearColor> VectorDefaults;
		const FMaterialCachedParameterEntry& Vectors = RecoveredRetailEntry(Retail, EMaterialParameterType::Vector);
		for (int32 Index = 0; Index < Vectors.ParameterInfos.Num(); ++Index)
		{
			if (Parameters.VectorValues.IsValidIndex(Index)) { VectorDefaults.Add(Vectors.ParameterInfos[Index].Name, Parameters.VectorValues[Index]); }
		}

		for (UMaterialExpression* Expression : Master.Expressions)
		{
			if (UMaterialExpressionVectorParameter* Vector = Cast<UMaterialExpressionVectorParameter>(Expression))
			{
				if (const FLinearColor* Default = VectorDefaults.Find(Vector->ParameterName)) { Vector->DefaultValue = *Default; }
				continue;
			}
			UMaterialExpressionTextureSampleParameter* Parameter = Cast<UMaterialExpressionTextureSampleParameter>(Expression);
			if (!Parameter)
			{
				continue;
			}
			const EMaterialSamplerType Wanted = Parameter->SamplerType;
			UTexture* Chosen = nullptr;
			if (UTexture* const* RetailDefault = TextureDefaults.Find(Parameter->ParameterName))
			{
				if (*RetailDefault && RecoveredSamplerTypeOf(*RetailDefault) == Wanted) { Chosen = *RetailDefault; }
			}
			else if (Parameter->Texture && RecoveredSamplerTypeOf(Parameter->Texture) == Wanted)
			{
				Chosen = Parameter->Texture; // Not an RM_Surface parameter (blue noise, recovered adapters): keep it.
			}
			if (!Chosen) { Chosen = RecoveredNeutralTexture(Wanted, Parameter->ParameterName); }
			if (Chosen) { Parameter->Texture = Chosen; }
		}
	}

	TSet<FName> RecoveredParameterNamesOf(const UMaterial& Master)
	{
		TSet<FName> Names;
		for (UMaterialExpression* Expression : Master.Expressions)
		{
			if (const UMaterialExpressionParameter* Parameter = Cast<UMaterialExpressionParameter>(Expression))
			{
				Names.Add(Parameter->ParameterName);
			}
			else if (const UMaterialExpressionTextureSampleParameter* Texture = Cast<UMaterialExpressionTextureSampleParameter>(Expression))
			{
				Names.Add(Texture->ParameterName);
			}
			else if (const UMaterialExpressionShaderResourceBufferObjectParameter* Buffer = Cast<UMaterialExpressionShaderResourceBufferObjectParameter>(Expression))
			{
				Names.Add(Buffer->ParameterName);
			}
		}
		return Names;
	}

	template <typename T>
	T* RecoveredNewExpression(UMaterial& Master, const FString& GuidSeed)
	{
		T* Expression = NewObject<T>(&Master, NAME_None, RF_Transient);
		Expression->Material = &Master;
		Master.Expressions.Add(Expression);
		if (!GuidSeed.IsEmpty())
		{
			// Deterministic parameter ids keep static parameter sets (and so shader map keys) stable between sessions.
			const FGuid Guid = RecoveredGuid(FString(RecoveredRecipeIdentity) + TEXT("/") + GuidSeed);
			if (UMaterialExpressionParameter* Parameter = Cast<UMaterialExpressionParameter>(Expression))
			{
				Parameter->ExpressionGUID = Guid;
			}
			else if (UMaterialExpressionTextureSampleParameter* TextureParameter = Cast<UMaterialExpressionTextureSampleParameter>(Expression))
			{
				TextureParameter->ExpressionGUID = Guid;
			}
			else if (UMaterialExpressionShaderResourceBufferObjectParameter* BufferParameter = Cast<UMaterialExpressionShaderResourceBufferObjectParameter>(Expression))
			{
				BufferParameter->ExpressionGUID = Guid;
			}
		}
		return Expression;
	}

	/**
	 * Every RM_Surface parameter and static switch exists in the master, unconnected when the family does not use it. The
	 * Material Instance Editor rewrites an instance's overrides from its base material's parameter list on each edit, so a
	 * missing name would silently drop that override from the user's instance.
	 */
	void RecoveredDeclareRetailParameters(UMaterial& Master, const UMaterial& Retail)
	{
		static const FName ValuesGroup(TEXT("RM_Surface (not used by the recovered preview)"));
		static const FName SwitchesGroup(TEXT("RM_Surface switches (not used by the recovered preview)"));
		TSet<FName> Existing = RecoveredParameterNamesOf(Master);
		const FMaterialCachedParameters& Parameters = Retail.GetCachedExpressionData().Parameters;

		const FMaterialCachedParameterEntry& Textures = RecoveredRetailEntry(Retail, EMaterialParameterType::Texture);
		for (int32 Index = 0; Index < Textures.ParameterInfos.Num(); ++Index)
		{
			const FName Name = Textures.ParameterInfos[Index].Name;
			if (Name.IsNone() || Existing.Contains(Name)) { continue; }
			UMaterialExpressionTextureObjectParameter* Parameter = RecoveredNewExpression<UMaterialExpressionTextureObjectParameter>(Master, TEXT("Texture/") + Name.ToString());
			Parameter->ParameterName = Name;
			Parameter->Group = ValuesGroup;
			Parameter->Texture = Parameters.TextureValues.IsValidIndex(Index) ? Parameters.TextureValues[Index] : nullptr;
			Parameter->SamplerType = Parameter->Texture ? RecoveredSamplerTypeOf(Parameter->Texture) : SAMPLERTYPE_Color;
			Existing.Add(Name);
		}

		const FMaterialCachedParameterEntry& Vectors = RecoveredRetailEntry(Retail, EMaterialParameterType::Vector);
		for (int32 Index = 0; Index < Vectors.ParameterInfos.Num(); ++Index)
		{
			const FName Name = Vectors.ParameterInfos[Index].Name;
			if (Name.IsNone() || Existing.Contains(Name)) { continue; }
			UMaterialExpressionVectorParameter* Parameter = RecoveredNewExpression<UMaterialExpressionVectorParameter>(Master, TEXT("Vector/") + Name.ToString());
			Parameter->ParameterName = Name;
			Parameter->Group = ValuesGroup;
			Parameter->DefaultValue = Parameters.VectorValues.IsValidIndex(Index) ? Parameters.VectorValues[Index] : FLinearColor::Black;
			Existing.Add(Name);
		}

		const FMaterialCachedParameterEntry& Buffers = RecoveredRetailEntry(Retail, EMaterialParameterType::ShaderResourceBuffer);
		for (int32 Index = 0; Index < Buffers.ParameterInfos.Num(); ++Index)
		{
			const FName Name = Buffers.ParameterInfos[Index].Name;
			if (Name.IsNone() || Existing.Contains(Name)) { continue; }
			UMaterialExpressionShaderResourceBufferObjectParameter* Parameter = RecoveredNewExpression<UMaterialExpressionShaderResourceBufferObjectParameter>(Master, TEXT("Buffer/") + Name.ToString());
			Parameter->ParameterName = Name;
			Parameter->Group = ValuesGroup;
			Parameter->ShaderResourceBuffer = Parameters.ShaderResourceBufferValues.IsValidIndex(Index) ? Parameters.ShaderResourceBufferValues[Index] : nullptr;
			Existing.Add(Name);
		}

		const FMaterialCachedParameterEntry& RetailScalars = RecoveredRetailEntry(Retail, EMaterialParameterType::Scalar);
		TArray<FName> Scalars;
		for (const FMaterialParameterInfo& Info : RetailScalars.ParameterInfos) { Scalars.Add(Info.Name); }
		Scalars.AddUnique(FName(TEXT("RefractionDepthBias"))); // set by most retail character instances
		for (int32 Index = 0; Index < Scalars.Num(); ++Index)
		{
			const FName Name = Scalars[Index];
			if (Name.IsNone() || Existing.Contains(Name)) { continue; }
			UMaterialExpressionScalarParameter* Parameter = RecoveredNewExpression<UMaterialExpressionScalarParameter>(Master, TEXT("Scalar/") + Name.ToString());
			Parameter->ParameterName = Name;
			Parameter->Group = ValuesGroup;
			Parameter->DefaultValue = Index < RetailScalars.ParameterInfos.Num() && Parameters.ScalarValues.IsValidIndex(Index) ? Parameters.ScalarValues[Index] : 0.0f;
			Existing.Add(Name);
		}

		// The known list keeps the masters identical whether RM_Surface is cooked (switch list stripped) or editable.
		TArray<FName> Switches;
		for (const TCHAR* SwitchText : RecoveredRetailSwitchNames) { Switches.Add(FName(SwitchText)); }
		for (const FName& Name : Switches)
		{
			if (Existing.Contains(Name)) { continue; }
			UMaterialExpressionStaticSwitchParameter* Switch = RecoveredNewExpression<UMaterialExpressionStaticSwitchParameter>(Master, TEXT("Switch/") + Name.ToString());
			Switch->ParameterName = Name;
			Switch->Group = SwitchesGroup;
			Switch->DefaultValue = false;
			Existing.Add(Name);
		}
	}

	template <typename T>
	T* RecoveredFindNamedExpression(UMaterial& Master, FName Name)
	{
		for (UMaterialExpression* Expression : Master.Expressions)
		{
			if (T* Typed = Cast<T>(Expression))
			{
				if (Typed->ParameterName == Name) { return Typed; }
			}
		}
		return nullptr;
	}

	UMaterialExpressionScalarParameter* RecoveredFindOrAddScalar(UMaterial& Master, const TCHAR* Name, float DefaultValue)
	{
		if (UMaterialExpressionScalarParameter* Existing = RecoveredFindNamedExpression<UMaterialExpressionScalarParameter>(Master, FName(Name)))
		{
			return Existing;
		}
		UMaterialExpressionScalarParameter* Parameter = RecoveredNewExpression<UMaterialExpressionScalarParameter>(Master, FString(TEXT("Scalar/")) + Name);
		Parameter->ParameterName = FName(Name);
		Parameter->DefaultValue = DefaultValue;
		return Parameter;
	}

	/**
	 * The retail coverage test of the CoverageWide family (recovered SSA) behind RM_Surface's Coverage_ switch: the pixel
	 * is kept when the primitive's dynamic coverage and the Coverage texture both exceed the frame's spatiotemporal
	 * blue-noise thresholds. Switch off, the family's own opacity mask (or 1) is used.
	 */
	bool RecoveredAddCoverageSwitch(UMaterial& Master, FString& OutError)
	{
		UMaterialExpressionTextureObjectParameter* Coverage = RecoveredFindNamedExpression<UMaterialExpressionTextureObjectParameter>(Master, FName(TEXT("Coverage")));
		if (!Coverage)
		{
			OutError = TEXT("the family master has no Coverage texture to drive the retail coverage");
			return false;
		}
		Coverage->Group = NAME_None;
		if (!Coverage->Texture) { Coverage->Texture = RecoveredNeutralTexture(SAMPLERTYPE_Alpha, Coverage->ParameterName); }
		if (!Coverage->Texture)
		{
			OutError = TEXT("no default texture for Coverage");
			return false;
		}
		Coverage->SamplerType = RecoveredSamplerTypeOf(Coverage->Texture);

		UMaterialExpressionTextureObjectParameter* Noise = RecoveredFindNamedExpression<UMaterialExpressionTextureObjectParameter>(Master, FName(TEXT("Noise")));
		if (!Noise)
		{
			UTexture* BlueNoise = LoadObject<UTexture>(nullptr, RecoveredBlueNoisePath, nullptr, LOAD_NoWarn | LOAD_Quiet);
			if (!BlueNoise)
			{
				OutError = TEXT("the spatiotemporal blue-noise texture is missing");
				return false;
			}
			Noise = RecoveredNewExpression<UMaterialExpressionTextureObjectParameter>(Master, TEXT("Texture/Noise"));
			Noise->ParameterName = FName(TEXT("Noise"));
			Noise->Texture = BlueNoise;
			Noise->SamplerType = RecoveredSamplerTypeOf(BlueNoise);
		}
		UMaterialExpressionScalarParameter* PrimitiveCoverage = RecoveredFindOrAddScalar(Master, TEXT("NativePrimitiveCoverage"), 1.0f);
		UMaterialExpressionScalarParameter* CoverageMipBias = RecoveredFindOrAddScalar(Master, TEXT("RetailCoverageMipBias"), 0.0f);

		UMaterialExpressionTextureCoordinate* UV0 = RecoveredNewExpression<UMaterialExpressionTextureCoordinate>(Master, FString());
		UV0->CoordinateIndex = 0;

		UMaterialExpressionCustom* Custom = RecoveredNewExpression<UMaterialExpressionCustom>(Master, FString());
		Custom->Description = TEXT("Recovered retail stochastic coverage (CoverageWide)");
		Custom->OutputType = CMOT_Float1;
		Custom->Code = TEXT(
			"#if PIXELSHADER\n"
			"uint2 NoisePixel = uint2(Parameters.SvPosition.xy) & 127u;\n"
			"uint NoiseSlice = View.StateFrameIndex & 7u;\n"
			"float4 NoiseValue = NoiseTex.Load(int3(NoisePixel.x, NoisePixel.y + 128u * NoiseSlice, 0));\n"
			"float CoverageValue = Texture2DSampleBias(CoverageTex, CoverageTexSampler, UV0, RetailCoverageMipBias).r;\n"
			"bool bDiscard = true;\n"
			"if (NativePrimitiveCoverage > NoiseValue.a * 0.99609375f + 0.001953125f)\n"
			"{\n"
			"    bDiscard = !(CoverageValue > NoiseValue.r * 0.99609375f + 0.001953125f);\n"
			"}\n"
			"return bDiscard ? 0.0f : 1.0f;\n"
			"#else\n"
			"return 1.0f;\n"
			"#endif\n");
		Custom->Inputs.Reset();
		auto AddInput = [Custom](const TCHAR* InputName, UMaterialExpression* Source)
		{
			FCustomInput& Input = Custom->Inputs.AddDefaulted_GetRef();
			Input.InputName = FName(InputName);
			Input.Input.Expression = Source;
			Input.Input.OutputIndex = 0;
		};
		AddInput(TEXT("UV0"), UV0);
		AddInput(TEXT("CoverageTex"), Coverage);
		AddInput(TEXT("NoiseTex"), Noise);
		AddInput(TEXT("NativePrimitiveCoverage"), PrimitiveCoverage);
		AddInput(TEXT("RetailCoverageMipBias"), CoverageMipBias);

		UMaterialExpressionStaticSwitchParameter* Switch = RecoveredFindNamedExpression<UMaterialExpressionStaticSwitchParameter>(Master, RecoveredCoverageSwitchName());
		if (!Switch)
		{
			Switch = RecoveredNewExpression<UMaterialExpressionStaticSwitchParameter>(Master, TEXT("Switch/") + RecoveredCoverageSwitchName().ToString());
			Switch->ParameterName = RecoveredCoverageSwitchName();
			Switch->DefaultValue = false;
		}
		Switch->Group = NAME_None;
		Switch->A.Expression = Custom;
		Switch->A.OutputIndex = 0;
		if (Master.OpacityMask.Expression && !Master.OpacityMask.UseConstant)
		{
			Switch->B.Expression = Master.OpacityMask.Expression;
			Switch->B.OutputIndex = Master.OpacityMask.OutputIndex;
		}
		else
		{
			UMaterialExpressionConstant* One = RecoveredNewExpression<UMaterialExpressionConstant>(Master, FString());
			One->R = 1.0f;
			Switch->B.Expression = One;
			Switch->B.OutputIndex = 0;
		}
		Master.OpacityMask.Expression = Switch;
		Master.OpacityMask.OutputIndex = 0;
		Master.OpacityMask.UseConstant = false;
		return true;
	}

	UMaterial* RecoveredGetOrCreateMaster(ERecoveredFamily Family, const UMaterial& Retail, FString& OutError)
	{
		if (Family == ERecoveredFamily::Rebuilt)
		{
			// the rebuilt RM_Surface is the master: the cooked instances' bridges are its instances (it is left untouched)
			return const_cast<UMaterial*>(&Retail);
		}
		const FRecoveredFamilySource& Source = RecoveredSourceFor(Family);
		const FString Key = Source.Key;
		if (const TStrongObjectPtr<UMaterial>* Existing = GRecoveredMasters.Find(Key))
		{
			return Existing->Get();
		}
		if (const FString* Previous = GRecoveredMasterErrors.Find(Key))
		{
			OutError = *Previous;
			return nullptr;
		}

		UMaterial* Template = LoadObject<UMaterial>(nullptr, Source.ObjectPath);
		UMaterial* Master = nullptr;
		if (!Template)
		{
			OutError = FString::Printf(TEXT("recovered family master %s is missing"), Source.ObjectPath);
		}
		else
		{
			UPackage* Transient = GetTransientPackage();
			const FName Name = MakeUniqueObjectName(Transient, UMaterial::StaticClass(), FName(*(FString(TEXT("RecoveredSurface_")) + Key)));
			Master = DuplicateObject<UMaterial>(Template, Transient, Name);
			if (!Master) { OutError = TEXT("could not duplicate the recovered family master"); }
		}
		if (Master)
		{
			Master->SetFlags(RF_Transient);
			Master->ClearFlags(RF_Public | RF_Standalone);
			RecoveredApplyRetailDefaults(*Master, Retail);
			RecoveredDeclareRetailParameters(*Master, Retail);
			if (Source.bCoverageCapable && !RecoveredAddCoverageSwitch(*Master, OutError))
			{
				Master = nullptr;
			}
		}
		if (!Master)
		{
			GRecoveredMasterErrors.Add(Key, OutError);
			UE_LOG(LogRebirthRecoveredSurfaces, Warning, TEXT("Recovered surface family %s unavailable: %s"), *Key, *OutError);
			return nullptr;
		}
		// Stable identity: the same template, RM_Surface and recipe reuse the shader maps cached by an earlier session.
		Master->StateId = RecoveredGuid(FString::Printf(TEXT("%s/%s/%s/%s"), RecoveredRecipeIdentity, *Key,
			*Template->StateId.ToString(), *Retail.StateId.ToString()));
		Master->UpdateCachedExpressionData();
		Master->ForceRecompileForRendering();
		GRecoveredMasters.Add(Key, TStrongObjectPtr<UMaterial>(Master));
		UE_LOG(LogRebirthRecoveredSurfaces, Display, TEXT("Recovered surface family %s ready from %s (%d expressions; shaders compile in the background the first time)."),
			*Key, *Template->GetPathName(), Master->Expressions.Num());
		return Master;
	}

	template <typename TValue>
	void RecoveredAppendMissing(TArray<TValue>& Target, const TArray<TValue>& Source)
	{
		for (const TValue& Value : Source)
		{
			const bool bPresent = Target.ContainsByPredicate([&Value](const TValue& Existing) { return Existing.ParameterInfo == Value.ParameterInfo; });
			if (!bPresent) { Target.Add(Value); }
		}
	}

	/**
	 * The transient bridge of one cooked instance: an instance of the family master carrying the retail coverage switch,
	 * the base property overrides the master does not already have, and the parameter values the cooked instance inherited
	 * from its own cooked parents (which the redirect skips).
	 */
	UMaterialInstanceConstant* RecoveredCreateBridge(UMaterialInstance& Instance, const FRecoveredPlan& Plan, UMaterial& Master, const FString& FamilyKey,
		FString& OutDescription)
	{
		const FRecoveredFamilySource& Source = RecoveredSourceFor(Plan.Family);
		const FRecoveredPermutation& Permutation = Plan.Permutation;
		const bool bCoverageSwitch = Plan.bCoverage && Source.bCoverageCapable && !Source.bNativeCoverage;

		bool bBlend = Permutation.bBlendMode && Permutation.BlendMode.GetValue() != Master.BlendMode.GetValue();
		EBlendMode Blend = Permutation.BlendMode.GetValue();
		if (bCoverageSwitch && Master.BlendMode.GetValue() != BLEND_Masked)
		{
			bBlend = true;
			Blend = BLEND_Masked;
		}
		const bool bTwoSided = Permutation.bTwoSided && Permutation.TwoSided != (Master.TwoSided != 0);
		const bool bClip = Permutation.bClip && !FMath::IsNearlyEqual(Permutation.Clip, Master.OpacityMaskClipValue);
		const bool bDithered = Permutation.bDithered && Permutation.Dithered != (Master.DitheredLODTransition != 0);
		const bool bCastMasked = Permutation.bCastMasked && Permutation.CastMasked != (Master.bCastDynamicShadowAsMasked != 0);

		OutDescription = FamilyKey;
		if (bCoverageSwitch) { OutDescription += TEXT("+Coverage"); }
		if (bBlend) { OutDescription += FString::Printf(TEXT("+Blend%d"), static_cast<int32>(Blend)); }
		if (bTwoSided) { OutDescription += Permutation.TwoSided ? TEXT("+TwoSided") : TEXT("+OneSided"); }
		if (bClip) { OutDescription += FString::Printf(TEXT("+Clip%.4f"), Permutation.Clip); }
		if (bDithered) { OutDescription += Permutation.Dithered ? TEXT("+Dithered") : TEXT("+NotDithered"); }
		if (bCastMasked) { OutDescription += Permutation.CastMasked ? TEXT("+CastMasked") : TEXT("+CastOpaque"); }

		const FString Key = Instance.GetPathName();
		if (const TStrongObjectPtr<UMaterialInstanceConstant>* Existing = GRecoveredBridges.Find(Key))
		{
			if (Existing->Get() && Existing->Get()->Parent == &Master)
			{
				return Existing->Get();
			}
		}

		UPackage* Transient = GetTransientPackage();
		UMaterialInstanceConstant* Bridge = NewObject<UMaterialInstanceConstant>(Transient,
			MakeUniqueObjectName(Transient, UMaterialInstanceConstant::StaticClass(), FName(*(TEXT("RecoveredSurfaceBridge_") + Instance.GetName()))), RF_Transient);
		Bridge->Parent = &Master;
		for (const TWeakObjectPtr<UMaterialInstance>& Weak : Plan.Ancestors)
		{
			if (UMaterialInstance* Ancestor = Weak.Get())
			{
				RecoveredAppendMissing(Bridge->ScalarParameterValues, Ancestor->ScalarParameterValues);
				RecoveredAppendMissing(Bridge->VectorParameterValues, Ancestor->VectorParameterValues);
				RecoveredAppendMissing(Bridge->TextureParameterValues, Ancestor->TextureParameterValues);
				RecoveredAppendMissing(Bridge->ShaderResourceBufferParameterValues, Ancestor->ShaderResourceBufferParameterValues);
				RecoveredAppendMissing(Bridge->RuntimeVirtualTextureParameterValues, Ancestor->RuntimeVirtualTextureParameterValues);
				RecoveredAppendMissing(Bridge->FontParameterValues, Ancestor->FontParameterValues);
			}
		}
		if (Plan.Ancestors.Num() > 0 && Plan.Ancestors[0].IsValid())
		{
			OutDescription += TEXT(" + values of ") + Plan.Ancestors[0]->GetName();
		}
		if (bCoverageSwitch)
		{
			FGuid SwitchGuid;
			if (const UMaterialExpressionStaticSwitchParameter* Switch = RecoveredFindNamedExpression<UMaterialExpressionStaticSwitchParameter>(Master, RecoveredCoverageSwitchName()))
			{
				SwitchGuid = Switch->ExpressionGUID;
			}
			FStaticParameterSet& Static = const_cast<FStaticParameterSet&>(Bridge->GetStaticParameters());
			Static.StaticSwitchParameters.Add(FStaticSwitchParameter(FMaterialParameterInfo(RecoveredCoverageSwitchName()), true, true, SwitchGuid));
		}
		if (Plan.Family == ERecoveredFamily::Rebuilt)
		{
			// The rebuilt RM_Surface implements every static switch: the bridge carries the instance's whole permutation.
			FStaticParameterSet& Static = const_cast<FStaticParameterSet&>(Bridge->GetStaticParameters());
			for (const FName& Name : Permutation.Switches)
			{
				FGuid SwitchGuid;
				if (const UMaterialExpressionStaticSwitchParameter* Switch = RecoveredFindNamedExpression<UMaterialExpressionStaticSwitchParameter>(Master, Name))
				{
					SwitchGuid = Switch->ExpressionGUID;
				}
				Static.StaticSwitchParameters.Add(FStaticSwitchParameter(FMaterialParameterInfo(Name), true, true, SwitchGuid));
			}
			OutDescription += FString::Printf(TEXT("+%d switches"), Permutation.Switches.Num());
		}
		FMaterialInstanceBasePropertyOverrides& Overrides = Bridge->BasePropertyOverrides;
		Overrides.bOverride_BlendMode = bBlend;
		Overrides.BlendMode = bBlend ? Blend : Master.BlendMode.GetValue();
		Overrides.bOverride_TwoSided = bTwoSided;
		Overrides.TwoSided = Permutation.TwoSided;
		Overrides.bOverride_OpacityMaskClipValue = bClip;
		Overrides.OpacityMaskClipValue = Permutation.Clip;
		Overrides.bOverride_DitheredLODTransition = bDithered;
		Overrides.DitheredLODTransition = Permutation.Dithered;
		Overrides.bOverride_CastDynamicShadowAsMasked = bCastMasked;
		Overrides.bCastDynamicShadowAsMasked = Permutation.CastMasked;
		Bridge->UpdateCachedLayerParameters();
		Bridge->InitStaticPermutation();
		GRecoveredBridges.Add(Key, TStrongObjectPtr<UMaterialInstanceConstant>(Bridge));
		return Bridge;
	}

	void RecoveredNeutralize(UMaterialInstance& Instance)
	{
		const_cast<FStaticParameterSet&>(Instance.GetStaticParameters()) = FStaticParameterSet();
		FMaterialInstanceBasePropertyOverrides& Overrides = Instance.BasePropertyOverrides;
		Overrides.bOverride_OpacityMaskClipValue = false;
		Overrides.bOverride_BlendMode = false;
		Overrides.bOverride_ShadingModel = false;
		Overrides.bOverride_DitheredLODTransition = false;
		Overrides.bOverride_CastDynamicShadowAsMasked = false;
		Overrides.bOverride_TwoSided = false;
	}

	bool RecoveredIsUsable(const UMaterialInstance* Instance)
	{
		return IsValid(Instance) && !Instance->HasAnyFlags(RF_ClassDefaultObject | RF_Transient | RF_NeedLoad | RF_NeedPostLoad | RF_BeginDestroyed | RF_FinishDestroyed);
	}

	/**
	 * Cooked: instances that own an RM_Surface permutation (the retail RMI_Surface_* and instances with their own switches).
	 * Editable: direct children of RM_Surface; deeper editable instances compile their own switches against the master
	 * through their redirected parent and need nothing.
	 */
	bool RecoveredNeedsRedirect(UMaterialInstance* Instance, ERecoveredStyle& OutStyle)
	{
		if (!RecoveredIsUsable(Instance))
		{
			return false;
		}
		if (!RecoveredIsCookedObject(Instance))
		{
			OutStyle = ERecoveredStyle::EditableParent;
			const UMaterial* Retail = RecoveredRetailSurfaceOf(Instance->Parent);
			// an editable child of the rebuilt RM_Surface compiles its own permutation against it: nothing to redirect
			return Retail != nullptr && !RecoveredIsRebuiltRetail(*Retail);
		}
		OutStyle = ERecoveredStyle::CookedBridge;
		if (RecoveredRetailSurfaceOf(Instance->Parent))
		{
			return true;
		}
		if (Instance->GetStaticParameters().IsEmpty() && !RecoveredHasOverrideFlags(Instance->BasePropertyOverrides))
		{
			return false;
		}
		UMaterialInterface* Current = Instance->Parent;
		for (int32 Depth = 0; Current && Depth < 64; ++Depth)
		{
			if (RecoveredRetailSurfaceOf(Current)) { return true; }
			UMaterialInstance* Level = Cast<UMaterialInstance>(Current);
			Current = Level ? RecoveredOriginalParent(Level) : nullptr;
		}
		return false;
	}

	void RecoveredConsiderInstance(UMaterialInstance* Instance)
	{
		const TWeakObjectPtr<UMaterialInstance> Weak(Instance);
		if (!Instance || GRecoveredRecords.Contains(Weak) || GRecoveredSkipped.Contains(Weak) || GRecoveredPending.Contains(Weak))
		{
			return;
		}
		ERecoveredStyle Style = ERecoveredStyle::CookedBridge;
		if (RecoveredNeedsRedirect(Instance, Style))
		{
			GRecoveredPending.Add(Weak);
		}
	}

	void RecoveredConsiderChain(UMaterialInterface* Material)
	{
		UMaterialInterface* Current = Material;
		for (int32 Depth = 0; Current && Depth < 64; ++Depth)
		{
			UMaterialInstance* Instance = Cast<UMaterialInstance>(Current);
			if (!Instance) { return; }
			RecoveredConsiderInstance(Instance);
			Current = RecoveredOriginalParent(Instance);
		}
	}

	void RecoveredConsiderObject(UObject* Object)
	{
		if (UMaterialInterface* Material = Cast<UMaterialInterface>(Object))
		{
			RecoveredConsiderChain(Material);
		}
		else if (USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(Object))
		{
			for (const FSkeletalMaterial& Slot : SkeletalMesh->Materials) { RecoveredConsiderChain(Slot.MaterialInterface); }
		}
		else if (UStaticMesh* StaticMesh = Cast<UStaticMesh>(Object))
		{
			for (const FStaticMaterial& Slot : StaticMesh->StaticMaterials) { RecoveredConsiderChain(Slot.MaterialInterface); }
		}
	}

	void RecoveredScanLoaded()
	{
		TArray<UObject*> Instances;
		GetObjectsOfClass(UMaterialInstance::StaticClass(), Instances, true, RF_ClassDefaultObject, EInternalObjectFlags::PendingKill);
		for (UObject* Object : Instances)
		{
			RecoveredConsiderInstance(static_cast<UMaterialInstance*>(Object));
		}
	}

	bool RecoveredCanModifyMaterialsNow()
	{
		return IsInGameThread() && !GIsSavingPackage && !IsGarbageCollecting() && !IsAsyncLoading();
	}

	void RecoveredApplyPending()
	{
		if (GRecoveredPending.Num() == 0 || !RecoveredCanModifyMaterialsNow())
		{
			return;
		}
		TArray<FRecoveredPlan> Plans;
		for (const TWeakObjectPtr<UMaterialInstance>& Weak : GRecoveredPending)
		{
			UMaterialInstance* Instance = Weak.Get();
			ERecoveredStyle Style = ERecoveredStyle::CookedBridge;
			if (!Instance || GRecoveredRecords.Contains(Weak) || !RecoveredNeedsRedirect(Instance, Style))
			{
				continue;
			}
			FRecoveredPlan& Plan = Plans.AddDefaulted_GetRef();
			Plan.Instance = Instance;
			Plan.Style = Style;
			UMaterial* Retail = nullptr;
			if (!RecoveredComputePermutation(Instance, Plan.Permutation, Retail, Plan.Ancestors) || !Retail)
			{
				GRecoveredSkipped.Add(Weak);
				Plans.Pop();
				continue;
			}
			Plan.Retail = Retail;
			RecoveredChooseFamily(Plan, *Retail);
		}
		GRecoveredPending.Reset();
		if (Plans.Num() == 0)
		{
			return;
		}

		TUniquePtr<FMaterialUpdateContext> UpdateContext;
		TMap<FString, int32> FamilyCounts;
		int32 Applied = 0;
		for (const FRecoveredPlan& Plan : Plans)
		{
			UMaterialInstance* Instance = Plan.Instance.Get();
			UMaterial* Retail = Plan.Retail.Get();
			if (!RecoveredIsUsable(Instance) || !Retail)
			{
				continue;
			}
			FString Error;
			UMaterial* Master = RecoveredGetOrCreateMaster(Plan.Family, *Retail, Error);
			if (!Master)
			{
				GRecoveredSkipped.Add(Plan.Instance);
				continue;
			}
			if (!UpdateContext.IsValid())
			{
				// Created before the first instance changes: render states are torn down and rebuilt once for the batch.
				UpdateContext = MakeUnique<FMaterialUpdateContext>();
			}
			const FString FamilyKey = RecoveredSourceFor(Plan.Family).Key;
			FRecoveredRecord Record;
			Record.OriginalParent = Instance->Parent;
			Record.OriginalStaticParameters = Instance->GetStaticParameters();
			Record.OriginalBasePropertyOverrides = Instance->BasePropertyOverrides;

			UMaterialInterface* NewParent = nullptr;
			if (Plan.Style == ERecoveredStyle::CookedBridge)
			{
				UMaterialInstanceConstant* Bridge = RecoveredCreateBridge(*Instance, Plan, *Master, FamilyKey, Record.Description);
				if (!Bridge)
				{
					GRecoveredSkipped.Add(Plan.Instance);
					continue;
				}
				UpdateContext->AddMaterialInstance(Bridge);
				RecoveredNeutralize(*Instance);
				Record.bNeutralized = true;
				NewParent = Bridge;
			}
			else
			{
				Record.Description = FamilyKey + TEXT(" (editable; parent only, in memory)");
				NewParent = Master;
			}
			Record.RedirectParent = NewParent;
			GRecoveredRecords.Add(Plan.Instance, MoveTemp(Record));

			Instance->Parent = NewParent;
			Instance->UpdateCachedLayerParameters();
			Instance->InitStaticPermutation();
			UpdateContext->AddMaterialInstance(Instance);
			FamilyCounts.FindOrAdd(FamilyKey) += 1;
			++Applied;
		}
		// Destroying the context recompiles child static permutations against the recovered masters and rebuilds every
		// render state that may have cached RM_Surface or the default material.
		UpdateContext.Reset();
		if (Applied > 0)
		{
			FString Families;
			for (const TPair<FString, int32>& Pair : FamilyCounts)
			{
				Families += FString::Printf(TEXT("%s%s x%d"), Families.IsEmpty() ? TEXT("") : TEXT(", "), *Pair.Key, Pair.Value);
			}
			UE_LOG(LogRebirthRecoveredSurfaces, Display, TEXT("Recovered retail surface shading applied to %d RM_Surface material instance(s): %s."), Applied, *Families);
			RebirthPersonaPreviewSupport::RefreshPreviewMaterials();
		}
	}

	/** Puts the real parent (and, for cooked instances, the real static switches and overrides) back on Instance. */
	void RecoveredRestoreFields(UMaterialInstance& Instance, const FRecoveredRecord& Record)
	{
		Instance.Parent = Record.OriginalParent.Get();
		if (Record.bNeutralized)
		{
			const_cast<FStaticParameterSet&>(Instance.GetStaticParameters()) = Record.OriginalStaticParameters;
			Instance.BasePropertyOverrides = Record.OriginalBasePropertyOverrides;
		}
	}

	void RecoveredRestoreAll()
	{
		GRecoveredPending.Reset();
		GRecoveredSkipped.Reset();
		GRecoveredMasterErrors.Reset();
		if (GRecoveredRecords.Num() == 0 || !IsInGameThread() || GIsSavingPackage || IsGarbageCollecting())
		{
			return;
		}
		TArray<TPair<UMaterialInstance*, FRecoveredRecord>> Live;
		for (TPair<TWeakObjectPtr<UMaterialInstance>, FRecoveredRecord>& Pair : GRecoveredRecords)
		{
			if (UMaterialInstance* Instance = Pair.Key.Get())
			{
				Live.Emplace(Instance, MoveTemp(Pair.Value));
			}
		}
		GRecoveredRecords.Reset();
		int32 Restored = 0;
		{
			FMaterialUpdateContext UpdateContext;
			for (TPair<UMaterialInstance*, FRecoveredRecord>& Pair : Live)
			{
				UMaterialInstance* Instance = Pair.Key;
				if (!IsValid(Instance) || Instance->Parent != Pair.Value.RedirectParent.Get())
				{
					continue; // already restored by a save, or its parent was changed since
				}
				RecoveredRestoreFields(*Instance, Pair.Value);
				Instance->UpdateCachedLayerParameters();
				Instance->InitStaticPermutation();
				UpdateContext.AddMaterialInstance(Instance);
				++Restored;
			}
		}
		UE_LOG(LogRebirthRecoveredSurfaces, Display, TEXT("Recovered surface shading removed from %d material instance(s)."), Restored);
		RebirthPersonaPreviewSupport::RefreshPreviewMaterials();
	}

	/**
	 * UObject::PreSave of every object a save writes. A redirected instance, or a copy of one (duplicate, save as), is
	 * written with its real parent (and real switches); the next tick redirects it again.
	 */
	void RecoveredOnObjectSaved(UObject* Object)
	{
		UMaterialInstance* Instance = Cast<UMaterialInstance>(Object);
		if (!Instance || Instance->HasAnyFlags(RF_Transient | RF_ClassDefaultObject) || !Instance->Parent)
		{
			return;
		}
		const TWeakObjectPtr<UMaterialInstance> Weak(Instance);
		if (const FRecoveredRecord* Record = GRecoveredRecords.Find(Weak))
		{
			if (Instance->Parent == Record->RedirectParent.Get())
			{
				RecoveredRestoreFields(*Instance, *Record);
			}
			GRecoveredRecords.Remove(Weak);
			GRecoveredRefresh.Add(Weak);
			return;
		}
		if (const FRecoveredRecord* Source = RecoveredRecordOfRedirectParent(Instance->Parent))
		{
			RecoveredRestoreFields(*Instance, *Source);
			GRecoveredRefresh.Add(Weak);
			UE_LOG(LogRebirthRecoveredSurfaces, Display, TEXT("%s was copied from a previewed instance; saved with its real parent %s."),
				*Instance->GetPathName(), *GetPathNameSafe(Instance->Parent));
			return;
		}
		if (RecoveredIsMaster(Instance->Parent))
		{
			UMaterial* Retail = GRecoveredRetailBase.Get();
			if (!Retail) { Retail = LoadObject<UMaterial>(nullptr, RecoveredRetailSurfacePath, nullptr, LOAD_NoWarn | LOAD_Quiet); }
			if (Retail)
			{
				Instance->Parent = Retail;
				GRecoveredRefresh.Add(Weak);
				UE_LOG(LogRebirthRecoveredSurfaces, Display, TEXT("%s pointed at a recovered preview master; saved with RM_Surface as its parent."), *Instance->GetPathName());
			}
			else
			{
				UE_LOG(LogRebirthRecoveredSurfaces, Error, TEXT("%s points at a recovered preview master and RM_Surface could not be found; its parent will be saved empty."), *Instance->GetPathName());
			}
		}
	}

	/** After a save: re-apply the preview, or (preview off) refresh the render state of the restored instances. */
	void RecoveredProcessRefresh()
	{
		if (GRecoveredRefresh.Num() == 0)
		{
			return;
		}
		TArray<UMaterialInstance*> Instances;
		for (const TWeakObjectPtr<UMaterialInstance>& Weak : GRecoveredRefresh)
		{
			if (UMaterialInstance* Instance = Weak.Get()) { Instances.Add(Instance); }
		}
		GRecoveredRefresh.Reset();
		if (RecoveredIsEnabled())
		{
			for (UMaterialInstance* Instance : Instances) { RecoveredConsiderInstance(Instance); }
			return;
		}
		FMaterialUpdateContext UpdateContext;
		for (UMaterialInstance* Instance : Instances)
		{
			if (!RecoveredIsUsable(Instance)) { continue; }
			Instance->UpdateCachedLayerParameters();
			Instance->InitStaticPermutation();
			UpdateContext.AddMaterialInstance(Instance);
		}
	}

	// ---- the game's cooked instances compiled from the editable base material's own graph (no redirect) -------------
	//
	// This engine refuses to compile a shader map for a cooked material (MaterialShared.cpp: a cooked owner has no graph).
	// A cooked instance of the rebuilt, editable RM_Surface does have one: its base material's. So each such instance is
	// compiled the ordinary way, from RM_Surface, with its own parent, static switches and overrides untouched: its
	// package's cooked flags are lifted for the moment the compile is requested (a compile in flight never checks them
	// again) and put straight back, so nothing about the package can be saved. The resources it was loaded with (the
	// game's shader maps, which this editor cannot use) are replaced by fresh ones the first time.

	/** UMaterialInstance::StaticPermutationMaterialResources (private), reached through an explicit instantiation. */
	struct FRebirthPermutationResourcesTag
	{
		typedef TArray<FMaterialResource*> UMaterialInstance::* Type;
		friend Type RebirthMemberOf(FRebirthPermutationResourcesTag);
	};
	template <typename Tag, typename Tag::Type Member>
	struct TRebirthPrivateMember
	{
		friend typename Tag::Type RebirthMemberOf(Tag) { return Member; }
	};
	template struct TRebirthPrivateMember<FRebirthPermutationResourcesTag, &UMaterialInstance::StaticPermutationMaterialResources>;

	TAutoConsoleVariable<int32> CVarRecoveredSurfacesCompileCooked(
		TEXT("Rebirth.RecoveredSurfaces.CompileCooked"),
		1,
		TEXT("1 (default; with Rebirth.RecoveredSurfaces 0): the game's cooked material instances whose base material is editable ")
		TEXT("here (the rebuilt RM_Surface) compile their own static permutation from that material, keeping their real parent, ")
		TEXT("switches and overrides. In memory only: their packages stay cooked. 0: they render with the default material."),
		ECVF_Default);

	TMap<TWeakObjectPtr<UMaterialInstance>, FGuid> GCookedAttempted;   // the base material state each was compiled against
	TSet<TWeakObjectPtr<UMaterialInstance>> GCookedFresh;              // loaded resources already replaced
	TSet<TWeakObjectPtr<UMaterialInstance>> GCookedCompiling;          // compiles requested and not finished yet
	double GCookedNextScanSeconds = 0.0;   // the periodic scan
	double GCookedLastScanSeconds = 0.0;
	bool bGCookedScanSoon = true;          // something loaded: scan on a tick soon (at most twice a second)
	int32 GCookedReady = 0;
	int32 GCookedFailed = 0;
	TSet<TWeakObjectPtr<UMaterialInstance>> GCookedBlendWarned;

	bool CookedCompileEnabled()
	{
		return !RecoveredIsEnabled() && CVarRecoveredSurfacesCompileCooked.GetValueOnGameThread() != 0;
	}

	/** The editable base material a cooked instance would compile from (none when the base is cooked too). */
	UMaterial* CookedSourceBase(UMaterialInstance* Instance)
	{
		if (!RecoveredIsUsable(Instance) || !RecoveredIsCookedObject(Instance) || !Instance->bHasStaticPermutationResource)
		{
			return nullptr;
		}
		UMaterial* Base = Instance->GetMaterial();
		if (!IsValid(Base) || Base->HasAnyFlags(RF_Transient) || RecoveredIsCookedObject(Base) || Base->IsDefaultMaterial())
		{
			return nullptr;
		}
		return Base;
	}

	bool CookedResourceCompiling(const UMaterialInstance* Instance)
	{
		const FMaterialResource* Resource = Instance->GetMaterialResource(GMaxRHIFeatureLevel);
		return Resource && !Resource->IsCompilationFinished();
	}

	/** True when the instance's shader map for this editor is a finished compile of Base as it is now. */
	bool CookedHasOwnMap(const UMaterialInstance* Instance, const UMaterial* Base)
	{
		const FMaterialResource* Resource = Instance->GetMaterialResource(GMaxRHIFeatureLevel);
		const FMaterialShaderMap* Map = Resource ? Resource->GetGameThreadShaderMap() : nullptr;
		return Map && Map->CompiledSuccessfully() && Map->GetShaderMapId().BaseMaterialId == Base->StateId;
	}

	bool CookedNeedsCompile(UMaterialInstance* Instance)
	{
		UMaterial* Base = CookedSourceBase(Instance);
		if (!Base || CookedResourceCompiling(Instance) || CookedHasOwnMap(Instance, Base))
		{
			return false;
		}
		// one try per state of the base material: a permutation that fails to compile is not retried until it changes
		const FGuid* Tried = GCookedAttempted.Find(TWeakObjectPtr<UMaterialInstance>(Instance));
		return !Tried || *Tried != Base->StateId;
	}

	int32 CookedChainDepth(const UMaterialInstance* Instance)
	{
		int32 Depth = 0;
		for (const UMaterialInstance* Level = Instance; Level && Depth < 64; Level = Cast<UMaterialInstance>(Level->Parent))
		{
			++Depth;
		}
		return Depth;
	}

	/**
	 * The game's own base property values this engine has no meaning for, made the nearest ones it has (in memory): the
	 * game's extra blend mode (BLEND_AlphaCompositeColored, 7) draws with no blend state here and the renderer asserts, and a
	 * shading model past this engine's list would compile nothing sensible.
	 */
	void CookedSanitizeOverrides(UMaterialInstance& Instance)
	{
		FMaterialInstanceBasePropertyOverrides& Overrides = Instance.BasePropertyOverrides;
		const int32 Blend = static_cast<int32>(Overrides.BlendMode.GetValue());
		const int32 Model = static_cast<int32>(Overrides.ShadingModel.GetValue());
		const bool bBadBlend = Overrides.bOverride_BlendMode && (Blend < 0 || Blend >= static_cast<int32>(BLEND_MAX));
		const bool bBadModel = Overrides.bOverride_ShadingModel && (Model < 0 || Model >= static_cast<int32>(MSM_NUM))
			&& Model != static_cast<int32>(MSM_FromMaterialExpression);
		if (bBadBlend)
		{
			Overrides.BlendMode = RecoveredSupportedBlend(Blend);
		}
		if (bBadModel)
		{
			Overrides.bOverride_ShadingModel = false;
		}
		if ((bBadBlend || bBadModel) && !GCookedBlendWarned.Contains(TWeakObjectPtr<UMaterialInstance>(&Instance)))
		{
			GCookedBlendWarned.Add(TWeakObjectPtr<UMaterialInstance>(&Instance));
			UE_LOG(LogRebirthRecoveredSurfaces, Display, TEXT("%s: the game's %s%s%s renders as %s here (in memory only)."), *Instance.GetPathName(),
				bBadBlend ? *FString::Printf(TEXT("blend mode %d"), Blend) : TEXT(""), (bBadBlend && bBadModel) ? TEXT(" and ") : TEXT(""),
				bBadModel ? *FString::Printf(TEXT("shading model %d"), Model) : TEXT(""),
				bBadBlend ? TEXT("Alpha Composite") : TEXT("its parent's shading model"));
		}
	}

	void CookedCompile(const TArray<UMaterialInstance*>& Instances)
	{
		TArray<UMaterialInstance*> Batch;
		for (UMaterialInstance* Instance : Instances)
		{
			if (CookedSourceBase(Instance))
			{
				Batch.AddUnique(Instance);
			}
		}
		if (Batch.Num() == 0)
		{
			return;
		}
		// parents first: an instance takes its blend mode and the rest from its parent's state as of then
		Batch.StableSort([](const UMaterialInstance& A, const UMaterialInstance& B) { return CookedChainDepth(&A) < CookedChainDepth(&B); });

		TArray<FMaterialResource*> ToFree;
		{
			// drops every render state now and rebuilds them on the way out, so no draw command keeps a replaced resource
			FMaterialUpdateContext UpdateContext;
			for (UMaterialInstance* Instance : Batch)
			{
				UMaterial* Base = Instance->GetMaterial();
				const TWeakObjectPtr<UMaterialInstance> Weak(Instance);
				// the render thread reads these arrays (FMaterialInstanceResource::GetMaterialWithFallback), so nothing it
				// was given may still be running while one of them changes
				FlushRenderingCommands();
				if (!GCookedFresh.Contains(Weak))
				{
					// the game's shader maps were loaded into these (inline): this editor can't use them and they would keep
					// a compile from starting; InitStaticPermutation allocates fresh ones
					TArray<FMaterialResource*>& Resources = Instance->*RebirthMemberOf(FRebirthPermutationResourcesTag());
					bool bInFlight = false;
					for (const FMaterialResource* Resource : Resources)
					{
						bInFlight |= Resource && !Resource->IsCompilationFinished();
					}
					if (bInFlight)
					{
						continue;   // (not expected for cooked resources) the next scan tries again
					}
					ToFree.Append(Resources);
					Resources.Reset();
					GCookedFresh.Add(Weak);
				}
				CookedSanitizeOverrides(*Instance);
				// the compile request is the only thing that looks at these flags; they go straight back
				UPackage* Package = Instance->GetOutermost();
				const uint32 CookedFlags = Package->GetPackageFlags() & (PKG_Cooked | PKG_FilterEditorOnly);
				const bool bCookedForEditor = !!Package->bIsCookedForEditor;
				Package->ClearPackageFlags(CookedFlags);
				Package->bIsCookedForEditor = false;
				Instance->UpdateCachedLayerParameters();
				Instance->InitStaticPermutation();
				Package->SetPackageFlags(CookedFlags);
				Package->bIsCookedForEditor = bCookedForEditor;
				GCookedAttempted.Add(Weak, Base->StateId);
				GCookedCompiling.Add(Weak);
			}
		}
		if (ToFree.Num() > 0)
		{
			// as UMaterialInstance::DeleteDeferredResources: after everything the render thread was given before
			ENQUEUE_RENDER_COMMAND(RebirthFreeCookedMaterialResources)([ToFree](FRHICommandList&)
			{
				for (FMaterialResource* Resource : ToFree)
				{
					delete Resource;
				}
			});
		}
		UE_LOG(LogRebirthRecoveredSurfaces, Display, TEXT("Compiling %d of the game's cooked material instance(s) from their editable base material (their own parents, switches and overrides)."),
			Batch.Num());
	}

	void CookedConsiderChain(UMaterialInterface* Material, TArray<UMaterialInstance*>& Out)
	{
		UMaterialInterface* Current = Material;
		for (int32 Depth = 0; Current && Depth < 64; ++Depth)
		{
			UMaterialInstance* Instance = Cast<UMaterialInstance>(Current);
			if (!Instance)
			{
				return;
			}
			if (CookedNeedsCompile(Instance))
			{
				Out.AddUnique(Instance);
			}
			Current = Instance->Parent;
		}
	}

	void CookedPurgeStale()
	{
		for (auto It = GCookedAttempted.CreateIterator(); It; ++It)
		{
			if (!It.Key().IsValid()) { It.RemoveCurrent(); }
		}
		for (TSet<TWeakObjectPtr<UMaterialInstance>>* Set : { &GCookedFresh, &GCookedBlendWarned })
		{
			for (auto It = Set->CreateIterator(); It; ++It)
			{
				if (!It->IsValid()) { It.RemoveCurrent(); }
			}
		}
	}

	void CookedScan()
	{
		CookedPurgeStale();
		TArray<UObject*> Objects;
		GetObjectsOfClass(UMaterialInstance::StaticClass(), Objects, true, RF_ClassDefaultObject, EInternalObjectFlags::PendingKill);
		TArray<UMaterialInstance*> Batch;
		for (UObject* Object : Objects)
		{
			UMaterialInstance* Instance = static_cast<UMaterialInstance*>(Object);
			if (!CookedSourceBase(Instance))
			{
				continue;
			}
			// also for the ones that need no compile: their editable children take their blend mode from them
			CookedSanitizeOverrides(*Instance);
			if (CookedNeedsCompile(Instance))
			{
				Batch.Add(Instance);
			}
		}
		CookedCompile(Batch);
	}

	/** Compiles finished since the last tick: counted, and the previews pick the real materials up once all are done. */
	void CookedCheckFinished()
	{
		if (GCookedCompiling.Num() == 0)
		{
			return;
		}
		bool bAnyFinished = false;
		for (auto It = GCookedCompiling.CreateIterator(); It; ++It)
		{
			UMaterialInstance* Instance = It->Get();
			if (!Instance)
			{
				It.RemoveCurrent();
				continue;
			}
			if (CookedResourceCompiling(Instance))
			{
				continue;
			}
			UMaterial* Base = Instance->GetMaterial();
			if (Base && CookedHasOwnMap(Instance, Base))
			{
				++GCookedReady;
			}
			else
			{
				++GCookedFailed;
				UE_LOG(LogRebirthRecoveredSurfaces, Warning, TEXT("%s did not compile from %s (LogMaterial has the errors)."), *Instance->GetPathName(),
					*GetPathNameSafe(Base));
			}
			It.RemoveCurrent();
			bAnyFinished = true;
		}
		if (bAnyFinished && GCookedCompiling.Num() == 0)
		{
			UE_LOG(LogRebirthRecoveredSurfaces, Display, TEXT("Cooked material instances compiled from their editable base: %d ready, %d failed (LogMaterial has the errors)."),
				GCookedReady, GCookedFailed);
			RebirthPersonaPreviewSupport::RefreshPreviewMaterials();
		}
	}

	const TCHAR* RecoveredShaderState(const UMaterialInterface* Material)
	{
		const FMaterialResource* Resource = Material ? Material->GetMaterialResource(GMaxRHIFeatureLevel) : nullptr;
		if (!Resource) { return TEXT("no resource"); }
		if (!Resource->IsCompilationFinished()) { return TEXT("compiling"); }
		const FMaterialShaderMap* Map = Resource->GetGameThreadShaderMap();
		return Map && Map->CompiledSuccessfully() ? TEXT("ready") : TEXT("failed to compile (see LogMaterial / LogShaderCompilers)");
	}

	void RecoveredLogStatus()
	{
		UE_LOG(LogRebirthRecoveredSurfaces, Display, TEXT("Recovered surfaces: %s, %d redirected instance(s), %d pending, %d skipped."),
			RecoveredIsEnabled() ? TEXT("on") : TEXT("off"), GRecoveredRecords.Num(), GRecoveredPending.Num(), GRecoveredSkipped.Num());
		UE_LOG(LogRebirthRecoveredSurfaces, Display, TEXT("Cooked instances compiled from their editable base: %s, %d ready, %d failed, %d compiling."),
			CookedCompileEnabled() ? TEXT("on") : TEXT("off"), GCookedReady, GCookedFailed, GCookedCompiling.Num());
		for (const TPair<FString, TStrongObjectPtr<UMaterial>>& Pair : GRecoveredMasters)
		{
			UE_LOG(LogRebirthRecoveredSurfaces, Display, TEXT("  family %-20s %s"), *Pair.Key, RecoveredShaderState(Pair.Value.Get()));
		}
		for (const TPair<FString, FString>& Pair : GRecoveredMasterErrors)
		{
			UE_LOG(LogRebirthRecoveredSurfaces, Display, TEXT("  family %-20s unavailable: %s"), *Pair.Key, *Pair.Value);
		}
		for (const TPair<TWeakObjectPtr<UMaterialInstance>, FRecoveredRecord>& Pair : GRecoveredRecords)
		{
			if (const UMaterialInstance* Instance = Pair.Key.Get())
			{
				UE_LOG(LogRebirthRecoveredSurfaces, Display, TEXT("  %s -> %s [%s]"), *Instance->GetPathName(), *Pair.Value.Description,
					RecoveredShaderState(Instance));
			}
		}
	}

	void RecoveredOnAssetLoaded(UObject* Object)
	{
		if (RecoveredIsEnabled())
		{
			RecoveredConsiderObject(Object);
		}
		else if (CookedCompileEnabled() && Cast<UMaterialInterface>(Object))
		{
			bGCookedScanSoon = true;   // on a tick (loads are still finishing inside this callback)
		}
	}

	void RecoveredPurgeStale()
	{
		for (auto It = GRecoveredRecords.CreateIterator(); It; ++It)
		{
			if (!It.Key().IsValid()) { It.RemoveCurrent(); }
		}
		for (auto It = GRecoveredSkipped.CreateIterator(); It; ++It)
		{
			if (!It->IsValid()) { It.RemoveCurrent(); }
		}
	}

	bool RecoveredTick(float)
	{
		if (!RecoveredCanModifyMaterialsNow())
		{
			return true;
		}
		RecoveredProcessRefresh();
		if (!RecoveredIsEnabled())
		{
			if (GRecoveredRecords.Num() > 0)
			{
				RecoveredRestoreAll();
			}
			bGRecoveredWasEnabled = false;
			if (CookedCompileEnabled())
			{
				const double Now = FPlatformTime::Seconds();
				// loads are caught by OnAssetLoaded (a scan soon, at most twice a second: each compile batch rebuilds every
				// render state); the slow one covers the rest (and a change to the base material)
				if ((bGCookedScanSoon && Now >= GCookedLastScanSeconds + 0.5) || Now >= GCookedNextScanSeconds)
				{
					bGCookedScanSoon = false;
					GCookedLastScanSeconds = Now;
					GCookedNextScanSeconds = Now + 5.0;
					CookedScan();
				}
				CookedCheckFinished();
			}
			return true;
		}
		const double Now = FPlatformTime::Seconds();
		if (!bGRecoveredWasEnabled || Now >= GRecoveredNextScanSeconds)
		{
			// Loads are caught by OnAssetLoaded; this slow scan covers instances loaded before startup, while off, or
			// created in the editor (new instances of RM_Surface).
			bGRecoveredWasEnabled = true;
			GRecoveredNextScanSeconds = Now + 10.0;
			RecoveredPurgeStale();
			RecoveredScanLoaded();
		}
		RecoveredApplyPending();
		return true;
	}
}

namespace RebirthRecoveredSurfaces
{
	void Startup()
	{
		if (IsRunningCommandlet() || GRecoveredTickerHandle.IsValid())
		{
			return;
		}
		GRecoveredAssetLoadedHandle = FCoreUObjectDelegates::OnAssetLoaded.AddStatic(&RecoveredOnAssetLoaded);
		GRecoveredObjectSavedHandle = FCoreUObjectDelegates::OnObjectSaved.AddStatic(&RecoveredOnObjectSaved);
		GRecoveredTickerHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateStatic(&RecoveredTick), 0.0f);
		GRecoveredRestoreCommand = MakeUnique<FAutoConsoleCommand>(TEXT("Rebirth.RecoveredSurfaces.Restore"),
			TEXT("Put every RM_Surface instance back on its real parent until the next load or scan (use Rebirth.RecoveredSurfaces 0 to keep it off)."),
			FConsoleCommandDelegate::CreateStatic(&RecoveredRestoreAll));
		GRecoveredStatusCommand = MakeUnique<FAutoConsoleCommand>(TEXT("Rebirth.RecoveredSurfaces.Status"),
			TEXT("Log the recovered surface families, their shader state and which instances use them."),
			FConsoleCommandDelegate::CreateStatic(&RecoveredLogStatus));
		GRecoveredNextScanSeconds = 0.0;
		bGRecoveredWasEnabled = true;
		UE_LOG(LogRebirthRecoveredSurfaces, Display, TEXT("Recovered retail surface shading active for RM_Surface materials (Rebirth.RecoveredSurfaces=%d)."),
			CVarRecoveredSurfaces.GetValueOnGameThread());
	}

	void Shutdown()
	{
		if (GRecoveredAssetLoadedHandle.IsValid())
		{
			FCoreUObjectDelegates::OnAssetLoaded.Remove(GRecoveredAssetLoadedHandle);
			GRecoveredAssetLoadedHandle.Reset();
		}
		if (GRecoveredObjectSavedHandle.IsValid())
		{
			FCoreUObjectDelegates::OnObjectSaved.Remove(GRecoveredObjectSavedHandle);
			GRecoveredObjectSavedHandle.Reset();
		}
		if (GRecoveredTickerHandle.IsValid())
		{
			FTicker::GetCoreTicker().RemoveTicker(GRecoveredTickerHandle);
			GRecoveredTickerHandle.Reset();
		}
		GRecoveredRestoreCommand.Reset();
		GRecoveredStatusCommand.Reset();
		GRecoveredPending.Reset();
		GRecoveredSkipped.Reset();
		GRecoveredRefresh.Reset();
		GRecoveredRecords.Reset();
		GRecoveredMasterErrors.Reset();
		GCookedAttempted.Reset();
		GCookedFresh.Reset();
		GCookedCompiling.Reset();
		GCookedBlendWarned.Reset();
		// Strong references go before UObject shutdown; nothing is saved after this point.
		GRecoveredBridges.Reset();
		GRecoveredMasters.Reset();
	}

	void ApplyNow(UObject* Object)
	{
		if (!GRecoveredTickerHandle.IsValid() || !RecoveredCanModifyMaterialsNow())
		{
			return;
		}
		if (CookedCompileEnabled())
		{
			TArray<UMaterialInstance*> Batch;
			if (UMaterialInterface* Material = Cast<UMaterialInterface>(Object))
			{
				CookedConsiderChain(Material, Batch);
			}
			else if (USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(Object))
			{
				for (const FSkeletalMaterial& Slot : SkeletalMesh->Materials) { CookedConsiderChain(Slot.MaterialInterface, Batch); }
			}
			else if (UStaticMesh* StaticMesh = Cast<UStaticMesh>(Object))
			{
				for (const FStaticMaterial& Slot : StaticMesh->StaticMaterials) { CookedConsiderChain(Slot.MaterialInterface, Batch); }
			}
			CookedCompile(Batch);
			return;
		}
		if (!RecoveredIsEnabled())
		{
			return;
		}
		RecoveredConsiderObject(Object);
		RecoveredApplyPending();
	}

	bool IsRecovered(const UMaterialInterface* Material)
	{
		const UMaterialInterface* Current = Material;
		for (int32 Depth = 0; Current && Depth < 64; ++Depth)
		{
			if (const UMaterial* Base = Cast<UMaterial>(Current))
			{
				return RecoveredIsMaster(Base);
			}
			const UMaterialInstance* Instance = Cast<UMaterialInstance>(Current);
			Current = Instance ? Instance->Parent : nullptr;
		}
		return false;
	}

	bool IsRetailSurfaceBase(const UMaterialInterface* Material)
	{
		return RecoveredRetailSurfaceOf(const_cast<UMaterialInterface*>(Material)) != nullptr;
	}

	bool GetOriginalState(const UMaterialInstance* Instance, UMaterialInterface*& OutParent, FStaticParameterSet& OutStaticParameters,
		FMaterialInstanceBasePropertyOverrides& OutBasePropertyOverrides)
	{
		const FRecoveredRecord* Record = RecoveredRecordOf(Instance);
		if (!Record)
		{
			return false;
		}
		OutParent = Record->OriginalParent.Get();
		OutStaticParameters = Record->OriginalStaticParameters;
		OutBasePropertyOverrides = Record->OriginalBasePropertyOverrides;
		return true;
	}
}
