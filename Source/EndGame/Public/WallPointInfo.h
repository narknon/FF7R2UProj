#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WallPointData.h"
#include "WallPointInfo.generated.h"

USTRUCT(BlueprintType)
struct FWallPointInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FWallPointData Data;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Thickness;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 ID;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector Normal[3];
    
    ENDGAME_API FWallPointInfo();
};

