#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorLaunchExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorLaunchExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorLaunchExtraAction();
};

