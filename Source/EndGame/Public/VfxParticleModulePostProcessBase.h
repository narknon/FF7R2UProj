#pragma once
#include "CoreMinimal.h"
#include "EndParticleModuleBase.h"
#include "VfxParticleModulePostProcessBase.generated.h"

UCLASS(Abstract, Blueprintable, EditInlineNew)
class UVfxParticleModulePostProcessBase : public UEndParticleModuleBase {
    GENERATED_BODY()
public:
    UVfxParticleModulePostProcessBase();

};

