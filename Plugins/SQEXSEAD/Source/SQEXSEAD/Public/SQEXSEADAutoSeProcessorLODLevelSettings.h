#pragma once
#include "CoreMinimal.h"
#include "SQEXSEADAutoSeMotionSoundFilter.h"
#include "SQEXSEADAutoSeProcessorLODLevelSettings.generated.h"

USTRUCT(BlueprintType)
struct SQEXSEAD_API FSQEXSEADAutoSeProcessorLODLevelSettings {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEXSEADAutoSeMotionSoundFilter SoundFilter;
    
    FSQEXSEADAutoSeProcessorLODLevelSettings();
};

