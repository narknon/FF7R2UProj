#pragma once
#include "CoreMinimal.h"
#include "EndCameraOperator.h"
#include "EndCutCameraOperator.generated.h"

USTRUCT(BlueprintType)
struct FEndCutCameraOperator : public FEndCameraOperator {
    GENERATED_BODY()
public:
    ENDGAME_API FEndCutCameraOperator();
};

