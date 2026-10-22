#include "RebirthMaterialDiagnosticsLibrary.h"
#include "Materials/MaterialInterface.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialExpressionStaticSwitchParameter.h"
#include "Materials/MaterialExpression.h"
#include "Materials/MaterialExpressionComment.h"
#include "StaticParameterSet.h"
#include "MaterialShared.h"
#include "Engine/Texture.h"
#include "Engine/Texture2D.h"
#include "UObject/Package.h"
#include "RHI.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "UObject/UnrealType.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "RebirthDataObjectInspection.h"
#include "RebirthMaterialPreviewSafety.h"
#include "Editor.h"
#include "Engine/World.h"
#include "ImageUtils.h"
#include "LevelEditorViewport.h"
#include "Misc/App.h"
#include "UnrealClient.h"
#include "Camera/CameraActor.h"
#include "Application/ThrottleManager.h"
#include "SceneView.h"
#include "SceneManagement.h"

namespace
{
FString JsonString(const TSharedRef<FJsonObject>& Object)
{
    FString Result;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Result);
    FJsonSerializer::Serialize(Object, Writer);
    return Result;
}
}

FString URebirthMaterialDiagnosticsLibrary::GetMaterialPreviewPreflight(UMaterialInterface* Material)
{
    const RebirthMaterialPreviewSafety::FResult Result = RebirthMaterialPreviewSafety::Evaluate(Material);
    TSharedRef<FJsonObject> Report = MakeShared<FJsonObject>();
    Report->SetStringField(TEXT("asset"), GetPathNameSafe(Material));
    Report->SetBoolField(TEXT("can_render"), Result.bCanRender);
    Report->SetBoolField(TEXT("uses_cooked_chain"), Result.bUsesCookedChain);
    Report->SetBoolField(TEXT("parent_chain_valid"), Result.bParentChainValid);
    Report->SetBoolField(TEXT("invalid_blend_mode"), Result.bHasInvalidBlendMode);
    Report->SetBoolField(TEXT("unsupported_render_state"), Result.bHasUnsupportedRenderState);
    Report->SetStringField(TEXT("reason"), Result.Reason);
    Report->SetBoolField(TEXT("render_submitted"), false);
    Report->SetBoolField(TEXT("shader_compilation_requested"), false);
    return JsonString(Report);
}

