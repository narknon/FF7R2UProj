#pragma once
#include "CoreMinimal.h"
#include "EndCondorUnitController.h"
#include "EndCondorUnitCommanderController.generated.h"

UCLASS(Blueprintable)
class AEndCondorUnitCommanderController : public AEndCondorUnitController {
    GENERATED_BODY()
public:
    AEndCondorUnitCommanderController(const FObjectInitializer& ObjectInitializer);

};

