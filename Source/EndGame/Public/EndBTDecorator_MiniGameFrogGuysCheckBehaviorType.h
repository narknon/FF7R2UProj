#pragma once
#include "CoreMinimal.h"
#include "EEndAIFrogGuysBehaviorType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_MiniGameFrogGuysCheckBehaviorType.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_MiniGameFrogGuysCheckBehaviorType : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIFrogGuysBehaviorType Type;
    
    UEndBTDecorator_MiniGameFrogGuysCheckBehaviorType();

};

