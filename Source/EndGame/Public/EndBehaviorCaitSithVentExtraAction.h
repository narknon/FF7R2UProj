#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorFieldActionBase.h"
#include "EndBehaviorCaitSithVentExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorCaitSithVentExtraAction : public FEndBehaviorFieldActionBase {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorCaitSithVentExtraAction();
};

