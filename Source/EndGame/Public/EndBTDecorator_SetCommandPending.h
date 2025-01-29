#pragma once
#include "CoreMinimal.h"
#include "EndBTDecorator_InvokeBase.h"
#include "EndBTDecorator_SetCommandPending.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_SetCommandPending : public UEndBTDecorator_InvokeBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool Value;
    
    UEndBTDecorator_SetCommandPending();

};

