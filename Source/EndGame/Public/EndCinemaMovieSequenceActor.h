#pragma once
#include "CoreMinimal.h"
#include "EndCinemaSequenceActor.h"
#include "EndCinemaMovieSequenceActor.generated.h"

class UMediaSoundComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndCinemaMovieSequenceActor : public AEndCinemaSequenceActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UMediaSoundComponent* MediaSoundComponent;
    
public:
    AEndCinemaMovieSequenceActor(const FObjectInitializer& ObjectInitializer);

};

