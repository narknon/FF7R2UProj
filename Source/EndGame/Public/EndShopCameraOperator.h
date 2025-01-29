#pragma once
#include "CoreMinimal.h"
#include "EndCameraOperator.h"
#include "EndShopCameraOperator.generated.h"

USTRUCT(BlueprintType)
struct FEndShopCameraOperator : public FEndCameraOperator {
    GENERATED_BODY()
public:
    ENDGAME_API FEndShopCameraOperator();
};

