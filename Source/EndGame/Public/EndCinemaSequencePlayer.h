#pragma once
#include "CoreMinimal.h"
#include "LevelSequencePlayer.h"
#include "EndCinemaSequencePlayer.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndCinemaSequencePlayer : public ULevelSequencePlayer {
    GENERATED_BODY()
public:
    UEndCinemaSequencePlayer(const FObjectInitializer& ObjectInitializer);

};

