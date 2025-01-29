#pragma once
#include "CoreMinimal.h"
#include "OptionRangeInfo.generated.h"

USTRUCT(BlueprintType)
struct FOptionRangeInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 MinValue;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 MaxValue;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName OpenFlag;
    
    ENDGAME_API FOptionRangeInfo();
};

