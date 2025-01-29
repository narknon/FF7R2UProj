#pragma once
#include "CoreMinimal.h"
#include "EndBattleAbilityCancelComboCondition.h"
#include "EndCharacterAbilityCancelParameter.generated.h"

USTRUCT(BlueprintType)
struct FEndCharacterAbilityCancelParameter {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Number;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Timing;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EndBattleAbilityCancelComboCondition ComboCondition;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Combo;
    
    ENDGAME_API FEndCharacterAbilityCancelParameter();
};

