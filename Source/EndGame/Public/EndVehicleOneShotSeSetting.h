#pragma once
#include "CoreMinimal.h"
#include "SQEXSEADSoundKey.h"
#include "EEndVehicleSwitchValueSourceTypes.h"
#include "EndVehicleOneShotSeSetting.generated.h"

class USoundAttenuation;

USTRUCT(BlueprintType)
struct FEndVehicleOneShotSeSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEXSEADSoundKey Sound;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<EEndVehicleSwitchValueSourceTypes::Type> SwitchValueSourceType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AttachPointName;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundAttenuation* OverrideAttenuation[4];
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundAttenuation* OverrideConcurrency;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MoveThreshold;
    
    ENDGAME_API FEndVehicleOneShotSeSetting();
};

