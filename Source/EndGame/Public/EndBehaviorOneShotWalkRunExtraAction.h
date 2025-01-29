#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorSequentialExtraAction.h"
#include "EndBehaviorOneShotWalkRunExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorOneShotWalkRunExtraAction : public FEndBehaviorSequentialExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorOneShotWalkRunExtraAction();
};

