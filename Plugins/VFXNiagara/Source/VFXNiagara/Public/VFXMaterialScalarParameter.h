#pragma once
#include "CoreMinimal.h"
#include "VFXMaterialParameterBase.h"
#include "VFXMaterialScalarParameter.generated.h"

USTRUCT(BlueprintType)
struct VFXNIAGARA_API FVFXMaterialScalarParameter : public FVFXMaterialParameterBase {
    GENERATED_BODY()
public:
    FVFXMaterialScalarParameter();
};

