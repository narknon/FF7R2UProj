#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorSequencePlayAction.h"
#include "EndBehaviorExtraAction.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndBehaviorExtraAction : public FEndBehaviorSequencePlayAction {
    GENERATED_BODY()
public:
    FEndBehaviorExtraAction();
};

