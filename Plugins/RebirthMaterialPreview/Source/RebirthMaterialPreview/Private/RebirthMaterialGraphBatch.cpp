#include "CoreMinimal.h"

#include "Dom/JsonObject.h"
#include "HAL/FileManager.h"
#include "HAL/IConsoleManager.h"
#include "HAL/PlatformProcess.h"
#include "MaterialShared.h"
#include "Materials/Material.h"
#include "Materials/MaterialExpressionCustom.h"
#include "Materials/MaterialExpressionIf.h"
#include "Misc/CommandLine.h"
#include "Misc/FileHelper.h"
#include "Misc/PackageName.h"
#include "Misc/Parse.h"
#include "Misc/Paths.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "UObject/Package.h"
#include "UObject/StrongObjectPtr.h"
#include "UObject/UnrealType.h"
#include "UObject/UObjectGlobals.h"

namespace RebirthMaterialGraphBatch
{
namespace
{
uint64 Serial = 0;

struct FResourceIdentity
{
    const FMaterialResource* Resource = nullptr;
    const FMaterialShaderMap* ShaderMap = nullptr;
    bool bFinished = false;
    bool bFinalized = false;
    bool bSuccessful = false;
    uint32 CompilingId = 0;
    FGuid MaterialId;
    FGuid ShaderBaseId;

    TSharedRef<FJsonObject> ToJson() const
    {
        const TSharedRef<FJsonObject> Value = MakeShared<FJsonObject>();
        Value->SetBoolField(TEXT("has_resource"), Resource != nullptr);
        Value->SetStringField(TEXT("resource_address"), FString::Printf(TEXT("%p"), Resource));
        Value->SetStringField(TEXT("shader_map_address"), FString::Printf(TEXT("%p"), ShaderMap));
        Value->SetBoolField(TEXT("has_shader_map"), ShaderMap != nullptr);
        Value->SetBoolField(TEXT("compilation_finished"), bFinished);
        Value->SetBoolField(TEXT("compilation_finalized"), bFinalized);
        Value->SetBoolField(TEXT("compiled_successfully"), bSuccessful);
        Value->SetNumberField(TEXT("compiling_id"), CompilingId);
        Value->SetStringField(TEXT("material_id"), MaterialId.ToString());
        Value->SetStringField(TEXT("shader_base_material_id"), ShaderBaseId.ToString());
        return Value;
    }

