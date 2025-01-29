#pragma once
#include "CoreMinimal.h"
#include "EntitySystem/IMovieSceneEntityProvider.h"
#include "MovieSceneSection.h"
#include "EndCinemaBeamTargetSection.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndCinemaBeamTargetSection : public UMovieSceneSection/*, public IMovieSceneEntityProvider*/ {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetActorName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetSocketName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetComponentName;
    
    UEndCinemaBeamTargetSection();


    // Fix for true pure virtual functions not being implemented
};

