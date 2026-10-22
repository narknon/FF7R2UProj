// Included after the viewport type. The diagnostic is registered only in a marked owned editor.
FString SRuntimePreviewViewport::RunOwnedAnimationProbeCommand(const TArray<FString>& Arguments)
{
    auto Report=MakeShared<FJsonObject>();
    Report->SetNumberField(TEXT("schema_version"),2);
    Report->SetBoolField(TEXT("owned_marker"),true);
    Report->SetNumberField(TEXT("process_id"),FPlatformProcess::GetCurrentProcessId());
    Report->SetStringField(TEXT("asset_path"),GetPathNameSafe(AnimationAsset.Get()));
    const FString Command=Arguments.Num()?Arguments[0].ToLower():TEXT("snapshot");
    Report->SetStringField(TEXT("command"),Command);
    bool bOK=PreviewClient.IsValid() && AnimationAsset.IsValid();
    FString Error;
    if (!bOK) { Error=TEXT("animation_preview_unavailable"); }
    else if (Command==TEXT("receiver"))
    {
        USkeletalMesh* Mesh=Arguments.Num()==2?FindObject<USkeletalMesh>(nullptr,*Arguments[1]):nullptr;
        if (!IsValid(Mesh)) { bOK=false;Error=TEXT("receiver_must_be_exact_loaded_skeletal_mesh"); }
        else { SetAnimationReceiverAsset(FAssetData(Mesh)); }
    }
    else if (Command==TEXT("focus"))
    {
        if (!PreviewClient->IsAnimationReady()) { bOK=false;Error=TEXT("focus_requires_ready_animation"); }
        else { Focus(); }
    }
    else if (Command==TEXT("focusface"))
    {
        if (!FocusAnimationFace()) { bOK=false;Error=TEXT("face_focus_requires_ready_original_head_bone"); }
    }
    else if (Command==TEXT("alignment"))
    {
        const FString Value=Arguments.Num()==2?Arguments[1].ToLower():FString();
        if (!PreviewClient->IsAnimationReady() || (Value!=TEXT("on") && Value!=TEXT("off")))
        { bOK=false;Error=TEXT("alignment_requires_ready_animation_and_on_or_off"); }
        else if (!SetAnimationRootAlignmentEnabled(Value==TEXT("on")))
        { bOK=false;Error=TEXT("preview_root_alignment_transform_validation_failed"); }
    }
    else if (Command==TEXT("pause")) { if (PreviewClient->bPlaying) { TogglePlayback(); } }
    else if (Command==TEXT("play"))
    {
        if (!PreviewClient->IsAnimationReady()) { bOK=false;Error=TEXT("animation_not_ready"); }
        else if (!PreviewClient->bPlaying) { TogglePlayback(); }
    }
    else if (Command==TEXT("restart"))
    {
        if (!PreviewClient->IsAnimationReady()) { bOK=false;Error=TEXT("animation_not_ready"); }
        else { Restart(); }
    }
    else if (Command==TEXT("seek"))
    {
        float Seconds=0;
        if (Arguments.Num()!=2 || !LexTryParseString(Seconds,*Arguments[1]) || !FMath::IsFinite(Seconds) || Seconds<0 ||
            Seconds>AnimationAsset->SequenceLength || !PreviewClient->IsAnimationReady())
        { bOK=false;Error=TEXT("seek_time_or_animation_invalid"); }
        else { SetAnimationNormalizedPosition(Seconds/AnimationAsset->SequenceLength); }
    }
    else if (Command==TEXT("step"))
    {
        float Delta=0;
        if (PreviewClient->bPlaying || !PreviewClient->IsAnimationReady())
        { bOK=false;Error=TEXT("manual_step_requires_paused_ready_animation"); }
        else if (Arguments.Num()!=2 || !LexTryParseString(Delta,*Arguments[1]) || !FMath::IsFinite(Delta) || Delta<0 || Delta>10.0f)
        { bOK=false;Error=TEXT("step_delta_invalid"); }
        else
        {
            PreviewClient->bPlaying=true;PreviewClient->Tick(Delta);PreviewClient->bPlaying=false;
            bAnimationWantsPlay=false;Invalidate();Report->SetNumberField(TEXT("requested_step_seconds"),Delta);
        }
    }
    else if (Command!=TEXT("snapshot") && Command!=TEXT("capture"))
    { bOK=false;Error=TEXT("unknown_animation_probe_command"); }

    USkeletalMeshComponent* Mesh=Cast<USkeletalMeshComponent>(Component);
    UAnimSingleNodeInstance* Instance=Mesh?Mesh->GetSingleNodeInstance():nullptr;
    Report->SetStringField(TEXT("receiver_path"),GetPathNameSafe(AnimationReceivingMesh.Get()));
    Report->SetStringField(TEXT("receiver_skeleton"),GetPathNameSafe(AnimationReceivingMesh.IsValid()?AnimationReceivingMesh->Skeleton:nullptr));
    Report->SetBoolField(TEXT("ready"),PreviewClient.IsValid() && PreviewClient->IsAnimationReady());
    Report->SetBoolField(TEXT("playing"),PreviewClient.IsValid() && PreviewClient->bPlaying);
    Report->SetBoolField(TEXT("bonamik_enabled"),PreviewClient.IsValid() && PreviewClient->IsBonamikEnabled());
    Report->SetBoolField(TEXT("bonamik_ready"),PreviewClient.IsValid() && PreviewClient->IsBonamikReady());
    Report->SetBoolField(TEXT("original_animation_retained"),Instance && Instance->GetAnimationAsset()==AnimationAsset.Get());
    Report->SetBoolField(TEXT("genuine_receiver_skeleton_retained"),Mesh && Instance && Mesh->SkeletalMesh==AnimationReceivingMesh.Get() &&
        AnimationReceivingMesh.IsValid() && AnimationReceivingMesh->Skeleton==Instance->GetRequiredBones().GetSkeletonAsset());
    Report->SetBoolField(TEXT("component_transient"),Mesh && Mesh->HasAnyFlags(RF_Transient));
    Report->SetBoolField(TEXT("sole_manual_animation_tick"),Mesh && !Mesh->IsComponentTickEnabled());
    Report->SetBoolField(TEXT("curves_enabled"),false);
    Report->SetStringField(TEXT("status"),GetStatus().ToString());
    if (PreviewClient.IsValid())
    {
        Report->SetBoolField(TEXT("native_pose_validation_passed"),PreviewClient->bAnimationPoseValidated);
        Report->SetBoolField(TEXT("refusal_counter_delta_detected"),PreviewClient->bAnimationRefusalDelta);
        Report->SetBoolField(TEXT("raw_fallback_selected"),PreviewClient->bAnimationRawFallbackSelected);
        Report->SetNumberField(TEXT("pose_guard_checks"),PreviewClient->AnimationGuardChecks);
        Report->SetNumberField(TEXT("valid_curve_destinations"),PreviewClient->AnimationValidCurveCount);
        Report->SetNumberField(TEXT("motion_validation_samples"),PreviewClient->AnimationValidationSamples);
        Report->SetNumberField(TEXT("motion_validation_max_cm"),PreviewClient->AnimationValidationMotionCm);
        Report->SetNumberField(TEXT("motion_validation_max_rotation_radians"),PreviewClient->AnimationValidationRotationRadians);
        Report->SetBoolField(TEXT("motion_validation_pose_digest_changed"),PreviewClient->bAnimationValidationDigestChanged);
        Report->SetNumberField(TEXT("preserved_source_compressed_curve_count"),AnimationAsset->CompressedData.CompressedCurveNames.Num());
        Report->SetNumberField(TEXT("native_viewport_tick_calls"),PreviewClient->NativeViewportTickCalls);
        Report->SetBoolField(TEXT("native_viewport_visible"),PreviewClient->IsVisible());
        Report->SetBoolField(TEXT("native_viewport_realtime"),PreviewClient->IsRealtime());
        Report->SetBoolField(TEXT("native_intra_frame_debugging"),GIntraFrameDebuggingGameThread);
        Report->SetBoolField(TEXT("native_viewport_registered"),GEditor && GEditor->GetAllViewportClients().Contains(PreviewClient.Get()));
        Report->SetNumberField(TEXT("native_time"),PreviewClient->GetAnimationTime());
        Report->SetNumberField(TEXT("applied_frames"),PreviewClient->AnimationAppliedFrames);
        Report->SetNumberField(TEXT("applied_seconds"),PreviewClient->AnimationAppliedSeconds);
        Report->SetNumberField(TEXT("dropped_seconds"),PreviewClient->AnimationDroppedSeconds);
        Report->SetStringField(TEXT("camera_location"),PreviewClient->GetViewLocation().ToString());
        Report->SetStringField(TEXT("camera_rotation"),PreviewClient->GetViewRotation().ToString());
        Report->SetBoolField(TEXT("root_alignment_enabled"),bAnimationRootAlignmentEnabled);
        Report->SetBoolField(TEXT("root_alignment_active"),PreviewClient->bAnimationRootAlignmentActive);
        Report->SetBoolField(TEXT("root_alignment_verified"),PreviewClient->bAnimationRootAlignmentVerified);
        Report->SetStringField(TEXT("root_alignment_initial_native_root_rotation"),PreviewClient->AnimationInitialRootRotation.ToString());
        Report->SetStringField(TEXT("root_alignment_reference_root_rotation"),PreviewClient->AnimationReferenceRootRotation.ToString());
        Report->SetStringField(TEXT("root_alignment_component_rotation"),PreviewClient->AnimationAlignedComponentTransform.GetRotation().ToString());
        Report->SetNumberField(TEXT("root_alignment_world_initial_root_error_radians"),PreviewClient->AnimationWorldInitialRootErrorRadians);
        Report->SetNumberField(TEXT("root_alignment_reference_rotation_error_radians_current"),PreviewClient->GetAnimationCurrentRootReferenceError());
        Report->SetStringField(TEXT("original_component_transform"),PreviewClient->AnimationOriginalComponentTransform.ToString());
        Report->SetStringField(TEXT("aligned_component_transform"),PreviewClient->AnimationAlignedComponentTransform.ToString());
        Report->SetBoolField(TEXT("studio_lighting_enabled"),PreviewClient->IsCharacterStudioLightingEnabled());
        Report->SetNumberField(TEXT("studio_directional_light_count"),PreviewClient->IsCharacterStudioLightingEnabled()?3:0);
        Report->SetBoolField(TEXT("studio_manual_exposure"),PreviewClient->IsCharacterStudioLightingEnabled());
        Report->SetNumberField(TEXT("animation_bounds_scale"),Mesh?Mesh->BoundsScale:0.0f);
        Report->SetBoolField(TEXT("animation_bounds_contains_required_world_box"),PreviewClient->AnimationBoundsContainRequiredWorldBox());
        Report->SetNumberField(TEXT("animation_bounds_scale_updates"),PreviewClient->AnimationBoundsScaleUpdates);
        Report->SetStringField(TEXT("animation_focus_mode"),OwnedAnimationFocusMode);
    }
    if (Mesh && Mesh->SkeletalMesh)
    {
        const FTransform ComponentWorld=Mesh->GetComponentTransform();
        const FBoxSphereBounds Imported=Mesh->SkeletalMesh->GetBounds();
        const FBoxSphereBounds Calculated=Mesh->CalcBounds(ComponentWorld);
        Report->SetStringField(TEXT("component_transform"),ComponentWorld.ToString());
        Report->SetStringField(TEXT("imported_bounds_origin"),Imported.Origin.ToString());
        Report->SetStringField(TEXT("imported_bounds_extent"),Imported.BoxExtent.ToString());
        Report->SetStringField(TEXT("component_bounds_origin"),Mesh->Bounds.Origin.ToString());
        Report->SetStringField(TEXT("component_bounds_extent"),Mesh->Bounds.BoxExtent.ToString());
        Report->SetStringField(TEXT("calculated_bounds_origin"),Calculated.Origin.ToString());
        Report->SetStringField(TEXT("calculated_bounds_extent"),Calculated.BoxExtent.ToString());
        const auto& ComponentPose=Mesh->GetComponentSpaceTransforms();
        const auto& LocalPose=Mesh->GetBoneSpaceTransforms();
        if (LocalPose.Num()>0 && ComponentPose.Num()>0)
        {
            Report->SetStringField(TEXT("root_bone_name"),Mesh->SkeletalMesh->RefSkeleton.GetBoneName(0).ToString());
            Report->SetStringField(TEXT("root_local_transform"),LocalPose[0].ToString());
            Report->SetStringField(TEXT("root_component_transform"),ComponentPose[0].ToString());
            Report->SetStringField(TEXT("root_reference_transform"),Mesh->SkeletalMesh->RefSkeleton.GetRefBonePose()[0].ToString());
        }
        FBox FrameBounds(ForceInit),BoneBounds(ForceInit);int32 RequiredCount=0;
        const bool bFraming=PreviewClient->GetAnimationFramingBounds(FrameBounds,BoneBounds,RequiredCount);
        Report->SetBoolField(TEXT("evaluated_pose_framing_bounds_valid"),bFraming);
        Report->SetBoolField(TEXT("focused_evaluated_pose"),bAnimationFocusedEvaluatedPose);
        Report->SetStringField(TEXT("focus_camera_before"),AnimationFocusBefore);
        Report->SetStringField(TEXT("focus_camera_after"),AnimationFocusAfter);
        Report->SetNumberField(TEXT("framing_required_bone_count"),RequiredCount);
        Report->SetNumberField(TEXT("horizontal_fov_degrees"),PreviewClient->ViewFOV);
        if (bFraming)
        {
            Report->SetStringField(TEXT("required_bone_world_bounds_min"),BoneBounds.Min.ToString());
            Report->SetStringField(TEXT("required_bone_world_bounds_max"),BoneBounds.Max.ToString());
            Report->SetStringField(TEXT("framing_bounds_min"),FrameBounds.Min.ToString());
            Report->SetStringField(TEXT("framing_bounds_max"),FrameBounds.Max.ToString());
        }
        const auto Local=Mesh->GetBoneSpaceTransforms();
        bool bFinite=Local.Num()==Mesh->SkeletalMesh->RefSkeleton.GetNum();
        FString Canonical;
        for (const FTransform& T:Local)
        {
            bFinite &= T.IsValid() && T.IsRotationNormalized();
            const FQuat Q=T.GetRotation();const FVector P=T.GetTranslation(),S=T.GetScale3D();
            Canonical+=FString::Printf(TEXT("%.9g,%.9g,%.9g,%.9g|%.9g,%.9g,%.9g|%.9g,%.9g,%.9g\n"),
                Q.X,Q.Y,Q.Z,Q.W,P.X,P.Y,P.Z,S.X,S.Y,S.Z);
        }
        FTCHARToUTF8 UTF8(*Canonical);FSHAHash Hash;FSHA1::HashBuffer(UTF8.Get(),UTF8.Length(),Hash.Hash);
        Report->SetStringField(TEXT("pose_sha1"),Hash.ToString());
        TArray<int32> AllComponentBones;
        for (int32 Bone=0;Bone<ComponentPose.Num();++Bone) { AllComponentBones.Add(Bone); }
        Report->SetStringField(TEXT("component_pose_sha1"),PreviewClient->AnimationRequiredPoseDigest(ComponentPose,AllComponentBones));
        Report->SetNumberField(TEXT("bone_count"),Local.Num());
        Report->SetBoolField(TEXT("finite_normalized_pose"),bFinite);
        TArray<TSharedPtr<FJsonValue>> Materials;
        for (int32 Index=0;Index<Mesh->GetNumMaterials();++Index) { Materials.Add(MakeShared<FJsonValueString>(GetPathNameSafe(Mesh->GetMaterial(Index)))); }
        Report->SetArrayField(TEXT("preview_materials"),Materials);
    }
    if (bOK && Command==TEXT("capture"))
    {
        const FString Label=Arguments.Num()==2?Arguments[1]:FString();
        bool bSafeLabel=Label.Len()>0 && Label.Len()<=48;
        for (TCHAR C:Label) { bSafeLabel &= FChar::IsAlnum(C) || C==TEXT('_') || C==TEXT('-'); }
        FViewport* Viewport=PreviewClient->Viewport;
        if (!bSafeLabel || !Viewport) { bOK=false;Error=TEXT("capture_label_or_viewport_invalid"); }
        else
        {
            const FIntPoint Size=Viewport->GetSizeXY();const int64 Count=int64(Size.X)*Size.Y;
            Report->SetNumberField(TEXT("width"),Size.X);Report->SetNumberField(TEXT("height"),Size.Y);
            if (Size.X<=0 || Size.Y<=0 || Size.X>8192 || Size.Y>8192 || Count>16LL*1024LL*1024LL)
            { bOK=false;Error=TEXT("capture_size_invalid"); }
            else
            {
                const FString Directory=FPaths::ProjectSavedDir()/TEXT("AnimationOwnedProbe");
                const FString Filename=Directory/(Label+TEXT(".png"));
                IFileManager::Get().MakeDirectory(*Directory,true);
                Scene->GetWorld()->SendAllEndOfFrameUpdates();Viewport->Draw(false);FlushRenderingCommands();
                TArray<FColor> Pixels;
                const bool bRead=Viewport->GetSizeXY()==Size && Viewport->ReadPixels(Pixels,FReadSurfaceDataFlags(RCM_UNorm),FIntRect(0,0,Size.X,Size.Y));
                Report->SetBoolField(TEXT("read_succeeded"),bRead);
                if (!bRead || int64(Pixels.Num())!=Count) { bOK=false;Error=TEXT("capture_pixels_invalid"); }
                else
                {
                    for (FColor& Pixel:Pixels) { Pixel.A=255; }
                    TArray<uint8> PNG;FImageUtils::CompressImageArray(Size.X,Size.Y,Pixels,PNG);
                    const uint8 Signature[]={137,80,78,71,13,10,26,10};
                    if (PNG.Num()<=8 || FMemory::Memcmp(PNG.GetData(),Signature,8)!=0 || !FFileHelper::SaveArrayToFile(PNG,*Filename))
                    { bOK=false;Error=TEXT("capture_png_write_failed"); }
                    else
                    {
                        Report->SetStringField(TEXT("capture_path"),FPaths::ConvertRelativePathToFull(Filename));
                        Report->SetNumberField(TEXT("png_bytes"),PNG.Num());
                        Report->SetBoolField(TEXT("captured_custom_preview_viewport"),true);
                    }
                }
            }
        }
    }
    Report->SetBoolField(TEXT("ok"),bOK);if (!Error.IsEmpty()) { Report->SetStringField(TEXT("error"),Error); }
    FString JSON;FJsonSerializer::Serialize(Report,TJsonWriterFactory<>::Create(&JSON));return JSON;
}

