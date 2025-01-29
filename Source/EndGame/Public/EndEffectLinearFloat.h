#pragma once
#include "CoreMinimal.h"
#include "Distributions/DistributionFloatConstantCurve.h"
#include "EndEffectLinearFloat.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class UEndEffectLinearFloat : public UDistributionFloatConstantCurve {
    GENERATED_BODY()
public:
    UEndEffectLinearFloat();

};

