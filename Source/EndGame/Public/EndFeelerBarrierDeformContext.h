#pragma once
#include "CoreMinimal.h"
#include "EndFeelerBarrierDeformContext.generated.h"

USTRUCT(BlueprintType)
struct FEndFeelerBarrierDeformContext {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float StartFrame;
    
    ENDGAME_API FEndFeelerBarrierDeformContext();
};

