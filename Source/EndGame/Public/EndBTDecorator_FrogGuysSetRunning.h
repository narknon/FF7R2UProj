#pragma once
#include "CoreMinimal.h"
#include "EndBTDecorator_InvokeBase.h"
#include "EndBTDecorator_FrogGuysSetRunning.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_FrogGuysSetRunning : public UEndBTDecorator_InvokeBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool AllowRunning;
    
    UEndBTDecorator_FrogGuysSetRunning();

};

