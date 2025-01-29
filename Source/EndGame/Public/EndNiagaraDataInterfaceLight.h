#pragma once
#include "CoreMinimal.h"
#include "NiagaraDataInterface.h"
#include "EndNiagaraDataInterfaceLight.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndNiagaraDataInterfaceLight : public UNiagaraDataInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_Dummy;
    
    UEndNiagaraDataInterfaceLight();

};

