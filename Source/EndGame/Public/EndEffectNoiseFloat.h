#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Distributions/DistributionFloatConstantCurve.h"
#include "Distributions/DistributionFloat.h"
#include "EEndEffectInterpolateKind.h"
#include "EndEffectNoiseFloat.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class UEndEffectNoiseFloat : public UDistributionFloatConstantCurve {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndEffectInterpolateKind m_InterpolateKind;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FInterpCurveFloat m_CycleTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionFloat m_RandomCurve;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_RandomSeed;
    
    UEndEffectNoiseFloat();

};

