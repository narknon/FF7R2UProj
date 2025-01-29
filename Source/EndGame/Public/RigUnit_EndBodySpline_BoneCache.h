#pragma once
#include "CoreMinimal.h"
#include "Rigs/RigHierarchyCache.h"
#include "UObject/NoExportTypes.h"
#include "RigUnit_EndBodySpline_BoneCache.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndBodySpline_BoneCache {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FCachedRigElement CachedItem;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FQuat DeltaRotation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Alpha;
    
    ENDGAME_API FRigUnit_EndBodySpline_BoneCache();
};

