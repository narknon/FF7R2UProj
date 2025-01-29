#pragma once
#include "CoreMinimal.h"
#include "SQEXSEADAutoSeComponentArmInitParams.h"
#include "SQEXSEADAutoSeComponentBodyInitParams.h"
#include "SQEXSEADAutoSeComponentFootInitParams.h"
#include "SQEXSEADAutoSeComponentSwingInitParams.h"
#include "SQEXSEADAutoSeComponentWingInitParams.h"
#include "SQEXSEADAutoSeComponentInitParams.generated.h"

USTRUCT(BlueprintType)
struct SQEXSEAD_API FSQEXSEADAutoSeComponentInitParams {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FSQEXSEADAutoSeComponentFootInitParams> Feet;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FSQEXSEADAutoSeComponentArmInitParams> Arms;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FSQEXSEADAutoSeComponentWingInitParams> Wings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FSQEXSEADAutoSeComponentSwingInitParams> Swings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEXSEADAutoSeComponentBodyInitParams Body;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AutoCalcHeelRatio;
    
    FSQEXSEADAutoSeComponentInitParams();
};

