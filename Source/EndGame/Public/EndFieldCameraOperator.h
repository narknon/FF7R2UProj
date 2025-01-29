#pragma once
#include "CoreMinimal.h"
#include "EndModularCameraOperator.h"
#include "EndFieldCameraOperator.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldCameraOperator : public FEndModularCameraOperator {
    GENERATED_BODY()
public:
    ENDGAME_API FEndFieldCameraOperator();
};

