#pragma once
#include "CoreMinimal.h"
#include "EndFieldSimpleInteractNameMatchingEditOnly.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldSimpleInteractNameMatchingEditOnly {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MatchingName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Name;
    
    ENDGAME_API FEndFieldSimpleInteractNameMatchingEditOnly();
};

