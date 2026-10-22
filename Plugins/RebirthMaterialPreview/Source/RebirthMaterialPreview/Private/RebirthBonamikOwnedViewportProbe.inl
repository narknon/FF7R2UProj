// Included inside RebirthPreview after the concrete viewport class. No UHT,
// normal-launch command or UObject mutation is introduced by this owned probe.
FString SRuntimePreviewViewport::RunOwnedBonamikProbeCommand(const TArray<FString>& Arguments)
{
    TSharedRef<FJsonObject> Report = MakeShared<FJsonObject>();
    Report->SetNumberField(TEXT("schema_version"), 1);
    Report->SetBoolField(TEXT("owned_marker"), true);
    const FString Command = Arguments.Num() ? Arguments[0].ToLower() : TEXT("snapshot");
    Report->SetStringField(TEXT("command"), Command);
    Report->SetStringField(TEXT("asset_path"), OwnedBonamikProbeAssetPath);
    bool bOK = PreviewClient.IsValid();
    FString Error;
    if (!bOK) Error = TEXT("preview_client_unavailable");
    else if (Command == TEXT("pause")) { if (PreviewClient->bPlaying) TogglePlayback(); }
    else if (Command == TEXT("play")) { if (!PreviewClient->bPlaying) TogglePlayback(); }
    else if (Command == TEXT("off")) { if (PreviewClient->IsBonamikEnabled()) ToggleBonamik(); }
    else if (Command == TEXT("on"))
    {
        if (!PreviewClient->IsBonamikReady()) { bOK=false; Error=TEXT("bonamik_session_unavailable"); }
        else if (!PreviewClient->IsBonamikEnabled()) ToggleBonamik();
    }
    else if (Command == TEXT("restart")) { Restart(); }
    else if (Command == TEXT("step"))
    {
        float Delta=0.0f;
        if (PreviewClient->bPlaying || !PreviewClient->IsBonamikReady() || !PreviewClient->IsBonamikEnabled())
        { bOK=false; Error=TEXT("manual_step_requires_paused_enabled_session"); }
        else if (Arguments.Num()!=2 || !LexTryParseString(Delta,*Arguments[1]) || !FMath::IsFinite(Delta) || Delta<0.0f || Delta>10.0f)
        { bOK=false; Error=TEXT("manual_step_delta_invalid"); }
        else
        {
            // Exercises the actual viewport tick clamp, including long background
            // frames; pause is retained after this one explicit step.
            PreviewClient->bPlaying=true;
            PreviewClient->Tick(Delta);
            PreviewClient->bPlaying=false;
            Report->SetNumberField(TEXT("requested_step_seconds"), Delta);
            Invalidate();
        }
    }
    else if (Command != TEXT("snapshot") && Command != TEXT("capture"))
    { bOK=false; Error=TEXT("unknown_probe_command"); }

    UPoseableMeshComponent* Poseable=Cast<UPoseableMeshComponent>(Component);
    const FRebirthBonamikPreviewSession* Session=PreviewClient.IsValid() ? PreviewClient->GetBonamikSession() : nullptr;
    Report->SetBoolField(TEXT("ready"), Session && Session->IsReady());
    Report->SetBoolField(TEXT("enabled"), PreviewClient.IsValid() && PreviewClient->IsBonamikEnabled());
    Report->SetBoolField(TEXT("playing"), PreviewClient.IsValid() && PreviewClient->bPlaying);
    Report->SetStringField(TEXT("status"), GetStatus().ToString());
    Report->SetBoolField(TEXT("component_transient"), Poseable && Poseable->HasAnyFlags(RF_Transient));
    if (PreviewClient.IsValid())
    {
        Report->SetNumberField(TEXT("applied_frames"), PreviewClient->BonamikAppliedFrames);
        Report->SetNumberField(TEXT("applied_seconds"), PreviewClient->BonamikAppliedSeconds);
        Report->SetNumberField(TEXT("dropped_tick_count"), PreviewClient->BonamikDroppedTickCount);
        Report->SetNumberField(TEXT("dropped_seconds"), PreviewClient->BonamikDroppedSeconds);
        Report->SetStringField(TEXT("camera_location"), PreviewClient->GetViewLocation().ToString());
        Report->SetStringField(TEXT("camera_rotation"), PreviewClient->GetViewRotation().ToString());
    }
    if (Session)
    {
        Report->SetNumberField(TEXT("body_count"), Session->GetBodyCount());
        Report->SetNumberField(TEXT("attachment_count"), Session->GetAttachmentCount());
        Report->SetNumberField(TEXT("shape_count"), Session->GetAuthoredShapeCount());
        Report->SetNumberField(TEXT("pair_count"), Session->GetAuthoredCollisionPairCount());
    }
    if (Poseable && Poseable->SkeletalMesh)
    {
        const TArray<FTransform>& Local=Poseable->BoneSpaceTransforms;
        const FReferenceSkeleton& Ref=Poseable->SkeletalMesh->RefSkeleton;
        const TArray<FTransform> Base=Session ? Session->GetReferenceComponentPose() : TArray<FTransform>();
        TArray<FTransform> Current=Local;
        bool bFinite=Local.Num()==Ref.GetNum();
        float MaxDisplacement=0.0f, MaxRotation=0.0f;
        FString Canonical;
        for (int32 Index=0; Index<Local.Num(); ++Index)
        {
            const FTransform& T=Local[Index];
            bFinite &= !T.ContainsNaN() && T.GetRotation().IsNormalized();
            const FQuat Q=T.GetRotation(); const FVector P=T.GetTranslation(), S=T.GetScale3D();
            Canonical+=FString::Printf(TEXT("%.9g,%.9g,%.9g,%.9g|%.9g,%.9g,%.9g|%.9g,%.9g,%.9g\n"),
                Q.X,Q.Y,Q.Z,Q.W,P.X,P.Y,P.Z,S.X,S.Y,S.Z);
            if (Ref.IsValidIndex(Index))
            {
                const int32 Parent=Ref.GetParentIndex(Index);
                if (Parent!=INDEX_NONE && Current.IsValidIndex(Parent)) Current[Index]=Current[Index]*Current[Parent];
            }
            if (Base.IsValidIndex(Index))
            {
                MaxDisplacement=FMath::Max(MaxDisplacement,FVector::Dist(Current[Index].GetTranslation(),Base[Index].GetTranslation()));
                MaxRotation=FMath::Max(MaxRotation,FMath::RadiansToDegrees(Current[Index].GetRotation().AngularDistance(Base[Index].GetRotation())));
            }
        }
        FTCHARToUTF8 UTF8(*Canonical);
        FSHAHash Digest; FSHA1::HashBuffer(UTF8.Get(),UTF8.Length(),Digest.Hash);
        Report->SetStringField(TEXT("pose_sha1"), Digest.ToString());
        Report->SetNumberField(TEXT("bone_count"), Local.Num());
        Report->SetBoolField(TEXT("finite_normalized_pose"), bFinite);
        Report->SetNumberField(TEXT("max_component_displacement_cm"), MaxDisplacement);
        Report->SetNumberField(TEXT("max_component_rotation_degrees"), MaxRotation);
        TArray<TSharedPtr<FJsonValue>> Materials;
        for (int32 Index=0; Index<Poseable->GetNumMaterials(); ++Index)
            Materials.Add(MakeShared<FJsonValueString>(GetPathNameSafe(Poseable->GetMaterial(Index))));
        Report->SetArrayField(TEXT("preview_materials"), Materials);
    }

    if (bOK && Command==TEXT("capture"))
    {
        const FString Label=Arguments.Num()==2 ? Arguments[1] : FString();
        bool bSafeLabel=Label.Len()>0 && Label.Len()<=48;
        for (TCHAR C : Label) bSafeLabel &= FChar::IsAlnum(C) || C==TEXT('_') || C==TEXT('-');
        FViewport* Viewport=PreviewClient->Viewport;
        if (!bSafeLabel || !Viewport) { bOK=false; Error=TEXT("capture_label_or_viewport_invalid"); }
        else
        {
            const FIntPoint Size=Viewport->GetSizeXY();
            const int64 Expected=static_cast<int64>(Size.X)*Size.Y;
            Report->SetNumberField(TEXT("width"),Size.X); Report->SetNumberField(TEXT("height"),Size.Y);
            if (Size.X<=0 || Size.Y<=0 || Size.X>8192 || Size.Y>8192 || Expected>16LL*1024LL*1024LL)
            { bOK=false; Error=TEXT("capture_size_invalid"); }
            else
            {
                const FString Directory=FPaths::Combine(FPaths::ProjectSavedDir(),TEXT("BonamikOwnedProbe"));
                const FString Filename=FPaths::Combine(Directory,Label+TEXT(".png"));
                IFileManager::Get().MakeDirectory(*Directory,true);
                Scene->GetWorld()->SendAllEndOfFrameUpdates();
                Viewport->Draw(false);
                FlushRenderingCommands();
                TArray<FColor> Pixels;
                const bool bRead=Viewport->GetSizeXY()==Size && Viewport->ReadPixels(Pixels,FReadSurfaceDataFlags(RCM_UNorm),FIntRect(0,0,Size.X,Size.Y));
                Report->SetBoolField(TEXT("read_succeeded"),bRead);
                if (!bRead || static_cast<int64>(Pixels.Num())!=Expected) { bOK=false; Error=TEXT("capture_pixels_invalid"); }
                else
                {
                    for (FColor& Pixel : Pixels) Pixel.A=255;
                    TArray<uint8> PNG; FImageUtils::CompressImageArray(Size.X,Size.Y,Pixels,PNG);
                    const uint8 Signature[]={137,80,78,71,13,10,26,10};
                    if (PNG.Num()<=8 || FMemory::Memcmp(PNG.GetData(),Signature,8)!=0 || !FFileHelper::SaveArrayToFile(PNG,*Filename))
                    { bOK=false; Error=TEXT("capture_png_write_failed"); }
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
    Report->SetBoolField(TEXT("ok"),bOK);
    if (!Error.IsEmpty()) Report->SetStringField(TEXT("error"),Error);
    FString JSON; FJsonSerializer::Serialize(Report,TJsonWriterFactory<>::Create(&JSON));
    return JSON;
}

static void RunBonamikOwnedProbe(const TArray<FString>& Arguments)
{
    if (!IsInGameThread() || IsGarbageCollecting() || IsEngineExitRequested() ||
        !FParse::Param(FCommandLine::Get(),TEXT("RebirthBonamikOwnedPreviewProbe"))) return;
    FString JSON=TEXT("{\"schema_version\":1,\"ok\":false,\"error\":\"owned_preview_viewport_unavailable\"}");
    if (TSharedPtr<SRuntimePreviewViewport> Viewport=OwnedBonamikProbeViewport.Pin())
        JSON=Viewport->RunOwnedBonamikProbeCommand(Arguments);
    const FString Directory=FPaths::Combine(FPaths::ProjectSavedDir(),TEXT("BonamikOwnedProbe"));
    const FString Filename=FPaths::Combine(Directory,TEXT("LatestState.json"));
    IFileManager::Get().MakeDirectory(*Directory,true);
    const bool bSaved=FFileHelper::SaveStringToFile(JSON,*Filename,FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
    UE_LOG(LogRebirthPreview,Display,TEXT("BonamikOwnedProbe result_written=%d filename=%s json=%s"),bSaved?1:0,*Filename,*JSON);
}
