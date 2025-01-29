#pragma once
#include "CoreMinimal.h"
#include "EndFeelerLaserDeformContext.generated.h"

USTRUCT(BlueprintType)
struct FEndFeelerLaserDeformContext {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float StartFrame;
    
    ENDGAME_API FEndFeelerLaserDeformContext();
};

