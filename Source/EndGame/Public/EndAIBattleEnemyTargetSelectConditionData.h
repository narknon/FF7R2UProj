#pragma once
#include "CoreMinimal.h"
#include "EndAIBattleEnemyTargetSelectConditionElement.h"
#include "EndAIBattleEnemyTargetSelectConditionData.generated.h"

USTRUCT(BlueprintType)
struct FEndAIBattleEnemyTargetSelectConditionData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAIBattleEnemyTargetSelectConditionElement> Elements;
    
    ENDGAME_API FEndAIBattleEnemyTargetSelectConditionData();
};

