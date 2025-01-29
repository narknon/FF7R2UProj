#pragma once
#include "CoreMinimal.h"
#include "EndFeelerSplineDeformContext.generated.h"

USTRUCT(BlueprintType)
struct FEndFeelerSplineDeformContext {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float StartFrame;
    
    ENDGAME_API FEndFeelerSplineDeformContext();
};

