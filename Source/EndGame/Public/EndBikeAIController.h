#pragma once
#include "CoreMinimal.h"
#include "EndBikeControllerBase.h"
#include "EndBikeAIController.generated.h"

UCLASS(Blueprintable)
class AEndBikeAIController : public AEndBikeControllerBase {
    GENERATED_BODY()
public:
    AEndBikeAIController(const FObjectInitializer& ObjectInitializer);

};

