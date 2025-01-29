#pragma once
#include "CoreMinimal.h"
#include "Particles/Camera/ParticleModuleCameraBase.h"
#include "EndCameraShakeParam.h"
#include "EndParticleModuleCameraShake.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndParticleModuleCameraShake : public UParticleModuleCameraBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndCameraShakeParam m_EndCameraShakeParam;
    
    UEndParticleModuleCameraShake();

};

