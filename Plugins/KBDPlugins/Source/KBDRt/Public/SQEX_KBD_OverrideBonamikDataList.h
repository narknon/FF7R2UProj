#pragma once
#include "CoreMinimal.h"
#include "SQEX_KBD_OverrideBonamikDataList.generated.h"

class USQEX_BonamikAsset;

USTRUCT(BlueprintType)
struct KBDRT_API FSQEX_KBD_OverrideBonamikDataList {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName EnsembleName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<USQEX_BonamikAsset*> BonamikDataList;
    
    FSQEX_KBD_OverrideBonamikDataList();
};

