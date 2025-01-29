#pragma once
#include "CoreMinimal.h"
#include "EndCameraOperator.h"
#include "EndMiniGameCardOperator.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndMiniGameCardOperator : public FEndCameraOperator {
    GENERATED_BODY()
public:
    FEndMiniGameCardOperator();
};

