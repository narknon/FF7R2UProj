#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Distributions/DistributionVectorConstantCurve.h"
#include "Distributions/DistributionVector.h"
#include "EEndEffectInterpolateKind.h"
#include "EndEffectNoiseVector.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class UEndEffectNoiseVector : public UDistributionVectorConstantCurve {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndEffectInterpolateKind m_InterpolateKind;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FInterpCurveFloat m_CycleTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionVector m_RandomCurve;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_RandomSeed;
    
    UEndEffectNoiseVector();

};

