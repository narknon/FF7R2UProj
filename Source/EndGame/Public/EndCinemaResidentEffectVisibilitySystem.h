#pragma once
#include "CoreMinimal.h"
#include "EntitySystem/MovieSceneEntitySystem.h"
#include "EntitySystem/MovieScenePreAnimatedStateSystem.h"
#include "EndCinemaResidentEffectVisibilitySystem.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndCinemaResidentEffectVisibilitySystem : public UMovieSceneEntitySystem, public IMovieScenePreAnimatedStateSystemInterface {
    GENERATED_BODY()
public:
    UEndCinemaResidentEffectVisibilitySystem(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

