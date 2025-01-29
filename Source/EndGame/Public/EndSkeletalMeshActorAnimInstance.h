#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimSingleNodeInstance.h"
#include "EEndPlayRateModifierType.h"
#include "EndAnimInstanceInterface.h"
#include "EndSkeletalMeshActorAnimInstance.generated.h"

UCLASS(Blueprintable, NonTransient)
class UEndSkeletalMeshActorAnimInstance : public UAnimSingleNodeInstance, public IEndAnimInstanceInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    float PlayRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TMap<EEndPlayRateModifierType, float> PlayRateModifierMap;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    bool bPlayingCutScene;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    bool bPlayingDialogue;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    bool bRequestedPoseTransition;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    float RequestedPoseTransitionBlendTime;
    
    UEndSkeletalMeshActorAnimInstance();


    // Fix for true pure virtual functions not being implemented
};

