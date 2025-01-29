#pragma once
#include "CoreMinimal.h"
#include "EndBTTask_Jump.h"
#include "EndBTTask_AppearInJump.generated.h"

UCLASS(Blueprintable)
class UEndBTTask_AppearInJump : public UEndBTTask_Jump {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bResetMovementMode;
    
    UEndBTTask_AppearInJump();

};

