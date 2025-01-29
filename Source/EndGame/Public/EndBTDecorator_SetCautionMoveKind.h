#pragma once
#include "CoreMinimal.h"
#include "EEndAIEnemyCautionMoveKind.h"
#include "EndBTDecorator_InvokeBase.h"
#include "EndBTDecorator_SetCautionMoveKind.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_SetCautionMoveKind : public UEndBTDecorator_InvokeBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIEnemyCautionMoveKind MoveKind;
    
    UEndBTDecorator_SetCautionMoveKind();

};

