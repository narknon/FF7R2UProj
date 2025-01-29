#pragma once
#include "CoreMinimal.h"
#include "EndCameraOperator.h"
#include "EndRailCameraOperator.generated.h"

USTRUCT(BlueprintType)
struct FEndRailCameraOperator : public FEndCameraOperator {
    GENERATED_BODY()
public:
    ENDGAME_API FEndRailCameraOperator();
};

