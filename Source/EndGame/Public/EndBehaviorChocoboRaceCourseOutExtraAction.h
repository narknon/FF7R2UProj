#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorChocoboRaceCourseOutExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorChocoboRaceCourseOutExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorChocoboRaceCourseOutExtraAction();
};

