#pragma once
#include "CoreMinimal.h"
#include "EndModularCameraOperator.h"
#include "EndBattleCameraOperator.generated.h"

USTRUCT(BlueprintType)
struct FEndBattleCameraOperator : public FEndModularCameraOperator {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBattleCameraOperator();
};

