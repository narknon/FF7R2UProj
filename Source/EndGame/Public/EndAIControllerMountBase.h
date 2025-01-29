#pragma once
#include "CoreMinimal.h"
#include "EndAIControllerBluePrintBase.h"
#include "EndAIControllerMountBase.generated.h"

UCLASS(Blueprintable)
class AEndAIControllerMountBase : public AEndAIControllerBluePrintBase {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FollowLimitTime;
    
public:
    AEndAIControllerMountBase(const FObjectInitializer& ObjectInitializer);

};