FString URebirthMaterialDiagnosticsLibrary::GetMaterialDiagnostics(UMaterialInterface* Material, bool bWaitForCompilation)
{
    TSharedRef<FJsonObject> Report = MakeShared<FJsonObject>();
    Report->SetStringField(TEXT("asset"), GetPathNameSafe(Material));
    Report->SetBoolField(TEXT("valid_material"), IsValid(Material));
    Report->SetBoolField(TEXT("game_thread"), IsInGameThread());
    if (IsValid(Material) && IsInGameThread())
    {
        const RebirthMaterialPreviewSafety::FResult Preflight = RebirthMaterialPreviewSafety::Evaluate(Material);
        Report->SetStringField(TEXT("preview_preflight_json"), GetMaterialPreviewPreflight(Material));
        if (!Preflight.bParentChainValid) { return JsonString(Report); }
        UPackage* Package = Material->GetOutermost();
        const bool bCooked = Package && (Package->bIsCookedForEditor || Package->HasAnyPackageFlags(PKG_Cooked | PKG_FilterEditorOnly));
        Report->SetBoolField(TEXT("cooked_for_editor"), bCooked);
        Report->SetNumberField(TEXT("package_flags"), Package ? Package->GetPackageFlags() : 0);
        Report->SetNumberField(TEXT("rhi_shader_platform"), static_cast<int32>(GMaxRHIShaderPlatform));
        Report->SetNumberField(TEXT("rhi_feature_level"), static_cast<int32>(GMaxRHIFeatureLevel));

        TArray<TSharedPtr<FJsonValue>> Resources;
        for (int32 Quality = 0; Quality <= static_cast<int32>(EMaterialQualityLevel::Num); ++Quality)
        {
            const EMaterialQualityLevel::Type RequestedQuality = static_cast<EMaterialQualityLevel::Type>(Quality);
            FMaterialResource* Resource = Material->GetMaterialResource(GMaxRHIFeatureLevel, RequestedQuality);
            TSharedRef<FJsonObject> Entry = MakeShared<FJsonObject>();
            Entry->SetNumberField(TEXT("requested_quality"), Quality);
            Entry->SetBoolField(TEXT("has_resource"), Resource != nullptr);
            TArray<TSharedPtr<FJsonValue>> Errors;
            if (Resource)
            {
                if (bWaitForCompilation && !bCooked)
                {
                    Resource->FinishCompilation();
                }
                Entry->SetNumberField(TEXT("resource_quality"), static_cast<int32>(Resource->GetQualityLevel()));
                Entry->SetBoolField(TEXT("compilation_finished"), Resource->IsCompilationFinished());
                // Read-only identity telemetry. A finalized map may belong to an
                // older UMaterial state; retain the native completion flag above.
                const FGuid ResourceMaterialId = Resource->GetMaterialId();
                Entry->SetStringField(TEXT("resource_material_id"), ResourceMaterialId.ToString(EGuidFormats::DigitsWithHyphens));
                Entry->SetBoolField(TEXT("resource_material_id_valid"), ResourceMaterialId.IsValid());
                const FMaterialShaderMap* ShaderMap = Resource->GetGameThreadShaderMap();
                Entry->SetBoolField(TEXT("has_shader_map"), ShaderMap != nullptr);
                Entry->SetBoolField(TEXT("compiled_successfully"), ShaderMap && ShaderMap->CompiledSuccessfully());
                Entry->SetBoolField(TEXT("compilation_finalized"), ShaderMap && ShaderMap->IsCompilationFinalized());
                Entry->SetBoolField(TEXT("shader_map_current_material_id_matches"), false);
                // IsComplete and the protected unfinished-ID accessor are not
                // exported by this exact Engine DLL/import library. Do not call
                // private RVAs, downcast objects, or infer completion from IDs.
                Entry->SetBoolField(TEXT("shader_map_is_complete_available"), false);
                Entry->SetBoolField(TEXT("shader_map_completeness_checked"), false);
                Entry->SetStringField(TEXT("shader_map_is_complete_unavailable_reason"), TEXT("FMaterialShaderMap::IsComplete is not exported by this engine build."));
                if (ShaderMap)
                {
                    const FGuid ShaderMapBaseMaterialId = ShaderMap->GetShaderMapId().BaseMaterialId;
                    Entry->SetStringField(TEXT("shader_map_base_material_id"), ShaderMapBaseMaterialId.ToString(EGuidFormats::DigitsWithHyphens));
                    Entry->SetBoolField(TEXT("shader_map_base_material_id_valid"), ShaderMapBaseMaterialId.IsValid());
                    Entry->SetNumberField(TEXT("shader_map_compiling_id"), ShaderMap->GetCompilingId());
                    Entry->SetBoolField(TEXT("shader_map_current_material_id_matches"), ResourceMaterialId.IsValid() && ShaderMapBaseMaterialId.IsValid() && ShaderMapBaseMaterialId == ResourceMaterialId);
                    Entry->SetNumberField(TEXT("shader_count"), ShaderMap->GetShaderNum());
                    Entry->SetBoolField(TEXT("has_shader_resource"), ShaderMap->GetResource() != nullptr);
                    Entry->SetNumberField(TEXT("resource_shader_count"), ShaderMap->GetResource() ? ShaderMap->GetResource()->GetNumShaders() : 0);
                    Entry->SetNumberField(TEXT("shader_platform"), static_cast<int32>(ShaderMap->GetShaderPlatform()));
                    Entry->SetNumberField(TEXT("feature_level"), static_cast<int32>(ShaderMap->GetShaderMapId().FeatureLevel));
                    Entry->SetNumberField(TEXT("shader_quality"), static_cast<int32>(ShaderMap->GetShaderMapId().QualityLevel));
                }
                for (const FString& Error : Resource->GetCompileErrors())
                {
                    Errors.Add(MakeShared<FJsonValueString>(Error));
                }
            }
            Entry->SetArrayField(TEXT("compile_errors"), Errors);
            Resources.Add(MakeShared<FJsonValueObject>(Entry));
        }
        Report->SetArrayField(TEXT("resources"), Resources);

        TArray<UTexture*> Textures;
        Material->GetUsedTextures(Textures, EMaterialQualityLevel::Num, true, GMaxRHIFeatureLevel, false);
        TArray<TSharedPtr<FJsonValue>> Paths;
        TArray<TSharedPtr<FJsonValue>> TextureStates;
        for (UTexture* Texture : Textures)
        {
            Paths.Add(MakeShared<FJsonValueString>(GetPathNameSafe(Texture)));
            if (UTexture2D* Texture2D = Cast<UTexture2D>(Texture))
            {
                TSharedRef<FJsonObject> State = MakeShared<FJsonObject>();
                State->SetStringField(TEXT("asset"), Texture2D->GetPathName());
                State->SetNumberField(TEXT("size_x"), Texture2D->GetSizeX());
                State->SetNumberField(TEXT("size_y"), Texture2D->GetSizeY());
                State->SetNumberField(TEXT("total_mips"), Texture2D->GetNumMips());
                State->SetNumberField(TEXT("resident_mips"), Texture2D->GetNumResidentMips());
                State->SetBoolField(TEXT("fully_resident"), Texture2D->GetNumResidentMips() == Texture2D->GetNumMips());
                TextureStates.Add(MakeShared<FJsonValueObject>(State));
            }
        }
        Report->SetArrayField(TEXT("used_texture_paths"), Paths);
        Report->SetArrayField(TEXT("used_texture_residency"), TextureStates);
        if (UMaterial* Base = Material->GetMaterial())
        {
            Report->SetStringField(TEXT("base_material"), Base->GetPathName());
            Report->SetStringField(TEXT("base_material_state_id"), Base->StateId.ToString(EGuidFormats::DigitsWithHyphens));
            Report->SetBoolField(TEXT("base_material_state_id_valid"), Base->StateId.IsValid());
            Report->SetNumberField(TEXT("expression_count"), Base->Expressions.Num());
        }
    }
    FString Json;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Json);
    FJsonSerializer::Serialize(Report, Writer);
    return Json;
}

