#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EndBTTask_AIPCAttackBase.h"
#include "EndBTTask_AIPCContinuousAttack.generated.h"

UCLASS(Blueprintable)
class UEndBTTask_AIPCContinuousAttack : public UEndBTTask_AIPCAttackBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector CombatRangeCoefficientBlackboardKey;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bForceMaxTime;
    
    UEndBTTask_AIPCContinuousAttack();

};

