#pragma once
#include "CoreMinimal.h"
#include "ESQEX_Bonamik_CollisionShape_v2.generated.h"

UENUM(BlueprintType)
enum ESQEX_Bonamik_CollisionShape_v2 {
    ESQEX_Bonamik_CollisionShape_v2_None,
    ESQEX_Bonamik_CollisionShape_v2_Sphere,
    ESQEX_Bonamik_CollisionShape_v2_Capsule,
    ESQEX_Bonamik_CollisionShape_v2_Inverse_Sphere,
    ESQEX_Bonamik_CollisionShape_v2_Inverse_Capsule,
    ESQEX_Bonamik_CollisionShape_v2_ReservedA,
    ESQEX_Bonamik_CollisionShape_v2_Plane,
    ESQEX_Bonamik_CollisionShape_v2_ReservedB,
    ESQEX_Bonamik_CollisionShape_v2_Box,
    ESQEX_Bonamik_CollisionShape_v2_Self_Collision,
};

