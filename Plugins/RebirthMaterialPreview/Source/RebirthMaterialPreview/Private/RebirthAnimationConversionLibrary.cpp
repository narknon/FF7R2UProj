#include "RebirthAnimationConversionLibrary.h"

#include "Animation/AnimSequence.h"
#include "Animation/Skeleton.h"

#if WITH_EDITOR
#include "Animation/AnimBoneCompressionCodec.h"
#include "Animation/AnimBoneCompressionSettings.h"
#include "Animation/AnimCurveCompressionSettings.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AssetRegistryModule.h"
#include "HAL/FileManager.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "UObject/Package.h"
#include "UObject/StrongObjectPtr.h"
#include "UObject/UnrealType.h"
#endif

namespace RebirthAnimationConversion
{
#if WITH_EDITOR
	static bool ValidateSkeleton(USkeleton* Skeleton, FString& Error)
	{
		if (!Skeleton || Skeleton->GetClass() != USkeleton::StaticClass())
		{
			Error = TEXT("A loaded native USkeleton is required; custom skeleton subclasses are unsupported.");
			return false;
		}
		if (Skeleton->HasAnyFlags(RF_NeedLoad | RF_NeedPostLoad))
		{
			Error = TEXT("The skeleton has not finished loading.");
			return false;
		}
		const FReferenceSkeleton& Ref = Skeleton->GetReferenceSkeleton();
		const TArray<FTransform>& Poses = Ref.GetRawRefBonePose();
		if (Ref.GetRawBoneNum() < 1 || Ref.GetRawBoneNum() > 65535 || Poses.Num() != Ref.GetRawBoneNum())
		{
			Error = TEXT("The raw reference skeleton is empty, oversized or inconsistent.");
			return false;
		}
		TSet<FName> Names;
		for (int32 Bone = 0; Bone < Ref.GetRawBoneNum(); ++Bone)
		{
			const int32 Parent = Ref.GetParentIndex(Bone);
			const FName Name = Ref.GetBoneName(Bone);
			if (Name.IsNone() || Names.Contains(Name) || (Bone == 0 ? Parent != INDEX_NONE : Parent < 0 || Parent >= Bone))
			{
				Error = FString::Printf(TEXT("Invalid bone name/root/parent ordering at bone %d (%s)."), Bone, *Name.ToString());
				return false;
			}
			Names.Add(Name);
			if (!Poses[Bone].IsValid() || !Poses[Bone].GetScale3D().Equals(FVector::OneVector, 0.001f))
			{
				Error = FString::Printf(TEXT("Bone %s has an invalid or non-unit bind scale; scaled rigs are outside this MVP."), *Name.ToString());
				return false;
			}
		}
		return true;
	}

	static void BuildComponentPoses(const FReferenceSkeleton& Ref, const TArray<FTransform>& Local, TArray<FTransform>& Component)
	{
		Component.SetNumUninitialized(Local.Num());
		for (int32 Bone = 0; Bone < Local.Num(); ++Bone)
		{
			const int32 Parent = Ref.GetParentIndex(Bone);
			Component[Bone] = Parent == INDEX_NONE ? Local[Bone] : Local[Bone] * Component[Parent];
			Component[Bone].NormalizeRotation();
		}
	}

	// Maps receiving raw-bone indices to source raw-bone indices. A skipped ancestor skips its descendants.
	static bool BuildBoneMap(const FReferenceSkeleton& Source, const FReferenceSkeleton& Target,
		const TMap<FName, FName>& Overrides, TArray<int32>& TargetToSource, TArray<FString>& Reasons, FString& Error)
	{
		TargetToSource.Init(INDEX_NONE, Target.GetRawBoneNum());
		Reasons.SetNum(Target.GetRawBoneNum());
		TSet<int32> ExplicitSources;
		TSet<int32> ExplicitTargets;
		for (const TPair<FName, FName>& Pair : Overrides)
		{
			const int32 SourceBone = Source.FindRawBoneIndex(Pair.Key);
			const int32 TargetBone = Target.FindRawBoneIndex(Pair.Value);
			if (SourceBone == INDEX_NONE || TargetBone == INDEX_NONE || ExplicitTargets.Contains(TargetBone))
			{
				Error = FString::Printf(TEXT("Invalid or many-to-one mapping: %s -> %s. Only existing raw bones with unique targets are supported."), *Pair.Key.ToString(), *Pair.Value.ToString());
				return false;
			}
			ExplicitSources.Add(SourceBone);
			ExplicitTargets.Add(TargetBone);
			TargetToSource[TargetBone] = SourceBone;
		}
		for (int32 Bone = 0; Bone < Target.GetRawBoneNum(); ++Bone)
		{
			if (!ExplicitTargets.Contains(Bone))
			{
				const int32 Match = Source.FindRawBoneIndex(Target.GetBoneName(Bone));
				if (Match != INDEX_NONE && !ExplicitSources.Contains(Match))
				{
					TargetToSource[Bone] = Match;
				}
			}
			const int32 SourceBone = TargetToSource[Bone];
			if (SourceBone == INDEX_NONE)
			{
				Reasons[Bone] = TEXT("unmapped bone");
				continue;
			}
			const int32 TargetParent = Target.GetParentIndex(Bone);
			const int32 SourceParent = Source.GetParentIndex(SourceBone);
			if (TargetParent == INDEX_NONE ? SourceParent != INDEX_NONE
				: TargetToSource[TargetParent] == INDEX_NONE || TargetToSource[TargetParent] != SourceParent)
			{
				Reasons[Bone] = TEXT("different or unmapped parent chain");
				TargetToSource[Bone] = INDEX_NONE;
			}
		}
		return true;
	}

