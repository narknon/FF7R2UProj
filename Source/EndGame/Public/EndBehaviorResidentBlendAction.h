#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorSequencePlayAction.h"
#include "EndBehaviorResidentBlendAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorResidentBlendAction : public FEndBehaviorSequencePlayAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorResidentBlendAction();
};

