#pragma once
#include "CoreMinimal.h"
#include "ESQEX_Bonamik_PropagationMode.generated.h"

UENUM(BlueprintType)
enum ESQEX_Bonamik_PropagationMode {
    ESQEX_Bonamik_PropagationMode_SelfAndChildren,
    ESQEX_Bonamik_PropagationMode_SelfOnly,
    ESQEX_Bonamik_PropagationMode_ChildrenOnly,
};

