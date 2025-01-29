#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndGameJumpActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndGameJumpActor : public AActor {
    GENERATED_BODY()
public:
    AEndGameJumpActor(const FObjectInitializer& ObjectInitializer);

};

