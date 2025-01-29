#pragma once
#include "CoreMinimal.h"
#include "EndAnimNotifyEnableInputCancel.h"
#include "EndAnimNotifyBattleStateChange.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyBattleStateChange : public UEndAnimNotifyEnableInputCancel {
    GENERATED_BODY()
public:
    UEndAnimNotifyBattleStateChange();

};

