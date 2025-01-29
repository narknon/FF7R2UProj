#pragma once
#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "EndBattleCameraLevelScriptActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndBattleCameraLevelScriptActor : public ALevelScriptActor {
    GENERATED_BODY()
public:
    AEndBattleCameraLevelScriptActor(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void BattleCameraLevelConstructionScript();
    
};

