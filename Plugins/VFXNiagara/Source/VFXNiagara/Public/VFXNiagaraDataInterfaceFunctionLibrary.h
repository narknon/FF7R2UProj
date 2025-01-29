#pragma once
#include "CoreMinimal.h"
#include "NiagaraDataInterface.h"
#include "VFXNiagaraDataInterfaceFunctionLibrary.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class VFXNIAGARA_API UVFXNiagaraDataInterfaceFunctionLibrary : public UNiagaraDataInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_Dummy;
    
    UVFXNiagaraDataInterfaceFunctionLibrary();

};

