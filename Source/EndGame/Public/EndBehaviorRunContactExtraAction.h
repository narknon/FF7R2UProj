#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorContactExtraAction.h"
#include "EndBehaviorRunContactExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorRunContactExtraAction : public FEndBehaviorContactExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorRunContactExtraAction();
};

