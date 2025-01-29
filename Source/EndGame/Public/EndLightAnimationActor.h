#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndActorBaseInterface.h"
#include "EndLightAnimationActor.generated.h"

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndLightAnimationActor : public AActor, public IEndActorBaseInterface {
    GENERATED_BODY()
public:
    AEndLightAnimationActor(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