FString URebirthMaterialDiagnosticsLibrary::GetAssetDiagnostics(UObject* Asset)
{
    TSharedRef<FJsonObject> Report = MakeShared<FJsonObject>();
    Report->SetStringField(TEXT("phase"), TEXT("loaded_object_inspection"));
    Report->SetStringField(TEXT("asset"), GetPathNameSafe(Asset));
    Report->SetBoolField(TEXT("valid_object"), IsValid(Asset));
    Report->SetBoolField(TEXT("game_thread"), IsInGameThread());
    Report->SetBoolField(TEXT("gameplay_executed"), false);
    Report->SetBoolField(TEXT("graph_recompiled"), false);
    if (IsValid(Asset) && IsInGameThread())
    {
        Report->SetStringField(TEXT("class"), Asset->GetClass()->GetPathName());
        Report->SetNumberField(TEXT("object_flags"), Asset->GetFlags());
        UPackage* Package = Asset->GetOutermost();
        Report->SetStringField(TEXT("package"), GetPathNameSafe(Package));
        Report->SetNumberField(TEXT("package_flags"), Package ? Package->GetPackageFlags() : 0);
        Report->SetBoolField(TEXT("cooked_for_editor"), Package && (Package->bIsCookedForEditor || Package->HasAnyPackageFlags(PKG_Cooked | PKG_FilterEditorOnly)));
        TArray<TSharedPtr<FJsonValue>> Properties;
        int32 Count = 0;
        for (TFieldIterator<FProperty> Iterator(Asset->GetClass()); Iterator && Count < 512; ++Iterator, ++Count)
        {
            const FProperty* Property = *Iterator;
            TSharedRef<FJsonObject> Entry = MakeShared<FJsonObject>();
            Entry->SetStringField(TEXT("property"), Property->GetName());
            Entry->SetStringField(TEXT("type"), Property->GetCPPType());
            Entry->SetNumberField(TEXT("static_array_size"), Property->ArrayDim);
            const void* Value = Property->ContainerPtrToValuePtr<void>(Asset);
            // Only scalar exports are used. Never invoke an asset-specific exporter,
            // custom Details panel, nested struct serialization, or resolve a soft reference.
            if (const FArrayProperty* Array = CastField<FArrayProperty>(Property))
            {
                Entry->SetNumberField(TEXT("count"), FScriptArrayHelper(Array, Value).Num());
            }
            else if (const FMapProperty* Map = CastField<FMapProperty>(Property))
            {
                Entry->SetNumberField(TEXT("count"), FScriptMapHelper(Map, Value).Num());
            }
            else if (const FSetProperty* Set = CastField<FSetProperty>(Property))
            {
                Entry->SetNumberField(TEXT("count"), FScriptSetHelper(Set, Value).Num());
            }
            else if (const FStructProperty* Struct = CastField<FStructProperty>(Property))
            {
                Entry->SetStringField(TEXT("struct"), GetPathNameSafe(Struct->Struct));
                Entry->SetStringField(TEXT("value"), TEXT("Nested structure is not expanded."));
            }
            else if (const FObjectProperty* Reference = CastField<FObjectProperty>(Property))
            {
                Entry->SetStringField(TEXT("value"), GetPathNameSafe(Reference->GetObjectPropertyValue(Value)));
            }
            else if (CastField<FBoolProperty>(Property) || CastField<FNumericProperty>(Property) ||
                CastField<FEnumProperty>(Property) || CastField<FNameProperty>(Property) ||
                CastField<FStrProperty>(Property) || CastField<FTextProperty>(Property))
            {
                FString Text;
                Property->ExportText_InContainer(0, Text, Asset, nullptr, Asset, PPF_None);
                Entry->SetStringField(TEXT("value"), Text.Left(1024));
                Entry->SetBoolField(TEXT("value_truncated"), Text.Len() > 1024);
            }
            else
            {
                Entry->SetStringField(TEXT("value"), TEXT("Not expanded; references and executable data remain untouched."));
            }
            Properties.Add(MakeShared<FJsonValueObject>(Entry));
        }
        Report->SetArrayField(TEXT("properties"), Properties);
        Report->SetBoolField(TEXT("property_limit_reached"), Count >= 512);
        AppendEndDataObjectDiagnostics(Asset, Report, 100);
    }
    return JsonString(Report);
}

