#pragma once
#include "CoreMinimal.h"
#include "EndFeelerTornadeDeformContext.generated.h"

USTRUCT(BlueprintType)
struct FEndFeelerTornadeDeformContext {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float StartFrame;
    
    ENDGAME_API FEndFeelerTornadeDeformContext();
};

