#pragma once
#include "CoreMinimal.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "EndWeaponSwimTemplate.generated.h"

USTRUCT(BlueprintType)
struct FEndWeaponSwimTemplate : public FMovieSceneEvalTemplate {
    GENERATED_BODY()
public:
    ENDGAME_API FEndWeaponSwimTemplate();
};

