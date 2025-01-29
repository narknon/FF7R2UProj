#pragma once
#include "CoreMinimal.h"
#include "EEndBattleSpecialStatusChangeType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_IsSetCancelSpecialStatusChange.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_IsSetCancelSpecialStatusChange : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndBattleSpecialStatusChangeType Type;
    
    UEndBTDecorator_IsSetCancelSpecialStatusChange();

};