	static int32 ReflectedArrayCount(const UObject* Object, const FName PropertyName)
	{
		const FArrayProperty* Property = FindFProperty<FArrayProperty>(Object->GetClass(), PropertyName);
		if (!Property)
		{
			return INDEX_NONE;
		}
		FScriptArrayHelper Helper(Property, Property->ContainerPtrToValuePtr<void>(Object));
		return Helper.Num();
	}

	static bool HasNativeNotifyClass(const UObject* Notify)
	{
		return !Notify || Notify->GetClass()->GetOutermost()->GetName() == TEXT("/Script/Engine");
	}

	static bool ReceiverUnchanged(USkeleton* Skeleton, const FGuid& Guid, const FGuid& VirtualGuid,
		const TArray<FMeshBoneInfo>& Infos, const TArray<FTransform>& Poses, bool bWasDirty)
	{
		const FReferenceSkeleton& Ref = Skeleton->GetReferenceSkeleton();
		if (Skeleton->GetGuid() != Guid || Skeleton->GetVirtualBoneGuid() != VirtualGuid
			|| Ref.GetRawBoneNum() != Infos.Num() || Skeleton->GetOutermost()->IsDirty() != bWasDirty)
		{
			return false;
		}
		for (int32 Bone = 0; Bone < Infos.Num(); ++Bone)
		{
			if (Ref.GetBoneName(Bone) != Infos[Bone].Name || Ref.GetParentIndex(Bone) != Infos[Bone].ParentIndex
				|| !Ref.GetRawRefBonePose()[Bone].Equals(Poses[Bone], 0.0f))
			{
				return false;
			}
		}
		return true;
	}
#endif
}

FRebirthSkeletonInspection URebirthAnimationConversionLibrary::InspectSkeletons(USkeleton* SourceSkeleton, USkeleton* TargetSkeleton)
{
	FRebirthSkeletonInspection Result;
#if WITH_EDITOR
	using namespace RebirthAnimationConversion;
	FString Error;
	if (!IsInGameThread() || !ValidateSkeleton(SourceSkeleton, Error) || !ValidateSkeleton(TargetSkeleton, Error))
	{
		Result.Diagnostics.Add(Error.IsEmpty() ? TEXT("Call this editor utility on the game thread.") : Error);
		return Result;
	}
	Result.SourceSkeletonPath = SourceSkeleton->GetPathName();
	Result.TargetSkeletonPath = TargetSkeleton->GetPathName();
	const FReferenceSkeleton& Source = SourceSkeleton->GetReferenceSkeleton();
	const FReferenceSkeleton& Target = TargetSkeleton->GetReferenceSkeleton();
	Result.SourceBoneCount = Source.GetRawBoneNum();
	Result.TargetBoneCount = Target.GetRawBoneNum();
	Result.SourceVirtualBoneCount = Source.GetNum() - Source.GetRawBoneNum();
	Result.TargetVirtualBoneCount = Target.GetNum() - Target.GetRawBoneNum();
	for (int32 Bone = 0; Bone < Source.GetRawBoneNum(); ++Bone)
	{
		if (Target.FindRawBoneIndex(Source.GetBoneName(Bone)) == INDEX_NONE)
		{
			Result.SourceOnlyBones.Add(Source.GetBoneName(Bone));
		}
	}
	TArray<int32> Map;
	TArray<FString> Reasons;
	if (!BuildBoneMap(Source, Target, TMap<FName, FName>(), Map, Reasons, Error))
	{
		Result.Diagnostics.Add(Error);
		return Result;
	}
	for (int32 Bone = 0; Bone < Target.GetRawBoneNum(); ++Bone)
	{
		const FName Name = Target.GetBoneName(Bone);
		const int32 SourceBone = Source.FindRawBoneIndex(Name);
		if (SourceBone == INDEX_NONE)
		{
			Result.TargetOnlyBones.Add(Name);
			continue;
		}
		++Result.SharedNameCount;
		if (Map[Bone] != INDEX_NONE)
		{
			++Result.CompatibleChainCount;
		}
		else
		{
			const int32 SP = Source.GetParentIndex(SourceBone);
			const int32 TP = Target.GetParentIndex(Bone);
			Result.ParentChainDifferences.Add(FString::Printf(TEXT("%s: source parent %s; target parent %s; %s"),
				*Name.ToString(), SP == INDEX_NONE ? TEXT("<root>") : *Source.GetBoneName(SP).ToString(),
				TP == INDEX_NONE ? TEXT("<root>") : *Target.GetBoneName(TP).ToString(), *Reasons[Bone]));
		}
	}
	Result.Diagnostics.Add(TEXT("Inspection only: shared names do not make two USkeleton objects runtime-compatible. Conversion must reference the receiving skeleton."));
	Result.bSucceeded = true;
#else
	Result.Diagnostics.Add(TEXT("Animation conversion is available in the editor only."));
#endif
	return Result;
}

