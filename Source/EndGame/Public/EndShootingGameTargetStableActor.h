#pragma once
#include "CoreMinimal.h"
#include "EndShootingGameTargetActorBase.h"
#include "EndShootingGameTargetStableActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndShootingGameTargetStableActor : public AEndShootingGameTargetActorBase {
    GENERATED_BODY()
public:
    AEndShootingGameTargetStableActor(const FObjectInitializer& ObjectInitializer);

};

