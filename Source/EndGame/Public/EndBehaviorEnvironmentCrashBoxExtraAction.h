#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorEnvironmentCrashBoxExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorEnvironmentCrashBoxExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorEnvironmentCrashBoxExtraAction();
};

