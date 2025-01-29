#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorChocoboGetOffExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorChocoboGetOffExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorChocoboGetOffExtraAction();
};

