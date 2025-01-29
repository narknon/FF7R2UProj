#pragma once
#include "CoreMinimal.h"
#include "AerialPointData.h"
#include "AerialPointInfo.generated.h"

USTRUCT(BlueprintType)
struct FAerialPointInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FAerialPointData Data;
    
    ENDGAME_API FAerialPointInfo();
};

