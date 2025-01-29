#pragma once
#include "CoreMinimal.h"
#include "NiagaraDataInterface.h"
#include "EndCameraShakeParam.h"
#include "EndNiagaraDataInterfaceCameraShake.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndNiagaraDataInterfaceCameraShake : public UNiagaraDataInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndCameraShakeParam m_EndCameraShakeParam;
    
    UEndNiagaraDataInterfaceCameraShake();

};

