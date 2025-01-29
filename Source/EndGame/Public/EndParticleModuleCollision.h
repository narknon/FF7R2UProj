#pragma once
#include "CoreMinimal.h"
#include "Particles/Collision/ParticleModuleCollision.h"
#include "EndParticleModuleCollision.generated.h"

UCLASS(Blueprintable, EditInlineNew, MinimalAPI)
class UEndParticleModuleCollision : public UParticleModuleCollision {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_HitOffsetNormalScale;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_FreezeTranslationVelocityLength;
    
    UEndParticleModuleCollision();

};

