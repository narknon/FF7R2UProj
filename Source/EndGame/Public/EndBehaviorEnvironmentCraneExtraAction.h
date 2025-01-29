#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorEnvironmentCraneExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorEnvironmentCraneExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorEnvironmentCraneExtraAction();
};

