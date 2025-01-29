#pragma once
#include "CoreMinimal.h"
#include "SQEX_BonamikTwoBodiesHolderDesc.h"
#include "SQEX_BonamikKDIDesc.generated.h"

USTRUCT(BlueprintType)
struct FSQEX_BonamikKDIDesc : public FSQEX_BonamikTwoBodiesHolderDesc {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float mTranslationWeight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float mRotationWeight;
    
    BONAMIKRT_API FSQEX_BonamikKDIDesc();
};

