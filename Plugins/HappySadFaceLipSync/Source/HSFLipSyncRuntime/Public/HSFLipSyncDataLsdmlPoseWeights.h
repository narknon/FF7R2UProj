#pragma once
#include "CoreMinimal.h"
#include "HSFLipSyncDataLsdmlPoseWeights.generated.h"

USTRUCT(BlueprintType)
struct HSFLIPSYNCRUNTIME_API FHSFLipSyncDataLsdmlPoseWeights {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<float> Weights;
    
    FHSFLipSyncDataLsdmlPoseWeights();
};

