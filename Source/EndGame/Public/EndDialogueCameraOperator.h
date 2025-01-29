#pragma once
#include "CoreMinimal.h"
#include "EndCameraOperator.h"
#include "EndDialogueCameraOperator.generated.h"

USTRUCT(BlueprintType)
struct FEndDialogueCameraOperator : public FEndCameraOperator {
    GENERATED_BODY()
public:
    ENDGAME_API FEndDialogueCameraOperator();
};

