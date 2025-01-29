#pragma once
#include "CoreMinimal.h"
#include "EEndAICautionType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_CheckCautionType.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_CheckCautionType : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAICautionType CheckType;
    
    UEndBTDecorator_CheckCautionType();

};

