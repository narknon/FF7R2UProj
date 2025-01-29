#pragma once
#include "CoreMinimal.h"
#include "EndVehicleZeroOneModifierSetting.h"
#include "EndVehicleZeroOneSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndVehicleZeroOneSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndVehicleZeroOneModifierSetting ZeroOneModifierSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ZeroOneFadeTime;
    
    ENDGAME_API FEndVehicleZeroOneSetting();
};

