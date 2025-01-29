#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldExtraAction.h"
#include "EndBehaviorCloudSuppressExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorCloudSuppressExtraAction : public FEndBehaviorNewFieldExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorCloudSuppressExtraAction();
};

