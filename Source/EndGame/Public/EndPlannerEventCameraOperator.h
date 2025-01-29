#pragma once
#include "CoreMinimal.h"
#include "EndCameraOperator.h"
#include "EndPlannerEventCameraOperator.generated.h"

USTRUCT(BlueprintType)
struct FEndPlannerEventCameraOperator : public FEndCameraOperator {
    GENERATED_BODY()
public:
    ENDGAME_API FEndPlannerEventCameraOperator();
};

