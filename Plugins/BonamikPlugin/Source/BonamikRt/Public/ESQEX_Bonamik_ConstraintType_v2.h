#pragma once
#include "CoreMinimal.h"
#include "ESQEX_Bonamik_ConstraintType_v2.generated.h"

UENUM(BlueprintType)
enum ESQEX_Bonamik_ConstraintType_v2 {
    ESQEX_Bonamik_ConstraintType_v2_None,
    ESQEX_Bonamik_ConstraintType_v2_Sphere,
    ESQEX_Bonamik_ConstraintType_v2_Spring,
    ESQEX_Bonamik_ConstraintType_v2_GroundAttach,
    ESQEX_Bonamik_ConstraintType_v2_SecondOrder_Sphere,
};

