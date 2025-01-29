#pragma once
#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "EndActorBaseInterface.h"
#include "EndSaveActorInterface.h"
#include "EndTriggerBox.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndTriggerBox : public ATriggerBox, public IEndSaveActorInterface, public IEndActorBaseInterface {
    GENERATED_BODY()
public:
    AEndTriggerBox(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

