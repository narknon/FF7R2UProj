#pragma once
#include "CoreMinimal.h"
#include "EndCameraOperator.h"
#include "EndSequenceCameraOperator.generated.h"

USTRUCT(BlueprintType)
struct FEndSequenceCameraOperator : public FEndCameraOperator {
    GENERATED_BODY()
public:
    ENDGAME_API FEndSequenceCameraOperator();
};

