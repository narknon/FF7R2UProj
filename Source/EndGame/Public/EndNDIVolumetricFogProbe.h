#pragma once
#include "CoreMinimal.h"
#include "NiagaraDataInterface.h"
#include "EndNDIVolumetricFogProbe.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndNDIVolumetricFogProbe : public UNiagaraDataInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_MaxCreateCount;
    
    UEndNDIVolumetricFogProbe();

};

