#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndCharacterAbilityCancelParameter.h"
#include "EndCharacterAbilityCancelStartParameter.h"
#include "EndAnimNotifyBattleAbilityCancelStart.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UEndAnimNotifyBattleAbilityCancelStart : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<int32> CancelNumbers;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndCharacterAbilityCancelParameter> CancelParameters;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool NewProperty;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndCharacterAbilityCancelStartParameter> CancelStartParameters;
    
    UEndAnimNotifyBattleAbilityCancelStart();

};

