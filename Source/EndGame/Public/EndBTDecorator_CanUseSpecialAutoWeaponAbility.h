#pragma once
#include "CoreMinimal.h"
#include "EAutoWeaponAbilitySpecialCaseType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_CanUseSpecialAutoWeaponAbility.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_CanUseSpecialAutoWeaponAbility : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EAutoWeaponAbilitySpecialCaseType Type;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bCheckRider;
    
    UEndBTDecorator_CanUseSpecialAutoWeaponAbility();

};

