#pragma once
#include "CoreMinimal.h"
#include "EndAIControllerBluePrintBase.h"
#include "EndAIControllerAnimalBase.generated.h"

UCLASS(Blueprintable)
class AEndAIControllerAnimalBase : public AEndAIControllerBluePrintBase {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Animal_CautionDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Animal_SenseDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Animal_EscapeDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Animal_WanderingRadius;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Animal_WaitTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Animal_WaitTimeRandom;
    
public:
    AEndAIControllerAnimalBase(const FObjectInitializer& ObjectInitializer);

};

