#pragma once
#include "CoreMinimal.h"
#include "MaterialParameterLight.h"
#include "EndEmissiveColorParameter.generated.h"

USTRUCT(BlueprintType)
struct FEndEmissiveColorParameter : public FMaterialParameterLight {
    GENERATED_BODY()
public:
    ENDGAME_API FEndEmissiveColorParameter();
};

