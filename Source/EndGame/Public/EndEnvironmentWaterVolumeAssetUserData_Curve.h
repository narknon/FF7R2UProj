#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndEnvironmentWaterVolumeAssetUserData_Curve.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndEnvironmentWaterVolumeAssetUserData_Curve {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FVector> Points;
    
    FEndEnvironmentWaterVolumeAssetUserData_Curve();
};

