#pragma once
#include "CoreMinimal.h"
#include "RigUnit_EndLipSyncAudioAttackBrowAnimationCache.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndLipSyncAudioAttackBrowAnimationCache {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Timer;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BlendInTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BlendOutTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float OffsetValue;
    
    ENDGAME_API FRigUnit_EndLipSyncAudioAttackBrowAnimationCache();
};

