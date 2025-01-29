#pragma once
#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "EndActorBaseInterface.h"
#include "EndSaveActorInterface.h"
#include "EndTriggerVolume.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndTriggerVolume : public ATriggerVolume, public IEndSaveActorInterface, public IEndActorBaseInterface {
    GENERATED_BODY()
public:
    AEndTriggerVolume(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

