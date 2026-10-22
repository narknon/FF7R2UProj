// Included in FRuntimePreviewClient's public section; no reflected state or ABI changes.
    static double AnimationRotationDifference(const FTransform& A,const FTransform& B)
    {
        const FQuat QA=A.GetRotation(),QB=B.GetRotation();
        if ((QA.X==QB.X && QA.Y==QB.Y && QA.Z==QB.Z && QA.W==QB.W) ||
            (QA.X==-QB.X && QA.Y==-QB.Y && QA.Z==-QB.Z && QA.W==-QB.W)) { return 0.0; }
        const double AX=QA.X,AY=QA.Y,AZ=QA.Z,AW=QA.W,BX=QB.X,BY=QB.Y,BZ=QB.Z,BW=QB.W;
        const double DX=AW*BX-AX*BW-AY*BZ+AZ*BY,DY=AW*BY+AX*BZ-AY*BW-AZ*BX;
        const double DZ=AW*BZ-AX*BY+AY*BX-AZ*BW,DW=AW*BW+AX*BX+AY*BY+AZ*BZ;
        return 2.0*std::atan2(std::sqrt(DX*DX+DY*DY+DZ*DZ),std::abs(DW));
    }

    static FString AnimationRequiredPoseDigest(const TArray<FTransform>& Pose,const TArray<int32>& Required)
    {
        FSHA1 Hash;
        for (int32 Bone:Required)
        {
            const FVector P=Pose[Bone].GetTranslation(),S=Pose[Bone].GetScale3D();
            const FQuat Q=Pose[Bone].GetRotation();
            const float Values[]={P.X,P.Y,P.Z,Q.X,Q.Y,Q.Z,Q.W,S.X,S.Y,S.Z};
            Hash.Update(reinterpret_cast<const uint8*>(&Bone),sizeof(Bone));
            Hash.Update(reinterpret_cast<const uint8*>(Values),sizeof(Values));
        }
        Hash.Final();uint8 Bytes[20];Hash.GetHash(Bytes);return BytesToHex(Bytes,20).ToLower();
    }

    static bool SnapshotAnimationRefusals(TMap<FString,double>& Out)
    {
        TSharedPtr<FJsonObject> JSON;
        const FString Text=RebirthSkeletonCompatibility::GetDiagnostics();
        if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),JSON) || !JSON.IsValid()) { return false; }
        for (const auto& Item:JSON->Values)
        {
            if (Item.Key==TEXT("directed_pairs") || Item.Key==TEXT("revision") || Item.Value->Type!=EJson::Number) { continue; }
            const double Value=Item.Value->AsNumber();
            if (!FMath::IsFinite(Value) || Value<0.0) { return false; }
            Out.Add(Item.Key,Value);
        }
        return Out.Num()>0;
    }

    void ClearAnimationPreview()
    {
        if (USkeletalMeshComponent* Mesh=AnimationComponent.Get())
        {
            Mesh->HandleExistingParallelEvaluationTask(true,true);
            Mesh->Stop();Mesh->SetAnimation(nullptr);Mesh->SetSkeletalMesh(nullptr);
            Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
        }
        AnimationComponent.Reset();AnimationSequence.Reset();AnimationRuntimeStatus.Reset();
        AnimationAppliedFrames=0;AnimationAppliedSeconds=0.0;AnimationDroppedSeconds=0.0;
        bAnimationPoseValidated=false;bAnimationRefusalDelta=false;bAnimationRawFallbackSelected=false;
        AnimationGuardChecks=0;AnimationValidCurveCount=0;AnimationValidationSamples=0;
        AnimationValidationMotionCm=0.0;AnimationValidationRotationRadians=0.0;
        bAnimationValidationDigestChanged=false;
        bAnimationRootAlignmentInitialized=false;bAnimationRootAlignmentActive=false;bAnimationRootAlignmentVerified=false;
        AnimationOriginalComponentTransform=FTransform::Identity;AnimationAlignedComponentTransform=FTransform::Identity;
        AnimationInitialRootRotation=FQuat::Identity;AnimationReferenceRootRotation=FQuat::Identity;
        AnimationWorldInitialRootErrorRadians=0.0;AnimationBoundsScaleUpdates=0;
    }

    void StopAnimationForGuard(const FString& Reason)
    {
        if (USkeletalMeshComponent* Mesh=AnimationComponent.Get())
        {
            Mesh->HandleExistingParallelEvaluationTask(true,true);
            Mesh->Stop();Mesh->SetAnimation(nullptr);
            Mesh->TickAnimation(0.0f,false);Mesh->RefreshBoneTransforms(nullptr);
        }
        bAnimationPoseValidated=false;bPlaying=false;
        AnimationRuntimeStatus=TEXT("Animation stopped: ")+Reason;
    }

    bool CheckAnimationEvaluationContract(FString& Reason)
    {
        USkeletalMeshComponent* Mesh=AnimationComponent.Get();UAnimSequence* Sequence=AnimationSequence.Get();
        UAnimSingleNodeInstance* Instance=Mesh?Mesh->GetSingleNodeInstance():nullptr;
        if (!Mesh || !Sequence || !Mesh->SkeletalMesh || !Mesh->SkeletalMesh->Skeleton || !Instance ||
            Instance->GetAnimationAsset()!=Sequence)
        { Reason=TEXT("the native single-node instance no longer retains the original clip and receiving mesh.");return false; }
        if (!Mesh->SkeletalMesh->Skeleton->IsCompatible(Sequence->GetSkeleton()))
        { Reason=TEXT("its compatible skeleton pair is no longer registered. Select the receiving mesh again after registration.");return false; }
        const FBoneContainer& Bones=Instance->GetRequiredBones();
        if (!Bones.IsValid() || Bones.GetSkeletonAsset()!=Mesh->SkeletalMesh->Skeleton || Bones.GetCompactPoseNumBones()<1)
        { Reason=TEXT("the native receiving required-bone container is invalid or belongs to another skeleton.");return false; }
        bAnimationRawFallbackSelected=Sequence->UseRawDataForPoseExtraction(Bones);
        if (bAnimationRawFallbackSelected)
        {
            Reason=(Sequence->GetRawAnimationData().Num()==0 || Sequence->GetRawTrackToSkeletonMapTable().Num()==0)
                ?TEXT("native pose extraction selected empty raw animation data instead of the original compressed clip.")
                :TEXT("native pose extraction selected a raw branch; this preview requires the original compressed animation path.");
            return false;
        }
        AnimationValidCurveCount=0;
        for (uint16 Index:Bones.GetUIDToArrayLookupTable()) { AnimationValidCurveCount+=(Index!=MAX_uint16); }
        FMemMark Mark(FMemStack::Get());FBlendedCurve Curves;Curves.InitFrom(Bones);
        if (AnimationValidCurveCount!=0 || Curves.NumValidCurveCount!=0)
        { Reason=TEXT("curve evaluation is disabled, but native receiving curve destinations remain active.");return false; }
        return true;
    }

    bool EvaluateAnimationPreview(float DeltaSeconds,FString& Reason)
    {
        if (!FMath::IsFinite(DeltaSeconds) || DeltaSeconds<0.0f || DeltaSeconds>0.1f)
        { Reason=TEXT("invalid bounded animation delta.");return false; }
        if (!CheckAnimationEvaluationContract(Reason)) { return false; }
        TMap<FString,double> Before,After;
        if (!SnapshotAnimationRefusals(Before)) { Reason=TEXT("native pose refusal diagnostics are unavailable.");return false; }
        USkeletalMeshComponent* Mesh=AnimationComponent.Get();
        Mesh->TickAnimation(DeltaSeconds,false);Mesh->RefreshBoneTransforms(nullptr);
        ++AnimationGuardChecks;
        if (!SnapshotAnimationRefusals(After) || Before.Num()!=After.Num())
        { Reason=TEXT("native pose refusal diagnostics changed schema during evaluation.");return false; }
        for (const auto& Counter:Before)
        {
            const double* Value=After.Find(Counter.Key);
            if (!Value || *Value!=Counter.Value)
            {
                bAnimationRefusalDelta=true;
                Reason=TEXT("native pose evaluation refused this request (")+Counter.Key+TEXT("). Original clips remain unchanged.");
                return false;
            }
        }
        if (!CheckAnimationEvaluationContract(Reason)) { return false; }
        const auto& Local=Mesh->GetBoneSpaceTransforms();const auto& CS=Mesh->GetComponentSpaceTransforms();
        const int32 Expected=Mesh->SkeletalMesh->RefSkeleton.GetNum();
        if (Expected<1 || Local.Num()!=Expected || CS.Num()!=Expected)
        { Reason=TEXT("native animation did not provide complete receiving bone buffers.");return false; }
        for (int32 Bone=0;Bone<Expected;++Bone)
        {
            if (!Local[Bone].IsValid() || !Local[Bone].IsRotationNormalized() || !CS[Bone].IsValid() || !CS[Bone].IsRotationNormalized())
            { Reason=TEXT("native animation produced nonfinite or nonnormalized receiving bone transforms.");return false; }
        }
        return EnsureAnimationPreviewBounds(Reason);
    }

    bool InitializeAnimationPreview(USkeletalMeshComponent* Mesh,UAnimSequence* Sequence,bool bStartPlaying,bool bAlignRootOrientation)
    {
        ClearBonamik(); // The validated Bonamik path takes a reference pose as input.
        AnimationComponent=Mesh;AnimationSequence=Sequence;
        AnimationAppliedFrames=0;AnimationAppliedSeconds=0.0;AnimationDroppedSeconds=0.0;
        bAnimationPoseValidated=false;bAnimationRefusalDelta=false;bAnimationRawFallbackSelected=false;
        AnimationGuardChecks=0;AnimationValidCurveCount=0;AnimationValidationSamples=0;
        AnimationValidationMotionCm=0.0;AnimationValidationRotationRadians=0.0;bAnimationValidationDigestChanged=false;
        Mesh->SetComponentTickEnabled(false); // This viewport owns the sole bounded animation tick.
        Mesh->SetAllowAnimCurveEvaluation(false);
        Mesh->PlayAnimation(Sequence,true);
        UAnimSingleNodeInstance* Instance=Mesh->GetSingleNodeInstance();
        if (!Instance || Instance->GetAnimationAsset()!=Sequence)
        { StopAnimationForGuard(TEXT("the native animation instance rejected this original clip."));return false; }
        Instance->SetPosition(0.0f,false);
        FString Reason;
        if (!EvaluateAnimationPreview(0.0f,Reason)) { StopAnimationForGuard(Reason);return false; }
        const auto Initial=Mesh->GetComponentSpaceTransforms();
        TArray<int32> Required;
        const FBoneContainer& Bones=Instance->GetRequiredBones();
        for (int32 Compact=0;Compact<Bones.GetCompactPoseNumBones();++Compact)
        {
            const int32 Bone=Bones.MakeMeshPoseIndex(FCompactPoseBoneIndex(Compact)).GetInt();
            if (!Initial.IsValidIndex(Bone) || Required.Contains(Bone))
            { StopAnimationForGuard(TEXT("native required-bone indices are invalid or duplicated."));return false; }
            Required.Add(Bone);
        }
        const FString InitialDigest=AnimationRequiredPoseDigest(Initial,Required);
        // Validate actual original-clip motion before showing Ready. These bounded, no-notify
        // native samples are restored to t=0 and do not count as elapsed user playback.
        for (float Fraction:{0.25f,0.5f,1.0f})
        {
            const float Time=FMath::Min(2.0f,Sequence->SequenceLength*0.5f)*Fraction;
            Instance->SetPosition(Time,false);
            if (!EvaluateAnimationPreview(0.0f,Reason)) { StopAnimationForGuard(Reason);return false; }
            const auto& CS=Mesh->GetComponentSpaceTransforms();
            bAnimationValidationDigestChanged|=AnimationRequiredPoseDigest(CS,Required)!=InitialDigest;
            for (int32 Bone:Required)
            {
                AnimationValidationMotionCm=FMath::Max(AnimationValidationMotionCm,double(FVector::Dist(Initial[Bone].GetTranslation(),CS[Bone].GetTranslation())));
                AnimationValidationRotationRadians=FMath::Max(AnimationValidationRotationRadians,AnimationRotationDifference(Initial[Bone],CS[Bone]));
            }
            ++AnimationValidationSamples;
        }
        Instance->SetPosition(0.0f,false);
        if (!EvaluateAnimationPreview(0.0f,Reason)) { StopAnimationForGuard(Reason);return false; }
        if (!bAnimationValidationDigestChanged || !(AnimationValidationMotionCm>0.001 || AnimationValidationRotationRadians>0.0001))
        { StopAnimationForGuard(TEXT("the original clip was accepted, but native receiving bone poses did not show meaningful animation motion."));return false; }
        // The retail idle's initial root orientation differs from this mesh's reference basis.
        // Correct only the transient preview component; original local/CS poses are untouched.
        AnimationOriginalComponentTransform=Mesh->GetComponentTransform();
        const auto& RestoredPose=Mesh->GetComponentSpaceTransforms();
        const auto& ReferencePose=Mesh->SkeletalMesh->RefSkeleton.GetRefBonePose();
        if (RestoredPose.Num()<1 || ReferencePose.Num()<1 || !AnimationOriginalComponentTransform.IsValid() ||
            !AnimationOriginalComponentTransform.IsRotationNormalized())
        { StopAnimationForGuard(TEXT("the preview root alignment inputs are invalid."));return false; }
        AnimationInitialRootRotation=RestoredPose[0].GetRotation();
        AnimationReferenceRootRotation=ReferencePose[0].GetRotation();
        const FVector BaseScale=AnimationOriginalComponentTransform.GetScale3D();
        if (!AnimationInitialRootRotation.IsNormalized() || !AnimationReferenceRootRotation.IsNormalized() ||
            BaseScale.GetMin()<=0.0f || !FMath::IsNearlyEqual(BaseScale.X,BaseScale.Y) || !FMath::IsNearlyEqual(BaseScale.X,BaseScale.Z))
        { StopAnimationForGuard(TEXT("preview root alignment requires finite normalized rotations and positive uniform component scale."));return false; }
        const FQuat BaseRotation=AnimationOriginalComponentTransform.GetRotation();
        const FQuat AlignedRotation=(BaseRotation*AnimationReferenceRootRotation*AnimationInitialRootRotation.Inverse()).GetNormalized();
        AnimationAlignedComponentTransform=AnimationOriginalComponentTransform;
        AnimationAlignedComponentTransform.SetRotation(AlignedRotation);
        AnimationWorldInitialRootErrorRadians=AnimationRotationDifference(
            FTransform((AlignedRotation*AnimationInitialRootRotation).GetNormalized()),
            FTransform((BaseRotation*AnimationReferenceRootRotation).GetNormalized()));
        if (!AnimationAlignedComponentTransform.IsValid() || !AnimationAlignedComponentTransform.IsRotationNormalized() ||
            !FMath::IsFinite(AnimationWorldInitialRootErrorRadians) || AnimationWorldInitialRootErrorRadians>0.0001)
        { StopAnimationForGuard(TEXT("the derived preview root orientation does not match the genuine reference root."));return false; }
        bAnimationRootAlignmentInitialized=true;bAnimationPoseValidated=true;bPlaying=bStartPlaying;
        if (!SetAnimationRootAlignment(bAlignRootOrientation,Reason)) { StopAnimationForGuard(Reason);return false; }
        AnimationRuntimeStatus=TEXT("Validated original compressed bone animation. Curve metadata is preserved; curve evaluation and Bonamik are disabled.");
        return true;
    }

    // This is a display transform, not a pose-retargeting or retail actor-basis claim.
    // It is derived once at t=0 and stays constant, retaining later animated root turns.
    bool SetAnimationRootAlignment(bool bEnabled,FString& Reason)
    {
        USkeletalMeshComponent* Mesh=AnimationComponent.Get();
        UAnimSingleNodeInstance* Instance=Mesh?Mesh->GetSingleNodeInstance():nullptr;
        if (!bAnimationRootAlignmentInitialized || !IsAnimationReady() || !Mesh || !Instance)
        { Reason=TEXT("root alignment requires a validated original animation preview.");return false; }
        TArray<int32> AllBones;for (int32 Bone=0;Bone<Mesh->GetBoneSpaceTransforms().Num();++Bone) { AllBones.Add(Bone); }
        const FString LocalBefore=AnimationRequiredPoseDigest(Mesh->GetBoneSpaceTransforms(),AllBones);
        const FString CSBefore=AnimationRequiredPoseDigest(Mesh->GetComponentSpaceTransforms(),AllBones);
        const float TimeBefore=Instance->GetCurrentTime();
        const FTransform Desired=bEnabled?AnimationAlignedComponentTransform:AnimationOriginalComponentTransform;
        Mesh->SetWorldTransform(Desired,false,nullptr,ETeleportType::TeleportPhysics);
        Mesh->InvalidateCachedBounds();Mesh->UpdateBounds();Mesh->MarkRenderTransformDirty();
        if (!EnsureAnimationPreviewBounds(Reason)) { return false; }
        const FTransform Actual=Mesh->GetComponentTransform();
        if (!Actual.IsValid() || !Actual.IsRotationNormalized() ||
            FVector::Dist(Actual.GetTranslation(),Desired.GetTranslation())>0.0001f ||
            FVector::Dist(Actual.GetScale3D(),Desired.GetScale3D())>0.0001f ||
            AnimationRotationDifference(Actual,Desired)>0.0001 || Instance->GetCurrentTime()!=TimeBefore ||
            AnimationRequiredPoseDigest(Mesh->GetBoneSpaceTransforms(),AllBones)!=LocalBefore ||
            AnimationRequiredPoseDigest(Mesh->GetComponentSpaceTransforms(),AllBones)!=CSBefore)
        { Reason=TEXT("changing the preview component orientation altered native pose/time or failed transform validation.");return false; }
        bAnimationRootAlignmentActive=bEnabled;bAnimationRootAlignmentVerified=bEnabled;
        return true;
    }

    double GetAnimationCurrentRootReferenceError() const
    {
        USkeletalMeshComponent* Mesh=AnimationComponent.Get();
        if (!bAnimationRootAlignmentInitialized || !Mesh || Mesh->GetComponentSpaceTransforms().Num()<1) { return 0.0; }
        const FQuat WorldRoot=Mesh->GetComponentTransform().GetRotation()*Mesh->GetComponentSpaceTransforms()[0].GetRotation();
        const FQuat ReferenceWorld=AnimationOriginalComponentTransform.GetRotation()*AnimationReferenceRootRotation;
        return AnimationRotationDifference(FTransform(WorldRoot.GetNormalized()),FTransform(ReferenceWorld.GetNormalized()));
    }

    bool GatherAnimationRequiredWorldBox(FBox& OutBox) const
    {
        OutBox=FBox(ForceInit);USkeletalMeshComponent* Mesh=AnimationComponent.Get();
        UAnimSingleNodeInstance* Instance=Mesh?Mesh->GetSingleNodeInstance():nullptr;
        if (!Mesh || !Mesh->SkeletalMesh || !Instance) { return false; }
        const auto& Pose=Mesh->GetComponentSpaceTransforms();const FBoneContainer& Bones=Instance->GetRequiredBones();
        const FTransform World=Mesh->GetComponentTransform();
        if (!World.IsValid() || !World.IsRotationNormalized() || !Bones.IsValid() || Bones.GetCompactPoseNumBones()<1) { return false; }
        for (int32 Compact=0;Compact<Bones.GetCompactPoseNumBones();++Compact)
        {
            const int32 Bone=Bones.MakeMeshPoseIndex(FCompactPoseBoneIndex(Compact)).GetInt();
            if (!Pose.IsValidIndex(Bone) || !Pose[Bone].IsValid()) { return false; }
            const FVector Point=World.TransformPosition(Pose[Bone].GetTranslation());
            if (Point.ContainsNaN()) { return false; }
            OutBox+=Point;
        }
        if (!OutBox.IsValid || OutBox.GetExtent().GetMax()>100000.0f) { return false; }
        const float Padding=FMath::Clamp(Mesh->SkeletalMesh->GetBounds().BoxExtent.Size()*0.15f,10.0f,50.0f);
        OutBox=OutBox.ExpandBy(Padding);return true;
    }

    bool AnimationBoundsContainRequiredWorldBox() const
    {
        USkeletalMeshComponent* Mesh=AnimationComponent.Get();FBox Required(ForceInit);
        if (!Mesh || !GatherAnimationRequiredWorldBox(Required)) { return false; }
        for (int32 Axis=0;Axis<3;++Axis)
        {
            const double Low=Mesh->Bounds.Origin[Axis]-Mesh->Bounds.BoxExtent[Axis];
            const double High=Mesh->Bounds.Origin[Axis]+Mesh->Bounds.BoxExtent[Axis];
            if (!FMath::IsFinite(Low) || !FMath::IsFinite(High) || Required.Min[Axis]<Low || Required.Max[Axis]>High) { return false; }
        }
        return true;
    }

    bool EnsureAnimationPreviewBounds(FString& Reason)
    {
        USkeletalMeshComponent* Mesh=AnimationComponent.Get();FBox Required(ForceInit);
        if (!Mesh || !GatherAnimationRequiredWorldBox(Required) || !FMath::IsFinite(Mesh->BoundsScale) || Mesh->BoundsScale<=0.0f || Mesh->BoundsScale>64.0f)
        { Reason=TEXT("the native preview bounds or bounded scale are invalid.");return false; }
        // Native cooked meshes may fall back to imported, unanimated bounds. Expand
        // this transient component uniformly and monotonically; do not alter assets.
        Mesh->InvalidateCachedBounds();Mesh->UpdateBounds();
        double Ratio=1.0;
        for (int32 Axis=0;Axis<3;++Axis)
        {
            const double Extent=Mesh->Bounds.BoxExtent[Axis],Origin=Mesh->Bounds.Origin[Axis];
            if (!FMath::IsFinite(Extent) || !FMath::IsFinite(Origin) || Extent<=0.001)
            { Reason=TEXT("native preview bounds have an invalid or degenerate extent.");return false; }
            const double Needed=FMath::Max(FMath::Abs(double(Required.Min[Axis])-Origin),FMath::Abs(double(Required.Max[Axis])-Origin));
            Ratio=FMath::Max(Ratio,Needed/Extent);
        }
        if (Ratio>1.0)
        {
            const double NextScale=double(Mesh->BoundsScale)*Ratio*1.01;
            if (!FMath::IsFinite(NextScale) || NextScale>64.0)
            { Reason=TEXT("the animated preview requires bounds beyond the bounded component scale limit.");return false; }
            TArray<int32> AllBones;for (int32 Bone=0;Bone<Mesh->GetBoneSpaceTransforms().Num();++Bone) { AllBones.Add(Bone); }
            const FString LocalBefore=AnimationRequiredPoseDigest(Mesh->GetBoneSpaceTransforms(),AllBones);
            const FString CSBefore=AnimationRequiredPoseDigest(Mesh->GetComponentSpaceTransforms(),AllBones);
            const float TimeBefore=Mesh->GetSingleNodeInstance()->GetCurrentTime();
            Mesh->SetBoundsScale(float(NextScale));Mesh->InvalidateCachedBounds();Mesh->UpdateBounds();Mesh->MarkRenderTransformDirty();
            ++AnimationBoundsScaleUpdates;
            if (Mesh->GetSingleNodeInstance()->GetCurrentTime()!=TimeBefore ||
                AnimationRequiredPoseDigest(Mesh->GetBoneSpaceTransforms(),AllBones)!=LocalBefore ||
                AnimationRequiredPoseDigest(Mesh->GetComponentSpaceTransforms(),AllBones)!=CSBefore)
            { Reason=TEXT("expanding transient preview bounds altered native animation state.");return false; }
        }
        if (!AnimationBoundsContainRequiredWorldBox())
        { Reason=TEXT("native preview bounds do not contain the evaluated required-bone world box.");return false; }
        return true;
    }

    // Camera bounds use the evaluated receiving required bones in world space.
    // This reads the evaluated pose and current display component transform without altering either.
    bool GetAnimationFramingBounds(FBox& OutBounds,FBox& OutBoneBounds,int32& OutRequiredCount) const
    {
        OutBounds=FBox(ForceInit);OutBoneBounds=FBox(ForceInit);OutRequiredCount=0;
        USkeletalMeshComponent* Mesh=AnimationComponent.Get();
        UAnimSingleNodeInstance* Instance=Mesh?Mesh->GetSingleNodeInstance():nullptr;
        if (!Mesh || !Mesh->SkeletalMesh || !Instance || !IsAnimationReady()) { return false; }
        const FTransform World=Mesh->GetComponentTransform();
        if (!World.IsValid() || !World.IsRotationNormalized()) { return false; }
        const TArray<FTransform>& Pose=Mesh->GetComponentSpaceTransforms();
        const FBoneContainer& Bones=Instance->GetRequiredBones();
        if (!Bones.IsValid() || Bones.GetCompactPoseNumBones()<1) { return false; }
        for (int32 Compact=0;Compact<Bones.GetCompactPoseNumBones();++Compact)
        {
            const int32 Bone=Bones.MakeMeshPoseIndex(FCompactPoseBoneIndex(Compact)).GetInt();
            if (!Pose.IsValidIndex(Bone) || !Pose[Bone].IsValid()) { return false; }
            const FVector Position=World.TransformPosition(Pose[Bone].GetTranslation());
            if (Position.ContainsNaN()) { return false; }
            OutBoneBounds+=Position;++OutRequiredCount;
        }
        if (!OutBoneBounds.IsValid || OutBoneBounds.GetExtent().GetMax()>100000.0f) { return false; }
        const float Padding=FMath::Clamp(Mesh->SkeletalMesh->GetBounds().BoxExtent.Size()*0.15f,10.0f,50.0f);
        OutBounds=OutBoneBounds.ExpandBy(Padding);
        return OutBounds.IsValid && OutBounds.GetExtent().GetMax()>=1.0f;
    }

    bool IsAnimationReady() const
    {
        USkeletalMeshComponent* Mesh=AnimationComponent.Get();UAnimSequence* Sequence=AnimationSequence.Get();
        return bAnimationPoseValidated && Mesh && Sequence && Mesh->SkeletalMesh && Mesh->SkeletalMesh->Skeleton &&
            Mesh->SkeletalMesh->Skeleton->IsCompatible(Sequence->GetSkeleton()) && Mesh->GetSingleNodeInstance() &&
            Mesh->GetSingleNodeInstance()->GetAnimationAsset()==Sequence;
    }

    void TickAnimationPreview(float DeltaSeconds)
    {
        if (!AnimationComponent.IsValid() || !AnimationSequence.IsValid()) { return; }
        FString Reason;
        if (!EvaluateAnimationPreview(DeltaSeconds,Reason)) { StopAnimationForGuard(Reason);return; }
        if (!bAnimationPoseValidated) { bPlaying=false;return; }
        ++AnimationAppliedFrames;AnimationAppliedSeconds+=DeltaSeconds;
    }

    void SeekAnimation(float Seconds)
    {
        if (!IsAnimationReady() || !FMath::IsFinite(Seconds)) { return; }
        AnimationComponent->GetSingleNodeInstance()->SetPosition(FMath::Clamp(Seconds,0.0f,AnimationSequence->SequenceLength),false);
        FString Reason;if (!EvaluateAnimationPreview(0.0f,Reason)) { StopAnimationForGuard(Reason); }
    }

    void RestartAnimationPreview()
    {
        if (!IsAnimationReady()) { return; }
        SeekAnimation(0.0f);
        if (!IsAnimationReady()) { return; }
        AnimationAppliedFrames=0;AnimationAppliedSeconds=0.0;AnimationDroppedSeconds=0.0;bPlaying=true;
    }

    float GetAnimationTime() const { return IsAnimationReady()?AnimationComponent->GetSingleNodeInstance()->GetCurrentTime():0.0f; }
    FString GetAnimationRuntimeStatus() const { return AnimationRuntimeStatus; }
    int32 AnimationAppliedFrames=0,AnimationGuardChecks=0,AnimationValidCurveCount=0,AnimationValidationSamples=0;
    double AnimationAppliedSeconds=0.0,AnimationDroppedSeconds=0.0,AnimationValidationMotionCm=0.0,AnimationValidationRotationRadians=0.0;
    bool bAnimationPoseValidated=false,bAnimationRefusalDelta=false,bAnimationRawFallbackSelected=false,bAnimationValidationDigestChanged=false;
    TWeakObjectPtr<USkeletalMeshComponent> AnimationComponent;
    TWeakObjectPtr<UAnimSequence> AnimationSequence;
    FString AnimationRuntimeStatus;
    bool bAnimationRootAlignmentInitialized=false,bAnimationRootAlignmentActive=false,bAnimationRootAlignmentVerified=false;
    FTransform AnimationOriginalComponentTransform=FTransform::Identity,AnimationAlignedComponentTransform=FTransform::Identity;
    FQuat AnimationInitialRootRotation=FQuat::Identity,AnimationReferenceRootRotation=FQuat::Identity;
    double AnimationWorldInitialRootErrorRadians=0.0;
    int32 AnimationBoundsScaleUpdates=0;
