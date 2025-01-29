#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndWheeledVehicleSpawnableAreaData.generated.h"

USTRUCT(BlueprintType)
struct FEndWheeledVehicleSpawnableAreaData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector BoxSize;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BoxQueryHeightOffset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FVector> FloorCheckSamplingPoints;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TraceBaseFloorLength;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TraceGroundLength;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TolelanceGroundPitchAngle;
    
    ENDGAME_API FEndWheeledVehicleSpawnableAreaData();
};

