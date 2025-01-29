#pragma once
#include "CoreMinimal.h"
#include "EntitySystem/IMovieSceneEntityProvider.h"
#include "MovieSceneSection.h"
#include "EEndCinemaResidentEffectVisibility.h"
#include "EndCinemaResidentEffectVisibilitySection.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndCinemaResidentEffectVisibilitySection : public UMovieSceneSection/*, public IMovieSceneEntityProvider*/ {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetActorName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetLocationName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetAccessorID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndCinemaResidentEffectVisibility Visibility;
    
    UEndCinemaResidentEffectVisibilitySection();


    // Fix for true pure virtual functions not being implemented
};

