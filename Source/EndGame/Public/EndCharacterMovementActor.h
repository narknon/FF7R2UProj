#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndCharacterMovementActor.generated.h"

UCLASS(Blueprintable, NotPlaceable)
class ENDGAME_API AEndCharacterMovementActor : public AActor {
    GENERATED_BODY()
public:
    AEndCharacterMovementActor(const FObjectInitializer& ObjectInitializer);

};

