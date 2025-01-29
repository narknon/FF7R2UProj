#pragma once
#include "CoreMinimal.h"
#include "ESQEX_Bonamik_LinkType_v2.generated.h"

UENUM(BlueprintType)
enum ESQEX_Bonamik_LinkType_v2 {
    ESQEX_Bonamik_LinkType_v2_Lateral,
    ESQEX_Bonamik_LinkType_v2_ParentChild,
    ESQEX_Bonamik_LinkType_v2_Bending,
    ESQEX_Bonamik_LinkType_v2_PinConstraint,
    ESQEX_Bonamik_LinkType_v2_KdiConstraint,
    ESQEX_Bonamik_LinkType_v2_ReactionTransfer,
    ESQEX_Bonamik_LinkType_v2_InverseFreeConstraint,
};

