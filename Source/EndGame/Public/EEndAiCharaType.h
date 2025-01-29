#pragma once
#include "CoreMinimal.h"
#include "EEndAiCharaType.generated.h"

UENUM(BlueprintType)
namespace EEndAiCharaType {
    enum Type {
        None,
        PCMembers,
        EnemyMembers,
        Leader,
    };
}

