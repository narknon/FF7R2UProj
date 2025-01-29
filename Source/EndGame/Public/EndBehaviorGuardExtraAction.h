#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorSimpleFsmExtraAction.h"
#include "EndBehaviorGuardExtraAction.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndBehaviorGuardExtraAction : public FEndBehaviorSimpleFsmExtraAction {
    GENERATED_BODY()
public:
    FEndBehaviorGuardExtraAction();
};