    bool Equals(const FResourceIdentity& Other) const
    {
        return Resource == Other.Resource && ShaderMap == Other.ShaderMap
            && bFinished == Other.bFinished && bFinalized == Other.bFinalized
            && bSuccessful == Other.bSuccessful && CompilingId == Other.CompilingId
            && MaterialId == Other.MaterialId && ShaderBaseId == Other.ShaderBaseId;
    }
};

FResourceIdentity Observe(UMaterial* Material)
{
    FResourceIdentity Result;
    // Find the existing current-RHI resource only. No creation, wait, or cache request.
    Result.Resource = Material->GetMaterialResource(GMaxRHIFeatureLevel, EMaterialQualityLevel::Num);
    if (Result.Resource)
    {
        Result.bFinished = Result.Resource->IsCompilationFinished();
        Result.MaterialId = Result.Resource->GetMaterialId();
        Result.ShaderMap = Result.Resource->GetGameThreadShaderMap();
        if (Result.ShaderMap)
        {
            Result.bFinalized = Result.ShaderMap->IsCompilationFinalized();
            Result.bSuccessful = Result.ShaderMap->CompiledSuccessfully();
            Result.CompilingId = Result.ShaderMap->GetCompilingId();
            Result.ShaderBaseId = Result.ShaderMap->GetShaderMapId().BaseMaterialId;
        }
    }
    return Result;
}

bool IsOwnedInvocation(FString& OwnedRun)
{
    const TCHAR* CommandLine = FCommandLine::Get();
    if (!IsInGameThread()
        || !FParse::Param(CommandLine, TEXT("RebirthMaterialFamilyGeneration"))
        || !FParse::Param(CommandLine, TEXT("RebirthMaterialOwnedProbe"))
        || !FParse::Param(CommandLine, TEXT("RebirthCookedMaterialMetadataOnly"))
        || !FParse::Value(CommandLine, TEXT("RebirthMaterialOwnedRun="), OwnedRun)
        || OwnedRun.Len() != 32)
    {
        return false;
    }
    for (const TCHAR Character : OwnedRun)
    {
        if (!FChar::IsHexDigit(Character)) { return false; }
    }
    return true;
}

bool IsFreshOwnedPackage(UMaterial* Material, FString& Reason)
{
    const FString PackageName = Material->GetOutermost()->GetName();
    const FString Prefix = TEXT("/Game/RebirthCompatibility/EditorPreview/MaterialFamilies/");
    if (!PackageName.StartsWith(Prefix) || PackageName.Len() <= Prefix.Len()
        || PackageName.Mid(Prefix.Len()).Contains(TEXT("/")))
    {
        Reason = TEXT("requires_fresh_direct_material_family_package");
        return false;
    }
    UPackage* Package = Material->GetOutermost();
    if (Package->bIsCookedForEditor || Package->HasAnyPackageFlags(PKG_Cooked | PKG_FilterEditorOnly))
    {
        Reason = TEXT("cooked_owner_refused");
        return false;
    }
    if (FPackageName::DoesPackageExist(PackageName))
    {
        Reason = TEXT("existing_package_file_refused");
        return false;
    }
    const FString Stem = FPackageName::LongPackageNameToFilename(PackageName);
    for (const TCHAR* Suffix : { TEXT(".uasset"), TEXT(".uexp"), TEXT(".ubulk"), TEXT(".uptnl") })
    {
        if (IFileManager::Get().FileExists(*(Stem + Suffix)))
        {
            Reason = TEXT("existing_package_sidecar_refused");
            return false;
        }
    }
    return true;
}

bool WriteAtomic(const TSharedRef<FJsonObject>& Report, const TCHAR* FileName = TEXT("LatestCustomOutputBatch.json"))
{
    FString Text;
    const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Text);
    if (!FJsonSerializer::Serialize(Report, Writer)) { return false; }
    const FString Directory = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("MaterialOwnedProbe"));
    if (!IFileManager::Get().DirectoryExists(*Directory)
        && !IFileManager::Get().MakeDirectory(*Directory, true)) { return false; }
    const FString Target = FPaths::Combine(Directory, FileName);
    const FString Pending = Target + FString::Printf(TEXT(".%u.%llu.pending"), FPlatformProcess::GetCurrentProcessId(), Serial);
    if (IFileManager::Get().FileExists(*Pending)) { return false; }
    if (!FFileHelper::SaveStringToFile(Text, *Pending, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM)) { return false; }
    if (!IFileManager::Get().Move(*Target, *Pending, true, false, false, true))
    {
        IFileManager::Get().Delete(*Pending, false, true, true);
        return false;
    }
    return true;
}

