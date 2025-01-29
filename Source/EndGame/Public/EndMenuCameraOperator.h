#pragma once
#include "CoreMinimal.h"
#include "EndCameraOperator.h"
#include "EndMenuCameraOperator.generated.h"

USTRUCT(BlueprintType)
struct FEndMenuCameraOperator : public FEndCameraOperator {
    GENERATED_BODY()
public:
    ENDGAME_API FEndMenuCameraOperator();
};

