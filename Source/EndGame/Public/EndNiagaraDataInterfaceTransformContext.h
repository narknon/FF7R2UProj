#pragma once
#include "CoreMinimal.h"
#include "NiagaraDataInterface.h"
#include "VFXShaderResourceBufferInfo.h"
#include "EndNiagaraDataInterfaceTransformContext.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndNiagaraDataInterfaceTransformContext : public UNiagaraDataInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVFXShaderResourceBufferInfo m_Translation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVFXShaderResourceBufferInfo m_Rotation;
    
    UEndNiagaraDataInterfaceTransformContext();

};

