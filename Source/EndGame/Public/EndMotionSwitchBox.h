#pragma once
#include "CoreMinimal.h"
#include "EndTriggerBox.h"
#include "EndMotionSwitchBox.generated.h"

UCLASS(Blueprintable)
class AEndMotionSwitchBox : public AEndTriggerBox {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MotionSwitchName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bIgnoreLowerPriorityAnimSet;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName BeginOverlapPlayActionName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName EndOverlapPlayActionName;
    
public:
    AEndMotionSwitchBox(const FObjectInitializer& ObjectInitializer);

};

