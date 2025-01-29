#pragma once
#include "CoreMinimal.h"
#include "EntitySystem/MovieSceneEntitySystem.h"
#include "EndCinemaSceneLightCurveSystem.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndCinemaSceneLightCurveSystem : public UMovieSceneEntitySystem {
    GENERATED_BODY()
public:
    UEndCinemaSceneLightCurveSystem(const FObjectInitializer& ObjectInitializer);

};

