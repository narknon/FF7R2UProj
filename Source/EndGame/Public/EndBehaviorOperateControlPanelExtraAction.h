#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorOperateControlPanelExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorOperateControlPanelExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorOperateControlPanelExtraAction();
};

