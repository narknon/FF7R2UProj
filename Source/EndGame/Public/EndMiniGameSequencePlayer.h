#pragma once
#include "CoreMinimal.h"
#include "LevelSequencePlayer.h"
#include "EndMiniGameSequencePlayer.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndMiniGameSequencePlayer : public ULevelSequencePlayer {
    GENERATED_BODY()
public:
    UEndMiniGameSequencePlayer(const FObjectInitializer& ObjectInitializer);

};

