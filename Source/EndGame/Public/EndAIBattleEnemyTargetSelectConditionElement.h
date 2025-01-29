#pragma once
#include "CoreMinimal.h"
#include "EEndAIEnemyTargetSelectCharacterType.h"
#include "EEndAIEnemyTargetSelectConditionType.h"
#include "EndAIBattleEnemyTargetSelectConditionElement.generated.h"

USTRUCT(BlueprintType)
struct FEndAIBattleEnemyTargetSelectConditionElement {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Priority;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIEnemyTargetSelectCharacterType CharacterType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIEnemyTargetSelectConditionType ConditionType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bMatchExclusion;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Ratio;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 ContinuousLimit;
    
    ENDGAME_API FEndAIBattleEnemyTargetSelectConditionElement();
};

