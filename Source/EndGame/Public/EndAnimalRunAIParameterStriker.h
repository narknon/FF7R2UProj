#pragma once
#include "CoreMinimal.h"
#include "EndAnimalRunAIParameterAttackerBase.h"
#include "EndAnimalRunAIParameterStriker.generated.h"

UCLASS(Blueprintable)
class UEndAnimalRunAIParameterStriker : public UEndAnimalRunAIParameterAttackerBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bOverrideRangeMin;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RangeMin;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bOverrideRangeMax;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RangeMax;
    
    UEndAnimalRunAIParameterStriker();

};

