#pragma once
#include "CoreMinimal.h"
#include "EEndPartyCoordinatorTaskSequence.generated.h"

UENUM(BlueprintType)
enum class EEndPartyCoordinatorTaskSequence : uint8 {
    None,
    Initialize,
    StreamingLoop,
    ActorCreate,
    ActorCreate_WaitLoad,
    ActorCreate_WaitCreate,
    ActorDestroy,
    ActorDestroy_WaitDestroy,
    ActorDestroy_WaitUnload,
    SwitchSpec,
    SwitchSpec_WaitLoad,
    SwitchSpec_WaitUnload,
    Finish,
};

