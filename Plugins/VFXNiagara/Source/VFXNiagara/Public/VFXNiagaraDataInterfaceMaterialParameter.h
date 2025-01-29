#pragma once
#include "CoreMinimal.h"
#include "NiagaraDataInterface.h"
#include "VFXMaterialScalarParameter.h"
#include "VFXMaterialTextureParameter.h"
#include "VFXMaterialVectorParameter.h"
#include "VFXNiagaraDataInterfaceMaterialParameter.generated.h"

class UMaterialInstance;

UCLASS(Blueprintable, EditInlineNew)
class VFXNIAGARA_API UVFXNiagaraDataInterfaceMaterialParameter : public UNiagaraDataInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_EmitterName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_ModuleName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_OverrideParameterName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UMaterialInstance* m_MaterialInstance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FVFXMaterialScalarParameter> m_ScalarParameters;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FVFXMaterialVectorParameter> m_VectorParameters;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FVFXMaterialTextureParameter> m_TextureParameters;
    
    UVFXNiagaraDataInterfaceMaterialParameter();

};

