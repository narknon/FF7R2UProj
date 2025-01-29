#pragma once
#include "CoreMinimal.h"
#include "Distributions/DistributionVector.h"
#include "EndParticleModuleBase.h"
#include "VfxParticleModuleRandomUV.generated.h"

UCLASS(Blueprintable, EditInlineNew, MinimalAPI)
class UVfxParticleModuleRandomUV : public UEndParticleModuleBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionVector m_Init;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionVector m_Speed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionVector m_ScaleInit;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionVector m_ScaleSpeed;
    
    UVfxParticleModuleRandomUV();

};

