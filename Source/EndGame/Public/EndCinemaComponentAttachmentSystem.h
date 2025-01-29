#pragma once
#include "CoreMinimal.h"
#include "EntitySystem/MovieSceneEntityInstantiatorSystem.h"
#include "EntitySystem/MovieScenePreAnimatedStateSystem.h"
#include "EndCinemaComponentAttachmentSystem.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndCinemaComponentAttachmentSystem : public UMovieSceneEntityInstantiatorSystem, public IMovieScenePreAnimatedStateSystemInterface {
    GENERATED_BODY()
public:
    UEndCinemaComponentAttachmentSystem(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

