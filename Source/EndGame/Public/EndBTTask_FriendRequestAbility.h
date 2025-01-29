#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EFriendAbilityTargetType.h"
#include "EFriendAbilityType.h"
#include "EndBTTask_FriendRequestAbility.generated.h"

UCLASS(Blueprintable)
class UEndBTTask_FriendRequestAbility : public UBTTaskNode {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EFriendAbilityType AbilityType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EFriendAbilityTargetType TargetType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TimeOut;
    
    UEndBTTask_FriendRequestAbility();

};

