#pragma once
#include "CoreMinimal.h"
#include "OptionBaseInfo.h"
#include "OptionRangeInfo.h"
#include "OptionSelectInfo.h"
#include "OptionInfo.generated.h"

USTRUCT(BlueprintType)
struct FOptionInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FOptionBaseInfo BaseInfo;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FOptionSelectInfo SelectInfo;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FOptionRangeInfo RangeInfo;
    
    ENDGAME_API FOptionInfo();
};

