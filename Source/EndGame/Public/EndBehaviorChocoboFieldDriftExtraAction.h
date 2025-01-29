#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorFieldActionBase.h"
#include "EndBehaviorChocoboFieldDriftExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorChocoboFieldDriftExtraAction : public FEndBehaviorFieldActionBase {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorChocoboFieldDriftExtraAction();
};

