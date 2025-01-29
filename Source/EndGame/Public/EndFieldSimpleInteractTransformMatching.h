#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndFieldSimpleInteractTransformMatching.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldSimpleInteractTransformMatching {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MatchingName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform TargetTransform;
    
    ENDGAME_API FEndFieldSimpleInteractTransformMatching();
};