void RebuildCustomOutputs(const TArray<FString>& Args)
{
    FString OwnedRun;
    if (!IsOwnedInvocation(OwnedRun)) { return; }
    const TSharedRef<FJsonObject> Report = MakeShared<FJsonObject>();
    Report->SetNumberField(TEXT("schema"), 1);
    Report->SetNumberField(TEXT("pid"), FPlatformProcess::GetCurrentProcessId());
    Report->SetNumberField(TEXT("serial"), static_cast<double>(++Serial));
    Report->SetStringField(TEXT("owned_run"), OwnedRun);
    Report->SetStringField(TEXT("timestamp_utc"), FDateTime::UtcNow().ToIso8601());
    Report->SetBoolField(TEXT("success"), false);
    Report->SetBoolField(TEXT("shader_compilation_requested"), false);
    Report->SetBoolField(TEXT("asset_save_requested"), false);
    Report->SetBoolField(TEXT("compilation_flags_mutated"), false);
    Report->SetStringField(TEXT("notification_mode"), TEXT("Interactive"));

    FString Reason;
    if (Args.Num() != 1)
    {
        Reason = TEXT("requires_one_exact_already_loaded_custom_expression_path");
    }
    else
    {
        Report->SetStringField(TEXT("expression_path"), Args[0]);
        UMaterialExpressionCustom* Custom = FindObject<UMaterialExpressionCustom>(nullptr, *Args[0]);
        if (!IsValid(Custom) || Custom->GetPathName() != Args[0]
            || Custom->HasAnyFlags(RF_NeedLoad | RF_NeedPostLoad | RF_NeedPostLoadSubobjects | RF_BeginDestroyed | RF_FinishDestroyed))
        {
            Reason = TEXT("exact_live_fully_loaded_custom_expression_required");
        }
        else
        {
            UMaterial* Material = Cast<UMaterial>(Custom->GetOuter());
            if (!IsValid(Material) || Custom->Material != Material || Custom->Function != nullptr
                || Material->HasAnyFlags(RF_NeedLoad | RF_NeedPostLoad | RF_NeedPostLoadSubobjects | RF_BeginDestroyed | RF_FinishDestroyed)
                || !Material->Expressions.Contains(Custom) || Custom->GraphNode != nullptr
                || Material->bIsPreviewMaterial || Material->bIsFunctionPreviewMaterial)
            {
                Reason = TEXT("fresh_owned_normal_material_expression_without_graph_required");
            }
            else if (IsFreshOwnedPackage(Material, Reason))
            {
                const TStrongObjectPtr<UMaterial> HoldMaterial(Material);
                const TStrongObjectPtr<UMaterialExpressionCustom> HoldCustom(Custom);
                Report->SetStringField(TEXT("owner_path"), Material->GetPathName());
                Report->SetBoolField(TEXT("owner_context_preserved"), true);
                Report->SetBoolField(TEXT("function_null"), true);
                Report->SetBoolField(TEXT("graph_node_null"), true);
                FProperty* Property = FindFProperty<FProperty>(UMaterialExpressionCustom::StaticClass(), TEXT("AdditionalOutputs"));
                if (!Property)
                {
                    Reason = TEXT("native_additional_outputs_property_missing");
                }
                else
                {
                    const FResourceIdentity Before = Observe(Material);
                    Report->SetObjectField(TEXT("before_resource"), Before.ToJson());
                    // Custom's native virtual implementation rebuilds Outputs first.
                    // Its base expression skips owner PostEditChange for Interactive
                    // events (MaterialExpressions.cpp782-800 and11252-11302).
                    FPropertyChangedEvent Event(Property, EPropertyChangeType::Interactive);
                    Custom->PostEditChangeProperty(Event);
                    const FResourceIdentity After = Observe(Material);
                    Report->SetObjectField(TEXT("after_resource"), After.ToJson());
                    Report->SetBoolField(TEXT("existing_resource_identity_and_state_unchanged"), Before.Equals(After));
                    Report->SetBoolField(TEXT("owner_context_preserved"), Custom->Material == Material && Custom->Function == nullptr);
                    TArray<TSharedPtr<FJsonValue>> Pins;
                    const TArray<FExpressionOutput>& Outputs = Custom->GetOutputs();
                    bool bPinsMatch = Outputs.Num() == Custom->AdditionalOutputs.Num() + 1;
                    for (int32 Index = 0; Index < Outputs.Num(); ++Index)
                    {
                        Pins.Add(MakeShared<FJsonValueString>(Outputs[Index].OutputName.ToString()));
                        if (Index > 0)
                        {
                            bPinsMatch &= Custom->AdditionalOutputs.IsValidIndex(Index - 1)
                                && Outputs[Index].OutputName == Custom->AdditionalOutputs[Index - 1].OutputName;
                        }
                    }
                    Report->SetArrayField(TEXT("output_pins"), Pins);
                    Report->SetNumberField(TEXT("additional_output_count"), Custom->AdditionalOutputs.Num());
                    Report->SetBoolField(TEXT("named_output_pins_match"), bPinsMatch);
                    const bool bSuccess = Before.Equals(After) && bPinsMatch
                        && Custom->Material == Material && Custom->Function == nullptr && Custom->GraphNode == nullptr;
                    Report->SetBoolField(TEXT("success"), bSuccess);
                    Reason = bSuccess ? TEXT("named_outputs_rebuilt_without_owner_compilation") : TEXT("postcondition_failed");
                }
            }
        }
    }
    Report->SetStringField(TEXT("reason"), Reason);
    const bool bWritten = WriteAtomic(Report);
    UE_LOG(LogTemp, Display, TEXT("RebirthMaterialRebuildCustomOutputs pid=%u serial=%llu wrote=%d reason=%s"),
        FPlatformProcess::GetCurrentProcessId(), Serial, bWritten ? 1 : 0, *Reason);
}

