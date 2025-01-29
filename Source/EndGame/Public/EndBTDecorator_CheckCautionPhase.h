#pragma once
#include "CoreMinimal.h"
#include "EEndAIEnemyCautionPhase.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_CheckCautionPhase.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_CheckCautionPhase : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIEnemyCautionPhase CheckPhase;
    
    UEndBTDecorator_CheckCautionPhase();

};

