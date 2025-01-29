#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "EEndBTDecoratorInvokeType.h"
#include "EndBTDecorator_InvokeBase.generated.h"

UCLASS(Abstract, Blueprintable)
class UEndBTDecorator_InvokeBase : public UBTDecorator {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndBTDecoratorInvokeType InvokeType;
    
    UEndBTDecorator_InvokeBase();

};

