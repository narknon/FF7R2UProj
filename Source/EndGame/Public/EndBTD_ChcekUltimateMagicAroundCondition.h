#pragma once
#include "CoreMinimal.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTD_ChcekUltimateMagicAroundCondition.generated.h"

UCLASS(Blueprintable)
class UEndBTD_ChcekUltimateMagicAroundCondition : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Radius;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Height;
    
    UEndBTD_ChcekUltimateMagicAroundCondition();

};

