#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Evaluation/Blending/MovieSceneBlendType.h"
#include "Channels/MovieSceneFloatChannel.h"
#include "Evaluation/MovieScenePropertyTemplate.h"
#include "EndCinemaPropertyColorCurveSectionTemplate.generated.h"

class UEndCinemaPropertyColorCurveSection;

USTRUCT(BlueprintType)
struct ENDGAME_API FEndCinemaPropertyColorCurveSectionTemplate : public FMovieScenePropertySectionTemplate {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FMovieSceneFloatChannel Curves[4];
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EMovieSceneBlendType BlendType;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCinemaPropertyColorCurveSection* CurveSection;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FFrameRate FramePerTick;
    
public:
    FEndCinemaPropertyColorCurveSectionTemplate();
};

