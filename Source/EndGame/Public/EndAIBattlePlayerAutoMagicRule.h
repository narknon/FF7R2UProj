#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EAutoMagicEssentialConditionType.h"
#include "EAutoMagicLinkSortType.h"
#include "EAutoMagicSelectRuleType.h"
#include "EAutoMagicTargetConditionType.h"
#include "EAutoMagicTargetPriorityType.h"
#include "EndAIBattlePlayerAutoMagicRule.generated.h"

UCLASS(Blueprintable)
class UEndAIBattlePlayerAutoMagicRule : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EAutoMagicEssentialConditionType> EssentialConditions;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EAutoMagicTargetPriorityType> TargetPriorities;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EAutoMagicTargetConditionType> TargetConditions;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EAutoMagicSelectRuleType SelectRule;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLinkGroup;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EAutoMagicLinkSortType GroupLinkSortType;
    
    UEndAIBattlePlayerAutoMagicRule();

};

