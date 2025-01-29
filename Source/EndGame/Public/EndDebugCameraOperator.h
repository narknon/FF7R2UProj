#pragma once
#include "CoreMinimal.h"
#include "EndCameraOperator.h"
#include "EndDebugCameraOperator.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndDebugCameraOperator : public FEndCameraOperator {
    GENERATED_BODY()
public:
    FEndDebugCameraOperator();
};

