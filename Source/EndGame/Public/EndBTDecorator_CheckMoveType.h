#pragma once
#include "CoreMinimal.h"
#include "EEndMoveType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_CheckMoveType.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_CheckMoveType : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndMoveType MoveType;
    
    UEndBTDecorator_CheckMoveType();

};

