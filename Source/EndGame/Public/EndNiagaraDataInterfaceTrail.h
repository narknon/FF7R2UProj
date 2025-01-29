#pragma once
#include "CoreMinimal.h"
#include "NiagaraDataInterface.h"
#include "EndNiagaraDataInterfaceTrail.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndNiagaraDataInterfaceTrail : public UNiagaraDataInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_MaxTrailCount;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_PerTrailParticleCount;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_RingBufferSize;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_UpdateBufferFPS;
    
    UEndNiagaraDataInterfaceTrail();

};

