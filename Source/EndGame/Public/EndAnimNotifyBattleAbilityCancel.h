#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndCharacterAbilityCancelParameter.h"
#include "EndAnimNotifyBattleAbilityCancel.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UEndAnimNotifyBattleAbilityCancel : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<int32> CancelNumbers;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool NewProperty;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndCharacterAbilityCancelParameter> CancelParameters;
    
    UEndAnimNotifyBattleAbilityCancel();

};

