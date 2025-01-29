#pragma once
#include "CoreMinimal.h"
#include "SQEX_BonamikTwoBodiesHolderDesc.h"
#include "SQEX_BonamikSimpleLinkDesc.generated.h"

USTRUCT(BlueprintType)
struct FSQEX_BonamikSimpleLinkDesc : public FSQEX_BonamikTwoBodiesHolderDesc {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float mStretchedStrength;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float mCompressedStrength;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float mLinkParentStrength;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bIsBending;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableJointTwist;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableLengthAnimation;
    
    BONAMIKRT_API FSQEX_BonamikSimpleLinkDesc();
};