FString URebirthMaterialDiagnosticsLibrary::LoadAssetDiagnostics(const FString& ObjectPath)
{
    TSharedRef<FJsonObject> Phase = MakeShared<FJsonObject>();
    const FString Directory = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("RebirthMaterialPreview/Diagnostics"));
    const FString Filename = FPaths::Combine(Directory, FString::Printf(TEXT("Load-%s.json"), *FGuid::NewGuid().ToString(EGuidFormats::Digits)));
    Phase->SetStringField(TEXT("asset_path"), ObjectPath);
    Phase->SetStringField(TEXT("phase_file"), Filename);
    Phase->SetStringField(TEXT("phase"), TEXT("before_native_load"));
    Phase->SetStringField(TEXT("utc"), FDateTime::UtcNow().ToIso8601());
    Phase->SetBoolField(TEXT("gameplay_executed"), false);
    if (!IsInGameThread() || ObjectPath.IsEmpty())
    {
        Phase->SetStringField(TEXT("phase"), TEXT("rejected_invalid_request"));
        return JsonString(Phase);
    }
    IFileManager::Get().MakeDirectory(*Directory, true);
    if (!FFileHelper::SaveStringToFile(JsonString(Phase), *Filename))
    {
        Phase->SetStringField(TEXT("phase"), TEXT("rejected_phase_marker_write_failed"));
        return JsonString(Phase);
    }
    UE_LOG(LogTemp, Display, TEXT("Rebirth cooked asset diagnostics: before_native_load %s; phase file %s"), *ObjectPath, *Filename);
    UObject* Asset = LoadObject<UObject>(nullptr, *ObjectPath);
    Phase->SetStringField(TEXT("phase"), Asset ? TEXT("native_load_returned") : TEXT("native_load_failed"));
    Phase->SetBoolField(TEXT("load_succeeded"), Asset != nullptr);
    Phase->SetStringField(TEXT("inspection_json"), GetAssetDiagnostics(Asset));
    Phase->SetStringField(TEXT("utc"), FDateTime::UtcNow().ToIso8601());
    const FString Result = JsonString(Phase);
    FFileHelper::SaveStringToFile(Result, *Filename);
    UE_LOG(LogTemp, Display, TEXT("Rebirth cooked asset diagnostics: %s %s"), Asset ? TEXT("native_load_returned") : TEXT("native_load_failed"), *ObjectPath);
    return Result;
}

