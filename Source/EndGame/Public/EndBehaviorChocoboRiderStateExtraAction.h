#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorChocoboRiderStateExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorChocoboRiderStateExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorChocoboRiderStateExtraAction();
};

