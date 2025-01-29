#pragma once
#include "CoreMinimal.h"
#include "Rigs/RigHierarchyCache.h"
#include "RigUnit_EndContactShake_ItemCache.h"
#include "RigUnit_EndContactShake_Cache.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndContactShake_Cache {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bNeedInitialize;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FRigUnit_EndContactShake_ItemCache> ItemCaches;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FCachedRigElement CachedDebugTarget;
    
    ENDGAME_API FRigUnit_EndContactShake_Cache();
};

