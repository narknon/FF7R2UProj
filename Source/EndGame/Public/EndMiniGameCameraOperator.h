#pragma once
#include "CoreMinimal.h"
#include "EndCameraOperator.h"
#include "EndMiniGameCameraOperator.generated.h"

USTRUCT(BlueprintType)
struct FEndMiniGameCameraOperator : public FEndCameraOperator {
    GENERATED_BODY()
public:
    ENDGAME_API FEndMiniGameCameraOperator();
};

