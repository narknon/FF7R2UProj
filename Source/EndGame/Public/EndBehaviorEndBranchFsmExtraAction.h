#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorEndBranchFsmExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorEndBranchFsmExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorEndBranchFsmExtraAction();
};

