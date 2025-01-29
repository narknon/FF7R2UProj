#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorSimpleFsmExtraAction.h"
#include "EndBehaviorAppearanceExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorAppearanceExtraAction : public FEndBehaviorSimpleFsmExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorAppearanceExtraAction();
};

