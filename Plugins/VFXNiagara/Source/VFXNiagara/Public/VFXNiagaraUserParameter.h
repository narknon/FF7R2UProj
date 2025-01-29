#pragma once
#include "CoreMinimal.h"
#include "NiagaraTypes.h"
#include "UObject/NoExportTypes.h"

#include "NiagaraVariant.h"
#include "VFXNiagaraUserParameter.generated.h"

USTRUCT(BlueprintType)
struct VFXNIAGARA_API FVFXNiagaraUserParameter {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FNiagaraVariable m_Variable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FNiagaraVariant m_Variant;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSoftObjectPath m_ObjectPath;
    
    FVFXNiagaraUserParameter();
};

