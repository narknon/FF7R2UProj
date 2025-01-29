#pragma once
#include "CoreMinimal.h"
#include "EndParticleModuleBase.h"
#include "EndParticleModuleFootStep.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndParticleModuleFootStep : public UEndParticleModuleBase {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 m_BurstCount;
    
    UEndParticleModuleFootStep();

};

