#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorEnvironmentCrashBoxGearBoxExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorEnvironmentCrashBoxGearBoxExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorEnvironmentCrashBoxGearBoxExtraAction();
};

