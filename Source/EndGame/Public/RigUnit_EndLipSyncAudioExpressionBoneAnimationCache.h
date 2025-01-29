#pragma once
#include "CoreMinimal.h"
#include "Rigs/RigHierarchyCache.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "RigUnit_EndLipSyncAudioExpressionBoneAnimationCache.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndLipSyncAudioExpressionBoneAnimationCache {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FCachedRigElement CachedItem;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector CachedTranslation0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector CachedTranslation1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FQuat CachedRotation0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FQuat CachedRotation1;
    
    ENDGAME_API FRigUnit_EndLipSyncAudioExpressionBoneAnimationCache();
};

