#pragma once
#include "CoreMinimal.h"
#include "EndAnimationSettingsBlend.generated.h"

USTRUCT(BlueprintType)
struct FEndAnimationSettingsBlend {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FieldAndBattleBehaviorActionDefaultBlendTime;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float EventBehaviorActionDefaultBlendTime;
    
    ENDGAME_API FEndAnimationSettingsBlend();
};

