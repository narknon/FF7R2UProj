#pragma once
#include "CoreMinimal.h"
#include "EndAIController.h"
#include "EndCondorUnitController.generated.h"

UCLASS(Blueprintable)
class AEndCondorUnitController : public AEndAIController {
    GENERATED_BODY()
public:
    AEndCondorUnitController(const FObjectInitializer& ObjectInitializer);

};

