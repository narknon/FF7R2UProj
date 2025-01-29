#pragma once
#include "CoreMinimal.h"
#include "EEndAiMathCmp.h"
#include "EEndAnimalRunAngleType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_MiniGameRunWildCheckAngle.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_MiniGameRunWildCheckAngle : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimalRunAngleType A;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimalRunAngleType B;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAiMathCmp Operator;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Angle;
    
    UEndBTDecorator_MiniGameRunWildCheckAngle();

};

