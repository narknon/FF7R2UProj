#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldExtraAction.h"
#include "EndBehaviorBarretComboExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorBarretComboExtraAction : public FEndBehaviorNewFieldExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorBarretComboExtraAction();
};

