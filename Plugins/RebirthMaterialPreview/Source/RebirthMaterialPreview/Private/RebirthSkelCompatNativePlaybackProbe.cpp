// Owned diagnostic only. No reflected types, asset conversion, saves, or game hooks.
#include "CoreMinimal.h"
#include <cmath>
#include "RebirthSkeletonCompatibilityEditorLibrary.h"
#include "Animation/AnimBoneCompressionCodec.h"
#include "Animation/AnimCompressionTypes.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimSingleNodeInstance.h"
#include "Animation/AnimationPoseData.h"
#include "Animation/CustomAttributesRuntime.h"
#include "Animation/RebirthSkeletonCompatibility.h"
#include "Animation/Skeleton.h"
#include "BoneContainer.h"
#include "BonePose.h"
#include "Components/SkeletalMeshComponent.h"
#include "Dom/JsonObject.h"
#include "Engine/Engine.h"
#include "Engine/SkeletalMesh.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformProcess.h"
#include "Misc/CommandLine.h"
#include "Misc/CoreMisc.h"
#include "Misc/FileHelper.h"
#include "Misc/MemStack.h"
#include "Misc/Parse.h"
#include "Misc/Paths.h"
#include "Misc/SecureHash.h"
#include "PreviewScene.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "UObject/GarbageCollection.h"
#include "UObject/Package.h"
#include "UObject/StrongObjectPtr.h"

namespace RebirthOwnedSingleNodePlayback
{
    static const TCHAR* MeshPath=TEXT("/Game/Character/Player/PC0010_00_Sephiroth_Standard/Model/PC0010_00.PC0010_00");
    static const TCHAR* SephPath=TEXT("/Game/Motion/Player/PC0010_Sephiroth/Neutral00/N_Idle01_1.N_Idle01_1");
    static const TCHAR* CloudPath=TEXT("/Game/Motion/Player/PC0000_Cloud/Neutral00/N_Idle01_1.N_Idle01_1");

