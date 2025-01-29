#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndOnRailsPlayerControllerBase.generated.h"

UCLASS(Abstract, Blueprintable)
class AEndOnRailsPlayerControllerBase : public AActor {
    GENERATED_BODY()
public:
    AEndOnRailsPlayerControllerBase(const FObjectInitializer& ObjectInitializer);

};

