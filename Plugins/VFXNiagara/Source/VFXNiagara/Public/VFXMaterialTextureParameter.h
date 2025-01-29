#pragma once
#include "CoreMinimal.h"
#include "VFXMaterialParameterBase.h"
#include "VFXMaterialTextureParameter.generated.h"

class UTexture;

USTRUCT(BlueprintType)
struct VFXNIAGARA_API FVFXMaterialTextureParameter : public FVFXMaterialParameterBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UTexture* m_Value;
    
    FVFXMaterialTextureParameter();
};

