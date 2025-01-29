#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorContactExtraAction.h"
#include "EndBehaviorWalkContactExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorWalkContactExtraAction : public FEndBehaviorContactExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorWalkContactExtraAction();
};

