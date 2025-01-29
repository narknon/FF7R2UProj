#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EndBTTask_AIPCRequestAutoWeaponAbility.generated.h"

UCLASS(Blueprintable)
class UEndBTTask_AIPCRequestAutoWeaponAbility : public UBTTaskNode {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TimeOut;
    
    UEndBTTask_AIPCRequestAutoWeaponAbility();

};

