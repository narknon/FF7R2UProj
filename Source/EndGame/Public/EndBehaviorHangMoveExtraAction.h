#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorHangMoveExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorHangMoveExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorHangMoveExtraAction();
};

