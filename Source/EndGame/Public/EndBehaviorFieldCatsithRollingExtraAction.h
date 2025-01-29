#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldExtraAction.h"
#include "EndBehaviorFieldCatsithRollingExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorFieldCatsithRollingExtraAction : public FEndBehaviorNewFieldExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorFieldCatsithRollingExtraAction();
};

