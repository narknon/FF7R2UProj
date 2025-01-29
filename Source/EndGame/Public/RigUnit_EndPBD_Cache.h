#pragma once
#include "CoreMinimal.h"
#include "RigUnit_EndPBD_ParticleCache.h"
#include "RigUnit_EndPBD_Cache.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndPBD_Cache {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bNeedInitialize;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FRigUnit_EndPBD_ParticleCache> ParticleCaches;
    
    ENDGAME_API FRigUnit_EndPBD_Cache();
};

