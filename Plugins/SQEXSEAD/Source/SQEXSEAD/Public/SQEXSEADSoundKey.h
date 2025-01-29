#pragma once
#include "CoreMinimal.h"
#include "SQEXSEADSoundKey.generated.h"

class USQEXSEADSound;

USTRUCT(BlueprintType)
struct FSQEXSEADSoundKey {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSoftObjectPtr<USQEXSEADSound> SoundRef;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 SoundIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SoundName;
    
    SQEXSEAD_API FSQEXSEADSoundKey();
};

