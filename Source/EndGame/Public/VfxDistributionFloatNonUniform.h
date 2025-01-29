#pragma once
#include "CoreMinimal.h"
#include "Distributions/DistributionFloatUniform.h"
#include "VfxNonUniformRandom.h"
#include "VfxDistributionFloatNonUniform.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class UVfxDistributionFloatNonUniform : public UDistributionFloatUniform {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVfxNonUniformRandom m_NonUniformRandom;
    
    UVfxDistributionFloatNonUniform();

};

