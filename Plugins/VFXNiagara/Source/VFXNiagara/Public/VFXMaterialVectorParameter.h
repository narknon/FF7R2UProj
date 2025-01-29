#pragma once
#include "CoreMinimal.h"
#include "VFXMaterialParameterBase.h"
#include "VFXMaterialVectorParameter.generated.h"

USTRUCT(BlueprintType)
struct VFXNIAGARA_API FVFXMaterialVectorParameter : public FVFXMaterialParameterBase {
    GENERATED_BODY()
public:
    FVFXMaterialVectorParameter();
};

