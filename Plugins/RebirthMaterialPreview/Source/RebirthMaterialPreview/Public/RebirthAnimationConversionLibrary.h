#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RebirthAnimationConversionLibrary.generated.h"

class UAnimSequence;
class USkeleton;

USTRUCT(BlueprintType)
struct REBIRTHMATERIALPREVIEW_API FRebirthSkeletonInspection
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	bool bSucceeded = false;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	FString SourceSkeletonPath;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	FString TargetSkeletonPath;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	int32 SourceBoneCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	int32 TargetBoneCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	int32 SourceVirtualBoneCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	int32 TargetVirtualBoneCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	int32 SharedNameCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	int32 CompatibleChainCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	TArray<FName> SourceOnlyBones;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	TArray<FName> TargetOnlyBones;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	TArray<FString> ParentChainDifferences;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	TArray<FString> Diagnostics;
};

USTRUCT(BlueprintType)
struct REBIRTHMATERIALPREVIEW_API FRebirthAnimationConversionResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	bool bSucceeded = false;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	bool bSaved = false;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	UAnimSequence* CreatedAnimation = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	FString DestinationPackageName;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	FString SavedFilename;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	int32 SourceCompressedTrackCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	int32 ConvertedBoneCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	int32 SampledFrameCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	int32 OmittedNotifyCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	int32 OmittedCurveEntryCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	int32 OmittedSyncMarkerCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	int32 ChildBonesWithDiscardedTranslation = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	float LargestDiscardedChildTranslation = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	TArray<FName> ReferencePoseBones;
	UPROPERTY(BlueprintReadOnly, Category = "Rebirth|Animation")
	TArray<FString> Diagnostics;
};

/** Editor utility only. Generated assets use the game's existing UAnimSequence/USkeleton types. */
UCLASS()
class REBIRTHMATERIALPREVIEW_API URebirthAnimationConversionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Inspect actual loaded skeletons. Counts exclude virtual bones; differences use exact bone names. */
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Animation", meta = (DevelopmentOnly))
	static FRebirthSkeletonInspection InspectSkeletons(USkeleton* SourceSkeleton, USkeleton* TargetSkeleton);

	/**
	 * Bake one ordinary cooked ACL clip onto an unchanged receiving skeleton.
	 * DestinationPackageName is a NEW /Game/.../AssetName package, never an existing asset.
	 * SourceToTargetBoneMap overrides same-name matching; this MVP requires one-to-one parent chains.
	 * RootTranslationScale scales root displacement from bind pose in the existing component axes.
	 * Child translations/scales use the target bind pose; this is a rotation/trajectory MVP, without IK.
	 * Curves, native notifies and sync markers require explicit permission to omit; custom metadata is refused.
	 * Saving creates an editable source asset; a successful cook and in-game test remain necessary.
	 */
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Animation", meta = (DevelopmentOnly))
	static FRebirthAnimationConversionResult ConvertCookedAnimation(
		UAnimSequence* SourceAnimation,
		USkeleton* TargetSkeleton,
		const FString& DestinationPackageName,
		const TMap<FName, FName>& SourceToTargetBoneMap,
		float RootTranslationScale,
		bool bAllowOmittingCurvesNotifiesAndMarkers,
		bool bSaveAsset);
};
