#pragma once
#include "CoreMinimal.h"
#include "EEndAiMoveType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_IsRequestMoveType.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_IsRequestMoveType : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndAiMoveType> MoveTypes;
    
    UEndBTDecorator_IsRequestMoveType();

};

