#pragma once
#include "CoreMinimal.h"
#include "HSFLipSyncDataEmotion.h"
#include "HSFLipSyncDataInfo.h"
#include "HSFLipSyncDataKeyFrame.h"
#include "HSFLipSyncDataLsdmlPoseWeights.h"
#include "HSFLipSyncData.generated.h"

USTRUCT(BlueprintType)
struct HSFLIPSYNCRUNTIME_API FHSFLipSyncData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FHSFLipSyncDataInfo Info;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FHSFLipSyncDataKeyFrame> KeyFrames;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FHSFLipSyncDataKeyFrame> OverrideKeyFrames;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUseLsdml;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FHSFLipSyncDataLsdmlPoseWeights> LsdmlPoseWeights;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> LsdmlPoseNames;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FHSFLipSyncDataEmotion> Emotions;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FHSFLipSyncDataEmotion> OverrideEmotions;
    
    FHSFLipSyncData();
};

