#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorSimpleFsmExtraAction.h"
#include "EndBehaviorTalkExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorTalkExtraAction : public FEndBehaviorSimpleFsmExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorTalkExtraAction();
};

