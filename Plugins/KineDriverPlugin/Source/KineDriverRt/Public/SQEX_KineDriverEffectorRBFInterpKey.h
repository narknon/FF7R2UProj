#pragma once
#include "CoreMinimal.h"
#include "SQEX_KineDriverEffectorRBFInterpKey.generated.h"

USTRUCT(BlueprintType)
struct FSQEX_KineDriverEffectorRBFInterpKey {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<float> inArray;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<float> OutArray;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Scale;
    
    KINEDRIVERRT_API FSQEX_KineDriverEffectorRBFInterpKey();
};

