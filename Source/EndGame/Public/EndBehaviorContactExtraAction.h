#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorSequentialExtraAction.h"
#include "EndBehaviorContactExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorContactExtraAction : public FEndBehaviorSequentialExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorContactExtraAction();
};

