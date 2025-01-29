#pragma once
#include "CoreMinimal.h"
#include "EndChocoboSliderSpeedSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndChocoboSliderSpeedSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PitchAngle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MaxSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Acceleration;
    
    ENDGAME_API FEndChocoboSliderSpeedSetting();
};

