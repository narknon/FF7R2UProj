#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndWheeledVehicleActionActorBase.generated.h"

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndWheeledVehicleActionActorBase : public AActor {
    GENERATED_BODY()
public:
    AEndWheeledVehicleActionActorBase(const FObjectInitializer& ObjectInitializer);

};

