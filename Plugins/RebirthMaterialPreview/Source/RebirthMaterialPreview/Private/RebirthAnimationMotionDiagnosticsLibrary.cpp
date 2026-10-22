#include "RebirthAnimationMotionDiagnosticsLibrary.h"

#include "Animation/AnimSequence.h"
#include "Animation/Skeleton.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

#if WITH_EDITOR
#include "Animation/AnimBoneCompressionCodec.h"
#include "Animation/AnimBoneCompressionSettings.h"
#include "Animation/AnimCurveCompressionSettings.h"
#include "Misc/SecureHash.h"
#include "UObject/Package.h"
#include "UObject/StrongObjectPtr.h"
#endif

namespace RebirthMotionDiagnostics
{
	static FString Json(const TSharedRef<FJsonObject>& Report)
	{
		FString Result;
		const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Result);
		FJsonSerializer::Serialize(Report, Writer);
		return Result;
	}

#if WITH_EDITOR
	static constexpr float PositionTolerance = 0.05f;
	static constexpr float RotationToleranceDegrees = 0.25f;
	static constexpr float ScaleTolerance = 0.001f;
	// Component-space error can accumulate along an entire chain after ACL compression.
	static constexpr float ComponentPositionTolerance = 0.5f;
	static constexpr float ComponentRotationToleranceDegrees = 0.5f;
	static const TCHAR* ACLClass = TEXT("/Script/ACLPlugin.AnimBoneCompressionCodec_ACL");

	struct FErrors
	{
		float Position = 0.0f, RotationDegrees = 0.0f, Scale = 0.0f;
		int64 Samples = 0;
		bool Add(const FTransform& Expected, const FTransform& Actual)
		{
			if (!Expected.IsValid() || !Actual.IsValid()) { return false; }
			Position = FMath::Max(Position, FVector::Dist(Expected.GetTranslation(), Actual.GetTranslation()));
			RotationDegrees = FMath::Max(RotationDegrees, FMath::RadiansToDegrees(
				Expected.GetRotation().GetNormalized().AngularDistance(Actual.GetRotation().GetNormalized())));
			Scale = FMath::Max(Scale, (Expected.GetScale3D() - Actual.GetScale3D()).GetAbsMax());
			++Samples;
			return FMath::IsFinite(Position) && FMath::IsFinite(RotationDegrees) && FMath::IsFinite(Scale);
		}
		bool Within(float PositionLimit = PositionTolerance, float RotationLimit = RotationToleranceDegrees) const
		{
			return Samples > 0 && Position <= PositionLimit && RotationDegrees <= RotationLimit && Scale <= ScaleTolerance;
		}
		TSharedRef<FJsonObject> Report(float PositionLimit = PositionTolerance, float RotationLimit = RotationToleranceDegrees) const
		{
			const TSharedRef<FJsonObject> Result = MakeShared<FJsonObject>();
			Result->SetNumberField(TEXT("sample_count"), double(Samples));
			Result->SetNumberField(TEXT("max_position_error_cm"), Position);
			Result->SetNumberField(TEXT("max_rotation_error_degrees"), RotationDegrees);
			Result->SetNumberField(TEXT("max_scale_error"), Scale);
			Result->SetNumberField(TEXT("position_limit_cm"), PositionLimit);
			Result->SetNumberField(TEXT("rotation_limit_degrees"), RotationLimit);
			Result->SetNumberField(TEXT("scale_limit"), ScaleTolerance);
			Result->SetBoolField(TEXT("passed"), Within(PositionLimit, RotationLimit));
			return Result;
		}
	};

	static bool ValidSkeleton(USkeleton* Skeleton, FString& Error)
	{
		if (!Skeleton || Skeleton->GetClass() != USkeleton::StaticClass()
			|| Skeleton->HasAnyFlags(RF_NeedLoad | RF_NeedPostLoad))
		{
			Error = TEXT("A fully loaded native USkeleton is required."); return false;
		}
		const FReferenceSkeleton& Ref = Skeleton->GetReferenceSkeleton();
		if (Ref.GetRawBoneNum() < 1 || Ref.GetRawBoneNum() > 65535 || Ref.GetRawRefBonePose().Num() != Ref.GetRawBoneNum())
		{
			Error = TEXT("Invalid reference skeleton size."); return false;
		}
		TSet<FName> Names;
		for (int32 Bone = 0; Bone < Ref.GetRawBoneNum(); ++Bone)
		{
			const int32 Parent = Ref.GetParentIndex(Bone);
			const FName Name = Ref.GetBoneName(Bone);
			if (Name.IsNone() || Names.Contains(Name) || (Bone == 0 ? Parent != INDEX_NONE : Parent < 0 || Parent >= Bone)
				|| !Ref.GetRawRefBonePose()[Bone].IsValid()
				|| !Ref.GetRawRefBonePose()[Bone].GetScale3D().Equals(FVector::OneVector, ScaleTolerance))
			{
				Error = TEXT("Invalid bone hierarchy, pose, or non-unit reference scale."); return false;
			}
			Names.Add(Name);
		}
		return true;
	}

	struct FSkeletonSnapshot
	{
		USkeleton* Skeleton;
		FGuid Guid, VirtualGuid;
		TArray<FMeshBoneInfo> Infos;
		TArray<FTransform> Poses;
		bool bDirty;
		explicit FSkeletonSnapshot(USkeleton* InSkeleton)
			: Skeleton(InSkeleton), Guid(InSkeleton->GetGuid()), VirtualGuid(InSkeleton->GetVirtualBoneGuid()),
			Infos(InSkeleton->GetReferenceSkeleton().GetRawRefBoneInfo()),
			Poses(InSkeleton->GetReferenceSkeleton().GetRawRefBonePose()), bDirty(InSkeleton->GetOutermost()->IsDirty()) {}
		bool Unchanged() const
		{
			const FReferenceSkeleton& Ref = Skeleton->GetReferenceSkeleton();
			if (Skeleton->GetGuid() != Guid || Skeleton->GetVirtualBoneGuid() != VirtualGuid
				|| Skeleton->GetOutermost()->IsDirty() != bDirty || Ref.GetRawBoneNum() != Infos.Num()) { return false; }
			for (int32 Bone = 0; Bone < Infos.Num(); ++Bone)
			{
				if (Ref.GetBoneName(Bone) != Infos[Bone].Name || Ref.GetParentIndex(Bone) != Infos[Bone].ParentIndex
					|| !Ref.GetRawRefBonePose()[Bone].Equals(Poses[Bone], 0.0f)) { return false; }
			}
			return true;
		}
	};

	static FString CompressedSHA1(const UAnimSequence* Sequence)
	{
		const auto& Bytes = Sequence->CompressedData.CompressedByteStream;
		uint8 Digest[20];
		FSHA1::HashBuffer(Bytes.GetData(), Bytes.Num(), Digest);
		return BytesToHex(Digest, UE_ARRAY_COUNT(Digest)).ToLower();
	}

	static bool NativeCompressedReady(UAnimSequence* Sequence, bool bCompleteMap, FString& Error)
	{
		if (!Sequence || Sequence->GetClass() != UAnimSequence::StaticClass()
			|| Sequence->HasAnyFlags(RF_NeedLoad | RF_NeedPostLoad))
		{
			Error = TEXT("A fully loaded native UAnimSequence is required."); return false;
		}
		const FCompressedAnimSequence& Data = Sequence->CompressedData;
		if (Sequence->OnlyUseRawData() || !Sequence->IsCompressedDataValid() || !Data.CompressedDataStructure
			|| !Data.CompressedDataStructure->IsValid() || !Data.BoneCompressionCodec
			|| Data.BoneCompressionCodec->GetClass()->GetPathName() != ACLClass
			|| Data.CompressedByteStream.Num() < 1 || Data.CompressedByteStream.Num() > 268435456)
		{
			Error = TEXT("Missing/invalid/stale native ACL data; raw or identity fallback is forbidden."); return false;
		}
		if (!Sequence->BoneCompressionSettings || !Sequence->CurveCompressionSettings
			|| !Sequence->BoneCompressionSettings->AreSettingsValid() || !Sequence->CurveCompressionSettings->AreSettingsValid()
			|| Sequence->BoneCompressionSettings->Codecs.Num() != 1
			|| Sequence->BoneCompressionSettings->Codecs[0] != Data.BoneCompressionCodec)
		{
			Error = TEXT("Invalid or inconsistent compression settings/codec identity."); return false;
		}
		if (!ValidSkeleton(Sequence->GetSkeleton(), Error)) { return false; }
		const FReferenceSkeleton& Ref = Sequence->GetSkeleton()->GetReferenceSkeleton();
		const auto& Map = Sequence->GetCompressedTrackToSkeletonMapTable();
		if (Map.Num() < 1 || Map.Num() > 65535 || Map[0].BoneTreeIndex != 0)
		{
			Error = TEXT("Missing root-at-track-zero compressed map."); return false;
		}
		TSet<int32> Seen;
		for (const FTrackToSkeletonMap& Entry : Map)
		{
			if (Entry.BoneTreeIndex < 0 || Entry.BoneTreeIndex >= Ref.GetNum() || Seen.Contains(Entry.BoneTreeIndex))
			{
				Error = TEXT("Compressed map has an invalid/duplicate skeleton index."); return false;
			}
			Seen.Add(Entry.BoneTreeIndex);
		}
		if (bCompleteMap)
		{
			for (int32 Bone = 0; Bone < Ref.GetRawBoneNum(); ++Bone)
			{
				if (!Seen.Contains(Bone)) { Error = TEXT("Output compressed map omits a raw bone."); return false; }
			}
		}
		const int32 Frames = Sequence->GetRawNumberOfFrames();
		if (Frames < 2 || Frames > 10000 || int64(Frames) * Ref.GetRawBoneNum() > 2000000
			|| !FMath::IsFinite(Sequence->SequenceLength) || Sequence->SequenceLength <= 0.0f
			|| Data.CompressedDataStructure->CompressedNumberOfFrames < 1
			|| Data.CompressedDataStructure->CompressedNumberOfFrames > Frames)
		{
			Error = TEXT("Invalid frame metadata or diagnostic exceeds 2M bone samples/10k frames."); return false;
		}
		return true;
	}

	static bool Decode(UAnimSequence* Sequence, float Time, TArray<FTransform>& Local)
	{
		// These predicates prevent GetBoneTransform's documented raw-data fallback.
		if (Sequence->OnlyUseRawData() || !Sequence->IsCompressedDataValid()
			|| !Sequence->CompressedData.BoneCompressionCodec || !Sequence->CompressedData.CompressedDataStructure
			|| !Sequence->CompressedData.CompressedDataStructure->IsValid()) { return false; }
		const FReferenceSkeleton& Ref = Sequence->GetSkeleton()->GetReferenceSkeleton();
		Local = Ref.GetRawRefBonePose();
		const auto& Map = Sequence->GetCompressedTrackToSkeletonMapTable();
		for (int32 Track = 0; Track < Map.Num(); ++Track)
		{
			const int32 Bone = Map[Track].BoneTreeIndex;
			if (Bone >= Ref.GetRawBoneNum()) { continue; }
			FTransform Value = FTransform::Identity;
			Sequence->GetBoneTransform(Value, Track, Time, false);
			if (!Value.IsValid() || Value.GetTranslation().GetAbsMax() > 10000000.0f
				|| Value.GetScale3D().GetAbsMax() > 1000.0f) { return false; }
			Value.NormalizeRotation();
			Local[Bone] = Value;
		}
		return true;
	}

	static bool ComponentPose(const FReferenceSkeleton& Ref, const TArray<FTransform>& Local, TArray<FTransform>& Component)
	{
		Component.SetNumUninitialized(Local.Num());
		for (int32 Bone = 0; Bone < Local.Num(); ++Bone)
		{
			const int32 Parent = Ref.GetParentIndex(Bone);
			Component[Bone] = Parent == INDEX_NONE ? Local[Bone] : Local[Bone] * Component[Parent];
			Component[Bone].NormalizeRotation();
			if (!Component[Bone].IsValid()) { return false; }
		}
		return true;
	}

	static void CopyMotionSettings(UAnimSequence* Source, UAnimSequence* Target)
	{
		Target->SetSkeleton(Source->GetSkeleton());
		Target->SequenceLength = Source->SequenceLength;
		Target->SetRawNumberOfFrame(Source->GetRawNumberOfFrames());
		Target->RateScale = Source->RateScale;
		Target->Interpolation = Source->Interpolation;
		Target->RootMotionScale = Source->RootMotionScale;
		Target->bEnableRootMotion = Source->bEnableRootMotion;
		Target->RootMotionRootLock = Source->RootMotionRootLock;
		Target->bForceRootLock = Source->bForceRootLock;
		Target->bUseNormalizedRootMotionScale = Source->bUseNormalizedRootMotionScale;
		Target->bRootMotionSettingsCopiedFromMontage = Source->bRootMotionSettingsCopiedFromMontage;
		Target->BoneCompressionSettings = Source->BoneCompressionSettings;
		Target->CurveCompressionSettings = Source->CurveCompressionSettings;
		Target->RetargetSource = NAME_None;
		Target->bAllowFrameStripping = false;
	}
