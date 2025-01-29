#pragma once
#include "CoreMinimal.h"
#include "EndBikeModelInfo.generated.h"

USTRUCT(BlueprintType)
struct FEndBikeModelInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FrontLength;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RearLength;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float WidthLength;
    
    ENDGAME_API FEndBikeModelInfo();
};

