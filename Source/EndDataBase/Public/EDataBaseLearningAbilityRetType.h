#pragma once
#include "CoreMinimal.h"
#include "EDataBaseLearningAbilityRetType.generated.h"

UENUM()
enum class EDataBaseLearningAbilityRetType {
    Error = -1,
    None = 0,
    Already,
    Learning,
};