FString URebirthMaterialDiagnosticsLibrary::CaptureEditorViewportImage(const FString& Filename, bool bUsePilotedCameraSettings)
{
    TSharedRef<FJsonObject> Report = MakeShared<FJsonObject>();
    Report->SetStringField(TEXT("filename"), Filename);
    Report->SetNumberField(TEXT("width"), 0);
    Report->SetNumberField(TEXT("height"), 0);
    Report->SetNumberField(TEXT("pixel_count"), 0);
    Report->SetBoolField(TEXT("success"), false);
    Report->SetBoolField(TEXT("game_thread"), IsInGameThread());
    Report->SetBoolField(TEXT("draw_requested"), false);
    Report->SetBoolField(TEXT("read_succeeded"), false);
    auto Fail = [&Report](const FString& Reason)
    {
        Report->SetStringField(TEXT("reason"), Reason);
        return JsonString(Report);
    };
    if (!IsInGameThread()) { return Fail(TEXT("capture_requires_game_thread")); }
    if (IsRunningCommandlet()) { return Fail(TEXT("capture_requires_editor_viewport_not_commandlet")); }
    if (!GEditor || !FApp::CanEverRender() || GMaxRHIShaderPlatform == SP_NumPlatforms)
    {
        return Fail(TEXT("rendering_editor_not_available"));
    }
    // Do not draw recursively if a capture caller is itself reached by drawing.
    static bool bCapturing = false;
    if (bCapturing) { return Fail(TEXT("recursive_viewport_capture_rejected")); }
    TGuardValue<bool> CaptureGuard(bCapturing, true);

    FText PathError;
    if (Filename.IsEmpty() || FPaths::IsRelative(Filename) ||
        !FPaths::GetExtension(Filename).Equals(TEXT("png"), ESearchCase::IgnoreCase) ||
        !FPaths::ValidatePath(Filename, &PathError))
    {
        return Fail(TEXT("capture_filename_must_be_valid_absolute_png_path"));
    }
    FString OutputFilename = FPaths::ConvertRelativePathToFull(Filename);
    FPaths::NormalizeFilename(OutputFilename);
    if (!FPaths::CollapseRelativeDirectories(OutputFilename))
    {
        return Fail(TEXT("capture_filename_cannot_be_normalized"));
    }
    Report->SetStringField(TEXT("filename"), OutputFilename);

    FViewport* Viewport = GEditor->GetActiveViewport();
    if (!Viewport) { return Fail(TEXT("active_editor_viewport_missing")); }
    FLevelEditorViewportClient* LevelClient = nullptr;
    for (FLevelEditorViewportClient* Candidate : GEditor->GetLevelViewportClients())
    {
        if (Candidate && Candidate->Viewport == Viewport && Viewport->GetClient() == Candidate)
        {
            LevelClient = Candidate;
            break;
        }
    }
    if (!LevelClient) { return Fail(TEXT("active_viewport_is_not_a_level_editor_viewport")); }
    UWorld* World = LevelClient->GetWorld();
    if (!World || !World->Scene || World->IsGameWorld())
    {
        return Fail(TEXT("active_level_editor_world_not_available"));
    }
    ACameraActor* PilotedCamera = Cast<ACameraActor>(LevelClient->GetActiveActorLock().Get());
    if (bUsePilotedCameraSettings && (!IsValid(PilotedCamera) || PilotedCamera->GetWorld() != World))
    {
        return Fail(TEXT("piloted_camera_settings_require_a_camera_in_the_active_world"));
    }
    // Actor piloting can follow only the transform while keeping the editor's
    // default90-degree lens. Explicit capture callers can instead request the
    // camera's own lens, aspect ratio and post process for this synchronous draw.
    TGuardValue<bool> LockedCameraViewGuard(LevelClient->bLockedCameraView,
        bUsePilotedCameraSettings ? true : LevelClient->bLockedCameraView);
    TGuardValue<float> ViewFOVGuard(LevelClient->ViewFOV, LevelClient->ViewFOV);
    if (bUsePilotedCameraSettings)
    {
        LevelClient->UpdateViewForLockedActor(0.0f);
    }
    Report->SetBoolField(TEXT("piloted_camera_settings_applied"), bUsePilotedCameraSettings);
    Report->SetNumberField(TEXT("view_fov"), LevelClient->ViewFOV);
    Report->SetStringField(TEXT("world"), World->GetPathName());
    Report->SetStringField(TEXT("view_location"), LevelClient->GetViewLocation().ToString());
    Report->SetStringField(TEXT("view_rotation"), LevelClient->GetViewRotation().ToString());
    Report->SetBoolField(TEXT("perspective"), LevelClient->IsPerspective());
    Report->SetBoolField(TEXT("realtime"), LevelClient->IsRealtime());
    Report->SetBoolField(TEXT("temporal_aa_show_flag"), LevelClient->EngineShowFlags.TemporalAA);
    Report->SetBoolField(TEXT("anti_aliasing_show_flag"), LevelClient->EngineShowFlags.AntiAliasing);
    Report->SetBoolField(TEXT("post_processing_show_flag"), LevelClient->EngineShowFlags.PostProcessing);
    const bool bExpensiveTasksAllowed = FSlateThrottleManager::Get().IsAllowingExpensiveTasks();
    Report->SetBoolField(TEXT("slate_expensive_tasks_allowed"), bExpensiveTasksAllowed);
    // Mirror FEditorViewportClient::Draw's family realtime condition. Show flags
    // alone do not establish that the renderer actually uses temporal AA.
    FSceneViewFamilyContext DiagnosticFamily(FSceneViewFamily::ConstructionValues(
        Viewport, LevelClient->GetScene(), LevelClient->EngineShowFlags)
        .SetRealtimeUpdate(LevelClient->IsRealtime() && bExpensiveTasksAllowed));
    FSceneView* DiagnosticView = LevelClient->CalcSceneView(&DiagnosticFamily);
    Report->SetBoolField(TEXT("actual_family_realtime"), DiagnosticFamily.bRealtimeUpdate);
    if (DiagnosticView)
    {
        Report->SetNumberField(TEXT("actual_anti_aliasing_method"), static_cast<int32>(DiagnosticView->AntiAliasingMethod));
        Report->SetBoolField(TEXT("view_state_present"), DiagnosticView->State != nullptr);
        Report->SetBoolField(TEXT("camera_cut"), DiagnosticView->bCameraCut);
        if (DiagnosticView->State)
        {
            Report->SetNumberField(TEXT("temporal_sample_before_draw"), DiagnosticView->State->GetCurrentTemporalAASampleIndex());
        }
    }
    if (const IConsoleVariable* Quality = IConsoleManager::Get().FindConsoleVariable(TEXT("r.PostProcessAAQuality")))
    {
        Report->SetNumberField(TEXT("post_process_aa_quality"), Quality->GetInt());
    }
    const FIntPoint Size = Viewport->GetSizeXY();
    const int64 ExpectedPixels = static_cast<int64>(Size.X) * static_cast<int64>(Size.Y);
    Report->SetNumberField(TEXT("width"), Size.X);
    Report->SetNumberField(TEXT("height"), Size.Y);
    if (Size.X <= 0 || Size.Y <= 0 || Size.X > 16384 || Size.Y > 16384 || ExpectedPixels > 64LL * 1024LL * 1024LL)
    {
        return Fail(TEXT("active_viewport_size_empty_or_exceeds_capture_limit"));
    }
    const FString Directory = FPaths::GetPath(OutputFilename);
    if (!IFileManager::Get().DirectoryExists(*Directory) && !IFileManager::Get().MakeDirectory(*Directory, true))
    {
        return Fail(TEXT("capture_output_directory_create_failed"));
    }

    UE_LOG(LogTemp, Display, TEXT("RebirthViewportCapture phase=before_end_of_frame_updates filename=%s size=%dx%d"), *OutputFilename, Size.X, Size.Y);
    World->SendAllEndOfFrameUpdates();
    UE_LOG(LogTemp, Display, TEXT("RebirthViewportCapture phase=before_draw filename=%s"), *OutputFilename);
    Report->SetBoolField(TEXT("draw_requested"), true);
    // Direct draw does not depend on the background Slate window deciding to
    // present. ReadPixels below flushes the queued render work synchronously.
    Viewport->Draw(false);
    UE_LOG(LogTemp, Display, TEXT("RebirthViewportCapture phase=before_read_pixels filename=%s"), *OutputFilename);
    if (Viewport->GetSizeXY() != Size) { return Fail(TEXT("viewport_resized_during_capture")); }
    TArray<FColor> Pixels;
    const bool bRead = Viewport->ReadPixels(Pixels, FReadSurfaceDataFlags(RCM_UNorm), FIntRect(0, 0, Size.X, Size.Y));
    Report->SetBoolField(TEXT("read_succeeded"), bRead);
    if (DiagnosticView && DiagnosticView->State)
    {
        // ReadPixels has flushed render work before this diagnostic read.
        Report->SetNumberField(TEXT("temporal_sample_after_draw"), DiagnosticView->State->GetCurrentTemporalAASampleIndex());
    }
    Report->SetNumberField(TEXT("pixel_count"), Pixels.Num());
    if (!bRead || static_cast<int64>(Pixels.Num()) != ExpectedPixels)
    {
        return Fail(TEXT("viewport_read_pixels_failed_or_count_mismatch"));
    }
    // Viewport alpha is not a useful transparency channel for an editor image.
    for (FColor& Pixel : Pixels) { Pixel.A = 255; }
    UE_LOG(LogTemp, Display, TEXT("RebirthViewportCapture phase=before_png_compression filename=%s pixels=%d"), *OutputFilename, Pixels.Num());
    TArray<uint8> Compressed;
    // Engine's exported helper uses the editor thumbnail PNG compressor. The
    // Engine/UnrealEd modules already own their ImageWrapper dependency.
    FImageUtils::CompressImageArray(Size.X, Size.Y, Pixels, Compressed);
    const uint8 PngSignature[] = { 137, 80, 78, 71, 13, 10, 26, 10 };
    if (Compressed.Num() <= 8 || FMemory::Memcmp(Compressed.GetData(), PngSignature, 8) != 0)
    {
        return Fail(TEXT("viewport_png_compression_failed"));
    }
    Report->SetNumberField(TEXT("png_bytes"), Compressed.Num());
    const bool bSaved = FFileHelper::SaveArrayToFile(Compressed, *OutputFilename);
    if (!bSaved || IFileManager::Get().FileSize(*OutputFilename) != Compressed.Num())
    {
        return Fail(TEXT("viewport_png_file_write_failed_or_size_mismatch"));
    }
    Report->SetBoolField(TEXT("success"), true);
    Report->SetStringField(TEXT("reason"), TEXT("captured_active_level_editor_viewport"));
    UE_LOG(LogTemp, Display, TEXT("RebirthViewportCapture phase=saved filename=%s pixels=%d bytes=%d"), *OutputFilename, Pixels.Num(), Compressed.Num());
    return JsonString(Report);
}

