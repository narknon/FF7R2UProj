#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorChocoboSmellExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorChocoboSmellExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorChocoboSmellExtraAction();
};

