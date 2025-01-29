#pragma once
#include "CoreMinimal.h"
#include "EEndAnimalRunTimerType.h"
#include "EndBTDecorator_InvokeBase.h"
#include "EndBTDecorator_RunWildSetTimer.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_RunWildSetTimer : public UEndBTDecorator_InvokeBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimalRunTimerType Type;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bStop;
    
    UEndBTDecorator_RunWildSetTimer();

};

