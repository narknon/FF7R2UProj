#pragma once
#include "CoreMinimal.h"
#include "ECautionMoveKind.h"
#include "EndBTTask_MoveTo.h"
#include "EndBTTask_CautionMoveTo.generated.h"

UCLASS(Blueprintable)
class UEndBTTask_CautionMoveTo : public UEndBTTask_MoveTo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<ECautionMoveKind::Type> CautionMoveKind;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bFixLocationInRequestedMoveTo;
    
    UEndBTTask_CautionMoveTo();

};

