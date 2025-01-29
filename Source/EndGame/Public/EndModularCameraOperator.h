#pragma once
#include "CoreMinimal.h"
#include "EndCameraOperator.h"
#include "EndModularCameraOperator.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndModularCameraOperator : public FEndCameraOperator {
    GENERATED_BODY()
public:
    FEndModularCameraOperator();
};

