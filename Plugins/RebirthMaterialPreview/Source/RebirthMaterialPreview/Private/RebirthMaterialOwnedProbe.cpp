#include "RebirthMaterialOwnedProbe.h"

#include "RebirthMaterialFamilySnapshot.h"
#include "RebirthMaterialPreviewSafety.h"
#include "RebirthPreviewMaterialResolver.h"
#include "Dom/JsonObject.h"
#include "HAL/FileManager.h"
#include "HAL/IConsoleManager.h"
#include "HAL/PlatformProcess.h"
#include "Materials/MaterialInterface.h"
#include "Misc/CommandLine.h"
#include "Misc/FileHelper.h"
#include "Misc/Parse.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "UObject/StrongObjectPtr.h"
#include "UObject/UObjectGlobals.h"

namespace RebirthMaterialOwnedProbe
{
    namespace
    {
        TUniquePtr<FAutoConsoleCommand> InspectCommand;
        uint64 Serial = 0;

        TSharedRef<FJsonObject> SafetyObject(const RebirthMaterialPreviewSafety::FResult& Safety)
        {
            const TSharedRef<FJsonObject> Value = MakeShared<FJsonObject>();
            Value->SetBoolField(TEXT("can_render"), Safety.bCanRender);
            Value->SetBoolField(TEXT("uses_cooked_chain"), Safety.bUsesCookedChain);
            Value->SetBoolField(TEXT("parent_chain_valid"), Safety.bParentChainValid);
            Value->SetBoolField(TEXT("invalid_blend_mode"), Safety.bHasInvalidBlendMode);
            Value->SetBoolField(TEXT("unsupported_render_state"), Safety.bHasUnsupportedRenderState);
            Value->SetStringField(TEXT("reason"), Safety.Reason);
            return Value;
        }

        void Inspect(const TArray<FString>& Args)
        {
            if (!FParse::Param(FCommandLine::Get(), TEXT("RebirthMaterialOwnedProbe")) || !IsInGameThread()) { return; }
            const TSharedRef<FJsonObject> Report = MakeShared<FJsonObject>();
            Report->SetNumberField(TEXT("schema"), 1);
            Report->SetNumberField(TEXT("pid"), FPlatformProcess::GetCurrentProcessId());
            Report->SetNumberField(TEXT("serial"), static_cast<double>(++Serial));
            Report->SetStringField(TEXT("timestamp_utc"), FDateTime::UtcNow().ToIso8601());
            Report->SetBoolField(TEXT("success"), false);
            Report->SetBoolField(TEXT("originals_loaded_by_probe"), false);
            Report->SetBoolField(TEXT("originals_mutated_or_saved"), false);
            Report->SetBoolField(TEXT("registered_companion_load_permitted"), true);
            if (Args.Num() != 1)
            {
                Report->SetStringField(TEXT("reason"), TEXT("requires_one_already_loaded_material_object_path"));
            }
            else
            {
                Report->SetStringField(TEXT("original_path"), Args[0]);
                UMaterialInterface* Original = FindObject<UMaterialInterface>(nullptr, *Args[0]);
                if (!IsValid(Original) || Original->GetPathName() != Args[0])
                {
                    Report->SetStringField(TEXT("reason"), TEXT("exact_original_material_not_already_loaded"));
                }
                else
                {
                    const FString SnapshotText = RebirthMaterialFamilySnapshot::Inspect(Original);
                    TSharedPtr<FJsonObject> Snapshot;
                    const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(SnapshotText);
                    if (!FJsonSerializer::Deserialize(Reader, Snapshot) || !Snapshot.IsValid())
                    {
                        Report->SetStringField(TEXT("reason"), TEXT("snapshot_serialization_failed"));
                    }
                    else
                    {
                        Report->SetObjectField(TEXT("snapshot"), Snapshot);
                        Report->SetObjectField(TEXT("original_safety"), SafetyObject(RebirthMaterialPreviewSafety::Evaluate(Original)));
                        const RebirthPreviewMaterialResolver::FResult Resolved = RebirthPreviewMaterialResolver::Resolve(Original, GetTransientPackage());
                        const TStrongObjectPtr<UMaterialInterface> HoldSelected(Resolved.Material);
                        const TSharedRef<FJsonObject> Selection = MakeShared<FJsonObject>();
                        Selection->SetStringField(TEXT("material"), Resolved.Material ? Resolved.Material->GetPathName() : FString());
                        Selection->SetStringField(TEXT("fidelity"), Resolved.Fidelity);
                        Selection->SetStringField(TEXT("reason"), Resolved.Reason);
                        Selection->SetBoolField(TEXT("uses_original_resource"), Resolved.bUsesOriginalResource);
                        Selection->SetBoolField(TEXT("pending_shader_resources"), Resolved.bPendingShaderResources);
                        Selection->SetBoolField(TEXT("gc_owned_during_inspection"), Resolved.Material != nullptr);
                        if (Resolved.Material) { Selection->SetObjectField(TEXT("safety"), SafetyObject(RebirthMaterialPreviewSafety::Evaluate(Resolved.Material))); }
                        Report->SetObjectField(TEXT("resolve"), Selection);
                        bool bSnapshotSucceeded = false;
                        Snapshot->TryGetBoolField(TEXT("success"), bSnapshotSucceeded);
                        Report->SetBoolField(TEXT("success"), bSnapshotSucceeded);
                        Report->SetStringField(TEXT("reason"), bSnapshotSucceeded ? FString() : TEXT("native_capability_snapshot_refused"));
                    }
                }
            }
            FString Text;
            const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Text);
            FJsonSerializer::Serialize(Report, Writer);
            const FString Directory = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("MaterialOwnedProbe"));
            IFileManager::Get().MakeDirectory(*Directory, true);
            const FString Path = FPaths::Combine(Directory, TEXT("LatestInspection.json"));
            const bool bSaved = FFileHelper::SaveStringToFile(Text, *Path, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
            UE_LOG(LogTemp, Display, TEXT("RebirthMaterialInspect pid=%u serial=%llu wrote=%d report=%s"), FPlatformProcess::GetCurrentProcessId(), Serial, bSaved ? 1 : 0, *Path);
        }
    }

    void Register()
    {
        if (!FParse::Param(FCommandLine::Get(), TEXT("RebirthMaterialOwnedProbe")) || InspectCommand) { return; }
        InspectCommand = MakeUnique<FAutoConsoleCommand>(
            TEXT("Rebirth.MaterialInspect"),
            TEXT("Inspect one already-loaded material; owned diagnostic process only."),
            FConsoleCommandWithArgsDelegate::CreateStatic(&Inspect));
    }

    void Unregister() { InspectCommand.Reset(); }
}
