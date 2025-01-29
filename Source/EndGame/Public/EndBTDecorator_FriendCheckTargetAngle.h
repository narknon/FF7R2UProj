#pragma once
#include "CoreMinimal.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_FriendCheckTargetAngle.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_FriendCheckTargetAngle : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SpecifiedAngle;
    
    UEndBTDecorator_FriendCheckTargetAngle();

};

