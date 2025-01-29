#pragma once
#include "CoreMinimal.h"
#include "EndAIController.h"
#include "Templates/SubclassOf.h"
#include "EndAnimalRunAIController.generated.h"

class UEndAnimalRunAIParameterBase;

UCLASS(Blueprintable, MinimalAPI)
class AEndAnimalRunAIController : public AEndAIController {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndAnimalRunAIParameterBase> DefaultParameterClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ToleranceDist2BallOnShoot;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RadiusMerginDribble;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RadiusMerginChase;
    
public:
    AEndAnimalRunAIController(const FObjectInitializer& ObjectInitializer);

};

