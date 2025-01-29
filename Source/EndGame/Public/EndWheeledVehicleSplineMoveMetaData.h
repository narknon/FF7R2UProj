#pragma once
#include "CoreMinimal.h"
#include "EndWheeledVehicleSplineMoveMetaData.generated.h"

USTRUCT(BlueprintType)
struct FEndWheeledVehicleSplineMoveMetaData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float InputKey;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MaxSpeed;
    
    ENDGAME_API FEndWheeledVehicleSplineMoveMetaData();
};