    FString Json(const TSharedRef<FJsonObject>& Report)
    {
        FString Text;
        FJsonSerializer::Serialize(Report,TJsonWriterFactory<>::Create(&Text));
        return Text;
    }
    bool Save(const TSharedRef<FJsonObject>& Report)
    {
        const FString Directory=FPaths::ProjectSavedDir()/TEXT("SkelCompatNativePlayback");
        IFileManager::Get().MakeDirectory(*Directory,true);
        return FFileHelper::SaveStringToFile(Json(Report),*(Directory/TEXT("Result.json")),FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
    }
    FString RefDigest(const FReferenceSkeleton& Ref)
    {
        FSHA1 Hash;
        for(int32 Index=0;Index<Ref.GetNum();++Index)
        {
            const FString Name=Ref.GetBoneName(Index).ToString();
            Hash.Update(reinterpret_cast<const uint8*>(*Name),Name.Len()*sizeof(TCHAR));
            const int32 Parent=Ref.GetParentIndex(Index);
            Hash.Update(reinterpret_cast<const uint8*>(&Parent),sizeof(Parent));
        }
        const auto& Poses=Ref.GetRefBonePose();
        Hash.Update(reinterpret_cast<const uint8*>(Poses.GetData()),Poses.Num()*sizeof(FTransform));
        Hash.Final();uint8 Bytes[20];Hash.GetHash(Bytes);
        return BytesToHex(Bytes,20).ToLower();
    }
    FString CompressedDigest(const UAnimSequence* Sequence)
    {
        const auto& Bytes=Sequence->CompressedData.CompressedByteStream;
        uint8 Hash[20];FSHA1::HashBuffer(Bytes.GetData(),Bytes.Num(),Hash);
        return BytesToHex(Hash,20).ToLower();
    }
    struct FOriginals
    {
        USkeletalMesh* Mesh;
        UAnimSequence* Sequence;
        USkeleton* MeshSkeleton;
        USkeleton* SourceSkeleton;
        FString MeshRef,TargetRef,SourceRef,Compressed;
        FGuid TargetGuid,SourceGuid;
        bool MeshDirty,SequenceDirty,TargetDirty,SourceDirty;
        int32 NotifyCount;
        TArray<int32> TrackIds;
        TArray<UMaterialInterface*> Materials;
        explicit FOriginals(USkeletalMesh* InMesh,UAnimSequence* InSequence)
            :Mesh(InMesh),Sequence(InSequence),MeshSkeleton(InMesh->Skeleton),SourceSkeleton(InSequence->GetSkeleton()),
             MeshRef(RefDigest(InMesh->RefSkeleton)),TargetRef(RefDigest(MeshSkeleton->GetReferenceSkeleton())),
             SourceRef(RefDigest(SourceSkeleton->GetReferenceSkeleton())),Compressed(CompressedDigest(InSequence)),
             TargetGuid(MeshSkeleton->GetGuid()),SourceGuid(SourceSkeleton->GetGuid()),
             MeshDirty(InMesh->GetOutermost()->IsDirty()),SequenceDirty(InSequence->GetOutermost()->IsDirty()),
             TargetDirty(MeshSkeleton->GetOutermost()->IsDirty()),SourceDirty(SourceSkeleton->GetOutermost()->IsDirty()),
             NotifyCount(InSequence->Notifies.Num())
        {
            for(const auto& Track:Sequence->GetCompressedTrackToSkeletonMapTable()){TrackIds.Add(Track.BoneTreeIndex);}
            for(const auto& Material:Mesh->Materials){Materials.Add(Material.MaterialInterface);}
        }
        bool Unchanged() const
        {
            bool bGood=Mesh->Skeleton==MeshSkeleton && Sequence->GetSkeleton()==SourceSkeleton &&
                MeshRef==RefDigest(Mesh->RefSkeleton) && TargetRef==RefDigest(MeshSkeleton->GetReferenceSkeleton()) &&
                SourceRef==RefDigest(SourceSkeleton->GetReferenceSkeleton()) && Compressed==CompressedDigest(Sequence) &&
                TargetGuid==MeshSkeleton->GetGuid() && SourceGuid==SourceSkeleton->GetGuid() &&
                MeshDirty==Mesh->GetOutermost()->IsDirty() && SequenceDirty==Sequence->GetOutermost()->IsDirty() &&
                TargetDirty==MeshSkeleton->GetOutermost()->IsDirty() && SourceDirty==SourceSkeleton->GetOutermost()->IsDirty() &&
                NotifyCount==Sequence->Notifies.Num() && TrackIds.Num()==Sequence->GetCompressedTrackToSkeletonMapTable().Num() &&
                Materials.Num()==Mesh->Materials.Num();
            for(int32 Index=0;bGood && Index<TrackIds.Num();++Index)
            {bGood=TrackIds[Index]==Sequence->GetCompressedTrackToSkeletonMapTable()[Index].BoneTreeIndex;}
            for(int32 Index=0;bGood && Index<Materials.Num();++Index)
            {bGood=Materials[Index]==Mesh->Materials[Index].MaterialInterface;}
            return bGood;
        }
    };
    bool GenuineSequence(UAnimSequence* Sequence)
    {
        return IsValid(Sequence) && Sequence->GetClass()==UAnimSequence::StaticClass() &&
            !Sequence->HasAnyFlags(RF_NeedLoad|RF_NeedPostLoad) && IsValid(Sequence->GetSkeleton()) &&
            !Sequence->IsValidAdditive() && !Sequence->OnlyUseRawData() && Sequence->IsCompressedDataValid() &&
            Sequence->CompressedData.CompressedDataStructure && Sequence->CompressedData.CompressedDataStructure->IsValid() &&
            Sequence->CompressedData.BoneCompressionCodec &&
            Sequence->CompressedData.BoneCompressionCodec->GetClass()->GetPathName()==TEXT("/Script/ACLPlugin.AnimBoneCompressionCodec_ACL") &&
            Sequence->CompressedData.CompressedByteStream.Num()>0 &&
            Sequence->CompressedData.CompressedByteStream.Num()<=268435456 && Sequence->SequenceLength>2.1f &&
            FMath::IsFinite(Sequence->SequenceLength) && Sequence->Notifies.Num()==0 &&
            (Sequence->GetOutermost()->GetPackageFlags()&PKG_Cooked);
    }
    bool ValidPose(const TArray<FTransform>& Pose,int32 Expected)
    {
        if(Pose.Num()!=Expected || Expected<1 || Expected>65535){return false;}
        for(const FTransform& Bone:Pose)
        {if(!Bone.IsValid() || !Bone.IsRotationNormalized()){return false;}}
        return true;
    }
    double RotationDifference(const FTransform& A,const FTransform& B)
    {
        const FQuat QA=A.GetRotation(),QB=B.GetRotation();
        // acos(dot) reports nonzero motion for the SAME finite near-unit quaternion.
        // q and -q encode the same orientation. Exact equality must give exact zero.
        if((QA.X==QB.X && QA.Y==QB.Y && QA.Z==QB.Z && QA.W==QB.W) ||
           (QA.X==-QB.X && QA.Y==-QB.Y && QA.Z==-QB.Z && QA.W==-QB.W)){return 0.0;}
        const double AX=QA.X,AY=QA.Y,AZ=QA.Z,AW=QA.W;
        const double BX=QB.X,BY=QB.Y,BZ=QB.Z,BW=QB.W;
        const double DX=AW*BX-AX*BW-AY*BZ+AZ*BY;
        const double DY=AW*BY+AX*BZ-AY*BW-AZ*BX;
        const double DZ=AW*BZ-AX*BY+AY*BX-AZ*BW;
        const double DW=AW*BW+AX*BX+AY*BY+AZ*BZ;
        return 2.0*std::atan2(std::sqrt(DX*DX+DY*DY+DZ*DZ),std::abs(DW));
    }
    FString RequiredPoseDigest(const TArray<FTransform>& Pose,const TArray<int32>& Required)
    {
        FSHA1 Hash;
        for(int32 Bone:Required)
        {
            const FTransform& Transform=Pose[Bone];
            const FVector Translation=Transform.GetTranslation(),Scale=Transform.GetScale3D();
            const FQuat Rotation=Transform.GetRotation();
            // Hash explicit components, never FTransform padding or unused bones.
            const float Values[]={Translation.X,Translation.Y,Translation.Z,
                Rotation.X,Rotation.Y,Rotation.Z,Rotation.W,Scale.X,Scale.Y,Scale.Z};
            Hash.Update(reinterpret_cast<const uint8*>(&Bone),sizeof(Bone));
            Hash.Update(reinterpret_cast<const uint8*>(Values),sizeof(Values));
        }
        Hash.Final();uint8 Bytes[20];Hash.GetHash(Bytes);
        return BytesToHex(Bytes,20).ToLower();
    }

    TSharedRef<FJsonObject> RunCase(USkeletalMesh* Mesh,UAnimSequence* Sequence,bool bAccept,const TCHAR* Label)
    {
        auto Report=MakeShared<FJsonObject>();
        Report->SetStringField(TEXT("label"),Label);
        Report->SetStringField(TEXT("original_animation"),Sequence->GetPathName());
        Report->SetStringField(TEXT("original_mesh"),Mesh->GetPathName());
        Report->SetBoolField(TEXT("expected_acceptance"),bAccept);
        Report->SetBoolField(TEXT("succeeded"),false);
        const FOriginals Originals(Mesh,Sequence);
        // A hidden CPU fixture uses the real owner skeleton and real mesh buffers.
        // No actor factory, mesh duplicate, physics scene, texture residency or post-process AnimBP.
        FPreviewScene Scene(FPreviewScene::ConstructionValues().SetEditor(true).SetTransactional(false)
            .SetCreateDefaultLighting(false).SetCreatePhysicsScene(false).ShouldSimulatePhysics(false)
            .AllowAudioPlayback(false).SetForceMipsResident(false));
        TStrongObjectPtr<USkeletalMeshComponent> Component(NewObject<USkeletalMeshComponent>(GetTransientPackage(),NAME_None,RF_Transient));
        bool bAdded=false;
        FString Error;
        auto Body=[&]() -> bool
        {
            Component->SetVisibility(false);
            Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            Component->bDisableClothSimulation=true;
            Component->SetDisablePostProcessBlueprint(true);
            Component->bEnableUpdateRateOptimizations=false;
            Component->VisibilityBasedAnimTickOption=EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
            Component->SetAllowAnimCurveEvaluation(false);
            Component->SetForcedLOD(1);
            Component->SetSkeletalMesh(Mesh);
            Scene.AddComponent(Component.Get(),FTransform::Identity);bAdded=true;
            Component->SetUpdateAnimationInEditor(true);
            if(!Component->IsRegistered() || Component->GetNumComponentSpaceTransforms()!=Mesh->RefSkeleton.GetNum())
            {Error=TEXT("Registered component did not allocate real mesh transform buffers.");return false;}
            Component->PlayAnimation(Sequence,true);
            UAnimSingleNodeInstance* Instance=Component->GetSingleNodeInstance();
            if(!IsValid(Instance)){Error=TEXT("PlayAnimation did not create a native AnimSingleNodeInstance.");return false;}
            Report->SetBoolField(TEXT("assigned_original_asset_retained"),Instance->GetAnimationAsset()==Sequence);
            if((Instance->GetAnimationAsset()==Sequence)!=bAccept)
            {Error=TEXT("Native single-node asset acceptance differs from registered-pair expectation.");return false;}
            Instance->SetPosition(0.0f,false);
            Component->TickAnimation(0.0f,false);
            Component->RefreshBoneTransforms(nullptr); // Null tick function forces synchronous evaluation.
            TArray<FTransform> Initial=Component->GetBoneSpaceTransforms();
            TArray<FTransform> InitialCS=Component->GetComponentSpaceTransforms();
            if(!ValidPose(Initial,Mesh->RefSkeleton.GetNum()) || !ValidPose(InitialCS,Mesh->RefSkeleton.GetNum()))
            {Error=TEXT("Initial real component local/component pose is incomplete or invalid.");return false;}
            TArray<int32> RequiredMeshBones;
            const FBoneContainer& InitialBones=Instance->GetRequiredBones();
            if(!InitialBones.IsValid() || InitialBones.GetCompactPoseNumBones()<1)
            {Error=TEXT("Native single-node instance has no valid receiving required-bone container.");return false;}
            for(int32 Compact=0;Compact<InitialBones.GetCompactPoseNumBones();++Compact)
            {
                const int32 MeshBone=InitialBones.MakeMeshPoseIndex(FCompactPoseBoneIndex(Compact)).GetInt();
                if(!Initial.IsValidIndex(MeshBone) || RequiredMeshBones.Contains(MeshBone))
                {Error=TEXT("Native receiving required-bone mesh indices are invalid or duplicated.");return false;}
                RequiredMeshBones.Add(MeshBone);
            }
            for(int32 MeshBone:RequiredMeshBones)
            {
                const int32 Parent=Mesh->RefSkeleton.GetParentIndex(MeshBone);
                if(Parent!=INDEX_NONE && !RequiredMeshBones.Contains(Parent))
                {Error=TEXT("Native receiving required-bone set is not parent closed.");return false;}
            }
            double MaxMotion=0,MaxRotation=0,MaxOraclePosition=0,MaxOracleRotation=0,MaxParentError=0;
            int32 Compared=0,ChangedComponentPoseSamples=0;
            const FString InitialRequiredPose=RequiredPoseDigest(InitialCS,RequiredMeshBones);
            FString FinalRequiredPose=InitialRequiredPose;
            TSet<FString> DistinctRequiredPoses;DistinctRequiredPoses.Add(InitialRequiredPose);
            float LastTime=Instance->GetCurrentTime();
            const float InitialTime=LastTime;
            for(int32 Frame=0;Frame<120;++Frame)
            {
                Component->TickAnimation(1.0f/60.0f,false);
                Component->RefreshBoneTransforms(nullptr);
                Instance=Component->GetSingleNodeInstance();
                if(!IsValid(Instance) || ((Instance->GetAnimationAsset()==Sequence)!=bAccept) || Component->SkeletalMesh!=Mesh || Mesh->Skeleton!=Originals.MeshSkeleton)
                {Error=TEXT("Original asset, native instance or genuine mesh skeleton changed during playback.");return false;}
                const auto Local=Component->GetBoneSpaceTransforms();
                const auto CS=Component->GetComponentSpaceTransforms();
                if(!ValidPose(Local,Initial.Num()) || !ValidPose(CS,InitialCS.Num()))
                {Error=TEXT("Playback produced incomplete, nonfinite or nonnormalized real component transforms.");return false;}
                const float Time=Instance->GetCurrentTime();
                if(!FMath::IsFinite(Time) || (bAccept && Time<=LastTime))
                {Error=TEXT("Native playback time did not advance on fixed animation ticks.");return false;}
                LastTime=Time;
                FinalRequiredPose=RequiredPoseDigest(CS,RequiredMeshBones);
                DistinctRequiredPoses.Add(FinalRequiredPose);
                if(FinalRequiredPose!=InitialRequiredPose){++ChangedComponentPoseSamples;}
                // FillComponentSpaceTransforms updates required bones only. Unrequired
                // buffer entries remain finite but are not a current-pose CS oracle.
                for(int32 Bone:RequiredMeshBones)
                {
                    MaxMotion=FMath::Max(MaxMotion,double(FVector::Dist(InitialCS[Bone].GetTranslation(),CS[Bone].GetTranslation())));
                    MaxRotation=FMath::Max(MaxRotation,double(RotationDifference(InitialCS[Bone],CS[Bone])));
                    const int32 Parent=Mesh->RefSkeleton.GetParentIndex(Bone);
                    FTransform ExpectedCS=Parent==INDEX_NONE?Local[Bone]:Local[Bone]*CS[Parent];ExpectedCS.NormalizeRotation();
                    MaxParentError=FMath::Max(MaxParentError,double(FVector::Dist(ExpectedCS.GetTranslation(),CS[Bone].GetTranslation())));
                }
                if(bAccept && (Frame%15==0 || Frame==119))
                {
                    // Oracle compares component playback against the original sequence's
                    // native extraction using the SAME receiving required-bones container.
                    // The separate pose oracle compares those destinations to source codec tracks.
                    FMemMark Mark(FMemStack::Get());
                    const FBoneContainer& Bones=Instance->GetRequiredBones();
                    FCompactPose Pose;Pose.SetBoneContainer(&Bones);Pose.ResetToRefPose();
                    FBlendedCurve Curves;Curves.InitFrom(Bones);
                    FStackCustomAttributes Attributes;
                    FAnimationPoseData Data(Pose,Curves,Attributes);
                    // Match FAnimNode_SingleNode's original root-motion extraction flag.
                    Sequence->GetAnimationPose(Data,FAnimExtractContext(Time,Sequence->bEnableRootMotion));
                    for(int32 Compact=0;Compact<Pose.GetNumBones();++Compact)
                    {
                        const int32 MeshBone=Bones.MakeMeshPoseIndex(FCompactPoseBoneIndex(Compact)).GetInt();
                        if(!Local.IsValidIndex(MeshBone) || !Pose[FCompactPoseBoneIndex(Compact)].IsValid())
                        {Error=TEXT("Native extraction oracle has invalid receiving compact-to-mesh index.");return false;}
                        const auto& Expected=Pose[FCompactPoseBoneIndex(Compact)];
                        MaxOraclePosition=FMath::Max(MaxOraclePosition,double(FVector::Dist(Expected.GetTranslation(),Local[MeshBone].GetTranslation())));
                        MaxOracleRotation=FMath::Max(MaxOracleRotation,double(RotationDifference(Expected,Local[MeshBone])));
                        ++Compared;
                    }
                }
            }
            const bool bMeaningfulMotion=MaxMotion>0.001 || MaxRotation>0.0001;
            const bool bPoseChanged=ChangedComponentPoseSamples>0 && DistinctRequiredPoses.Num()>1;
            const bool bMotion=bMeaningfulMotion && bPoseChanged;
            Report->SetNumberField(TEXT("fixed_ticks"),120);
            Report->SetNumberField(TEXT("initial_time"),InitialTime);
            Report->SetNumberField(TEXT("final_time"),LastTime);
            Report->SetNumberField(TEXT("bone_count"),Initial.Num());
            Report->SetNumberField(TEXT("required_mesh_bone_count"),RequiredMeshBones.Num());
            Report->SetStringField(TEXT("unrequired_bone_scope"),TEXT("Complete-buffer finite/normalized checks only; native CS update/motion/parent oracle covers parent-closed receiving required bones."));
            Report->SetBoolField(TEXT("oracle_uses_original_single_node_root_motion_flag"),true);
            Report->SetNumberField(TEXT("max_component_motion_cm"),MaxMotion);
            Report->SetNumberField(TEXT("max_component_rotation_radians"),MaxRotation);
            Report->SetBoolField(TEXT("nonconstant_native_component_motion"),bMotion);
            Report->SetBoolField(TEXT("meaningful_component_displacement_or_rotation"),bMeaningfulMotion);
            Report->SetBoolField(TEXT("required_component_pose_digest_changed"),bPoseChanged);
            Report->SetNumberField(TEXT("changed_component_pose_samples"),ChangedComponentPoseSamples);
            Report->SetNumberField(TEXT("distinct_required_component_poses"),DistinctRequiredPoses.Num());
            Report->SetStringField(TEXT("initial_required_component_pose_sha1"),InitialRequiredPose);
            Report->SetStringField(TEXT("final_required_component_pose_sha1"),FinalRequiredPose);
            Report->SetStringField(TEXT("rotation_metric"),TEXT("Exact quaternion/antipodal equality then double relative-quaternion 2*atan2(length(vector),abs(w)); acos norm noise cannot create motion."));
            Report->SetNumberField(TEXT("oracle_compared_local_transforms"),Compared);
            Report->SetNumberField(TEXT("max_native_extraction_local_error_cm"),MaxOraclePosition);
            Report->SetNumberField(TEXT("max_native_extraction_rotation_error_radians"),MaxOracleRotation);
            Report->SetNumberField(TEXT("max_local_parent_component_error_cm"),MaxParentError);
            Report->SetBoolField(TEXT("finite_normalized_complete_pose"),true);
            if(bAccept && (!bMotion || LastTime-InitialTime<1.9f || Compared<1 || MaxOraclePosition>0.002 || MaxOracleRotation>0.001 || MaxParentError>0.01))
            {Error=TEXT("Real playback motion/time or native local/component pose oracle failed.");return false;}
            if(!bAccept && bMeaningfulMotion)
            {Error=TEXT("Unregistered foreign animation moved the receiving component despite refusal.");return false;}
            return true;
        };
        const bool bBody=Body();
        Component->HandleExistingParallelEvaluationTask(true,true);
        Component->Stop();
        Component->SetAnimation(nullptr);
        Component->SetSkeletalMesh(nullptr);
        Component->SetAnimationMode(EAnimationMode::AnimationBlueprint); // Clear transient single-node instance without reinitializing a null mesh.
        if(bAdded){Scene.RemoveComponent(Component.Get());}
        Component->DestroyComponent();
        Report->SetBoolField(TEXT("component_unregistered_and_assets_cleared"),!Component->IsRegistered() && Component->SkeletalMesh==nullptr && Component->GetSingleNodeInstance()==nullptr);
        const bool bOriginals=Originals.Unchanged();
        Report->SetBoolField(TEXT("originals_unchanged"),bOriginals);
        Report->SetStringField(TEXT("original_compressed_sha1"),Originals.Compressed);
        Report->SetBoolField(TEXT("succeeded"),bBody && bOriginals && Report->GetBoolField(TEXT("component_unregistered_and_assets_cleared")));
        if(!Error.IsEmpty()){Report->SetStringField(TEXT("error"),Error);}
        return Report;
    }

    class FExec final : public FSelfRegisteringExec
    {
        bool Exec(UWorld* InWorld,const TCHAR* Cmd,FOutputDevice& Ar) override
        {
            if(!FParse::Command(&Cmd,TEXT("Rebirth.SkelCompatNativePlaybackTest"))){return false;}
            if(!FParse::Param(FCommandLine::Get(),TEXT("RebirthOriginalSkeletonCompatibilityProbe")))
            {Ar.Log(TEXT("Owned skeleton compatibility marker required."));return true;}
            auto Report=MakeShared<FJsonObject>();
            Report->SetStringField(TEXT("status"),TEXT("RUNNING"));
            Report->SetNumberField(TEXT("process_id"),FPlatformProcess::GetCurrentProcessId());
            Report->SetStringField(TEXT("run_id"),FGuid::NewGuid().ToString(EGuidFormats::Digits));
            Report->SetStringField(TEXT("project_file"),FPaths::ConvertRelativePathToFull(FPaths::GetProjectFilePath()));
            Report->SetBoolField(TEXT("clips_converted_or_baked"),false);
            Report->SetBoolField(TEXT("asset_saves"),false);
            Report->SetBoolField(TEXT("in_game_verified"),false);
            Report->SetBoolField(TEXT("succeeded"),false);
            Save(Report);
            auto Fail=[&](const TCHAR* Error){Report->SetStringField(TEXT("status"),TEXT("FAILED"));Report->SetStringField(TEXT("error"),Error);Save(Report);Ar.Log(*Json(Report));};
            FString ProjectFile=FPaths::ConvertRelativePathToFull(FPaths::GetProjectFilePath());
            FPaths::NormalizeFilename(ProjectFile);
            if(!ProjectFile.Equals(TEXT("C:/RebirthEngine/CompatibilityTestProject/End.uproject"),ESearchCase::IgnoreCase) ||
                !IFileManager::Get().FileExists(*(FPaths::ProjectDir()/TEXT("CodexCompatibilityFixture.json"))) ||
                !FParse::Param(FCommandLine::Get(),TEXT("RebirthCookedMaterialMetadataOnly")))
            {Fail(TEXT("Requires exact owned private fixture and metadata-only startup; refuse MAIN or saved-pair auto-loading."));return true;}
            if(!IsInGameThread() || !GIsEditor || !GEngine || IsGarbageCollecting() || IsEngineExitRequested() || GIsSlowTask || GIsPlayInEditorWorld || GIsAutomationTesting || !FString(Cmd).TrimStartAndEnd().IsEmpty())
            {Fail(TEXT("Requires idle owned editor game thread, exact command and no GC/slow task/exit."));return true;}
            USkeletalMesh* Mesh=FindObject<USkeletalMesh>(nullptr,MeshPath);
            UAnimSequence* Seph=FindObject<UAnimSequence>(nullptr,SephPath);
            UAnimSequence* Cloud=FindObject<UAnimSequence>(nullptr,CloudPath);
            if(!IsValid(Mesh) || Mesh->HasAnyFlags(RF_NeedLoad|RF_NeedPostLoad) || !IsValid(Mesh->Skeleton) || Mesh->RefSkeleton.GetNum()!=768 ||
                !GenuineSequence(Seph) || !GenuineSequence(Cloud) || Seph->GetSkeleton()!=Mesh->Skeleton || Cloud->GetSkeleton()==Mesh->Skeleton ||
                !Mesh->Skeleton->IsCompatibleMesh(Mesh) || RebirthSkeletonCompatibility::FindMapping(Seph->GetSkeleton(),Cloud->GetSkeleton()).IsValid())
            {Fail(TEXT("Preload exact genuine mesh and two native compressed no-notify idles; no pair may already be registered."));return true;}
            TStrongObjectPtr<USkeletalMesh> MeshRoot(Mesh);
            TStrongObjectPtr<UAnimSequence> SephRoot(Seph),CloudRoot(Cloud);
            TArray<TSharedPtr<FJsonValue>> Cases;
            auto Control=RunCase(Mesh,Seph,true,TEXT("same_skeleton_seph_idle"));Cases.Add(MakeShared<FJsonValueObject>(Control));
            auto Refusal=RunCase(Mesh,Cloud,false,TEXT("unregistered_cloud_idle_to_seph"));Cases.Add(MakeShared<FJsonValueObject>(Refusal));
            FString Diagnostic;
            const bool bRegistered=URebirthSkeletonCompatibilityEditorLibrary::RegisterCompatibleSkeletons(Seph->GetSkeleton(),Cloud->GetSkeleton(),Diagnostic,false);
            Report->SetBoolField(TEXT("registered_without_manifest_write"),bRegistered);
            Report->SetStringField(TEXT("registration_diagnostic"),Diagnostic);
            bool bMapped=false,bRemoved=false;
            if(bRegistered)
            {
                auto Mapped=RunCase(Mesh,Cloud,true,TEXT("registered_original_cloud_idle_to_seph"));
                Cases.Add(MakeShared<FJsonValueObject>(Mapped));bMapped=Mapped->GetBoolField(TEXT("succeeded"));
                bRemoved=URebirthSkeletonCompatibilityEditorLibrary::UnregisterCompatibleSkeletons(Seph->GetSkeleton(),Cloud->GetSkeleton(),Diagnostic,false);
            }
            Report->SetArrayField(TEXT("cases"),Cases);
            Report->SetBoolField(TEXT("registration_removed"),bRemoved);
            Report->SetBoolField(TEXT("unregistered_native_IsCompatible_false"),!Seph->GetSkeleton()->IsCompatible(Cloud->GetSkeleton()));
            Report->SetStringField(TEXT("diagnostics_after"),RebirthSkeletonCompatibility::GetDiagnostics());
            const bool bGood=Control->GetBoolField(TEXT("succeeded")) && Refusal->GetBoolField(TEXT("succeeded")) && bRegistered && bMapped && bRemoved && !Seph->GetSkeleton()->IsCompatible(Cloud->GetSkeleton());
            Report->SetBoolField(TEXT("succeeded"),bGood);
            Report->SetStringField(TEXT("status"),bGood?TEXT("VERIFIED_NATIVE_SINGLE_NODE_COMPONENT_PLAYBACK"):TEXT("FAILED"));
            Report->SetStringField(TEXT("evidence_limit"),TEXT("Native original-clip SingleNode component playback only; SequencePlayer/Evaluator, Montage, BlendSpace, Persona and AnimBP paths need separate native consumers/tests. No retail runtime adapter installed."));
            Save(Report);Ar.Log(*Json(Report));return true;
        }
    };
    static FExec Exec;
}
