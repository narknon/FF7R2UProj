#pragma once
#include "CoreMinimal.h"
#include "SQEX_BonamikTwoBodiesHolderDesc.generated.h"

USTRUCT(BlueprintType)
struct FSQEX_BonamikTwoBodiesHolderDesc {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString mA;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString mB;
    
    BONAMIKRT_API FSQEX_BonamikTwoBodiesHolderDesc();
};

