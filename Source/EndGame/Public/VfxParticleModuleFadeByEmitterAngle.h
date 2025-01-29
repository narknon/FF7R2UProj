#pragma once
#include "CoreMinimal.h"
#include "Particles/Color/ParticleModuleColorBase.h"
#include "VfxParticleModuleFadeByEmitterAngle.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UVfxParticleModuleFadeByEmitterAngle : public UParticleModuleColorBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_LimitAngle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_BlendAngle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_VisibleDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_BlendDistance;
    
    UVfxParticleModuleFadeByEmitterAngle();

};

