#pragma once
#include "CoreMinimal.h"
#include "SQEX_BonamikCollisionCliqueDesc.generated.h"

USTRUCT(BlueprintType)
struct FSQEX_BonamikCollisionCliqueDesc {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint32> mShapeIds;
    
    BONAMIKRT_API FSQEX_BonamikCollisionCliqueDesc();
};

