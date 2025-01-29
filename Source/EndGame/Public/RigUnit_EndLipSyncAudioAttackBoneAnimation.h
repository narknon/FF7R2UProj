#pragma once
#include "CoreMinimal.h"
#include "Rigs/RigHierarchyDefines.h"
#include "RigUnit_EndLipSyncAudioAttackAdditiveAnimation.h"
#include "RigUnit_EndLipSyncAudioAttackBoneAnimation.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndLipSyncAudioAttackBoneAnimation {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigElementKey Item;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FRigUnit_EndLipSyncAudioAttackAdditiveAnimation> Animations;
    
    ENDGAME_API FRigUnit_EndLipSyncAudioAttackBoneAnimation();
};

