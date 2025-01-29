#pragma once
#include "CoreMinimal.h"
#include "EndAnimationSettingsBattle.generated.h"

USTRUCT(BlueprintType)
struct FEndAnimationSettingsBattle {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DropWeaponVelocityBias;
    
    ENDGAME_API FEndAnimationSettingsBattle();
};

