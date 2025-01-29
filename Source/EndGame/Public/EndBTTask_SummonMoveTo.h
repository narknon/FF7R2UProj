#pragma once
#include "CoreMinimal.h"
#include "EndBTTask_MoveTo.h"
#include "EndBTTask_SummonMoveTo.generated.h"

UCLASS(Blueprintable)
class UEndBTTask_SummonMoveTo : public UEndBTTask_MoveTo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float StuckTimeLimit;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MoveTimeLimit;
    
    UEndBTTask_SummonMoveTo();

};

