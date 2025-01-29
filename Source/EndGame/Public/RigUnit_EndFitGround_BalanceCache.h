#pragma once
#include "CoreMinimal.h"
#include "Rigs/RigHierarchyCache.h"
#include "RigUnit_EndFitGround_BalanceCache.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndFitGround_BalanceCache {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FCachedRigElement CachedItem;
    
    ENDGAME_API FRigUnit_EndFitGround_BalanceCache();
};

