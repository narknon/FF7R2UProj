#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndShootingGameTargetActorBase.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndShootingGameTargetActorBase : public AActor {
    GENERATED_BODY()
public:
    AEndShootingGameTargetActorBase(const FObjectInitializer& ObjectInitializer);

};

