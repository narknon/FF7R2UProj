#pragma once
#include "CoreMinimal.h"
#include "EPlayerType.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EndAnimNotifyStateBattleAbilityCombination.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class UEndAnimNotifyStateBattleAbilityCombination : public UAnimNotifyState {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EPlayerType PlayerType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool FatMoogle;
    
    UEndAnimNotifyStateBattleAbilityCombination();

};

