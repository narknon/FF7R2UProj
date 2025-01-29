#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldExtraAction.h"
#include "EndBehaviorZiplineExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorZiplineExtraAction : public FEndBehaviorNewFieldExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorZiplineExtraAction();
};

