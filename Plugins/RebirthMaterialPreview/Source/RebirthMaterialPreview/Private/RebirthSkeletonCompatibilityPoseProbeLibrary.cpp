#include "RebirthSkeletonCompatibilityPoseProbeLibrary.h"
#include "Animation/AnimSequence.h"
#include "AnimationRuntime.h"
#include "Animation/AnimBoneCompressionCodec.h"
#include "Animation/AnimationPoseData.h"
#include "Animation/AnimCompressionTypes.h"
#include "Animation/AnimCurveTypes.h"
#include "Animation/CustomAttributesRuntime.h"
#include "Animation/RebirthSkeletonCompatibility.h"
#include "Animation/Skeleton.h"
#include "BoneContainer.h"
#include "BonePose.h"
#include "Dom/JsonObject.h"
#include "Engine/SkeletalMesh.h"
#include "HAL/UnrealMemory.h"
#include "Misc/MemStack.h"
#include "Misc/SecureHash.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "UObject/GarbageCollection.h"
#include "UObject/Package.h"
#include "UObject/StrongObjectPtr.h"
#include <cmath>

namespace RebirthOriginalPoseProbe
{
    FString Json(const TSharedRef<FJsonObject>& Report)
    {
        FString Result;
        FJsonSerializer::Serialize(Report, TJsonWriterFactory<>::Create(&Result));
        return Result;
    }
    FString Digest(const UAnimSequence* Sequence)
    {
        const auto& Bytes = Sequence->CompressedData.CompressedByteStream;
        uint8 Hash[20];
        FSHA1::HashBuffer(Bytes.GetData(), Bytes.Num(), Hash);
        return BytesToHex(Hash, UE_ARRAY_COUNT(Hash)).ToLower();
    }
    struct FError
    {
        double Position = 0, Radians = 0, Scale = 0;
        int32 Count = 0;
        bool Add(const FTransform& Expected, const FTransform& Actual)
        {
            if (!Expected.IsValid() || !Actual.IsValid()) { return false; }
            Position = FMath::Max(Position, double(FVector::Dist(Expected.GetTranslation(), Actual.GetTranslation())));
            Scale = FMath::Max(Scale, double((Expected.GetScale3D() - Actual.GetScale3D()).GetAbsMax()));
            const FQuat A = Expected.GetRotation(), B = Actual.GetRotation();
            const double Dot = double(A.X)*B.X + double(A.Y)*B.Y + double(A.Z)*B.Z + double(A.W)*B.W;
            const double AA = double(A.X)*A.X + double(A.Y)*A.Y + double(A.Z)*A.Z + double(A.W)*A.W;
            const double BB = double(B.X)*B.X + double(B.Y)*B.Y + double(B.Z)*B.Z + double(B.W)*B.W;
            if (AA <= 0 || BB <= 0) { return false; }
            Radians = FMath::Max(Radians, 2.0 * std::acos(FMath::Clamp(std::abs(Dot)/std::sqrt(AA*BB), 0.0, 1.0)));
            ++Count;
            return FMath::IsFinite(Position) && FMath::IsFinite(Radians) && FMath::IsFinite(Scale);
        }
        bool Passed() const { return Count > 0 && Position <= 0.001 && Radians <= 0.0001 && Scale <= 0.00001; }
        TSharedRef<FJsonObject> Report(bool bAllowEmpty = false) const
        {
            auto Result = MakeShared<FJsonObject>();
            Result->SetNumberField(TEXT("samples"), Count);
            Result->SetNumberField(TEXT("max_translation_error_cm"), Position);
            Result->SetNumberField(TEXT("max_rotation_error_radians"), Radians);
            Result->SetNumberField(TEXT("max_scale_error"), Scale);
            Result->SetBoolField(TEXT("passed"), (bAllowEmpty && Count == 0) || Passed());
            return Result;
        }
    };
    struct FSkeletonSnapshot
    {
        USkeleton* Skeleton;
        FGuid Guid, VirtualGuid;
        TArray<FMeshBoneInfo> Infos;
        TArray<FTransform> Poses;
        bool bDirty;
        explicit FSkeletonSnapshot(USkeleton* In) : Skeleton(In), Guid(In->GetGuid()), VirtualGuid(In->GetVirtualBoneGuid()),
            Infos(In->GetReferenceSkeleton().GetRawRefBoneInfo()), Poses(In->GetReferenceSkeleton().GetRawRefBonePose()),
            bDirty(In->GetOutermost()->IsDirty()) {}
        bool Unchanged() const
        {
            const auto& Ref = Skeleton->GetReferenceSkeleton();
            if (Skeleton->GetGuid() != Guid || Skeleton->GetVirtualBoneGuid() != VirtualGuid ||
                Skeleton->GetOutermost()->IsDirty() != bDirty || Ref.GetRawBoneNum() != Infos.Num()) { return false; }
            for (int32 Bone=0; Bone<Infos.Num(); ++Bone)
            {
                if (Ref.GetBoneName(Bone) != Infos[Bone].Name || Ref.GetParentIndex(Bone) != Infos[Bone].ParentIndex ||
                    !Ref.GetRawRefBonePose()[Bone].Equals(Poses[Bone], 0.0f)) { return false; }
            }
            return true;
        }
    };
    TSharedRef<FJsonObject> TransformJson(const FTransform& Value)
    {
        auto Result=MakeShared<FJsonObject>();
        const FVector P=Value.GetTranslation(), S=Value.GetScale3D();const FQuat Q=Value.GetRotation();
        Result->SetNumberField(TEXT("px"),P.X);Result->SetNumberField(TEXT("py"),P.Y);Result->SetNumberField(TEXT("pz"),P.Z);
        Result->SetNumberField(TEXT("qx"),Q.X);Result->SetNumberField(TEXT("qy"),Q.Y);Result->SetNumberField(TEXT("qz"),Q.Z);Result->SetNumberField(TEXT("qw"),Q.W);
        Result->SetNumberField(TEXT("sx"),S.X);Result->SetNumberField(TEXT("sy"),S.Y);Result->SetNumberField(TEXT("sz"),S.Z);
        return Result;
    }
    FString CanonicalPoseDigest(const TArray<FTransform>& Pose)
    {
        FSHA1 Hash;
        for(const FTransform& Value:Pose)
        {
            const FVector P=Value.GetTranslation(),S=Value.GetScale3D();const FQuat Q=Value.GetRotation();
            const float Fields[]={Q.X,Q.Y,Q.Z,Q.W,P.X,P.Y,P.Z,S.X,S.Y,S.Z};
            Hash.Update(reinterpret_cast<const uint8*>(Fields),sizeof(Fields));
        }
        Hash.Final();uint8 Bytes[20];Hash.GetHash(Bytes);return BytesToHex(Bytes,20).ToLower();
    }
    bool SetupBones(UObject& Asset, const FReferenceSkeleton& Ref, FBoneContainer& Container)
    {
        if (Ref.GetNum() < 1 || Ref.GetNum() > 65535 || Ref.GetVirtualBoneRefData().Num()) { return false; }
        TArray<FBoneIndexType> Required;
        for (int32 Bone=0; Bone<Ref.GetNum(); ++Bone) { Required.Add(FBoneIndexType(Bone)); }
        Container.InitializeTo(Required, FCurveEvaluationOption(false), Asset);
        Container.SetUseRAWData(false);
        Container.SetUseSourceData(false);
        return Container.IsValid() && Container.GetCompactPoseNumBones() == Required.Num();
    }
    bool Extract(UAnimSequence* Sequence, const FBoneContainer& Bones, float Time, TArray<FTransform>& Local)
    {
        FMemMark Mark(FMemStack::Get());
        FCompactPose Pose;
        Pose.SetBoneContainer(&Bones);
        Pose.ResetToRefPose();
        FBlendedCurve Curves;
        Curves.InitFrom(Bones);
        FStackCustomAttributes Attributes;
        FAnimationPoseData Data(Pose, Curves, Attributes);
        Sequence->GetAnimationPose(Data, FAnimExtractContext(Time, false));
        Local.SetNum(Pose.GetNumBones());
        for (int32 Bone=0; Bone<Pose.GetNumBones(); ++Bone)
        {
            Local[Bone] = Pose[FCompactPoseBoneIndex(Bone)];
            if (!Local[Bone].IsValid()) { return false; }
        }
        return true;
    }
    void ApplyOriginalRootLock(const UAnimSequence* Sequence, const FBoneContainer& Bones, const FTransform& FirstFrame, FTransform& Root)
    {
        if (!Sequence->bForceRootLock) { return; } // ExtractionContext.bExtractRootMotion is deliberately false.
        const FRootMotionReset Reset(Sequence->bEnableRootMotion, Sequence->RootMotionRootLock,
            Sequence->bForceRootLock, FirstFrame, false);
        Reset.ResetRootBoneForRootMotion(Root, Bones);
    }
    bool ComponentPose(const FBoneContainer& Bones, const TArray<FTransform>& Local, TArray<FTransform>& Component)
    {
        Component.SetNum(Local.Num());
        for (int32 Bone=0; Bone<Local.Num(); ++Bone)
        {
            const FCompactPoseBoneIndex Parent = Bones.GetParentBoneIndex(FCompactPoseBoneIndex(Bone));
            if (Parent != INDEX_NONE && (Parent.GetInt() < 0 || Parent.GetInt() >= Bone)) { return false; }
            Component[Bone] = Parent == INDEX_NONE ? Local[Bone] : Local[Bone] * Component[Parent.GetInt()];
            Component[Bone].NormalizeRotation();
            if (!Component[Bone].IsValid()) { return false; }
        }
        return true;
    }
}

