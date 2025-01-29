#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorSBScooterGetOffExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorSBScooterGetOffExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorSBScooterGetOffExtraAction();
};

