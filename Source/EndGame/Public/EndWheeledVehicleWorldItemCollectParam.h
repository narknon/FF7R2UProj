#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndWheeledVehicleWorldItemCollectParam.generated.h"

USTRUCT(BlueprintType)
struct FEndWheeledVehicleWorldItemCollectParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector BoxCenter;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector BoxExtent;
    
    ENDGAME_API FEndWheeledVehicleWorldItemCollectParam();
};

