#pragma once
#include "CoreMinimal.h"
#include "EEndAiBattleRole.generated.h"

UENUM(BlueprintType)
namespace EEndAiBattleRole {
    enum Type {
        None,
        Front,
        Middle,
        Back,
        Shield,
        Theif,
        PhysicsFrontDD,
        PhysicsBackDD,
        Unique1,
        Unique2,
        Unique3,
        Unique4,
    };
}

