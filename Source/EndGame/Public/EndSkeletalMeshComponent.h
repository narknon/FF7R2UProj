#pragma once
#include "CoreMinimal.h"
#include "SkeletalMeshComponentBudgeted.h"
#include "EEndAnimDisableUpdateCondition.h"
#include "EndSkeletalMeshComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndSkeletalMeshComponent : public USkeletalMeshComponentBudgeted {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bAutoSyncAnimationOnAttach;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bForceUpdateAnimation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimDisableUpdateCondition DisableUpdateCondition;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bIgnoreCameraDistanceOptimization;
    
    UEndSkeletalMeshComponent(const FObjectInitializer& ObjectInitializer);

};

