#pragma once
#include "CoreMinimal.h"
#include "EEndAnimalRunAIPhase.h"
#include "EndBTDecorator_InvokeBase.h"
#include "EndBTDecorator_RunWildSetPhase.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_RunWildSetPhase : public UEndBTDecorator_InvokeBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimalRunAIPhase Phase;
    
    UEndBTDecorator_RunWildSetPhase();

};