FRebirthAnimationConversionResult URebirthAnimationConversionLibrary::ConvertCookedAnimation(
	UAnimSequence* SourceAnimation, USkeleton* TargetSkeleton, const FString& DestinationPackageName,
	const TMap<FName, FName>& SourceToTargetBoneMap, float RootTranslationScale,
	bool bAllowOmittingCurvesNotifiesAndMarkers, bool bSaveAsset)
{
	FRebirthAnimationConversionResult Result;
	Result.DestinationPackageName = DestinationPackageName;
#if WITH_EDITOR
	using namespace RebirthAnimationConversion;
	auto Fail = [&Result](const FString& Error)
	{
		Result.Diagnostics.Add(TEXT("ERROR: ") + Error);
		return Result;
	};
	if (!IsInGameThread())
	{
		return Fail(TEXT("Call this editor utility on the game thread."));
	}
	if (!SourceAnimation || SourceAnimation->GetClass() != UAnimSequence::StaticClass()
		|| SourceAnimation->HasAnyFlags(RF_NeedLoad | RF_NeedPostLoad))
	{
		return Fail(TEXT("A fully loaded native UAnimSequence is required; custom sequence subclasses are unsupported."));
	}
	USkeleton* SourceSkeleton = SourceAnimation->GetSkeleton();
	FString Error;
	if (!ValidateSkeleton(SourceSkeleton, Error) || !ValidateSkeleton(TargetSkeleton, Error))
	{
		return Fail(Error);
	}
	if (SourceSkeleton == TargetSkeleton)
	{
		return Fail(TEXT("Choose a different receiving skeleton; this tool does not duplicate same-skeleton clips."));
	}
	UPackage* SourcePackage = SourceAnimation->GetOutermost();
	if (!SourcePackage->HasAnyPackageFlags(PKG_Cooked | PKG_FilterEditorOnly) && !SourcePackage->bIsCookedForEditor)
	{
		return Fail(TEXT("This MVP accepts genuine cooked source clips only; use ordinary editor retargeting for editable source animation."));
	}
	if (SourceAnimation->AdditiveAnimType != AAT_None || SourceAnimation->IsValidAdditive())
	{
		return Fail(TEXT("Additive clips require conversion of their base pose and are unsupported."));
	}
	if (!SourceAnimation->RetargetSource.IsNone() || SourceAnimation->ParentAsset || SourceAnimation->GetAssetMappingTable())
	{
		return Fail(TEXT("Authored retarget-source poses and inherited/remapped animation assets are unsupported."));
	}
	if (!FMath::IsFinite(RootTranslationScale) || RootTranslationScale < 0.0f || RootTranslationScale > 100.0f)
	{
		return Fail(TEXT("RootTranslationScale must be finite and between 0 and 100; 1 preserves source root displacement."));
	}
	const UAnimSequence* Defaults = GetDefault<UAnimSequence>();
	if (SourceAnimation->OverrideBehaviorActionBlendTime != Defaults->OverrideBehaviorActionBlendTime
		|| SourceAnimation->OverrideBehaviorActionBlendOutTime != Defaults->OverrideBehaviorActionBlendOutTime
		|| SourceAnimation->OverrideBehaviorActionBlendOutSequence != Defaults->OverrideBehaviorActionBlendOutSequence
		|| SourceAnimation->OverrideBehaviorActionBlendOutSequenceFilter != Defaults->OverrideBehaviorActionBlendOutSequenceFilter
		|| SourceAnimation->bPoseAnimation != Defaults->bPoseAnimation
		|| SourceAnimation->bIgnoreTranslationRetargeting != Defaults->bIgnoreTranslationRetargeting)
	{
		return Fail(TEXT("The clip contains non-default Rebirth behavior/pose/translation-retarget overrides; this MVP cannot safely transfer them."));
	}
	if (!FMath::IsFinite(SourceAnimation->SequenceLength) || SourceAnimation->SequenceLength <= 0.0f
		|| !FMath::IsFinite(SourceAnimation->RateScale) || SourceAnimation->RateScale <= 0.0f
		|| !FMath::IsFinite(SourceAnimation->RootMotionScale) || SourceAnimation->RootMotionScale < 0.0f)
	{
		return Fail(TEXT("Invalid sequence length, playback rate or Rebirth RootMotionScale."));
	}
	if (SourceAnimation->RootMotionRootLock != ERootMotionRootLock::RefPose
		&& SourceAnimation->RootMotionRootLock != ERootMotionRootLock::AnimFirstFrame
		&& SourceAnimation->RootMotionRootLock != ERootMotionRootLock::Zero)
	{
		return Fail(TEXT("Unknown root-motion locking policy."));
	}
	if (SourceAnimation->Interpolation != EAnimInterpolationType::Linear
		&& SourceAnimation->Interpolation != EAnimInterpolationType::Step)
	{
		return Fail(TEXT("Unknown animation interpolation policy."));
	}
	const int32 RawAttributeCount = ReflectedArrayCount(SourceAnimation, TEXT("PerBoneCustomAttributeData"));
	const int32 BakedAttributeCount = ReflectedArrayCount(SourceAnimation, TEXT("BakedPerBoneCustomAttributeData"));
	const TArray<UAssetUserData*>* UserData = SourceAnimation->GetAssetUserDataArray();
	if (RawAttributeCount != 0 || BakedAttributeCount != 0 || SourceAnimation->GetMetaData().Num() != 0
		|| (UserData && UserData->Num() != 0))
	{
		return Fail(FString::Printf(TEXT("Custom metadata/user data/attributes are unsupported (raw attributes=%d, baked=%d, metadata=%d, user data=%d). A missing reflection schema is also refused."),
			RawAttributeCount, BakedAttributeCount, SourceAnimation->GetMetaData().Num(), UserData ? UserData->Num() : 0));
	}
	for (const FAnimNotifyEvent& Notify : SourceAnimation->Notifies)
	{
		if (!HasNativeNotifyClass(Notify.Notify) || !HasNativeNotifyClass(Notify.NotifyStateClass))
		{
			return Fail(TEXT("The clip contains a custom game/Blueprint notify type; its semantics must be handled explicitly before conversion."));
		}
	}
	if (SourceAnimation->RawCurveData.VectorCurves.Num() != 0 || SourceAnimation->RawCurveData.TransformCurves.Num() != 0)
	{
		return Fail(TEXT("Editable vector/transform curve channels are outside this cooked-clip MVP."));
	}
	Result.OmittedNotifyCount = SourceAnimation->Notifies.Num();
	Result.OmittedSyncMarkerCount = SourceAnimation->AuthoredSyncMarkers.Num();
	Result.OmittedCurveEntryCount = SourceAnimation->GetCompressedCurveNames().Num() + SourceAnimation->RawCurveData.FloatCurves.Num();
	Result.Diagnostics.Add(FString::Printf(TEXT("Metadata policy: conversion would omit %d native/named notifies, %d curve entries and %d sync markers; custom metadata is refused. Curve counts include compressed and raw entries."),
		Result.OmittedNotifyCount, Result.OmittedCurveEntryCount, Result.OmittedSyncMarkerCount));
	for (const FSmartName& Curve : SourceAnimation->GetCompressedCurveNames())
	{
		Result.Diagnostics.Add(FString::Printf(TEXT("Omitted compressed curve: %s (source UID %d)."), *Curve.DisplayName.ToString(), int32(Curve.UID)));
	}
	for (const FAnimNotifyEvent& Notify : SourceAnimation->Notifies)
	{
		Result.Diagnostics.Add(FString::Printf(TEXT("Omitted notify: %s at %.6f seconds."), *Notify.NotifyName.ToString(), Notify.GetTriggerTime()));
	}
	for (const FFloatCurve& Curve : SourceAnimation->RawCurveData.FloatCurves)
	{
		Result.Diagnostics.Add(FString::Printf(TEXT("Omitted raw float curve: %s (source UID %d)."), *Curve.Name.DisplayName.ToString(), int32(Curve.Name.UID)));
	}
	for (const FAnimSyncMarker& Marker : SourceAnimation->AuthoredSyncMarkers)
	{
		Result.Diagnostics.Add(FString::Printf(TEXT("Omitted sync marker: %s at %.6f seconds."), *Marker.MarkerName.ToString(), Marker.Time));
	}
	if (!bAllowOmittingCurvesNotifiesAndMarkers
		&& (Result.OmittedNotifyCount || Result.OmittedCurveEntryCount || Result.OmittedSyncMarkerCount))
	{
		return Fail(TEXT("Metadata would be lost. Explicitly allow omission for a visual-only test, or choose a clip without these channels."));
	}
	const FCompressedAnimSequence& Compressed = SourceAnimation->CompressedData;
	if (!Compressed.CompressedDataStructure || !Compressed.CompressedDataStructure->IsValid()
		|| !Compressed.BoneCompressionCodec || !SourceAnimation->IsCompressedDataValid() || SourceAnimation->OnlyUseRawData())
	{
		return Fail(TEXT("Cooked compressed bone data/codec is missing, invalid or stale. Refusing the native decoder's identity/raw-data fallback."));
	}
	const FString BoneCodecClass = Compressed.BoneCompressionCodec->GetClass()->GetPathName();
	if (BoneCodecClass != TEXT("/Script/ACLPlugin.AnimBoneCompressionCodec_ACL"))
	{
		return Fail(TEXT("Unverified source codec: ") + BoneCodecClass + TEXT(". This Rebirth MVP accepts its native ACL bone codec only."));
	}
	if (!SourceAnimation->BoneCompressionSettings || !SourceAnimation->CurveCompressionSettings
		|| !SourceAnimation->BoneCompressionSettings->AreSettingsValid() || !SourceAnimation->CurveCompressionSettings->AreSettingsValid()
		|| SourceAnimation->BoneCompressionSettings->Codecs.Num() != 1
		|| SourceAnimation->BoneCompressionSettings->Codecs[0] != Compressed.BoneCompressionCodec
		|| SourceAnimation->BoneCompressionSettings->GetPathName() != TEXT("/Game/Animation/CompressionSettings/AnimBoneCompressionSettingsACL.AnimBoneCompressionSettingsACL")
		|| SourceAnimation->CurveCompressionSettings->GetPathName() != TEXT("/Game/Animation/CompressionSettings/AnimCurveCompressionSettingsACL.AnimCurveCompressionSettingsACL"))
	{
		return Fail(TEXT("The native Rebirth ACL compression settings are missing or unexpected; do not silently substitute another compressor/settings path."));
	}
	const FReferenceSkeleton& SourceRef = SourceSkeleton->GetReferenceSkeleton();
	const FReferenceSkeleton& TargetRef = TargetSkeleton->GetReferenceSkeleton();
	// Native extraction removes the initial root transform. Retaining component-axis
	// displacement is only a validated policy when the two bind root rotations agree.
	if (SourceRef.GetRawRefBonePose()[0].GetRotation().GetNormalized().AngularDistance(TargetRef.GetRawRefBonePose()[0].GetRotation().GetNormalized()) > 0.001f)
	{
		return Fail(TEXT("The bind root orientations differ. This MVP cannot preserve root-motion extraction axes for that pair."));
	}
	const TArray<FTrackToSkeletonMap>& CompressedMap = SourceAnimation->GetCompressedTrackToSkeletonMapTable();
	Result.SourceCompressedTrackCount = CompressedMap.Num();
	if (CompressedMap.Num() < 1 || CompressedMap.Num() > 65535)
	{
		return Fail(TEXT("The compressed track map is empty or oversized."));
	}
	TSet<int32> TrackBones;
	int32 SourceRootTrack = INDEX_NONE;
	int32 VirtualTracks = 0;
	for (int32 Track = 0; Track < CompressedMap.Num(); ++Track)
	{
		const int32 Bone = CompressedMap[Track].BoneTreeIndex;
		if (Bone < 0 || Bone >= SourceRef.GetNum() || TrackBones.Contains(Bone))
		{
			return Fail(TEXT("The compressed map has an invalid or duplicate skeleton bone index."));
		}
		TrackBones.Add(Bone);
		if (Bone == 0)
		{
			SourceRootTrack = Track;
		}
		if (Bone >= SourceRef.GetRawBoneNum())
		{
			++VirtualTracks;
		}
	}
	if (SourceRootTrack != 0)
	{
		return Fail(TEXT("The source must have skeleton bone zero as compressed track zero for a validated root-motion policy."));
	}
	const int32 NumFrames = SourceAnimation->GetRawNumberOfFrames();
	if (NumFrames < 1 || NumFrames > 10000 || int64(NumFrames) * TargetRef.GetRawBoneNum() > 2000000)
	{
		return Fail(TEXT("Invalid or excessive sample count; the MVP is limited to 10,000 frames and 2,000,000 target bone samples."));
	}
	if (Compressed.CompressedDataStructure->CompressedNumberOfFrames < 1
		|| Compressed.CompressedDataStructure->CompressedNumberOfFrames > NumFrames)
	{
		return Fail(TEXT("The native compressed frame count is invalid or exceeds the sequence frame count."));
	}
	TArray<int32> TargetToSource;
	TArray<FString> MapReasons;
	if (!BuildBoneMap(SourceRef, TargetRef, SourceToTargetBoneMap, TargetToSource, MapReasons, Error))
	{
		return Fail(Error);
	}
	if (TargetToSource[0] != 0)
	{
		return Fail(TEXT("The receiving root must map one-to-one to source skeleton bone zero."));
	}
	TArray<bool> SourceNeeded;
	SourceNeeded.Init(false, SourceRef.GetRawBoneNum());
	for (int32 Bone = 0; Bone < TargetToSource.Num(); ++Bone)
	{
		if (TargetToSource[Bone] != INDEX_NONE)
		{
			++Result.ConvertedBoneCount;
			SourceNeeded[TargetToSource[Bone]] = true;
			if (!TrackBones.Contains(TargetToSource[Bone]))
			{
				Result.Diagnostics.Add(FString::Printf(TEXT("Source bind pose used for mapped bone %s: no compressed track is present."), *SourceRef.GetBoneName(TargetToSource[Bone]).ToString()));
			}
		}
		else
		{
			Result.ReferencePoseBones.Add(TargetRef.GetBoneName(Bone));
			Result.Diagnostics.Add(FString::Printf(TEXT("Target bind pose: %s (%s)."), *TargetRef.GetBoneName(Bone).ToString(), *MapReasons[Bone]));
		}
	}
	if (Result.ConvertedBoneCount < 2)
	{
		return Fail(TEXT("Only the root is mapped; no useful ordinary body conversion is possible."));
	}
	FText PackageError;
	FString Filename;
	if (!DestinationPackageName.StartsWith(TEXT("/Game/"))
		|| !FPackageName::IsValidLongPackageName(DestinationPackageName, false, &PackageError)
		|| !FPackageName::TryConvertLongPackageNameToFilename(DestinationPackageName, Filename, FPackageName::GetAssetPackageExtension()))
	{
		return Fail(TEXT("Destination must be a valid new writable /Game/.../AssetName package. ") + PackageError.ToString());
	}
	if (FindPackage(nullptr, *DestinationPackageName) || FPackageName::DoesPackageExist(DestinationPackageName)
		|| IFileManager::Get().FileExists(*Filename))
	{
		return Fail(TEXT("The destination already exists. Choose a new package; this tool never overwrites assets."));
	}

	const FGuid TargetGuid = TargetSkeleton->GetGuid();
	const FGuid TargetVirtualGuid = TargetSkeleton->GetVirtualBoneGuid();
	const bool bTargetWasDirty = TargetSkeleton->GetOutermost()->IsDirty();
	const TArray<FMeshBoneInfo> TargetInfos = TargetRef.GetRawRefBoneInfo();
	const TArray<FTransform> TargetBindLocal = TargetRef.GetRawRefBonePose();
	TArray<FTransform> SourceBindCS, TargetBindCS;
	BuildComponentPoses(SourceRef, SourceRef.GetRawRefBonePose(), SourceBindCS);
	BuildComponentPoses(TargetRef, TargetBindLocal, TargetBindCS);
	TArray<FRawAnimSequenceTrack> Tracks;
	Tracks.SetNum(TargetRef.GetRawBoneNum());
	for (int32 Bone = 0; Bone < Tracks.Num(); ++Bone)
	{
		Tracks[Bone].PosKeys.Add(TargetBindLocal[Bone].GetTranslation());
		Tracks[Bone].ScaleKeys.Add(TargetBindLocal[Bone].GetScale3D());
		Tracks[Bone].RotKeys.Reserve(NumFrames);
	}
	Tracks[0].PosKeys.Reset(NumFrames);
	TArray<FTransform> SourceLocal, SourceCS, TargetCS;
	TargetCS.SetNum(TargetRef.GetRawBoneNum());
	TArray<bool> DiscardedTranslation;
	DiscardedTranslation.Init(false, TargetRef.GetRawBoneNum());
	for (int32 Frame = 0; Frame < NumFrames; ++Frame)
	{
		const float Time = NumFrames == 1 ? 0.0f : SourceAnimation->SequenceLength * (float(Frame) / float(NumFrames - 1));
		SourceLocal = SourceRef.GetRawRefBonePose();
		for (int32 Track = 0; Track < CompressedMap.Num(); ++Track)
		{
			const int32 Bone = CompressedMap[Track].BoneTreeIndex;
			if (Bone >= SourceRef.GetRawBoneNum())
			{
				continue;
			}
			FTransform Decoded = FTransform::Identity;
			// Native API takes the compressed TRACK index, never the skeleton bone index.
			SourceAnimation->GetBoneTransform(Decoded, Track, Time, false);
			if (!Decoded.IsValid() || (SourceNeeded[Bone] && !Decoded.GetScale3D().Equals(FVector::OneVector, 0.001f)))
			{
				return Fail(FString::Printf(TEXT("Invalid transform or unsupported animated scale at source bone %s, frame %d."), *SourceRef.GetBoneName(Bone).ToString(), Frame));
			}
			Decoded.NormalizeRotation();
			SourceLocal[Bone] = Decoded;
		}
		BuildComponentPoses(SourceRef, SourceLocal, SourceCS);
		for (int32 Bone = 0; Bone < TargetRef.GetRawBoneNum(); ++Bone)
		{
			FTransform Local = TargetBindLocal[Bone];
			const int32 SourceBone = TargetToSource[Bone];
			const int32 Parent = TargetRef.GetParentIndex(Bone);
			if (SourceBone != INDEX_NONE)
			{
				// At source bind pose this is exactly the target bind orientation.
				FQuat ComponentRotation = SourceCS[SourceBone].GetRotation()
					* SourceBindCS[SourceBone].GetRotation().Inverse() * TargetBindCS[Bone].GetRotation();
				ComponentRotation.Normalize();
				FQuat LocalRotation = Parent == INDEX_NONE ? ComponentRotation : TargetCS[Parent].GetRotation().Inverse() * ComponentRotation;
				LocalRotation.Normalize();
				Local.SetRotation(LocalRotation);
				if (Bone == 0)
				{
					const FVector Displacement = SourceLocal[SourceBone].GetTranslation() - SourceRef.GetRawRefBonePose()[SourceBone].GetTranslation();
					Local.SetTranslation(TargetBindLocal[0].GetTranslation() + Displacement * RootTranslationScale);
				}
				else
				{
					const float Delta = (SourceLocal[SourceBone].GetTranslation() - SourceRef.GetRawRefBonePose()[SourceBone].GetTranslation()).Size();
					if (Delta > 0.01f)
					{
						DiscardedTranslation[Bone] = true;
						Result.LargestDiscardedChildTranslation = FMath::Max(Result.LargestDiscardedChildTranslation, Delta);
					}
				}
			}
			TargetCS[Bone] = Parent == INDEX_NONE ? Local : Local * TargetCS[Parent];
			TargetCS[Bone].NormalizeRotation();
			if (!Local.IsValid() || !TargetCS[Bone].IsValid())
			{
				return Fail(FString::Printf(TEXT("Invalid converted pose at target bone %s, frame %d."), *TargetRef.GetBoneName(Bone).ToString(), Frame));
			}
			FQuat Rotation = Local.GetRotation();
			if (Frame > 0 && (Tracks[Bone].RotKeys.Last() | Rotation) < 0.0f)
			{
				Rotation = Rotation * -1.0f;
			}
			Tracks[Bone].RotKeys.Add(Rotation);
			if (Bone == 0)
			{
				Tracks[Bone].PosKeys.Add(Local.GetTranslation());
			}
		}
	}
	for (int32 Bone = 1; Bone < DiscardedTranslation.Num(); ++Bone)
	{
		if (DiscardedTranslation[Bone])
		{
			++Result.ChildBonesWithDiscardedTranslation;
		}
	}
	Result.SampledFrameCount = NumFrames;
	Result.Diagnostics.Add(FString::Printf(TEXT("Root displacement multiplier %.6f; child translations/scales use target bind pose. %d child bones had translated keys, largest discarded displacement %.6f. No foot/hand IK or weapon-grip solve was performed."),
		RootTranslationScale, Result.ChildBonesWithDiscardedTranslation, Result.LargestDiscardedChildTranslation));
	Result.Diagnostics.Add(FString::Printf(TEXT("%d source virtual-bone tracks ignored; the target's own virtual bones are handled by native compression. Preview references and transient editor package data are not copied."), VirtualTracks));

	// Finish and validate a transient asset before creating anything at the destination path.
	TStrongObjectPtr<UAnimSequence> NewSequence(NewObject<UAnimSequence>(GetTransientPackage(), NAME_None, RF_Transient));
	NewSequence->SetSkeleton(TargetSkeleton);
	NewSequence->SequenceLength = SourceAnimation->SequenceLength;
	NewSequence->SetRawNumberOfFrame(NumFrames);
	NewSequence->RateScale = SourceAnimation->RateScale;
	NewSequence->Interpolation = SourceAnimation->Interpolation;
	NewSequence->RootMotionScale = SourceAnimation->RootMotionScale;
	NewSequence->bEnableRootMotion = SourceAnimation->bEnableRootMotion;
	NewSequence->RootMotionRootLock = SourceAnimation->RootMotionRootLock;
	NewSequence->bForceRootLock = SourceAnimation->bForceRootLock;
	NewSequence->bUseNormalizedRootMotionScale = SourceAnimation->bUseNormalizedRootMotionScale;
	NewSequence->bRootMotionSettingsCopiedFromMontage = SourceAnimation->bRootMotionSettingsCopiedFromMontage;
	NewSequence->BoneCompressionSettings = SourceAnimation->BoneCompressionSettings;
	NewSequence->CurveCompressionSettings = SourceAnimation->CurveCompressionSettings;
	NewSequence->RetargetSource = NAME_None;
	NewSequence->bAllowFrameStripping = false;
	for (int32 Bone = 0; Bone < Tracks.Num(); ++Bone)
	{
		if (NewSequence->AddNewRawTrack(TargetRef.GetBoneName(Bone), &Tracks[Bone]) != Bone)
		{
			return Fail(TEXT("Failed to establish raw tracks in receiving skeleton order."));
		}
	}
	// AddNewRawTrack establishes the skeleton index; validate it without calling a private engine helper.
	const TArray<FTrackToSkeletonMap>& RawTrackMap = NewSequence->GetRawTrackToSkeletonMapTable();
	if (RawTrackMap.Num() != Tracks.Num())
	{
		return Fail(TEXT("Native raw-track creation did not establish the receiving track map."));
	}
	for (int32 Bone = 0; Bone < RawTrackMap.Num(); ++Bone)
	{
		if (RawTrackMap[Bone].BoneTreeIndex != Bone)
		{
			return Fail(TEXT("Native raw-track creation produced an unexpected receiving skeleton index."));
		}
	}
	NewSequence->PostProcessSequence();
	NewSequence->RequestSyncAnimRecompression();
	const FCompressedAnimSequence& OutputCompressed = NewSequence->CompressedData;
	const TArray<FTrackToSkeletonMap>& OutputMap = NewSequence->GetCompressedTrackToSkeletonMapTable();
	if (NewSequence->OnlyUseRawData() || !OutputCompressed.CompressedDataStructure
		|| !OutputCompressed.CompressedDataStructure->IsValid() || !OutputCompressed.BoneCompressionCodec
		|| OutputCompressed.CompressedDataStructure->CompressedNumberOfFrames != NumFrames
		|| OutputCompressed.BoneCompressionCodec->GetClass()->GetPathName() != BoneCodecClass
		|| OutputMap.Num() < 1 || OutputMap[0].BoneTreeIndex != 0 || NewSequence->GetSkeleton() != TargetSkeleton)
	{
		return Fail(TEXT("Native target compression did not produce a valid receiving-skeleton ACL animation with root track zero."));
	}
	TSet<int32> OutputBones;
	for (const FTrackToSkeletonMap& Track : OutputMap)
	{
		if (Track.BoneTreeIndex < 0 || Track.BoneTreeIndex >= TargetRef.GetNum() || OutputBones.Contains(Track.BoneTreeIndex))
		{
			return Fail(TEXT("Native compression produced an invalid or duplicate target track index."));
		}
		OutputBones.Add(Track.BoneTreeIndex);
	}
	for (int32 Bone = 0; Bone < TargetRef.GetRawBoneNum(); ++Bone)
	{
		if (!OutputBones.Contains(Bone))
		{
			return Fail(TEXT("Native compression omitted a target raw-bone track; the MVP requires a complete receiving track map."));
		}
	}
	// Check the new native decoder against the actual baked keys before publishing any package.
	// These bounded MVP tolerances are in Unreal units (centimeters), radians and unit scale.
	const float MaxPositionError = 0.05f;
	const float MaxRotationError = FMath::DegreesToRadians(0.25f);
	for (int32 Track = 0; Track < OutputMap.Num(); ++Track)
	{
		const int32 Bone = OutputMap[Track].BoneTreeIndex;
		if (Bone >= TargetRef.GetRawBoneNum())
		{
			continue; // Native compression creates target virtual-bone tracks separately.
		}
		const FRawAnimSequenceTrack& Expected = Tracks[Bone];
		for (int32 Frame = 0; Frame < NumFrames; ++Frame)
		{
			const float Time = NumFrames == 1 ? 0.0f : NewSequence->SequenceLength * (float(Frame) / float(NumFrames - 1));
			FTransform Decoded = FTransform::Identity;
			NewSequence->GetBoneTransform(Decoded, Track, Time, false);
			const FVector& ExpectedPosition = Expected.PosKeys[Expected.PosKeys.Num() == 1 ? 0 : Frame];
			const FQuat& ExpectedRotation = Expected.RotKeys[Frame];
			if (!Decoded.IsValid() || FVector::Dist(Decoded.GetTranslation(), ExpectedPosition) > MaxPositionError
				|| Decoded.GetRotation().AngularDistance(ExpectedRotation) > MaxRotationError
				|| !Decoded.GetScale3D().Equals(Expected.ScaleKeys[0], 0.001f))
			{
				return Fail(FString::Printf(TEXT("Native compressed output failed baked-pose validation at target bone %s, frame %d (limits: 0.05 cm, 0.25 degrees, 0.001 scale)."), *TargetRef.GetBoneName(Bone).ToString(), Frame));
			}
		}
	}
	Result.Diagnostics.Add(TEXT("Native compressed output was decoded and checked against every baked raw-bone key (0.05 cm, 0.25 degrees, 0.001 scale limits)."));
	auto RootMotionMatches = [&](float StartTime, float EndTime)
	{
		const FTransform SourceMotion = SourceAnimation->ExtractRootMotionFromRange(StartTime, EndTime);
		const FTransform TargetMotion = NewSequence->ExtractRootMotionFromRange(StartTime, EndTime);
		return SourceMotion.IsValid() && TargetMotion.IsValid()
			&& FVector::Dist(TargetMotion.GetTranslation(), SourceMotion.GetTranslation() * RootTranslationScale) <= MaxPositionError
			&& TargetMotion.GetRotation().AngularDistance(SourceMotion.GetRotation()) <= MaxRotationError
			&& TargetMotion.GetScale3D().Equals(SourceMotion.GetScale3D(), 0.001f);
	};
	if (!RootMotionMatches(0.0f, SourceAnimation->SequenceLength))
	{
		return Fail(TEXT("Native root-motion extraction did not preserve the full-clip rotation and explicitly scaled translation."));
	}
	for (int32 Frame = 1; Frame < NumFrames; ++Frame)
	{
		const float StartTime = SourceAnimation->SequenceLength * (float(Frame - 1) / float(NumFrames - 1));
		const float EndTime = SourceAnimation->SequenceLength * (float(Frame) / float(NumFrames - 1));
		if (!RootMotionMatches(StartTime, EndTime))
		{
			return Fail(FString::Printf(TEXT("Native root-motion extraction failed between frames %d and %d (limits: 0.05 cm, 0.25 degrees, 0.001 scale)."), Frame - 1, Frame));
		}
	}
	Result.Diagnostics.Add(TEXT("Native extracted root motion matched the source rotation and explicitly scaled translation over the full clip and every adjacent frame interval."));
	if (!ReceiverUnchanged(TargetSkeleton, TargetGuid, TargetVirtualGuid, TargetInfos, TargetBindLocal, bTargetWasDirty))
	{
		return Fail(TEXT("The receiving skeleton changed during conversion. Refusing to publish the generated clip."));
	}
	UPackage* Destination = CreatePackage(*DestinationPackageName);
	if (!Destination || Destination->HasAnyPackageFlags(PKG_Cooked | PKG_FilterEditorOnly))
	{
		return Fail(TEXT("Could not create a new editable destination package."));
	}
	const FString AssetName = FPackageName::GetLongPackageAssetName(DestinationPackageName);
	if (!NewSequence->Rename(*AssetName, Destination, REN_DontCreateRedirectors | REN_NonTransactional))
	{
		return Fail(TEXT("Could not place the generated animation in its new destination package."));
	}
	NewSequence->ClearFlags(RF_Transient);
	NewSequence->SetFlags(RF_Public | RF_Standalone);
	NewSequence->MarkPackageDirty();
	Result.CreatedAnimation = NewSequence.Get();
	FAssetRegistryModule::AssetCreated(Result.CreatedAnimation);
	if (bSaveAsset)
	{
		if (!IFileManager::Get().MakeDirectory(*FPaths::GetPath(Filename), true)
			|| !UPackage::SavePackage(Destination, Result.CreatedAnimation, RF_Public | RF_Standalone, *Filename,
				GError, nullptr, false, true, SAVE_None, nullptr, FDateTime::MinValue(), false)
			|| !IFileManager::Get().FileExists(*Filename))
		{
			return Fail(TEXT("The generated asset exists in memory, but saving failed. It has not been cooked or tested in game."));
		}
		Result.bSaved = true;
		Result.SavedFilename = FPaths::ConvertRelativePathToFull(Filename);
	}
	Result.Diagnostics.Add(TEXT("Created an ordinary target-skeleton UAnimSequence. Root-motion flags including montage policy, RateScale, Interpolation and Rebirth RootMotionScale were preserved; no source compressed bytes, package flags, skeleton edits or runtime compatibility extensions were copied."));
	Result.Diagnostics.Add(bSaveAsset ? TEXT("Editable asset saved. Cook/reload, decoded-pose/root-motion validation and in-game playback are still required.")
		: TEXT("Editable asset is in memory and unsaved. Cook/reload and in-game playback are still required."));
	Result.bSucceeded = true;
#else
	Result.Diagnostics.Add(TEXT("Animation conversion is available in the editor only."));
#endif
	return Result;
}
