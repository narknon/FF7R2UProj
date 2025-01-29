#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VFXNiagaraUserParameter.h"
#include "VFXNiagaraParameterInfo.generated.h"

USTRUCT(BlueprintType)
struct VFXNIAGARA_API FVFXNiagaraParameterInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSoftObjectPath m_Template;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FVFXNiagaraUserParameter> m_UserParams;
    
    FVFXNiagaraParameterInfo();
};