void ConnectShadingModel(const TArray<FString>& Args)
{
    FString OwnedRun;
    if (!IsOwnedInvocation(OwnedRun)) { return; }
    const TSharedRef<FJsonObject> Report = MakeShared<FJsonObject>();
    Report->SetNumberField(TEXT("schema"), 1);
    Report->SetNumberField(TEXT("pid"), FPlatformProcess::GetCurrentProcessId());
    Report->SetNumberField(TEXT("serial"), static_cast<double>(++Serial));
    Report->SetStringField(TEXT("owned_run"), OwnedRun);
    Report->SetStringField(TEXT("timestamp_utc"), FDateTime::UtcNow().ToIso8601());
    Report->SetBoolField(TEXT("success"), false);
    Report->SetBoolField(TEXT("shader_compilation_requested"), false);
    Report->SetBoolField(TEXT("asset_save_requested"), false);
    Report->SetBoolField(TEXT("compilation_flags_mutated"), false);
    Report->SetStringField(TEXT("material_property"), TEXT("MP_ShadingModel"));
    Report->SetNumberField(TEXT("native_material_property_index"), static_cast<int32>(MP_ShadingModel));

    FString Reason;
    if (Args.Num() != 1)
    {
        Reason = TEXT("requires_one_exact_already_loaded_if_expression_path");
    }
    else
    {
        Report->SetStringField(TEXT("expression_path"), Args[0]);
        UMaterialExpressionIf* Expression = FindObject<UMaterialExpressionIf>(nullptr, *Args[0]);
        if (!IsValid(Expression) || Expression->GetPathName() != Args[0]
            || Expression->HasAnyFlags(RF_NeedLoad | RF_NeedPostLoad | RF_NeedPostLoadSubobjects | RF_BeginDestroyed | RF_FinishDestroyed))
        {
            Reason = TEXT("exact_live_fully_loaded_if_expression_required");
        }
        else
        {
            UMaterial* Material = Cast<UMaterial>(Expression->GetOuter());
            if (!IsValid(Material) || Expression->Material != Material || Expression->Function != nullptr
                || Material->HasAnyFlags(RF_NeedLoad | RF_NeedPostLoad | RF_NeedPostLoadSubobjects | RF_BeginDestroyed | RF_FinishDestroyed)
                || !Material->Expressions.Contains(Expression) || Expression->GraphNode != nullptr
                || Material->bIsPreviewMaterial || Material->bIsFunctionPreviewMaterial)
            {
                Reason = TEXT("fresh_owned_normal_material_expression_without_graph_required");
            }
            else if (!Material->IsShadingModelFromMaterialExpression())
            {
                Reason = TEXT("owner_requires_shading_model_from_material_expression");
            }
            else if (IsFreshOwnedPackage(Material, Reason))
            {
                const TStrongObjectPtr<UMaterial> HoldMaterial(Material);
                const TStrongObjectPtr<UMaterialExpressionIf> HoldExpression(Expression);
                Report->SetStringField(TEXT("owner_path"), Material->GetPathName());
                Report->SetBoolField(TEXT("owner_context_preserved"), true);
                Report->SetBoolField(TEXT("function_null"), true);
                Report->SetBoolField(TEXT("graph_node_null"), true);
                Report->SetBoolField(TEXT("shading_model_from_material_expression"), true);
                FExpressionInput* Input = Material->GetExpressionInputForProperty(MP_ShadingModel);
                if (!Input || Input->IsConnected())
                {
                    Reason = TEXT("native_shading_model_input_missing_or_already_connected");
                }
                else if (!Expression->GetOutputs().IsValidIndex(0)
                    || !Expression->A.IsConnected() || !Expression->B.IsConnected()
                    || !Expression->AGreaterThanB.IsConnected() || !Expression->AEqualsB.IsConnected()
                    || !Expression->ALessThanB.IsConnected())
                {
                    Reason = TEXT("fully_connected_if_selector_required");
                }
                else
                {
                    const FResourceIdentity Before = Observe(Material);
                    Report->SetObjectField(TEXT("before_resource"), Before.ToJson());
                    Report->SetStringField(TEXT("before_connected_expression_path"), TEXT(""));
                    // Public native property/input API. Connect updates only this
                    // graph input and derives its mask from output zero; it does
                    // not dispatch a property notification or compile/save.
                    Input->Connect(0, Expression);
                    const FResourceIdentity After = Observe(Material);
                    Report->SetObjectField(TEXT("after_resource"), After.ToJson());
                    Report->SetBoolField(TEXT("existing_resource_identity_and_state_unchanged"), Before.Equals(After));
                    Report->SetStringField(TEXT("connected_expression_path"), Input->Expression ? Input->Expression->GetPathName() : TEXT(""));
                    Report->SetNumberField(TEXT("connected_output_index"), Input->OutputIndex);
                    const bool bContextPreserved = Expression->Material == Material && Expression->Function == nullptr && Expression->GraphNode == nullptr;
                    Report->SetBoolField(TEXT("owner_context_preserved"), bContextPreserved);
                    const bool bSuccess = Before.Equals(After) && bContextPreserved
                        && Material->GetExpressionInputForProperty(MP_ShadingModel) == Input
                        && Input->IsConnected() && Input->Expression == Expression && Input->OutputIndex == 0;
                    Report->SetBoolField(TEXT("success"), bSuccess);
                    Reason = bSuccess ? TEXT("native_shading_model_input_connected_without_compilation") : TEXT("postcondition_failed");
                }
            }
        }
    }
    Report->SetStringField(TEXT("reason"), Reason);
    const bool bWritten = WriteAtomic(Report, TEXT("LatestShadingModelConnection.json"));
    UE_LOG(LogTemp, Display, TEXT("RebirthMaterialConnectShadingModel pid=%u serial=%llu wrote=%d reason=%s"),
        FPlatformProcess::GetCurrentProcessId(), Serial, bWritten ? 1 : 0, *Reason);
}

FAutoConsoleCommand RebuildCommand(
    TEXT("Rebirth.MaterialRebuildCustomOutputs"),
    TEXT("Owned fresh graph generation only: rebuild Custom output pins without compiling its owner."),
    FConsoleCommandWithArgsDelegate::CreateStatic(&RebuildCustomOutputs));

FAutoConsoleCommand ConnectShadingModelCommand(
    TEXT("Rebirth.MaterialConnectShadingModel"),
    TEXT("Owned fresh graph generation only: connect an If selector to the native hidden shading-model input without compiling."),
    FConsoleCommandWithArgsDelegate::CreateStatic(&ConnectShadingModel));
}
}
