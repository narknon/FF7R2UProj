#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorChocoboJetExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorChocoboJetExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorChocoboJetExtraAction();
};

