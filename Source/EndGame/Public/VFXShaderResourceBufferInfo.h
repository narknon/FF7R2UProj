#pragma once
#include "CoreMinimal.h"
#include "VFXShaderResourceBufferInfo.generated.h"

class UShaderResourceBuffer;

USTRUCT(BlueprintType)
struct FVFXShaderResourceBufferInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UShaderResourceBuffer* m_ShaderResourceBuffer;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_NumberOfContext;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_NumberOfKey;
    
    ENDGAME_API FVFXShaderResourceBufferInfo();
};

