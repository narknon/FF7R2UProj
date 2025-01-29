#pragma once
#include "CoreMinimal.h"
#include "NiagaraDataInterface.h"
#include "EndNiagaraDataInterfaceActorMaterialParameter.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndNiagaraDataInterfaceActorMaterialParameter : public UNiagaraDataInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_Dummy;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> m_MaterialNames;
    
    UEndNiagaraDataInterfaceActorMaterialParameter();

};

