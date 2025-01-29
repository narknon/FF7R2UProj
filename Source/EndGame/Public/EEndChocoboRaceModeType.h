#pragma once
#include "CoreMinimal.h"
#include "EEndChocoboRaceModeType.generated.h"

UENUM(BlueprintType)
enum class EEndChocoboRaceModeType : uint8 {
    Beginner,
    Advanced,
    GoldCup,
    Tutorial,
    SubQuest,
    ShinraManager,
    MainStory,
};

