#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldExtraAction.h"
#include "EndBehaviorVaultExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorVaultExtraAction : public FEndBehaviorNewFieldExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorVaultExtraAction();
};

