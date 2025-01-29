#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldExtraAction.h"
#include "EndBehaviorNewFieldUpperExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorNewFieldUpperExtraAction : public FEndBehaviorNewFieldExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorNewFieldUpperExtraAction();
};

