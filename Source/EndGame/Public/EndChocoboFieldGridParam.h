#pragma once
#include "CoreMinimal.h"
#include "EndChocoboFieldGridMovementModifierParam.h"
#include "EndVehicleSmoothingParam.h"
#include "EndChocoboFieldGridParam.generated.h"

USTRUCT(BlueprintType)
struct FEndChocoboFieldGridParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float CheckForwardOffset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndVehicleSmoothingParam YawSmoothingParam;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 MaxAffectLevel;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float KeepHeight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndVehicleSmoothingParam KeepHeightSmoothing;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MinInputPower;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndChocoboFieldGridMovementModifierParam ModifireParam;
    
    ENDGAME_API FEndChocoboFieldGridParam();
};

