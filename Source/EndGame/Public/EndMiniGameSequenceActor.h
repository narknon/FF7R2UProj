#pragma once
#include "CoreMinimal.h"
#include "LevelSequenceActor.h"
#include "EndMiniGameSequenceActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndMiniGameSequenceActor : public ALevelSequenceActor {
    GENERATED_BODY()
public:
    AEndMiniGameSequenceActor(const FObjectInitializer& ObjectInitializer);

};

