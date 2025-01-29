#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EEndBattleBreakableRelationActionType.h"
#include "EndAnimNotifyBattleActionRelatedBreakable.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyBattleActionRelatedBreakable : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndBattleBreakableRelationActionType actionType_;
    
    UEndAnimNotifyBattleActionRelatedBreakable();

};

