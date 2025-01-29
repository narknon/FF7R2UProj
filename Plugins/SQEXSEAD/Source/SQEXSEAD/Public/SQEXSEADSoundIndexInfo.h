#pragma once
#include "CoreMinimal.h"
#include "SQEXSEADSoundIndexInfo.generated.h"

USTRUCT(BlueprintType)
struct FSQEXSEADSoundIndexInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 SoundIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Duration;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float VoicedSectionAdjustmentTime;
    
    SQEXSEAD_API FSQEXSEADSoundIndexInfo();
};

