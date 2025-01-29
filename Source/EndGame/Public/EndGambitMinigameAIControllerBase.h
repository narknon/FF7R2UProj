#pragma once
#include "CoreMinimal.h"
#include "EndAIControllerBluePrintBase.h"
#include "EndGambitMinigameAIControllerBase.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndGambitMinigameAIControllerBase : public AEndAIControllerBluePrintBase {
    GENERATED_BODY()
public:
    AEndGambitMinigameAIControllerBase(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    bool ResetWaitNextSec();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnGambitActivated();
    
};

