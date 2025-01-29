#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndCliffDataWrapper.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndCliffDataWrapper {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector CliffDirection;
    
    FEndCliffDataWrapper();
};

