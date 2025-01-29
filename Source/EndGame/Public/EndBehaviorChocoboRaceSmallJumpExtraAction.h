#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorChocoboRaceSmallJumpExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorChocoboRaceSmallJumpExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorChocoboRaceSmallJumpExtraAction();
};

