#pragma once
#include "CoreMinimal.h"
#include "EndAnimSetClusterWarning.generated.h"

USTRUCT(BlueprintType)
struct FEndAnimSetClusterWarning {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> Dependencies;
    
    ENDGAME_API FEndAnimSetClusterWarning();
};