UMaterialInstanceConstant* URebirthMaterialDiagnosticsLibrary::CreateStaticPermutation(UMaterial* Base, const TArray<FString>& StaticSwitchesOn, const FString& BlendMode)
{
    if (!IsValid(Base))
    {
        return nullptr;
    }
    UPackage* Transient = GetTransientPackage();
    UMaterialInstanceConstant* Instance = NewObject<UMaterialInstanceConstant>(Transient,
        MakeUniqueObjectName(Transient, UMaterialInstanceConstant::StaticClass(), FName(TEXT("RebirthPermutationTest"))), RF_Transient);
    Instance->SetParentEditorOnly(Base);
    FStaticParameterSet Static;
    for (const FString& Text : StaticSwitchesOn)
    {
        const FName Name(*Text);
        FGuid Guid;
        for (UMaterialExpression* Expression : Base->Expressions)
        {
            if (const UMaterialExpressionStaticSwitchParameter* Switch = Cast<UMaterialExpressionStaticSwitchParameter>(Expression))
            {
                if (Switch->ParameterName == Name)
                {
                    Guid = Switch->ExpressionGUID;
                    break;
                }
            }
        }
        Static.StaticSwitchParameters.Add(FStaticSwitchParameter(FMaterialParameterInfo(Name), true, true, Guid));
    }
    FMaterialInstanceBasePropertyOverrides Overrides = Instance->BasePropertyOverrides;
    if (!BlendMode.IsEmpty())
    {
        const int64 Value = StaticEnum<EBlendMode>()->GetValueByNameString(BlendMode);
        if (Value != INDEX_NONE && Value < BLEND_MAX)
        {
            Overrides.bOverride_BlendMode = true;
            Overrides.BlendMode = static_cast<EBlendMode>(Value);
        }
    }
    Instance->UpdateStaticPermutation(Static, Overrides, true);
    return Instance;
}

