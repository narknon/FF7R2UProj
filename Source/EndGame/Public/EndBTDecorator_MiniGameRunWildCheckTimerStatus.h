#pragma once
#include "CoreMinimal.h"
#include "EEndAnimalRunTimerType.h"
#include "EEndRunWildCheckTimerStatusType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_MiniGameRunWildCheckTimerStatus.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_MiniGameRunWildCheckTimerStatus : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimalRunTimerType Type;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndRunWildCheckTimerStatusType CheckStatusType;
    
    UEndBTDecorator_MiniGameRunWildCheckTimerStatus();

};

