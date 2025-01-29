#pragma once
#include "CoreMinimal.h"
#include "Particles/ParticleModule.h"
#include "EndParticleModuleBase.generated.h"

UCLASS(Abstract, Blueprintable, EditInlineNew)
class UEndParticleModuleBase : public UParticleModule {
    GENERATED_BODY()
public:
    UEndParticleModuleBase();

};

