#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorCrashBoxElectricExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorCrashBoxElectricExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorCrashBoxElectricExtraAction();
};

