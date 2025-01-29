#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "EndWheeledVehicleRespawnAfterBattleParam.generated.h"

USTRUCT(BlueprintType)
struct FEndWheeledVehicleRespawnAfterBattleParam {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FFloatInterval RadiusRangeBehindCamera;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FFloatInterval RadiusRangeFrontCamera;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector BoxSize;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector OffsetVehicleSpawnLocation;
    
    ENDGAME_API FEndWheeledVehicleRespawnAfterBattleParam();
};

