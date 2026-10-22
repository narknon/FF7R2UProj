// Test-only access to the real custom viewport. No original assets are modified.
FString SRuntimePreviewViewport::RunOwnedMaterialProbeCommand(const TArray<FString>& Arguments)
{
    static uint64 Serial = 0;
    TSharedRef<FJsonObject> Report = MakeShared<FJsonObject>();
    Report->SetNumberField(TEXT("schema_version"), 1);
    Report->SetNumberField(TEXT("process_id"), FPlatformProcess::GetCurrentProcessId());
    Report->SetNumberField(TEXT("serial"), ++Serial);
    Report->SetStringField(TEXT("original_path"), OwnedMaterialProbeAssetPath);
    Report->SetStringField(TEXT("status"), GetStatus().ToString());
    Report->SetBoolField(TEXT("pending"), bMaterialShaderRetryPending || bSkeletalShaderRetryPending);
    const bool bReady = Component && Component->IsRegistered() && PreviewClient.IsValid();
    Report->SetBoolField(TEXT("ready"), bReady);
    Report->SetNumberField(TEXT("native_viewport_ticks"), PreviewClient.IsValid() ? PreviewClient->NativeViewportTickCalls : 0);
    TArray<TSharedPtr<FJsonValue>> Materials;
    TArray<TSharedPtr<FJsonValue>> Snapshots;
    if (Component)
    {
        for (int32 Index=0; Index<Component->GetNumMaterials(); ++Index)
        {
            UMaterialInterface* Material=Component->GetMaterial(Index);
            Materials.Add(MakeShared<FJsonValueString>(GetPathNameSafe(Material)));
            if (Index<64 && Material)
            {
                TSharedPtr<FJsonObject> Snapshot;
                const FString JSON=RebirthMaterialFamilySnapshot::Inspect(Material);
                if (FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JSON),Snapshot) && Snapshot.IsValid())
                { Snapshots.Add(MakeShared<FJsonValueObject>(Snapshot)); }
            }
        }
    }
    Report->SetArrayField(TEXT("rendered_materials"), Materials);
    Report->SetArrayField(TEXT("rendered_snapshots"), Snapshots);
    const FString Command = Arguments.Num() ? Arguments[0] : FString();
    bool bOK = (Command == TEXT("snapshot") && Arguments.Num()==1) ||
        (Command == TEXT("capture") && Arguments.Num()==2);
    FString Error;
    if (!bOK) { Error = TEXT("invalid_command"); }
    if (bOK && Command==TEXT("capture"))
    {
        const FString Label=Arguments[1];
        bool bSafe=Label.Len()>0 && Label.Len()<=80;
        for (TCHAR C:Label) { bSafe &= FChar::IsAlnum(C) || C==TEXT('_') || C==TEXT('-'); }
        FViewport* Viewport=PreviewClient.IsValid() ? PreviewClient->Viewport : nullptr;
        if (!bReady || !bSafe || !Viewport) { bOK=false; Error=TEXT("capture_not_ready"); }
        else
        {
            const FIntPoint Size=Viewport->GetSizeXY(); const int64 Count=int64(Size.X)*Size.Y;
            if (Size.X<=0 || Size.Y<=0 || Size.X>8192 || Size.Y>8192 || Count>16LL*1024LL*1024LL)
            { bOK=false; Error=TEXT("capture_size_invalid"); }
            else
            {
                const FString Directory=FPaths::ProjectSavedDir()/TEXT("MaterialOwnedProbe");
                const FString Filename=Directory/(Label+TEXT(".png"));
                IFileManager::Get().MakeDirectory(*Directory,true);
                if (IFileManager::Get().FileExists(*Filename)) { bOK=false; Error=TEXT("capture_already_exists"); }
                else
                {
                    Scene->GetWorld()->SendAllEndOfFrameUpdates(); Viewport->Draw(false); FlushRenderingCommands();
                    TArray<FColor> Pixels;
                    const bool bRead=Viewport->GetSizeXY()==Size && Viewport->ReadPixels(Pixels,FReadSurfaceDataFlags(RCM_UNorm),FIntRect(0,0,Size.X,Size.Y));
                    if (!bRead || int64(Pixels.Num())!=Count) { bOK=false; Error=TEXT("capture_pixels_invalid"); }
                    else
                    {
                        for (FColor& Pixel:Pixels) { Pixel.A=255; }
                        TArray<uint8> PNG; FImageUtils::CompressImageArray(Size.X,Size.Y,Pixels,PNG);
                        const uint8 Signature[]={137,80,78,71,13,10,26,10};
                        if (PNG.Num()<=8 || FMemory::Memcmp(PNG.GetData(),Signature,8)!=0 || !FFileHelper::SaveArrayToFile(PNG,*Filename))
                        { bOK=false; Error=TEXT("capture_png_write_failed"); }
                        else
                        {
                            Report->SetStringField(TEXT("capture_path"),FPaths::ConvertRelativePathToFull(Filename));
                            Report->SetNumberField(TEXT("width"),Size.X); Report->SetNumberField(TEXT("height"),Size.Y);
                            Report->SetBoolField(TEXT("captured_actual_preview_viewport"),true);
                        }
                    }
                }
            }
        }
    }
    Report->SetBoolField(TEXT("ok"),bOK);
    if (!Error.IsEmpty()) { Report->SetStringField(TEXT("error"),Error); }
    FString JSON; FJsonSerializer::Serialize(Report,TJsonWriterFactory<>::Create(&JSON)); return JSON;
}

static void RunMaterialOwnedProbe(const TArray<FString>& Arguments)
{
    if (!IsInGameThread() || IsGarbageCollecting() || IsEngineExitRequested() || GIsPlayInEditorWorld ||
        !FParse::Param(FCommandLine::Get(),TEXT("RebirthMaterialOwnedProbe"))) { return; }
    FString JSON=FString::Printf(TEXT("{\"schema_version\":1,\"ok\":false,\"process_id\":%u,\"error\":\"owned_viewport_unavailable\"}"),FPlatformProcess::GetCurrentProcessId());
    if (TSharedPtr<SRuntimePreviewViewport> Viewport=OwnedMaterialProbeViewport.Pin()) { JSON=Viewport->RunOwnedMaterialProbeCommand(Arguments); }
    const FString Directory=FPaths::ProjectSavedDir()/TEXT("MaterialOwnedProbe");
    IFileManager::Get().MakeDirectory(*Directory,true);
    FFileHelper::SaveStringToFile(JSON,*(Directory/TEXT("LatestViewport.json")),FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
}
