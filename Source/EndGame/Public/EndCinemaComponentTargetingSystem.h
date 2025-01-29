#pragma once
#include "CoreMinimal.h"
#include "EntitySystem/MovieSceneEntitySystem.h"
#include "EndCinemaComponentTargetingSystem.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndCinemaComponentTargetingSystem : public UMovieSceneEntitySystem {
    GENERATED_BODY()
public:
    UEndCinemaComponentTargetingSystem(const FObjectInitializer& ObjectInitializer);

};

