#pragma once
#include "CoreMinimal.h"
#include "EEndChocoboRaceCourseRank.generated.h"

UENUM(BlueprintType)
enum class EEndChocoboRaceCourseRank : uint8 {
    Beginner,
    Advanced,
    Silver,
    Gold,
    Master,
    Special,
    Max,
};

