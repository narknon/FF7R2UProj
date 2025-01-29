#pragma once
#include "CoreMinimal.h"
#include "EEndAiMoveType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_CheckBattleCautionMoveType.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_CheckBattleCautionMoveType : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAiMoveType Type;
    
    UEndBTDecorator_CheckBattleCautionMoveType();

};