bool URebirthSkeletonCompatibilityPoseProbeLibrary::AreSkeletonsCompatible(USkeleton* A, USkeleton* B)
{
    // Compile against the staged Skeleton declaration/PCH. Registry-only checks
    // cannot detect a stale pointer-only IsCompatible COMDAT or inline consumer.
    return IsInGameThread() && !IsGarbageCollecting() && IsValid(A) && IsValid(B) && A->IsCompatible(B);
}

FString URebirthSkeletonCompatibilityPoseProbeLibrary::InspectRegisteredPair(USkeleton* A, USkeleton* B)
{
    auto Report=MakeShared<FJsonObject>();
    bool bPassed=IsInGameThread() && !IsGarbageCollecting() && IsValid(A) && IsValid(B) && A!=B;
    TArray<TSharedPtr<FJsonValue>> Directions;
    if(bPassed)
    {
        for(int32 Direction=0;Direction<2;++Direction)
        {
            USkeleton* Source=Direction==0 ? A : B;
            USkeleton* Target=Direction==0 ? B : A;
            const auto Mapping=RebirthSkeletonCompatibility::FindMapping(Source,Target);
            if(!Mapping.IsValid()){bPassed=false;break;}
            auto Row=MakeShared<FJsonObject>();
            Row->SetStringField(TEXT("source_skeleton"),Source->GetPathName());
            Row->SetStringField(TEXT("target_skeleton"),Target->GetPathName());
            const bool bNativeCompatible=Source->IsCompatible(Target);
            Row->SetBoolField(TEXT("native_USkeleton_IsCompatible"),bNativeCompatible);
            bPassed &= bNativeCompatible;
            Row->SetNumberField(TEXT("source_bones"),Mapping->SourceBoneCount);
            Row->SetNumberField(TEXT("target_bones"),Mapping->TargetBoneCount);
            Row->SetNumberField(TEXT("shared_names"),Mapping->SharedNames);
            Row->SetNumberField(TEXT("target_only_refpose"),Mapping->TargetOnlyBones);
            Row->SetNumberField(TEXT("parent_chain_differences"),Mapping->ParentChainDifferences);
            Row->SetNumberField(TEXT("root_target_index"),Mapping->Remap(0));
            Row->SetBoolField(TEXT("used_root_fallback"),Mapping->bUsedRootFallback);
            TArray<TSharedPtr<FJsonValue>> Indices;
            TSet<int32> Seen;
            bool bNamesValid=true;
            for(int32 Index=0;Index<Mapping->SourceToTarget.Num();++Index)
            {
                const int32 TargetIndex=Mapping->Remap(Index);
                Indices.Add(MakeShared<FJsonValueNumber>(TargetIndex));
                if(TargetIndex==INDEX_NONE){continue;}
                if(TargetIndex<0 || TargetIndex>=Mapping->TargetBoneCount || Seen.Contains(TargetIndex) ||
                    (Source->GetReferenceSkeleton().GetBoneName(Index)!=Target->GetReferenceSkeleton().GetBoneName(TargetIndex) &&
                     !(Index==0 && TargetIndex==0 && Mapping->bUsedRootFallback))) { bNamesValid=false; }
                Seen.Add(TargetIndex);
            }
            Row->SetBoolField(TEXT("native_name_destinations_unique_and_valid"),bNamesValid);
            Row->SetArrayField(TEXT("source_to_target"),Indices);
            bPassed &= bNamesValid && Mapping->Remap(0)==0;
            Directions.Add(MakeShared<FJsonValueObject>(Row));
        }
    }
    Report->SetBoolField(TEXT("succeeded"),bPassed);
    Report->SetArrayField(TEXT("directions"),Directions);
    Report->SetBoolField(TEXT("asset_mutation"),false);
    return RebirthOriginalPoseProbe::Json(Report);
}

