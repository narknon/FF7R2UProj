#pragma once
#include "CoreMinimal.h"
#include "SQEXSEADOrderSoundSetting.generated.h"

USTRUCT(BlueprintType)
struct FSQEXSEADOrderSoundSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> OrderNames;
    
    SQEXSEAD_API FSQEXSEADOrderSoundSetting();
};

