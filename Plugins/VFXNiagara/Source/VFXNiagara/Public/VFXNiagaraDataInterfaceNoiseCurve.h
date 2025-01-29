#pragma once
#include "CoreMinimal.h"
#include "NiagaraDataInterface.h"
#include "VFXNiagaraDataInterfaceNoiseCurve.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class VFXNIAGARA_API UVFXNiagaraDataInterfaceNoiseCurve : public UNiagaraDataInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_fCycleTime;
    
    UVFXNiagaraDataInterfaceNoiseCurve();

};

