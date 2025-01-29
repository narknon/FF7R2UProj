#pragma once
#include "CoreMinimal.h"
#include "EPlayerType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_CheckPlayerType.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_CheckPlayerType : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EPlayerType Type;
    
    UEndBTDecorator_CheckPlayerType();

};

