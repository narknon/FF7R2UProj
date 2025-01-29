#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTD_IsSummonMinRangeAbility.generated.h"

UCLASS(Blueprintable)
class UEndBTD_IsSummonMinRangeAbility : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector FromBlackboardKey_AbilityID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector FromBlackboardKey_ComboCount;
    
    UEndBTD_IsSummonMinRangeAbility();

};

