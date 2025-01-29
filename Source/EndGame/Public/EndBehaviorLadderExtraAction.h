#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorFieldActionBase.h"
#include "EndBehaviorLadderExtraAction.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndBehaviorLadderExtraAction : public FEndBehaviorFieldActionBase {
    GENERATED_BODY()
public:
    FEndBehaviorLadderExtraAction();
};

