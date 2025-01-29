#pragma once
#include "CoreMinimal.h"
#include "SQEXSEAD_BGMOptions.h"
#include "SQEXSEAD_BGMSlotSetting.generated.h"

USTRUCT(BlueprintType)
struct FSQEXSEAD_BGMSlotSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SlotName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEXSEAD_BGMOptions SlotOption;
    
    SQEXSEAD_API FSQEXSEAD_BGMSlotSetting();
};

