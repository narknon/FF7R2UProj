#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EndBTTask_FriendRequestAttackAbility.generated.h"

UCLASS(Blueprintable)
class UEndBTTask_FriendRequestAttackAbility : public UBTTaskNode {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TimeOut;
    
    UEndBTTask_FriendRequestAttackAbility();

};