static void RunAnimationOwnedProbe(const TArray<FString>& Arguments)
{
    if (!IsInGameThread() || IsGarbageCollecting() || IsEngineExitRequested() || GIsPlayInEditorWorld ||
        !FParse::Param(FCommandLine::Get(),TEXT("RebirthAnimationOwnedPreviewProbe"))) { return; }
    FString JSON=FString::Printf(TEXT("{\"schema_version\":1,\"ok\":false,\"process_id\":%u,\"error\":\"owned_animation_viewport_unavailable\"}"),FPlatformProcess::GetCurrentProcessId());
    if (TSharedPtr<SRuntimePreviewViewport> Viewport=OwnedAnimationProbeViewport.Pin()) { JSON=Viewport->RunOwnedAnimationProbeCommand(Arguments); }
    const FString Directory=FPaths::ProjectSavedDir()/TEXT("AnimationOwnedProbe");
    IFileManager::Get().MakeDirectory(*Directory,true);
    const FString Filename=Directory/TEXT("LatestState.json");
    const bool bSaved=FFileHelper::SaveStringToFile(JSON,*Filename,FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
    UE_LOG(LogRebirthPreview,Display,TEXT("AnimationOwnedProbe result_written=%d filename=%s json=%s"),bSaved?1:0,*Filename,*JSON);
}
