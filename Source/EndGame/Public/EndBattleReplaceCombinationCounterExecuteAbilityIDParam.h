#pragma once
#include "CoreMinimal.h"
#include "EndBattleReplaceCombinationCounterExecuteAbilityIDParam.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndBattleReplaceCombinationCounterExecuteAbilityIDParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MainBaseAbilityID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MainReplaceAbilityID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bRotateToCounterDamageSource;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SubBaseAbilityID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SubReplaceAbilityID;
    
    FEndBattleReplaceCombinationCounterExecuteAbilityIDParam();
};

