#pragma once
#include "CoreMinimal.h"
#include "EndBoidsTypeParam.h"
#include "EndBoidsParam.generated.h"

USTRUCT(BlueprintType)
struct FEndBoidsParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PersonalSpace;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBoidsTypeParam> BoidsParameter;
    
    ENDGAME_API FEndBoidsParam();
};

