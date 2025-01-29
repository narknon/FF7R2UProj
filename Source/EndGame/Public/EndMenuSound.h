#pragma once
#include "CoreMinimal.h"
#include "Sound/SoundBase.h"
#include "EndMenuSound.generated.h"

class USQEXSEADSound;

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndMenuSound : public USoundBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEXSEADSound* SoundAsset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SoundName;
    
    UEndMenuSound();

};

