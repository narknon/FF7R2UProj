#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorAICharacterExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorAICharacterExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorAICharacterExtraAction();
};

