#pragma once
#include "CoreMinimal.h"
#include "Distributions/DistributionFloat.h"
#include "VfxParticleModulePostProcessBase.h"
#include "VfxParticleModulePostProcessDirectionalBlur.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UVfxParticleModulePostProcessDirectionalBlur : public UVfxParticleModulePostProcessBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bOverride_DirectionalBlurDistortionIntensity: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bOverride_DirectionalBlurDistortionGradient: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bOverride_DirectionalBlurDistortionField: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bOverride_DirectionalBlurDistortionFrequency: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bOverride_DirectionalBlurDistortionPosition: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionFloat m_DirectionalBlurDistortionIntensity;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionFloat m_DirectionalBlurDistortionGradient;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionFloat m_DirectionalBlurDistortionField;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionFloat m_DirectionalBlurDistortionFrequency;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionFloat m_DirectionalBlurDistortionPosition;
    
    UVfxParticleModulePostProcessDirectionalBlur();

};

