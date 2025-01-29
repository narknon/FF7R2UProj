#pragma once
#include "CoreMinimal.h"
#include "SQEX_BonamikTwoBodiesHolderDesc.h"
#include "SQEX_BonamikLongRangeAttachmentDesc.generated.h"

USTRUCT(BlueprintType)
struct FSQEX_BonamikLongRangeAttachmentDesc : public FSQEX_BonamikTwoBodiesHolderDesc {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float mStrength;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float mDamping;
    
    BONAMIKRT_API FSQEX_BonamikLongRangeAttachmentDesc();
};

