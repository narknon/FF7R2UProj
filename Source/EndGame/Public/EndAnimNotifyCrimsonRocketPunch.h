#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EEndCrimsonRocketPunchMovementType.h"
#include "EEndCrimsonRocketPunchSide.h"
#include "EndAnimNotifyCrimsonRocketPunch.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyCrimsonRocketPunch : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndCrimsonRocketPunchSide Arm;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndCrimsonRocketPunchMovementType MovementType;
    
    UEndAnimNotifyCrimsonRocketPunch();

};

