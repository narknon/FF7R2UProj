#pragma once
#include "CoreMinimal.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_IsInAttackCoolDown.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_IsInAttackCoolDown : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UEndBTDecorator_IsInAttackCoolDown();

};

