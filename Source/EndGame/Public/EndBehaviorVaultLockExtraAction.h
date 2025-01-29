#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorVaultLockExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorVaultLockExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorVaultLockExtraAction();
};

