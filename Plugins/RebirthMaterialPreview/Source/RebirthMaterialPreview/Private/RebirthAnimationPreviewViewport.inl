// Included in SRuntimePreviewViewport's public section.
    bool IsAnimationMode() const { return AnimationAsset.IsValid(); }
    EVisibility AnimationVisibility() const { return IsAnimationMode()?EVisibility::Visible:EVisibility::Collapsed; }
    bool IsAnimationReady() const { return PreviewClient.IsValid() && PreviewClient->IsAnimationReady(); }
    FString GetAnimationReceiverPath() const { return AnimationReceivingMesh.IsValid()?AnimationReceivingMesh->GetPathName():FString(); }
    float GetAnimationNormalizedPosition() const
    {
        return AnimationAsset.IsValid() && AnimationAsset->SequenceLength>0.0f && PreviewClient.IsValid()
            ? FMath::Clamp(PreviewClient->GetAnimationTime()/AnimationAsset->SequenceLength,0.0f,1.0f):0.0f;
    }
    void SetAnimationNormalizedPosition(float Position)
    {
        if (AnimationAsset.IsValid() && PreviewClient.IsValid() && FMath::IsFinite(Position))
        { PreviewClient->SeekAnimation(FMath::Clamp(Position,0.0f,1.0f)*AnimationAsset->SequenceLength);Invalidate(); }
    }
    FText GetAnimationPositionLabel() const
    {
        return FText::FromString(AnimationAsset.IsValid()
            ? FString::Printf(TEXT("%.2f / %.2f s"),PreviewClient.IsValid()?PreviewClient->GetAnimationTime():0.0f,AnimationAsset->SequenceLength)
            : FString());
    }
    void SetAnimationReceiverAsset(const FAssetData& Data)
    {
        if (!AnimationAsset.IsValid()) { return; }
        // Loading is limited to the mesh the user explicitly picked.
        AnimationReceivingMesh.Reset(Data.IsValid()?Cast<USkeletalMesh>(Data.GetAsset()):nullptr);
        bAnimationWantsPlay=true;
        SetAsset(AnimationAsset.Get());
        Invalidate();
    }
    bool CheckAnimationRequest(FString& Reason) const
    {
        UAnimSequence* Sequence=AnimationAsset.Get();
        USkeletalMesh* Mesh=AnimationReceivingMesh.Get();
        if (!Sequence || !Mesh) { Reason=TEXT("Choose a receiving skeletal mesh to preview this original animation.");return false; }
        if (!IsValid(Sequence) || !IsValid(Mesh) || !Sequence->GetSkeleton() || !Mesh->Skeleton ||
            Sequence->HasAnyFlags(RF_NeedLoad|RF_NeedPostLoad) || Mesh->HasAnyFlags(RF_NeedLoad|RF_NeedPostLoad))
        { Reason=TEXT("The original animation and receiving mesh must be fully loaded with their real skeletons.");return false; }
        if (Sequence->GetClass()!=UAnimSequence::StaticClass() || Sequence->IsValidAdditive() || Sequence->OnlyUseRawData() ||
            !Sequence->IsCompressedDataValid() || !Sequence->CompressedData.CompressedDataStructure ||
            !Sequence->CompressedData.CompressedDataStructure->IsValid() || !Sequence->CompressedData.BoneCompressionCodec ||
            Sequence->CompressedData.BoneCompressionCodec->GetClass()->GetPathName()!=TEXT("/Script/ACLPlugin.AnimBoneCompressionCodec_ACL") ||
            Sequence->CompressedData.CompressedByteStream.Num()<1 || Sequence->CompressedData.CompressedByteStream.Num()>268435456 ||
            !FMath::IsFinite(Sequence->SequenceLength) || Sequence->SequenceLength<=0.0f)
        { Reason=TEXT("This preview currently supports loaded, nonadditive native ACL animation sequences. Raw fallback, additive clips and other animation types are not enabled.");return false; }
        if (Sequence->Notifies.Num()!=0)
        { Reason=TEXT("This clip contains animation notifies. Runtime game context and notify classes must be validated before playback; the original notify data is unchanged.");return false; }
        // Original curve metadata is retained. The initialized native receiving-bone
        // container must prove that curve evaluation has zero valid destinations.
        if (!Mesh->Skeleton->IsCompatibleMesh(Mesh))
        { Reason=TEXT("The receiving mesh does not pass its genuine owner skeleton's hierarchy check. Its skeleton has not been reassigned.");return false; }
        if (!Mesh->Skeleton->IsCompatible(Sequence->GetSkeleton()))
        { Reason=TEXT("These skeletons are not registered as compatible. Select the two skeletons in the Content Browser and choose Add Selected SkelCompat, then select the receiving mesh again.");return false; }
        return true;
    }
    FString RunOwnedAnimationProbeCommand(const TArray<FString>& Arguments);
