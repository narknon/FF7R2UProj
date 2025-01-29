#pragma once
#include "CoreMinimal.h"
#include "EEndForceFeedbackEffect.h"
#include "EEndForceFeedbackTrack.h"
#include "EndParticleModuleBase.h"
#include "VfxParticleModuleForceFeedback.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UVfxParticleModuleForceFeedback : public UEndParticleModuleBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndForceFeedbackTrack m_PriorityTrack;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndForceFeedbackEffect m_Effect;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_bWithPriorityControl: 1;
    
    UVfxParticleModuleForceFeedback();

};

