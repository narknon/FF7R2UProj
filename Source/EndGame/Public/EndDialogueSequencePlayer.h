#pragma once
#include "CoreMinimal.h"
#include "LevelSequencePlayer.h"
#include "EndDialogueSequencePlayer.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndDialogueSequencePlayer : public ULevelSequencePlayer {
    GENERATED_BODY()
public:
    UEndDialogueSequencePlayer(const FObjectInitializer& ObjectInitializer);

};

