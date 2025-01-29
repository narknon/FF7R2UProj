#pragma once
#include "CoreMinimal.h"
#include "EndBTTask_MoveTo.h"
#include "EndBTTask_RunWildMoveToBall.generated.h"

UCLASS(Blueprintable)
class UEndBTTask_RunWildMoveToBall : public UEndBTTask_MoveTo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bWrapAround;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bWrapAroundToTargetSide;
    
    UEndBTTask_RunWildMoveToBall();

};

