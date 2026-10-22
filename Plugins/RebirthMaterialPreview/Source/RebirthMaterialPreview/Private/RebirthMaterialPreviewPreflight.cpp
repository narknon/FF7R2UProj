#include "RebirthMaterialPreviewPreflight.h"

#include "Dom/JsonObject.h"
#include "Engine/EngineTypes.h"
#include "MaterialShared.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstance.h"
#include "Misc/App.h"
#include "RHI.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "UObject/Package.h"

namespace RebirthMaterialPreviewPreflight
{
	FResult Evaluate(UMaterialInterface* Material)
	{
		FResult Result;
		TSharedRef<FJsonObject> Report = MakeShared<FJsonObject>();
		Report->SetBoolField(TEXT("diagnostic_only"), true);
		Report->SetBoolField(TEXT("creates_or_compiles_resources"), false);
		TArray<TSharedPtr<FJsonValue>> ChainJson;
		auto Fail = [&Result](const FString& Reason)
		{
			if (Result.Reason.IsEmpty())
			{
				Result.Reason = Reason;
			}
		};

		if (!IsInGameThread())
		{
			Fail(TEXT("preflight_requires_game_thread"));
		}
		else if (!IsValid(Material))
		{
			Fail(TEXT("invalid_material"));
		}
		else
		{
			Report->SetStringField(TEXT("asset"), Material->GetPathName());
			TArray<UMaterialInterface*> Chain;
			TSet<UMaterialInterface*> Seen;
			UMaterialInterface* Current = Material;
			UMaterial* BaseMaterial = nullptr;
			while (Current)
			{
				if (!IsValid(Current) || Current->HasAnyFlags(RF_BeginDestroyed | RF_FinishDestroyed))
				{
					Fail(TEXT("parent_chain_contains_destroying_object"));
					break;
				}
				if (Seen.Contains(Current) || Chain.Num() >= 64)
				{
					Fail(TEXT("parent_chain_cycle_or_depth_limit"));
					break;
				}
				Seen.Add(Current);
				Chain.Add(Current);
				Result.bContainsCookedMaterial |= Current->GetOutermost()->bIsCookedForEditor;
				if (Current->HasAnyFlags(RF_NeedLoad | RF_NeedPostLoad | RF_NeedPostLoadSubobjects))
				{
					Fail(TEXT("parent_chain_not_fully_loaded"));
					break;
				}
				if (UMaterialInstance* Instance = Cast<UMaterialInstance>(Current))
				{
					Current = Instance->Parent;
					if (!Current)
					{
						Fail(TEXT("material_instance_has_no_parent"));
					}
				}
				else
				{
					BaseMaterial = Cast<UMaterial>(Current);
					if (!BaseMaterial)
					{
						Fail(TEXT("unsupported_material_interface_class"));
					}
					break;
				}
			}

			const bool bChainValidated = Result.Reason.IsEmpty() && BaseMaterial != nullptr;
			if (bChainValidated)
			{
				const int32 Domain = static_cast<int32>(BaseMaterial->MaterialDomain.GetValue());
				Report->SetNumberField(TEXT("base_material_domain"), Domain);
				if (Domain < 0 || Domain >= MD_MAX)
				{
					Fail(TEXT("unsupported_material_domain"));
				}
				Report->SetNumberField(TEXT("active_feature_level"), static_cast<int32>(GMaxRHIFeatureLevel));
				Report->SetNumberField(TEXT("active_shader_platform"), static_cast<int32>(GMaxRHIShaderPlatform));
				if (!FApp::CanEverRender() || GMaxRHIShaderPlatform == SP_NumPlatforms)
				{
					Fail(TEXT("renderer_not_available"));
				}

				for (UMaterialInterface* Node : Chain)
				{
					TSharedRef<FJsonObject> Item = MakeShared<FJsonObject>();
					Item->SetStringField(TEXT("asset"), Node->GetPathName());
					Item->SetBoolField(TEXT("cooked_for_editor"), Node->GetOutermost()->bIsCookedForEditor);
					const int32 Blend = static_cast<int32>(Node->GetBlendMode());
					Item->SetNumberField(TEXT("blend_mode"), Blend);
					if (Blend < 0 || Blend >= BLEND_MAX)
					{
						Fail(FString::Printf(TEXT("unsupported_blend_mode:%s:%d"), *Node->GetPathName(), Blend));
					}
					const FMaterialShadingModelField ShadingModels = Node->GetShadingModels();
					Item->SetNumberField(TEXT("shading_model_bits"), ShadingModels.GetShadingModelField());
					if (!ShadingModels.IsValid())
					{
						Fail(FString::Printf(TEXT("unsupported_shading_models:%s"), *Node->GetPathName()));
					}

					// GetMaterialResource finds an existing resource; it does not create one.
					const FMaterialResource* Resource = Node->GetMaterialResource(GMaxRHIFeatureLevel);
					Item->SetBoolField(TEXT("has_material_resource"), Resource != nullptr);
					if (!Resource)
					{
						Fail(FString::Printf(TEXT("missing_material_resource:%s"), *Node->GetPathName()));
					}
					else
					{
						const int32 ResourceBlend = static_cast<int32>(Resource->GetBlendMode());
						Item->SetNumberField(TEXT("resource_blend_mode"), ResourceBlend);
						if (ResourceBlend < 0 || ResourceBlend >= BLEND_MAX)
						{
							Fail(FString::Printf(TEXT("unsupported_resource_blend_mode:%s:%d"), *Node->GetPathName(), ResourceBlend));
						}
						const FMaterialShaderMap* Map = Resource->GetGameThreadShaderMap();
						Item->SetBoolField(TEXT("has_shader_map"), Map != nullptr);
						if (!Map)
						{
							Fail(FString::Printf(TEXT("missing_shader_map:%s"), *Node->GetPathName()));
						}
						else if (!Map->GetContent() || !Map->GetResource())
						{
							Fail(FString::Printf(TEXT("incomplete_shader_map_storage:%s"), *Node->GetPathName()));
						}
						else
						{
							const bool bFinalized = Map->IsCompilationFinalized();
							const bool bCompiled = Map->CompiledSuccessfully();
							const bool bInitialized = Map->GetResource()->IsInitialized();
							Item->SetBoolField(TEXT("compilation_finalized"), bFinalized);
							Item->SetBoolField(TEXT("compiled_successfully"), bCompiled);
							Item->SetBoolField(TEXT("resource_initialized"), bInitialized);
							Item->SetNumberField(TEXT("shader_map_platform"), static_cast<int32>(Map->GetShaderPlatform()));
							Item->SetNumberField(TEXT("resource_platform"), static_cast<int32>(Map->GetResource()->GetPlatform()));
							Item->SetNumberField(TEXT("shader_count"), Map->GetShaderNum());
							Item->SetNumberField(TEXT("resource_shader_count"), Map->GetResource()->GetNumShaders());
							if (!bFinalized || !bCompiled || Map->GetShaderNum() <= 0 || Map->GetResource()->GetNumShaders() <= 0)
							{
								Fail(FString::Printf(TEXT("shader_map_not_ready:%s"), *Node->GetPathName()));
							}
							else if (Map->GetShaderPlatform() != GMaxRHIShaderPlatform || Map->GetResource()->GetPlatform() != GMaxRHIShaderPlatform)
							{
								Fail(FString::Printf(TEXT("shader_platform_mismatch:%s"), *Node->GetPathName()));
							}
							else if (!bInitialized)
							{
								Fail(FString::Printf(TEXT("shader_resource_initialization_pending:%s"), *Node->GetPathName()));
							}
						}
					}
					ChainJson.Add(MakeShared<FJsonValueObject>(Item));
				}
			}
		}

		Result.bAllowed = Result.Reason.IsEmpty();
		Report->SetBoolField(TEXT("allowed"), Result.bAllowed);
		Report->SetBoolField(TEXT("contains_cooked_material"), Result.bContainsCookedMaterial);
		Report->SetStringField(TEXT("reason"), Result.bAllowed ? TEXT("preflight_passed_not_a_rendering_guarantee") : Result.Reason);
		Report->SetArrayField(TEXT("parent_chain"), ChainJson);
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Result.Json);
		if (!FJsonSerializer::Serialize(Report, Writer))
		{
			Result.bAllowed = false;
			Result.Reason = TEXT("preflight_json_serialization_failed");
			Result.Json = TEXT("{\"allowed\":false,\"reason\":\"preflight_json_serialization_failed\"}");
		}
		return Result;
	}
}

FString URebirthMaterialPreviewPreflightLibrary::GetMaterialRuntimePreviewPreflight(UMaterialInterface* Material)
{
	return RebirthMaterialPreviewPreflight::Evaluate(Material).Json;
}
