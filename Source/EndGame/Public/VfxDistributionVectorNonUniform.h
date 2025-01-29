#pragma once
#include "CoreMinimal.h"
#include "Distributions/DistributionVectorUniform.h"
#include "VfxNonUniformRandom.h"
#include "VfxDistributionVectorNonUniform.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class UVfxDistributionVectorNonUniform : public UDistributionVectorUniform {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVfxNonUniformRandom m_NonUniformRandomX;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVfxNonUniformRandom m_NonUniformRandomY;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVfxNonUniformRandom m_NonUniformRandomZ;
    
    UVfxDistributionVectorNonUniform();

};

