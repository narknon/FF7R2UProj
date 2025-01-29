#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EntitySystem/IMovieSceneEntityProvider.h"
#include "MovieSceneSection.h"
#include "EEndCinemaSceneLightCurveApplyType.h"
#include "EEndCinemaSceneLightCurvePlayType.h"
#include "EndCinemaSceneLightCurveSection.generated.h"

class UCurveBase;

UCLASS(Blueprintable, MinimalAPI)
class UEndCinemaSceneLightCurveSection : public UMovieSceneSection/*, public IMovieSceneEntityProvider*/ {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UCurveBase* PropertyCurve;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName PropertyName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndCinemaSceneLightCurvePlayType PlayMode;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndCinemaSceneLightCurveApplyType ApplyMode;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FFrameNumber StartFrameOffset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float CurveScaling;
    
    UEndCinemaSceneLightCurveSection();


    // Fix for true pure virtual functions not being implemented
};

