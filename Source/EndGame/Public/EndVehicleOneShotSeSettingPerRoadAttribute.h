#pragma once
#include "CoreMinimal.h"
#include "SQEXSEADSoundKey.h"
#include "EEndVehicleSwitchValueSourceTypes.h"
#include "EndVehicleOneShotSeSettingPerRoadAttribute.generated.h"

class USoundAttenuation;

USTRUCT(BlueprintType)
struct FEndVehicleOneShotSeSettingPerRoadAttribute {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEXSEADSoundKey Sound[7];
    
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
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SupressionTimeSec;
    
    ENDGAME_API FEndVehicleOneShotSeSettingPerRoadAttribute();
};

