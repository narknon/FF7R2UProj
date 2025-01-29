#pragma once
#include "CoreMinimal.h"
#include "EndBikeControllerBase.h"
#include "EndBikePlayerControllerBase.generated.h"

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndBikePlayerControllerBase : public AEndBikeControllerBase {
    GENERATED_BODY()
public:
    AEndBikePlayerControllerBase(const FObjectInitializer& ObjectInitializer);

};

