#pragma once
#include "CoreMinimal.h"
#include "NiagaraDataInterface.h"
#include "EndNiagaraDataInterfacePostProcessParameter.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndNiagaraDataInterfacePostProcessParameter : public UNiagaraDataInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_Dummy;
    
    UEndNiagaraDataInterfacePostProcessParameter();

};

