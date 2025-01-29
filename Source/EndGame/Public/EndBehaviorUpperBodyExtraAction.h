#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorSimpleFsmExtraAction.h"
#include "EndBehaviorUpperBodyExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorUpperBodyExtraAction : public FEndBehaviorSimpleFsmExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorUpperBodyExtraAction();
};

