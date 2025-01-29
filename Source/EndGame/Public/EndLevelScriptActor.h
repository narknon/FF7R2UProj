#pragma once
#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "EndLevelScriptActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndLevelScriptActor : public ALevelScriptActor {
    GENERATED_BODY()
public:
    AEndLevelScriptActor(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnSetStoryFlag(FName StoryFlagId, bool Value);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnSetChapterProgress(int32 Value);
    
};

