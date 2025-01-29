#pragma once
#include "CoreMinimal.h"
#include "RigUnit_EndBoneControl_ControllerCache.h"
#include "RigUnit_EndBoneControl_Cache.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndBoneControl_Cache {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bNeedInitialize;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 InitializeCounter;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FRigUnit_EndBoneControl_ControllerCache> ControllerCaches;
    
    ENDGAME_API FRigUnit_EndBoneControl_Cache();
};