FString URebirthSkeletonCompatibilityPoseProbeLibrary::ValidateOriginalCompressedPose(
    UAnimSequence* Sequence, USkeleton* ReceivingSkeleton, USkeletalMesh* ReceivingMesh, int32 SampleCount, bool bExpectRegistered)
{
    using namespace RebirthOriginalPoseProbe;
    auto Report = MakeShared<FJsonObject>();
    Report->SetBoolField(TEXT("succeeded"), false);
    Report->SetBoolField(TEXT("assets_saved"), false);
    Report->SetBoolField(TEXT("clips_converted_or_baked"), false);
    Report->SetBoolField(TEXT("in_game_verified"), false);
    auto Fail = [&](const FString& Error) { Report->SetStringField(TEXT("error"), Error); return Json(Report); };
    if (!IsInGameThread() || IsGarbageCollecting() || !IsValid(Sequence) || !IsValid(ReceivingSkeleton) ||
        SampleCount < 3 || SampleCount > 257) { return Fail(TEXT("Requires loaded assets, game thread outside GC and 3..257 samples.")); }
    if (ReceivingMesh && (!IsValid(ReceivingMesh) || ReceivingMesh->HasAnyFlags(RF_NeedLoad|RF_NeedPostLoad)))
    { return Fail(TEXT("Optional receiving mesh must be fully loaded and valid.")); }
    TStrongObjectPtr<UAnimSequence> SourceRoot(Sequence);
    TStrongObjectPtr<USkeleton> TargetRoot(ReceivingSkeleton), SourceSkeletonRoot(Sequence->GetSkeleton());
    TStrongObjectPtr<USkeletalMesh> MeshRoot(ReceivingMesh);
    USkeleton* SourceSkeleton = SourceSkeletonRoot.Get();
    if (!IsValid(SourceSkeleton) || Sequence->GetClass()!=UAnimSequence::StaticClass() ||
        SourceSkeleton->GetClass()!=USkeleton::StaticClass() || ReceivingSkeleton->GetClass()!=USkeleton::StaticClass() ||
        Sequence->HasAnyFlags(RF_NeedLoad|RF_NeedPostLoad) || SourceSkeleton->HasAnyFlags(RF_NeedLoad|RF_NeedPostLoad) ||
        ReceivingSkeleton->HasAnyFlags(RF_NeedLoad|RF_NeedPostLoad) || Sequence->IsValidAdditive() ||
        Sequence->OnlyUseRawData() || !Sequence->IsCompressedDataValid() || !Sequence->CompressedData.CompressedDataStructure ||
        !Sequence->CompressedData.CompressedDataStructure->IsValid() || !Sequence->CompressedData.BoneCompressionCodec ||
        Sequence->CompressedData.BoneCompressionCodec->GetClass()->GetPathName()!=TEXT("/Script/ACLPlugin.AnimBoneCompressionCodec_ACL") ||
        !(Sequence->GetOutermost()->GetPackageFlags()&PKG_Cooked) || Sequence->CompressedData.CompressedByteStream.Num()<1 ||
        Sequence->CompressedData.CompressedByteStream.Num()>268435456 || !FMath::IsFinite(Sequence->SequenceLength) || Sequence->SequenceLength<=0)
    { return Fail(TEXT("Requires genuine fully loaded nonadditive cooked native ACL animation; raw or missing-codec fallback forbidden.")); }
    if (ReceivingMesh && (ReceivingMesh->Skeleton!=ReceivingSkeleton || !ReceivingSkeleton->IsCompatibleMesh(ReceivingMesh)))
    { return Fail(TEXT("Optional receiving mesh must keep its genuine skeleton and pass its owner's strict native hierarchy check.")); }
    const auto& SourceRef = SourceSkeleton->GetReferenceSkeleton();
    const auto& TargetRef = ReceivingMesh ? ReceivingMesh->RefSkeleton : ReceivingSkeleton->GetReferenceSkeleton();
    const auto& Tracks = Sequence->GetCompressedTrackToSkeletonMapTable();
    if (Tracks.Num()<1 || Tracks.Num()>65535 || Tracks[0].BoneTreeIndex!=0 || int64(SampleCount)*(SourceRef.GetNum()+TargetRef.GetNum())>2000000)
    { return Fail(TEXT("Unsupported compressed map/root layout or bounded sample limit.")); }
    TSet<int32> SourceTrackBones;
    TArray<int32> TrackBoneSnapshot;
    for (const auto& Track : Tracks)
    {
        if (!SourceRef.IsValidIndex(Track.BoneTreeIndex) || SourceTrackBones.Contains(Track.BoneTreeIndex))
        { return Fail(TEXT("Invalid or duplicate original compressed track skeleton index.")); }
        SourceTrackBones.Add(Track.BoneTreeIndex); TrackBoneSnapshot.Add(Track.BoneTreeIndex);
    }
    const bool bForeign = SourceSkeleton!=ReceivingSkeleton;
    const auto Mapping = bForeign ? RebirthSkeletonCompatibility::FindMapping(SourceSkeleton, ReceivingSkeleton) : nullptr;
    if (bForeign && Mapping.IsValid()!=bExpectRegistered) { return Fail(TEXT("Current registration state differs from probe expectation.")); }
    if (SourceSkeleton->IsCompatible(ReceivingSkeleton) != (!bForeign || bExpectRegistered))
    { return Fail(TEXT("Direct native USkeleton::IsCompatible disagrees with registration; check stale inline/COMDAT bodies and staged header build.")); }
    FBoneContainer SourceBones, TargetBones;
    if (!SetupBones(*SourceSkeleton,SourceRef,SourceBones) ||
        !SetupBones(ReceivingMesh ? static_cast<UObject&>(*ReceivingMesh) : static_cast<UObject&>(*ReceivingSkeleton),TargetRef,TargetBones))
    { return Fail(TEXT("Cannot create bounded native source and receiving bone containers.")); }
    const FSkeletonSnapshot SourceSnapshot(SourceSkeleton), TargetSnapshot(ReceivingSkeleton);
    const FString SourceDigest=Digest(Sequence), BeforeDiagnostic=RebirthSkeletonCompatibility::GetDiagnostics();
    const bool bSourceDirty=Sequence->GetOutermost()->IsDirty();
    const int32 NotifyCount=Sequence->Notifies.Num();
    const FTransform FullRootMotion=Sequence->ExtractRootMotionFromRange(0,Sequence->SequenceLength);
    Report->SetStringField(TEXT("source_animation"),Sequence->GetPathName());
    Report->SetStringField(TEXT("source_skeleton"),SourceSkeleton->GetPathName());
    Report->SetStringField(TEXT("receiving_skeleton"),ReceivingSkeleton->GetPathName());
    Report->SetStringField(TEXT("receiving_mesh"),ReceivingMesh ? ReceivingMesh->GetPathName() : TEXT(""));
    Report->SetStringField(TEXT("codec_class"),Sequence->CompressedData.BoneCompressionCodec->GetClass()->GetPathName());
    Report->SetStringField(TEXT("source_compressed_sha1"),SourceDigest);
    Report->SetStringField(TEXT("diagnostics_before"),BeforeDiagnostic);
    Report->SetStringField(TEXT("sampling_route"),TEXT("Original UAnimSequence::GetAnimationPose receiving FBoneContainer vs original source GetBoneTransform(track,time,false); no output animation exists."));
    Report->SetNumberField(TEXT("source_skeleton_bones"),SourceRef.GetNum());
    Report->SetNumberField(TEXT("receiving_skeleton_bones"),ReceivingSkeleton->GetReferenceSkeleton().GetNum());
    Report->SetNumberField(TEXT("receiving_compact_bones"),TargetBones.GetCompactPoseNumBones());
    Report->SetNumberField(TEXT("original_compressed_track_count"),Tracks.Num());
    Report->SetNumberField(TEXT("same_name_pair_mappings"),Mapping.IsValid() ? Mapping->SharedNames : (bForeign ? 0 : SourceRef.GetNum()));
    Report->SetNumberField(TEXT("parent_chain_differences_reported_not_corrected"),Mapping.IsValid() ? Mapping->ParentChainDifferences : 0);
    Report->SetBoolField(TEXT("expect_registered"),bExpectRegistered);
    FTransform FirstFrame;
    Sequence->GetBoneTransform(FirstFrame,0,0,false);
    FError SourceIdentity, Destination, Fallback, Component, RootMotion;
    FError NativeRetargetedSourceIdentity, ActualSampleMotion, ActualVsReferencePose;
    TArray<FTransform> FirstActual;
    FString FirstActualDigest;bool bActualDigestChanged=false;
    TArray<FError> RawTrackErrors, ExistingTrackErrors, NativeRetargetedTrackErrors;
    RawTrackErrors.SetNum(Tracks.Num());ExistingTrackErrors.SetNum(Tracks.Num());NativeRetargetedTrackErrors.SetNum(Tracks.Num());
    TArray<TSharedPtr<FJsonObject>> FirstTrackTransforms;FirstTrackTransforms.SetNum(Tracks.Num());
    Report->SetBoolField(TEXT("sequence_enable_root_motion"),Sequence->bEnableRootMotion);
    Report->SetBoolField(TEXT("sequence_force_root_lock"),Sequence->bForceRootLock);
    Report->SetNumberField(TEXT("sequence_root_lock_mode"),int32(Sequence->RootMotionRootLock));
    Report->SetStringField(TEXT("sequence_retarget_source"),Sequence->RetargetSource.ToString());
    Report->SetBoolField(TEXT("sequence_only_use_raw_data"),Sequence->OnlyUseRawData());
    Report->SetStringField(TEXT("sequence_skeleton_virtual_bone_guid"),Sequence->GetSkeletonVirtualBoneGuid().ToString(EGuidFormats::Digits));
    Report->SetStringField(TEXT("skeleton_virtual_bone_guid"),SourceSkeleton->GetVirtualBoneGuid().ToString(EGuidFormats::Digits));
    Report->SetBoolField(TEXT("sequence_skeleton_virtual_bone_guid_matches"),Sequence->GetSkeletonVirtualBoneGuid()==SourceSkeleton->GetVirtualBoneGuid());
    Report->SetNumberField(TEXT("raw_track_to_skeleton_map_count"),Sequence->GetRawTrackToSkeletonMapTable().Num());
    Report->SetNumberField(TEXT("raw_animation_track_count"),Sequence->GetRawAnimationData().Num());
    Report->SetBoolField(TEXT("has_source_raw_data"),Sequence->HasSourceRawData());
    Report->SetBoolField(TEXT("source_container_should_use_raw_data"),SourceBones.ShouldUseRawData());
    Report->SetBoolField(TEXT("source_container_should_use_source_data"),SourceBones.ShouldUseSourceData());
    Report->SetBoolField(TEXT("target_container_should_use_raw_data"),TargetBones.ShouldUseRawData());
    Report->SetBoolField(TEXT("target_container_should_use_source_data"),TargetBones.ShouldUseSourceData());
    Report->SetBoolField(TEXT("source_UseRawDataForPoseExtraction"),Sequence->UseRawDataForPoseExtraction(SourceBones));
    Report->SetBoolField(TEXT("target_UseRawDataForPoseExtraction"),Sequence->UseRawDataForPoseExtraction(TargetBones));
    Report->SetBoolField(TEXT("source_container_disable_retargeting"),SourceBones.GetDisableRetargeting());
    Report->SetBoolField(TEXT("target_container_disable_retargeting"),TargetBones.GetDisableRetargeting());
    Report->SetObjectField(TEXT("source_reference_root"),TransformJson(SourceBones.GetRefPoseTransform(FCompactPoseBoneIndex(0))));
    Report->SetObjectField(TEXT("decoded_first_root_track"),TransformJson(FirstFrame));
    TArray<FTransform> SourceLocal,Actual,Expected,ExpectedCS,ActualCS,FirstExpected;
    TSet<int32> WrittenDestinations;
    bool bNonconstant=false;
    int32 IgnoredSourceTracks=0;
    for (int32 Sample=0; Sample<SampleCount; ++Sample)
    {
        const float Time=Sequence->SequenceLength*float(Sample)/float(SampleCount-1);
        if (!Extract(Sequence,SourceBones,Time,SourceLocal) || !Extract(Sequence,TargetBones,Time,Actual))
        { return Fail(TEXT("Native original pose extraction returned invalid transforms.")); }
        if(Sample==0){FirstActual=Actual;FirstActualDigest=CanonicalPoseDigest(Actual);}
        else{bActualDigestChanged|=CanonicalPoseDigest(Actual)!=FirstActualDigest;}
        for(int32 Bone=0;Bone<Actual.Num();++Bone)
        {
            if(!ActualSampleMotion.Add(FirstActual[Bone],Actual[Bone]) ||
                !ActualVsReferencePose.Add(TargetBones.GetRefPoseTransform(FCompactPoseBoneIndex(Bone)),Actual[Bone]))
            {return Fail(TEXT("Actual native pose motion/reference diagnostic became nonfinite."));}
        }
        Expected.SetNum(Actual.Num());
        for (int32 Bone=0; Bone<Expected.Num(); ++Bone) { Expected[Bone]=TargetBones.GetRefPoseTransform(FCompactPoseBoneIndex(Bone)); }
        WrittenDestinations.Reset();
        for (int32 Track=0; Track<Tracks.Num(); ++Track)
        {
            const int32 SourceIndex=Tracks[Track].BoneTreeIndex;
            FTransform Decoded;
            Sequence->GetBoneTransform(Decoded,Track,Time,false); // Original SOURCE codec track index.
            if (!Decoded.IsValid()) { return Fail(TEXT("Original compressed single-bone decoder returned invalid data.")); }
            const FCompactPoseBoneIndex SourceCompact=SourceBones.GetCompactPoseIndexFromSkeletonIndex(SourceIndex);
            FTransform SourceExpected=Decoded;
            if (SourceIndex==0) { ApplyOriginalRootLock(Sequence,SourceBones,FirstFrame,SourceExpected); }
            if (SourceCompact==INDEX_NONE || !SourceIdentity.Add(SourceExpected,SourceLocal[SourceCompact.GetInt()]))
            { return Fail(TEXT("Native source identity comparison failed or became nonfinite.")); }
            // Diagnostic alternative reproduces documented native semantic transforms
            // after original single-track codec decode; original pass/fail gate is unchanged.
            FTransform NativeSemantic=Decoded;
            FAnimationRuntime::RetargetBoneTransform(SourceSkeleton,Sequence->RetargetSource,NativeSemantic,SourceIndex,SourceCompact,SourceBones,false);
            if(SourceIndex==0){ApplyOriginalRootLock(Sequence,SourceBones,FirstFrame,NativeSemantic);}
            const FTransform& ActualSource=SourceLocal[SourceCompact.GetInt()];
            if(!RawTrackErrors[Track].Add(Decoded,ActualSource) || !ExistingTrackErrors[Track].Add(SourceExpected,ActualSource) ||
                !NativeRetargetedTrackErrors[Track].Add(NativeSemantic,ActualSource) || !NativeRetargetedSourceIdentity.Add(NativeSemantic,ActualSource))
            {return Fail(TEXT("Bounded per-track source diagnostic became nonfinite."));}
            if(Sample==0)
            {
                auto Values=MakeShared<FJsonObject>();
                Values->SetObjectField(TEXT("raw_original_codec"),TransformJson(Decoded));
                Values->SetObjectField(TEXT("existing_root_locked_expected"),TransformJson(SourceExpected));
                Values->SetObjectField(TEXT("native_retargeted_and_root_locked_expected"),TransformJson(NativeSemantic));
                Values->SetObjectField(TEXT("actual_source_GetAnimationPose"),TransformJson(ActualSource));
                FirstTrackTransforms[Track]=Values;
            }
            if (bForeign && !bExpectRegistered) { continue; }
            const int32 TargetIndex=Mapping.IsValid() ? Mapping->Remap(SourceIndex) : SourceIndex;
            const FCompactPoseBoneIndex TargetCompact=TargetIndex==INDEX_NONE ? FCompactPoseBoneIndex(INDEX_NONE) :
                TargetBones.GetCompactPoseIndexFromSkeletonIndex(TargetIndex);
            if (TargetCompact==INDEX_NONE) { if(Sample==0){++IgnoredSourceTracks;} continue; }
            if (WrittenDestinations.Contains(TargetCompact.GetInt())) { return Fail(TEXT("Multiple source tracks unexpectedly write one destination.")); }
            WrittenDestinations.Add(TargetCompact.GetInt());
            if (SourceIndex==0) { ApplyOriginalRootLock(Sequence,TargetBones,FirstFrame,Decoded); }
            Expected[TargetCompact.GetInt()]=Decoded;
        }
        if(Sample==0) { FirstExpected=Expected; }
        for (int32 Bone=0; Bone<Actual.Num(); ++Bone)
        {
            if (!Destination.Add(Expected[Bone],Actual[Bone])) { return Fail(TEXT("Nonfinite receiving local-pose error.")); }
            if (!WrittenDestinations.Contains(Bone) && !Fallback.Add(Expected[Bone],Actual[Bone]))
            { return Fail(TEXT("Nonfinite receiver reference-pose fallback error.")); }
            if (Sample>0 && WrittenDestinations.Contains(Bone) &&
                (!FirstExpected[Bone].GetTranslation().Equals(Expected[Bone].GetTranslation(),0.0001f) ||
                 !FirstExpected[Bone].GetRotation().Equals(Expected[Bone].GetRotation(),0.00001f))) { bNonconstant=true; }
        }
        if(!ComponentPose(TargetBones,Expected,ExpectedCS) || !ComponentPose(TargetBones,Actual,ActualCS))
        { return Fail(TEXT("Invalid receiving-parent component-space accumulation.")); }
        for(int32 Bone=0; Bone<ActualCS.Num(); ++Bone)
        { if(!Component.Add(ExpectedCS[Bone],ActualCS[Bone])) { return Fail(TEXT("Nonfinite receiving component-pose error.")); } }
    }
    bool bTrackMapUnchanged=Tracks.Num()==TrackBoneSnapshot.Num();
    for(int32 Track=0; bTrackMapUnchanged && Track<Tracks.Num(); ++Track)
    { bTrackMapUnchanged=Tracks[Track].BoneTreeIndex==TrackBoneSnapshot[Track]; }
    const bool bOriginalsUnchanged=SourceSnapshot.Unchanged() && TargetSnapshot.Unchanged() && bTrackMapUnchanged &&
        Sequence->GetSkeleton()==SourceSkeleton && SourceDigest==Digest(Sequence) && Sequence->GetOutermost()->IsDirty()==bSourceDirty &&
        Sequence->Notifies.Num()==NotifyCount && (!ReceivingMesh || ReceivingMesh->Skeleton==ReceivingSkeleton);
    RootMotion.Add(FullRootMotion,Sequence->ExtractRootMotionFromRange(0,Sequence->SequenceLength));
    const FString AfterDiagnostic=RebirthSkeletonCompatibility::GetDiagnostics();
    Report->SetStringField(TEXT("diagnostics_after"),AfterDiagnostic);
    Report->SetObjectField(TEXT("source_native_pose_vs_original_codec_tracks"),SourceIdentity.Report());
    Report->SetObjectField(TEXT("diagnostic_native_retargeted_source_identity"),NativeRetargetedSourceIdentity.Report());
    TArray<int32> ErrorTracks;
    for(int32 Track=0;Track<Tracks.Num();++Track)
    {if(Track==0 || !ExistingTrackErrors[Track].Passed()){ErrorTracks.Add(Track);}}
    ErrorTracks.Sort([&](int32 A,int32 B)
    {
        if(A==0 || B==0){return A==0 && B!=0;}
        const double ScoreA=FMath::Max(ExistingTrackErrors[A].Position/0.001,ExistingTrackErrors[A].Radians/0.0001);
        const double ScoreB=FMath::Max(ExistingTrackErrors[B].Position/0.001,ExistingTrackErrors[B].Radians/0.0001);
        return ScoreA==ScoreB?A<B:ScoreA>ScoreB;
    });
    Report->SetNumberField(TEXT("source_tracks_with_existing_gate_error"),ErrorTracks.Num()-(ExistingTrackErrors[0].Passed()?1:0));
    TArray<TSharedPtr<FJsonValue>> TrackDetails;
    for(int32 Rank=0;Rank<FMath::Min(32,ErrorTracks.Num());++Rank)
    {
        const int32 Track=ErrorTracks[Rank],SourceIndex=Tracks[Track].BoneTreeIndex;
        auto Detail=MakeShared<FJsonObject>();
        Detail->SetNumberField(TEXT("track_index"),Track);Detail->SetNumberField(TEXT("source_skeleton_index"),SourceIndex);
        Detail->SetStringField(TEXT("source_bone_name"),SourceRef.GetBoneName(SourceIndex).ToString());
        Detail->SetNumberField(TEXT("source_translation_retargeting_mode"),int32(SourceSkeleton->GetBoneTranslationRetargetingMode(SourceIndex)));
        Detail->SetObjectField(TEXT("raw_codec_vs_native"),RawTrackErrors[Track].Report());
        Detail->SetObjectField(TEXT("existing_root_lock_oracle_vs_native"),ExistingTrackErrors[Track].Report());
        Detail->SetObjectField(TEXT("native_retarget_and_root_lock_oracle_vs_native"),NativeRetargetedTrackErrors[Track].Report());
        Detail->SetObjectField(TEXT("first_sample_transforms"),FirstTrackTransforms[Track].ToSharedRef());
        TrackDetails.Add(MakeShared<FJsonValueObject>(Detail));
    }
    Report->SetArrayField(TEXT("bounded_source_track_errors_root_then_worst32"),TrackDetails);
    Report->SetStringField(TEXT("diagnostic_scope"),TEXT("Root first, then worst31 failed source tracks; original strict tolerances and all pass/fail gates unchanged. Native retarget helper comparison is diagnostic only."));

    Report->SetObjectField(TEXT("receiving_native_local_pose"),Destination.Report());
    Report->SetObjectField(TEXT("unwritten_receiving_bones_refpose"),Fallback.Report(true));
    Report->SetObjectField(TEXT("receiving_component_pose_from_target_parents"),Component.Report());
    Report->SetObjectField(TEXT("original_root_motion_unchanged"),RootMotion.Report());
    Report->SetNumberField(TEXT("mapped_compressed_tracks"),WrittenDestinations.Num());
    Report->SetNumberField(TEXT("ignored_source_tracks_or_missing_receiver_compact_bones"),IgnoredSourceTracks);
    Report->SetBoolField(TEXT("original_source_and_skeletons_unchanged"),bOriginalsUnchanged);
    Report->SetBoolField(TEXT("native_mapped_motion_nonconstant"),bNonconstant);
    const bool bActualNonconstant=ActualSampleMotion.Position>0.001 || ActualSampleMotion.Radians>0.0001;
    Report->SetBoolField(TEXT("native_actual_pose_motion_nonconstant"),bActualNonconstant);
    Report->SetBoolField(TEXT("native_actual_pose_canonical_digest_changed"),bActualDigestChanged);
    Report->SetStringField(TEXT("native_actual_first_pose_sha1"),FirstActualDigest);
    Report->SetObjectField(TEXT("native_actual_sample_motion"),ActualSampleMotion.Report());
    Report->SetObjectField(TEXT("native_actual_vs_receiver_refpose"),ActualVsReferencePose.Report());
    Report->SetBoolField(TEXT("native_source_only_ignored_target_only_refpose"),Destination.Passed() && (Fallback.Count==0 || Fallback.Passed()));
    Report->SetBoolField(TEXT("source_track_ids_preserved"),bTrackMapUnchanged);
    Report->SetStringField(TEXT("evidence_limit"),TEXT("Both native routes use the same original ACL codec; this is destination-mapping validation, not independent retail playback proof. Curves are disabled; custom attributes and side-effect ticks require separate gates."));
    const bool bPassed=SourceIdentity.Passed() && Destination.Passed() && Component.Passed() && RootMotion.Passed() &&
        (Fallback.Count==0 || Fallback.Passed()) && bOriginalsUnchanged &&
        ((!bForeign || bExpectRegistered) ? (bNonconstant && bActualNonconstant && bActualDigestChanged) : BeforeDiagnostic!=AfterDiagnostic);
    Report->SetBoolField(TEXT("succeeded"),bPassed);
    if(!bPassed){Report->SetStringField(TEXT("error"),TEXT("A recorded native comparison, nonconstant-motion, immutability or unregistered-refusal gate failed."));}
    return Json(Report);
}
