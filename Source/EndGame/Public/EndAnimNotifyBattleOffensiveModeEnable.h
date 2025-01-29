#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAnimNotifyBattleOffensiveModeEnable.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UEndAnimNotifyBattleOffensiveModeEnable : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool Enable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool Switch;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool IgnoreUpgradedOffensiveMode;
    
    UEndAnimNotifyBattleOffensiveModeEnable();

};

