#pragma once
#include "CoreMinimal.h"
#include "EndChocoboFieldGridMovementModifierParam.generated.h"

USTRUCT(BlueprintType)
struct FEndChocoboFieldGridMovementModifierParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 OverrideAffectLevel;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RotationPowerScale;
    
    ENDGAME_API FEndChocoboFieldGridMovementModifierParam();
};

