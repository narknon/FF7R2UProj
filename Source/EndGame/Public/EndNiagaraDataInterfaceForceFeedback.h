#pragma once
#include "CoreMinimal.h"
#include "NiagaraDataInterface.h"
#include "EEndForceFeedbackEffect.h"
#include "EEndForceFeedbackTrack.h"
#include "EndNiagaraDataInterfaceForceFeedback.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndNiagaraDataInterfaceForceFeedback : public UNiagaraDataInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndForceFeedbackTrack m_PriorityTrack;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndForceFeedbackEffect m_Effect;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_EffectName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_bWithPriorityControl: 1;
    
    UEndNiagaraDataInterfaceForceFeedback();

};

