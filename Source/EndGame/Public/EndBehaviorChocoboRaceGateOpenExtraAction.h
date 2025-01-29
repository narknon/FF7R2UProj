#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorChocoboRaceGateOpenExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorChocoboRaceGateOpenExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorChocoboRaceGateOpenExtraAction();
};