FString URebirthMaterialDiagnosticsLibrary::SetMaterialInstanceStaticParameters(UMaterialInstanceConstant* Instance, const TArray<FString>& SwitchNames,
    const TArray<bool>& SwitchValues, const TArray<FString>& MaskNames, const TArray<FString>& MaskValues, const FString& BlendMode, const FString& ShadingModel,
    int32 TwoSided, float OpacityMaskClipValue)
{
    TSharedRef<FJsonObject> Receipt = MakeShared<FJsonObject>();
    auto Finish = [&Receipt]()
    {
        FString Text;
        TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Text);
        FJsonSerializer::Serialize(Receipt, Writer);
        return Text;
    };
    if (!IsValid(Instance))
    {
        Receipt->SetStringField(TEXT("error"), TEXT("no instance"));
        return Finish();
    }
    if (Instance->Parent == nullptr)
    {
        Receipt->SetStringField(TEXT("error"), TEXT("the instance has no parent"));
        return Finish();
    }

    // the parent chain's static parameters (their expression guids)
    TMap<FName, FGuid> SwitchIds;
    TMap<FName, FGuid> MaskIds;
    {
        TArray<FMaterialParameterInfo> Infos;
        TArray<FGuid> Ids;
        Instance->Parent->GetAllStaticSwitchParameterInfo(Infos, Ids);
        for (int32 Index = 0; Index < Infos.Num(); ++Index)
        {
            SwitchIds.Add(Infos[Index].Name, Ids.IsValidIndex(Index) ? Ids[Index] : FGuid());
        }
        Infos.Reset();
        Ids.Reset();
        Instance->Parent->GetAllStaticComponentMaskParameterInfo(Infos, Ids);
        for (int32 Index = 0; Index < Infos.Num(); ++Index)
        {
            MaskIds.Add(Infos[Index].Name, Ids.IsValidIndex(Index) ? Ids[Index] : FGuid());
        }
    }

    FStaticParameterSet Static;
    TArray<TSharedPtr<FJsonValue>> Unknown;
    TArray<TSharedPtr<FJsonValue>> SetSwitches;
    for (int32 Index = 0; Index < SwitchNames.Num(); ++Index)
    {
        const FName Name(*SwitchNames[Index]);
        const bool bValue = SwitchValues.IsValidIndex(Index) ? SwitchValues[Index] : true;
        const FGuid* Id = SwitchIds.Find(Name);
        if (Id == nullptr)
        {
            Unknown.Add(MakeShared<FJsonValueString>(SwitchNames[Index]));
        }
        Static.StaticSwitchParameters.Add(FStaticSwitchParameter(FMaterialParameterInfo(Name), bValue, true, Id ? *Id : FGuid()));
        SetSwitches.Add(MakeShared<FJsonValueString>(FString::Printf(TEXT("%s=%s"), *SwitchNames[Index], bValue ? TEXT("true") : TEXT("false"))));
    }
    for (int32 Index = 0; Index < MaskNames.Num(); ++Index)
    {
        const FName Name(*MaskNames[Index]);
        const FString Letters = MaskValues.IsValidIndex(Index) ? MaskValues[Index].ToUpper() : FString();
        const FGuid* Id = MaskIds.Find(Name);
        if (Id == nullptr)
        {
            Unknown.Add(MakeShared<FJsonValueString>(MaskNames[Index]));
        }
        Static.StaticComponentMaskParameters.Add(FStaticComponentMaskParameter(FMaterialParameterInfo(Name), Letters.Contains(TEXT("R")),
            Letters.Contains(TEXT("G")), Letters.Contains(TEXT("B")), Letters.Contains(TEXT("A")), true, Id ? *Id : FGuid()));
    }

    FMaterialInstanceBasePropertyOverrides Overrides = Instance->BasePropertyOverrides;
    TArray<TSharedPtr<FJsonValue>> SetOverrides;
    if (!BlendMode.IsEmpty())
    {
        const int64 Value = StaticEnum<EBlendMode>()->GetValueByNameString(BlendMode);
        if (Value != INDEX_NONE && Value < BLEND_MAX)
        {
            Overrides.bOverride_BlendMode = true;
            Overrides.BlendMode = static_cast<EBlendMode>(Value);
            SetOverrides.Add(MakeShared<FJsonValueString>(TEXT("BlendMode=") + BlendMode));
        }
        else
        {
            Unknown.Add(MakeShared<FJsonValueString>(BlendMode));
        }
    }
    if (!ShadingModel.IsEmpty())
    {
        const int64 Value = StaticEnum<EMaterialShadingModel>()->GetValueByNameString(ShadingModel);
        if (Value != INDEX_NONE && Value < MSM_NUM)
        {
            Overrides.bOverride_ShadingModel = true;
            Overrides.ShadingModel = static_cast<EMaterialShadingModel>(Value);
            SetOverrides.Add(MakeShared<FJsonValueString>(TEXT("ShadingModel=") + ShadingModel));
        }
        else
        {
            Unknown.Add(MakeShared<FJsonValueString>(ShadingModel));
        }
    }
    if (TwoSided >= 0)
    {
        Overrides.bOverride_TwoSided = true;
        Overrides.TwoSided = TwoSided != 0;
        SetOverrides.Add(MakeShared<FJsonValueString>(FString::Printf(TEXT("TwoSided=%d"), TwoSided != 0 ? 1 : 0)));
    }
    if (OpacityMaskClipValue >= 0.0f)
    {
        Overrides.bOverride_OpacityMaskClipValue = true;
        Overrides.OpacityMaskClipValue = OpacityMaskClipValue;
        SetOverrides.Add(MakeShared<FJsonValueString>(FString::Printf(TEXT("OpacityMaskClipValue=%g"), OpacityMaskClipValue)));
    }

    Instance->Modify();
    Instance->UpdateStaticPermutation(Static, Overrides, true);
    Instance->MarkPackageDirty();

    Receipt->SetStringField(TEXT("instance"), Instance->GetPathName());
    Receipt->SetArrayField(TEXT("switches"), SetSwitches);
    Receipt->SetNumberField(TEXT("masks"), MaskNames.Num());
    Receipt->SetArrayField(TEXT("overrides"), SetOverrides);
    Receipt->SetArrayField(TEXT("unknown"), Unknown);
    Receipt->SetBoolField(TEXT("has_static_permutation"), Instance->bHasStaticPermutationResource);
    return Finish();
}

