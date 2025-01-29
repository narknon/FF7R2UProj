#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EEndBattleStatusChangeEffectType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_HasStatusChangeEffectType.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_HasStatusChangeEffectType : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector CharacterBBKey;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndBattleStatusChangeEffectType> Types;
    
    UEndBTDecorator_HasStatusChangeEffectType();

};

