#pragma once
#include "CoreMinimal.h"
#include "Distributions/DistributionVectorConstantCurve.h"
#include "EndEffectLinearVector.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class UEndEffectLinearVector : public UDistributionVectorConstantCurve {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_EnableLinearX: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_EnableLinearY: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_EnableLinearZ: 1;
    
    UEndEffectLinearVector();

};