#endif
}

FString URebirthAnimationMotionDiagnosticsLibrary::ValidateConvertedMotion(UAnimSequence* SourceAnimation,
	UAnimSequence* ConvertedAnimation, float RootTranslationScale)
{
	using namespace RebirthMotionDiagnostics;
	const TSharedRef<FJsonObject> Report = MakeShared<FJsonObject>();
	Report->SetBoolField(TEXT("succeeded"), false);
	Report->SetBoolField(TEXT("saved_assets"), false);
	Report->SetBoolField(TEXT("game_playback_verified"), false);
	Report->SetStringField(TEXT("sampling_route"), TEXT("UAnimSequence::GetBoneTransform(compressed_track,time,false) -> native ACL DecompressBone"));
	Report->SetStringField(TEXT("scope"), TEXT("Empty override mapping; target bind child translations/scales; no IK or secondary-physics transfer."));
#if WITH_EDITOR
	FString Error;
	auto Fail = [&](const FString& Message) { Report->SetStringField(TEXT("error"), Message); return Json(Report); };
	if (!IsInGameThread() || !FMath::IsFinite(RootTranslationScale) || RootTranslationScale < 0.0f || RootTranslationScale > 100.0f)
	{
		return Fail(TEXT("Call on the game thread with a finite root displacement multiplier in [0,100]."));
	}
	if (!NativeCompressedReady(SourceAnimation, false, Error) || !NativeCompressedReady(ConvertedAnimation, true, Error)) { return Fail(Error); }
	USkeleton* SourceSkeleton = SourceAnimation->GetSkeleton();
	USkeleton* TargetSkeleton = ConvertedAnimation->GetSkeleton();
	if (!(SourceAnimation->GetOutermost()->GetPackageFlags() & PKG_Cooked) || SourceSkeleton == TargetSkeleton)
	{
		return Fail(TEXT("A genuine cooked source and a distinct receiving skeleton are required."));
	}
	const int32 Frames = SourceAnimation->GetRawNumberOfFrames();
	if (ConvertedAnimation->GetRawNumberOfFrames() != Frames || ConvertedAnimation->SequenceLength != SourceAnimation->SequenceLength
		|| ConvertedAnimation->RateScale != SourceAnimation->RateScale || ConvertedAnimation->Interpolation != SourceAnimation->Interpolation
		|| ConvertedAnimation->RootMotionScale != SourceAnimation->RootMotionScale
		|| ConvertedAnimation->bEnableRootMotion != SourceAnimation->bEnableRootMotion
		|| ConvertedAnimation->RootMotionRootLock != SourceAnimation->RootMotionRootLock
		|| ConvertedAnimation->bForceRootLock != SourceAnimation->bForceRootLock
		|| ConvertedAnimation->bUseNormalizedRootMotionScale != SourceAnimation->bUseNormalizedRootMotionScale
		|| ConvertedAnimation->bRootMotionSettingsCopiedFromMontage != SourceAnimation->bRootMotionSettingsCopiedFromMontage
		|| SourceAnimation->BoneCompressionSettings != ConvertedAnimation->BoneCompressionSettings
		|| SourceAnimation->CurveCompressionSettings != ConvertedAnimation->CurveCompressionSettings)
	{
		return Fail(TEXT("Converted timing, playback/root policy or compression settings differ from source."));
	}
	const FSkeletonSnapshot SourceSnapshot(SourceSkeleton), TargetSnapshot(TargetSkeleton);
	const bool bSourceDirty = SourceAnimation->GetOutermost()->IsDirty();
	const FString SourceDigest = CompressedSHA1(SourceAnimation), OutputDigest = CompressedSHA1(ConvertedAnimation);
	auto Finish = [&](bool bSucceeded, const FString& Message)
	{
		const bool bUnchanged = SourceSnapshot.Unchanged() && TargetSnapshot.Unchanged()
			&& SourceAnimation->GetOutermost()->IsDirty() == bSourceDirty
			&& SourceAnimation->GetSkeleton() == SourceSkeleton && ConvertedAnimation->GetSkeleton() == TargetSkeleton
			&& SourceDigest == CompressedSHA1(SourceAnimation) && OutputDigest == CompressedSHA1(ConvertedAnimation);
		Report->SetBoolField(TEXT("source_and_skeletons_unchanged"), bUnchanged);
		Report->SetBoolField(TEXT("succeeded"), bSucceeded && bUnchanged);
		if (!Message.IsEmpty()) { Report->SetStringField(TEXT("error"), Message); }
		if (!bUnchanged) { Report->SetStringField(TEXT("error"), TEXT("Source animation, compressed streams or skeleton metadata changed.")); }
		return Json(Report);
	};
	Report->SetStringField(TEXT("source_animation"), SourceAnimation->GetPathName());
	Report->SetStringField(TEXT("source_compressed_sha1"), SourceDigest);
	Report->SetStringField(TEXT("converted_animation"), ConvertedAnimation->GetPathName());
	Report->SetStringField(TEXT("converted_compressed_sha1"), OutputDigest);
	Report->SetStringField(TEXT("source_skeleton"), SourceSkeleton->GetPathName());
	Report->SetStringField(TEXT("target_skeleton"), TargetSkeleton->GetPathName());
	Report->SetStringField(TEXT("source_skeleton_guid"), SourceSkeleton->GetGuid().ToString());
	Report->SetStringField(TEXT("target_skeleton_guid"), TargetSkeleton->GetGuid().ToString());
	Report->SetStringField(TEXT("codec_class"), SourceAnimation->CompressedData.BoneCompressionCodec->GetClass()->GetPathName());
	Report->SetStringField(TEXT("codec_object"), SourceAnimation->CompressedData.BoneCompressionCodec->GetPathName());
	Report->SetNumberField(TEXT("frames"), Frames);
	Report->SetNumberField(TEXT("duration_seconds"), SourceAnimation->SequenceLength);
	Report->SetNumberField(TEXT("root_translation_scale"), RootTranslationScale);
	Report->SetNumberField(TEXT("source_compressed_tracks"), SourceAnimation->GetCompressedTrackToSkeletonMapTable().Num());
	const FReferenceSkeleton& SourceRef = SourceSkeleton->GetReferenceSkeleton();
	const FReferenceSkeleton& TargetRef = TargetSkeleton->GetReferenceSkeleton();
	Report->SetNumberField(TEXT("source_raw_bones"), SourceRef.GetRawBoneNum());
	Report->SetNumberField(TEXT("target_raw_bones"), TargetRef.GetRawBoneNum());
	if (SourceSnapshot.Poses[0].GetRotation().AngularDistance(TargetSnapshot.Poses[0].GetRotation()) > 0.001f)
	{
		return Finish(false, TEXT("Bind root orientations disagree; root-motion axes are unsupported."));
	}
	TArray<int32> TargetToSource;
	TargetToSource.Init(INDEX_NONE, TargetRef.GetRawBoneNum());
	int32 Mapped = 0;
	for (int32 Bone = 0; Bone < TargetRef.GetRawBoneNum(); ++Bone)
	{
		const int32 SourceBone = SourceRef.FindRawBoneIndex(TargetRef.GetBoneName(Bone));
		if (SourceBone == INDEX_NONE) { continue; }
		const int32 Parent = TargetRef.GetParentIndex(Bone), SourceParent = SourceRef.GetParentIndex(SourceBone);
		if (Parent == INDEX_NONE ? SourceParent == INDEX_NONE : TargetToSource[Parent] != INDEX_NONE && TargetToSource[Parent] == SourceParent)
		{
			TargetToSource[Bone] = SourceBone; ++Mapped;
		}
	}
	Report->SetNumberField(TEXT("compatible_parent_chains"), Mapped);
	Report->SetNumberField(TEXT("target_bind_fallback_bones"), TargetRef.GetRawBoneNum() - Mapped);
	if (TargetToSource[0] != 0 || Mapped < 2) { return Finish(false, TEXT("No compatible root/body parent chain.")); }
	TArray<FTransform> SourceBindCS, TargetBindCS;
	if (!ComponentPose(SourceRef, SourceSnapshot.Poses, SourceBindCS) || !ComponentPose(TargetRef, TargetSnapshot.Poses, TargetBindCS))
	{
		return Finish(false, TEXT("Invalid reference component pose."));
	}
	TArray<FRawAnimSequenceTrack> LoopTracks;
	LoopTracks.SetNum(SourceRef.GetRawBoneNum());
	TArray<FTransform> SourceLocal, FirstSourceLocal;
	FErrors SourceVariation;
	FErrors MappedSourceVariation;
	bool bMappedPoseChanged = false;
	for (int32 Frame = 0; Frame < Frames; ++Frame)
	{
		const float Time = SourceAnimation->SequenceLength * float(Frame) / float(Frames - 1);
		if (!Decode(SourceAnimation, Time, SourceLocal)) { return Finish(false, TEXT("Source native decoder returned an invalid pose.")); }
		if (Frame == 0) { FirstSourceLocal = SourceLocal; }
		for (int32 Bone = 0; Bone < SourceLocal.Num(); ++Bone)
		{
			if (!SourceVariation.Add(FirstSourceLocal[Bone], SourceLocal[Bone]))
			{
				return Finish(false, TEXT("Nonfinite source motion variation."));
			}
			FRawAnimSequenceTrack& Track = LoopTracks[Bone];
			FQuat Rotation = SourceLocal[Bone].GetRotation();
			if (Frame > 0 && (Track.RotKeys.Last() | Rotation) < 0.0f) { Rotation = Rotation * -1.0f; }
			Track.PosKeys.Add(SourceLocal[Bone].GetTranslation());
			Track.RotKeys.Add(Rotation);
			Track.ScaleKeys.Add(SourceLocal[Bone].GetScale3D());
		}
		for (int32 SourceBone : TargetToSource)
		{
			if (SourceBone != INDEX_NONE && !MappedSourceVariation.Add(FirstSourceLocal[SourceBone], SourceLocal[SourceBone]))
			{
				return Finish(false, TEXT("Nonfinite mapped source motion variation."));
			}
			if (SourceBone != INDEX_NONE && (!FirstSourceLocal[SourceBone].GetTranslation().Equals(SourceLocal[SourceBone].GetTranslation(), 0.0001f)
				|| !FirstSourceLocal[SourceBone].GetRotation().Equals(SourceLocal[SourceBone].GetRotation(), 0.00001f)))
			{
				bMappedPoseChanged = true;
			}
		}
	}
	Report->SetNumberField(TEXT("source_max_motion_position_cm"), SourceVariation.Position);
	Report->SetNumberField(TEXT("source_max_motion_rotation_degrees"), SourceVariation.RotationDegrees);
	Report->SetNumberField(TEXT("mapped_source_max_motion_position_cm"), MappedSourceVariation.Position);
	Report->SetNumberField(TEXT("mapped_source_max_motion_rotation_degrees"), MappedSourceVariation.RotationDegrees);
	// Equality also gates this: AngularDistance alone can have a small float error for identical quaternions.
	const bool bNonconstant = bMappedPoseChanged && (MappedSourceVariation.Position > 0.0001f || MappedSourceVariation.RotationDegrees > 0.001f);
	Report->SetBoolField(TEXT("native_mapped_source_motion_nonconstant"), bNonconstant);
	if (!bNonconstant) { return Finish(false, TEXT("Mapped source motion is constant; identity/bind fallback cannot pass this motion probe.")); }
	TStrongObjectPtr<UAnimSequence> Loopback(NewObject<UAnimSequence>(GetTransientPackage(), NAME_None, RF_Transient));
	CopyMotionSettings(SourceAnimation, Loopback.Get());
	for (int32 Bone = 0; Bone < LoopTracks.Num(); ++Bone)
	{
		if (Loopback->AddNewRawTrack(SourceRef.GetBoneName(Bone), &LoopTracks[Bone]) != Bone)
		{
			return Finish(false, TEXT("Unable to establish transient source-order loopback tracks."));
		}
	}
	Loopback->PostProcessSequence();
	Loopback->RequestSyncAnimRecompression();
	if (!NativeCompressedReady(Loopback.Get(), true, Error)) { return Finish(false, TEXT("Transient source loopback: ") + Error); }
	Report->SetStringField(TEXT("loopback_evidence"), TEXT("Source-skeleton native ACL decompress/recompress/decompress consistency; same codec, not an independent retail playback oracle."));
	Report->SetStringField(TEXT("mapped_output_evidence"), TEXT("Native output decoding compared with source-decoded component rotation deltas and original target reference-pose lengths/scales; no raw-original readback."));
	Report->SetStringField(TEXT("loopback_compressed_sha1"), CompressedSHA1(Loopback.Get()));
	FErrors LoopLocalErrors, LoopComponentErrors, OutputLocalErrors, OutputComponentErrors, FallbackErrors;
	FErrors LoopRootErrors, OutputRootErrors;
	TArray<FTransform> LoopLocal, OutputLocal, SourceCS, LoopCS, OutputCS, ExpectedLocal, ExpectedCS;
	ExpectedLocal.SetNum(TargetRef.GetRawBoneNum()); ExpectedCS.SetNum(TargetRef.GetRawBoneNum());
	for (int32 Frame = 0; Frame < Frames; ++Frame)
	{
		const float Time = SourceAnimation->SequenceLength * float(Frame) / float(Frames - 1);
		if (!Decode(SourceAnimation, Time, SourceLocal) || !Decode(Loopback.Get(), Time, LoopLocal)
			|| !Decode(ConvertedAnimation, Time, OutputLocal)
			|| !ComponentPose(SourceRef, SourceLocal, SourceCS) || !ComponentPose(SourceRef, LoopLocal, LoopCS)
			|| !ComponentPose(TargetRef, OutputLocal, OutputCS))
		{
			return Finish(false, TEXT("Invalid native decoded local/component pose during validation."));
		}
		for (int32 Bone = 0; Bone < SourceLocal.Num(); ++Bone)
		{
			if (!LoopLocalErrors.Add(SourceLocal[Bone], LoopLocal[Bone]) || !LoopComponentErrors.Add(SourceCS[Bone], LoopCS[Bone]))
			{
				return Finish(false, TEXT("Nonfinite source loopback error."));
			}
		}
		for (int32 Bone = 0; Bone < TargetRef.GetRawBoneNum(); ++Bone)
		{
			const int32 SourceBone = TargetToSource[Bone], Parent = TargetRef.GetParentIndex(Bone);
			FTransform Local = TargetSnapshot.Poses[Bone];
			if (SourceBone != INDEX_NONE)
			{
				if (!SourceLocal[SourceBone].GetScale3D().Equals(FVector::OneVector, ScaleTolerance))
				{
					return Finish(false, TEXT("Animated source scale is outside the converter's mapped-bone policy."));
				}
				FQuat ComponentRotation = SourceCS[SourceBone].GetRotation() * SourceBindCS[SourceBone].GetRotation().Inverse() * TargetBindCS[Bone].GetRotation();
				ComponentRotation.Normalize();
				FQuat Rotation = Parent == INDEX_NONE ? ComponentRotation : ExpectedCS[Parent].GetRotation().Inverse() * ComponentRotation;
				Rotation.Normalize(); Local.SetRotation(Rotation);
				if (Bone == 0) { Local.SetTranslation(TargetSnapshot.Poses[0].GetTranslation()
					+ (SourceLocal[SourceBone].GetTranslation() - SourceSnapshot.Poses[SourceBone].GetTranslation()) * RootTranslationScale); }
			}
			else if (!FallbackErrors.Add(TargetSnapshot.Poses[Bone], OutputLocal[Bone]))
			{
				return Finish(false, TEXT("Nonfinite target bind-fallback error."));
			}
			ExpectedLocal[Bone] = Local;
			ExpectedCS[Bone] = Parent == INDEX_NONE ? Local : Local * ExpectedCS[Parent];
			ExpectedCS[Bone].NormalizeRotation();
			if (!OutputLocalErrors.Add(Local, OutputLocal[Bone]) || !OutputComponentErrors.Add(ExpectedCS[Bone], OutputCS[Bone]))
			{
				return Finish(false, TEXT("Nonfinite mapped output error."));
			}
		}
		if (Frame > 0)
		{
			const float Start = SourceAnimation->SequenceLength * float(Frame - 1) / float(Frames - 1);
			const FTransform SourceMotion = SourceAnimation->ExtractRootMotionFromRange(Start, Time);
			FTransform ExpectedMotion = SourceMotion;
			ExpectedMotion.SetTranslation(SourceMotion.GetTranslation() * RootTranslationScale);
			if (!LoopRootErrors.Add(SourceMotion, Loopback->ExtractRootMotionFromRange(Start, Time))
				|| !OutputRootErrors.Add(ExpectedMotion, ConvertedAnimation->ExtractRootMotionFromRange(Start, Time)))
			{
				return Finish(false, TEXT("Nonfinite native interval root-motion error."));
			}
		}
	}
	const FTransform FullSourceMotion = SourceAnimation->ExtractRootMotionFromRange(0.0f, SourceAnimation->SequenceLength);
	FTransform FullExpectedMotion = FullSourceMotion;
	FullExpectedMotion.SetTranslation(FullSourceMotion.GetTranslation() * RootTranslationScale);
	if (!LoopRootErrors.Add(FullSourceMotion, Loopback->ExtractRootMotionFromRange(0.0f, SourceAnimation->SequenceLength))
		|| !OutputRootErrors.Add(FullExpectedMotion, ConvertedAnimation->ExtractRootMotionFromRange(0.0f, SourceAnimation->SequenceLength)))
	{
		return Finish(false, TEXT("Nonfinite full-clip root-motion error."));
	}
	Report->SetObjectField(TEXT("source_same_codec_loopback_local"), LoopLocalErrors.Report());
	Report->SetObjectField(TEXT("source_same_codec_loopback_component"), LoopComponentErrors.Report(ComponentPositionTolerance, ComponentRotationToleranceDegrees));
	Report->SetObjectField(TEXT("mapped_output_native_local"), OutputLocalErrors.Report());
	Report->SetObjectField(TEXT("mapped_output_native_component"), OutputComponentErrors.Report(ComponentPositionTolerance, ComponentRotationToleranceDegrees));
	Report->SetObjectField(TEXT("target_bind_fallback_local"), FallbackErrors.Report());
	Report->SetObjectField(TEXT("source_same_codec_loopback_root_motion"), LoopRootErrors.Report());
	Report->SetObjectField(TEXT("mapped_output_native_root_motion"), OutputRootErrors.Report());
	const bool bPassed = LoopLocalErrors.Within() && LoopComponentErrors.Within(ComponentPositionTolerance, ComponentRotationToleranceDegrees)
		&& OutputLocalErrors.Within() && OutputComponentErrors.Within(ComponentPositionTolerance, ComponentRotationToleranceDegrees)
		&& (FallbackErrors.Samples == 0 || FallbackErrors.Within()) && LoopRootErrors.Within() && OutputRootErrors.Within();
	return Finish(bPassed, bPassed ? FString() : TEXT("Native motion validation exceeded recorded tolerances."));
#else
	Report->SetStringField(TEXT("error"), TEXT("This diagnostic is editor-only."));
	return Json(Report);
#endif
}
