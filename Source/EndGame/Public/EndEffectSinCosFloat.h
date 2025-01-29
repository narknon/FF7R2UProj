#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Distributions/DistributionFloatConstantCurve.h"
#include "EndEffectSinCosFloat.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class UEndEffectSinCosFloat : public UDistributionFloatConstantCurve {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FInterpCurveFloat m_ValueScale;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_CycleTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_UseCos: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_Absolute: 1;
    
    UEndEffectSinCosFloat();

};

