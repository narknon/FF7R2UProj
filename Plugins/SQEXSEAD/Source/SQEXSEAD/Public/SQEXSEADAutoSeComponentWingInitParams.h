#pragma once
#include "CoreMinimal.h"
#include "SQEXSEADAutoSeComponentWingInitParams.generated.h"

USTRUCT(BlueprintType)
struct SQEXSEAD_API FSQEXSEADAutoSeComponentWingInitParams {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName WingRootName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName WingEdgeName;
    
    FSQEXSEADAutoSeComponentWingInitParams();
};

