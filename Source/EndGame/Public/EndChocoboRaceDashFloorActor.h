#pragma once
#include "CoreMinimal.h"
#include "EndActorBaseInterface.h"
#include "EndChocoboRaceGimmickActorBase.h"
#include "EndChocoboRaceDashFloorActor.generated.h"

UCLASS(Blueprintable)
class AEndChocoboRaceDashFloorActor : public AEndChocoboRaceGimmickActorBase, public IEndActorBaseInterface {
    GENERATED_BODY()
public:
    AEndChocoboRaceDashFloorActor(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

