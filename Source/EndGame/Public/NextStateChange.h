#pragma once
#include "CoreMinimal.h"
#include "NextStateChange.generated.h"

USTRUCT(BlueprintType)
struct FNextStateChange {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName InputStateTrigger;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName NextStateChange;
    
    ENDGAME_API FNextStateChange();
};

