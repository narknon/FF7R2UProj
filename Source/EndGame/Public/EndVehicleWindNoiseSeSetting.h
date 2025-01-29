#pragma once
#include "CoreMinimal.h"
#include "SQEXSEADSoundKey.h"
#include "EndVehicleZeroOneSetting.h"
#include "EndVehicleWindNoiseSeSetting.generated.h"

class USoundAttenuation;

USTRUCT(BlueprintType)
struct FEndVehicleWindNoiseSeSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEXSEADSoundKey Sound;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AttachPointName;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundAttenuation* OverrideAttenuation[4];
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndVehicleZeroOneSetting ZeroOneSlot0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndVehicleZeroOneSetting ZeroOneSlot1;
    
    ENDGAME_API FEndVehicleWindNoiseSeSetting();
};

