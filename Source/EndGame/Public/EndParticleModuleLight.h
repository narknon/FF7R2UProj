#pragma once
#include "CoreMinimal.h"
#include "Particles/Light/ParticleModuleLightBase.h"
#include "Distributions/DistributionFloat.h"
#include "Distributions/DistributionVector.h"
#include "EVfxEffectLightKind.h"
#include "EndParticleModuleLight.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndParticleModuleLight : public UParticleModuleLightBase {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EVfxEffectLightKind m_LightKind;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionVector m_Color;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionFloat m_Intensity;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionFloat m_SourceRadius;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionFloat m_AttenuationRadius;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionFloat m_SourceLength;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_SourceLengthOffsetRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_bIsBeamLight: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_bRenderVolumetricFogOnly: 1;
    
    UEndParticleModuleLight();

};

