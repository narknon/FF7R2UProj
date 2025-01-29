#pragma once
#include "CoreMinimal.h"
#include "SQEXSEADSoundRandomProperty.generated.h"

USTRUCT(BlueprintType)
struct FSQEXSEADSoundRandomProperty {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SoundName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 RandomWeights;
    
    SQEXSEAD_API FSQEXSEADSoundRandomProperty();
};

