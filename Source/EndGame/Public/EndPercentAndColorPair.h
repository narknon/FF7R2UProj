#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndPercentAndColorPair.generated.h"

USTRUCT(BlueprintType)
struct FEndPercentAndColorPair {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Percent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor ColorAndOpacity;
    
    ENDGAME_API FEndPercentAndColorPair();
};

