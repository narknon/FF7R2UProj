#pragma once
#include "CoreMinimal.h"
#include "SQEXSEADSoundRandomProperty.h"
#include "SQEXSEADRandomSoundSetting.generated.h"

USTRUCT(BlueprintType)
struct FSQEXSEADRandomSoundSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FSQEXSEADSoundRandomProperty> RandomProperties;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 SilentRatio;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bIgnorePreviousSelectedSound: 1;
    
    SQEXSEAD_API FSQEXSEADRandomSoundSetting();
};

