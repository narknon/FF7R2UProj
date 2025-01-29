#pragma once
#include "CoreMinimal.h"
#include "EVFXAttachRotationKind.generated.h"

UENUM()
enum class EVFXAttachRotationKind : int8 {
    EVNR_Socket,
    EVNR_Actor,
    EVNR_World,
};

