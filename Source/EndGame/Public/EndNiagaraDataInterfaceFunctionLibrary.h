#pragma once
#include "CoreMinimal.h"
#include "NiagaraDataInterface.h"
#include "EndNiagaraDataInterfaceFunctionLibrary.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndNiagaraDataInterfaceFunctionLibrary : public UNiagaraDataInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_Dummy;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_EmitterName;
    
    UEndNiagaraDataInterfaceFunctionLibrary();

};