bool URebirthMaterialDiagnosticsLibrary::ConnectMaterialPropertyByName(UMaterialExpression* FromExpression, const FString& FromOutputName, const FString& PropertyName)
{
    if (!IsValid(FromExpression))
    {
        return false;
    }
    UMaterial* Material = Cast<UMaterial>(FromExpression->GetOuter());
    const UEnum* Enum = StaticEnum<EMaterialProperty>();
    const int64 Value = Enum != nullptr ? Enum->GetValueByNameString(PropertyName) : INDEX_NONE;
    if (Material == nullptr || Value == INDEX_NONE || Value < 0 || Value >= MP_MAX)
    {
        return false;
    }
    FExpressionInput* Input = Material->GetExpressionInputForProperty(static_cast<EMaterialProperty>(Value));
    if (Input == nullptr)
    {
        return false;
    }
    int32 OutputIndex = 0;
    if (!FromOutputName.IsEmpty())
    {
        OutputIndex = INDEX_NONE;
        const TArray<FExpressionOutput>& Outputs = FromExpression->GetOutputs();
        for (int32 Index = 0; Index < Outputs.Num(); ++Index)
        {
            if (Outputs[Index].OutputName.ToString() == FromOutputName)
            {
                OutputIndex = Index;
                break;
            }
        }
        if (OutputIndex == INDEX_NONE)
        {
            return false;
        }
    }
    Input->Connect(OutputIndex, FromExpression);
    Material->MarkPackageDirty();
    return true;
}

UMaterialExpressionComment* URebirthMaterialDiagnosticsLibrary::AddMaterialComment(UMaterial* Material, int32 X, int32 Y, int32 Width, int32 Height, const FString& Text)
{
    if (!IsValid(Material))
    {
        return nullptr;
    }
    UMaterialExpressionComment* Comment = NewObject<UMaterialExpressionComment>(Material, NAME_None, RF_Transactional);
    Comment->MaterialExpressionEditorX = X;
    Comment->MaterialExpressionEditorY = Y;
    Comment->SizeX = Width;
    Comment->SizeY = Height;
    Comment->Text = Text;
    Comment->Material = Material;
    Material->EditorComments.Add(Comment);
    Material->MarkPackageDirty();
    return Comment;
}

void URebirthMaterialDiagnosticsLibrary::ClearMaterialComments(UMaterial* Material)
{
    if (IsValid(Material))
    {
        Material->EditorComments.Empty();
        Material->MarkPackageDirty();
    }
}
