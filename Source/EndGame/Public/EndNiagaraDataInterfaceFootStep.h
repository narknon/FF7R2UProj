#pragma once
#include "CoreMinimal.h"
#include "NiagaraDataInterface.h"
#include "EEndFootAttributeTypes.h"
#include "EndNiagaraDataInterfaceFootStep.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndNiagaraDataInterfaceFootStep : public UNiagaraDataInterface {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndFootAttributeTypes m_FootAttributeTypes;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_SpawnCount;
    
    UEndNiagaraDataInterfaceFootStep();

};

