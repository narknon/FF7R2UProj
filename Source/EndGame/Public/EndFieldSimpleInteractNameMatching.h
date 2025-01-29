#pragma once
#include "CoreMinimal.h"
#include "EndFieldSimpleInteractNameMatching.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldSimpleInteractNameMatching {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MatchingName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Name;
    
    ENDGAME_API FEndFieldSimpleInteractNameMatching();
};

