#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NiagaraDataInterface.h"
#include "VFXNiagaraDataInterfaceMaterial.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class VFXNIAGARA_API UVFXNiagaraDataInterfaceMaterial : public UNiagaraDataInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSoftObjectPath m_MaterialInstance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_Dummy;
    
    UVFXNiagaraDataInterfaceMaterial();

};

