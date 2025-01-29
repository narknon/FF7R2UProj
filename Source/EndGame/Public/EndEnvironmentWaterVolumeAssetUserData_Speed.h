#pragma once
#include "CoreMinimal.h"
#include "EndEnvironmentWaterVolumeAssetUserData_Speed.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndEnvironmentWaterVolumeAssetUserData_Speed {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<float> Flows;
    
    FEndEnvironmentWaterVolumeAssetUserData_Speed();
};

