#pragma once
#include "CoreMinimal.h"
#include "EAutoMagicEssentialConditionType.h"
#include "EAutoMagicSelectRuleType.h"
#include "EAutoMagicTargetConditionType.h"
#include "EAutoMagicTargetPriorityType.h"
#include "EndAIAutoMagicRules.generated.h"

USTRUCT(BlueprintType)
struct FEndAIAutoMagicRules {
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
    
    ENDGAME_API FEndAIAutoMagicRules();
};

