#pragma once
#include "CoreMinimal.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTD_IsSummonCommandStackEmpty.generated.h"

UCLASS(Blueprintable)
class UEndBTD_IsSummonCommandStackEmpty : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UEndBTD_IsSummonCommandStackEmpty();

};

