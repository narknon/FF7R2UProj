#pragma once
#include "CoreMinimal.h"
#include "LineType.h"
#include "BikeLongShotInfo.generated.h"

USTRUCT(BlueprintType)
struct FBikeLongShotInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<LineType> LongShotOrder;
    
    ENDGAME_API FBikeLongShotInfo();
};

