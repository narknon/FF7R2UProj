#pragma once
#include "CoreMinimal.h"
#include "EndBTDecorator_InvokeBase.h"
#include "EndBTDecorator_SetFollowSteeringParameter.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_SetFollowSteeringParameter : public UEndBTDecorator_InvokeBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bApply;
    
    UEndBTDecorator_SetFollowSteeringParameter();

};

