#pragma once
#include "CoreMinimal.h"
#include "EEndAIActionPackTransOptionReleaseTiming.h"
#include "EndAIActionPackTransOption.generated.h"

USTRUCT(BlueprintType)
struct FEndAIActionPackTransOption {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bApply;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIActionPackTransOptionReleaseTiming ReleaseTiming;
    
    ENDGAME_API FEndAIActionPackTransOption();
};

