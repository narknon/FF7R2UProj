#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SQEXSEAD_BGMSlotSetting.h"
#include "SQEXSEADBGMManager.generated.h"

class USQEXSEADBGMSlot;
class USQEXSEADBGMSlotController;

UCLASS(Blueprintable, DefaultConfig, Config=Engine)
class SQEXSEAD_API USQEXSEADBGMManager : public UObject {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<USQEXSEADBGMSlot*> Slots_;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<USQEXSEADBGMSlotController*> Controllers_;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FSQEXSEAD_BGMSlotSetting> SlotSettings_;
    
public:
    USQEXSEADBGMManager();

};

