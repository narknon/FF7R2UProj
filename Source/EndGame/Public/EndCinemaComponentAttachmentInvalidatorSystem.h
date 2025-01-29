#pragma once
#include "CoreMinimal.h"
#include "EntitySystem/MovieSceneEntityInstantiatorSystem.h"
#include "EndCinemaComponentAttachmentInvalidatorSystem.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndCinemaComponentAttachmentInvalidatorSystem : public UMovieSceneEntityInstantiatorSystem {
    GENERATED_BODY()
public:
    UEndCinemaComponentAttachmentInvalidatorSystem(const FObjectInitializer& ObjectInitializer);

};

