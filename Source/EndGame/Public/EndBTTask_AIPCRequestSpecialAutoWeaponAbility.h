#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EAutoWeaponAbilitySpecialCaseType.h"
#include "EndBTTask_AIPCRequestSpecialAutoWeaponAbility.generated.h"

UCLASS(Blueprintable)
class UEndBTTask_AIPCRequestSpecialAutoWeaponAbility : public UBTTaskNode {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EAutoWeaponAbilitySpecialCaseType Type;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bRequestRider;
    
    UEndBTTask_AIPCRequestSpecialAutoWeaponAbility();

};

