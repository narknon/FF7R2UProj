#pragma once
#include "CoreMinimal.h"
#include "ESQEXSEADAudioVolumeCommand.h"
#include "SQEXSEADAudioVolumeEvent.generated.h"

USTRUCT(BlueprintType)
struct SQEXSEAD_API FSQEXSEADAudioVolumeEvent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<ESQEXSEADAudioVolumeCommand::Type> Command;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ExteriorAudioVolumeSoundOcclusionVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ExteriorAudioVolumeSoundOcclusionLPF;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ObstructionVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ObstructionLPF;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FadeTime;
    
    FSQEXSEADAudioVolumeEvent();
};

