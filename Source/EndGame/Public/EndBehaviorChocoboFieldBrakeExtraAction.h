#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorFieldActionBase.h"
#include "EndBehaviorChocoboFieldBrakeExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorChocoboFieldBrakeExtraAction : public FEndBehaviorFieldActionBase {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorChocoboFieldBrakeExtraAction();
};

