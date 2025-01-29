#pragma once
#include "CoreMinimal.h"
#include "SQEX_KineDriverEffectorRBFInterpKey.h"
#include "SQEX_KineDriverEffectorRBFInterp.generated.h"

USTRUCT(BlueprintType)
struct FSQEX_KineDriverEffectorRBFInterp {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<float> InputArray;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<float> InCoeffArray;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Filter;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FilterParameter;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<float> Weights;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FSQEX_KineDriverEffectorRBFInterpKey> Keys;
    
    KINEDRIVERRT_API FSQEX_KineDriverEffectorRBFInterp();
};

