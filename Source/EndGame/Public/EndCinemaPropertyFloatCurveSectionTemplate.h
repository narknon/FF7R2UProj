#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Evaluation/Blending/MovieSceneBlendType.h"
#include "Channels/MovieSceneFloatChannel.h"
#include "Evaluation/MovieScenePropertyTemplate.h"
#include "EndCinemaPropertyFloatCurveSectionTemplate.generated.h"

class UEndCinemaPropertyFloatCurveSection;

USTRUCT(BlueprintType)
struct ENDGAME_API FEndCinemaPropertyFloatCurveSectionTemplate : public FMovieScenePropertySectionTemplate {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FMovieSceneFloatChannel FloatCurve;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EMovieSceneBlendType BlendType;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCinemaPropertyFloatCurveSection* CurveSection;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FFrameRate FramePerTick;
    
public:
    FEndCinemaPropertyFloatCurveSectionTemplate();
};

