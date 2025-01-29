#pragma once
#include "CoreMinimal.h"
#include "EEndAIFrogGuysType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_MiniGameCheckFrogGuysType.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_MiniGameCheckFrogGuysType : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIFrogGuysType Type;
    
    UEndBTDecorator_MiniGameCheckFrogGuysType();

};

