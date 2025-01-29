#pragma once
#include "CoreMinimal.h"
#include "EndBikePlayerControllerBase.h"
#include "EndBikePlayerController.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndBikePlayerController : public AEndBikePlayerControllerBase {
    GENERATED_BODY()
public:
    AEndBikePlayerController(const FObjectInitializer& ObjectInitializer);

};

