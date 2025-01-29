#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EEndAnimWalkType.h"
#include "EndCrowdActorAnimInstance.generated.h"

UCLASS(Blueprintable, NonTransient)
class UEndCrowdActorAnimInstance : public UAnimInstance {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimWalkType WalkType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float StartPosition;
    
    UEndCrowdActorAnimInstance();

};

