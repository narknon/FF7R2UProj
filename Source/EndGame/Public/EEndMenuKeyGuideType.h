#pragma once
#include "CoreMinimal.h"
#include "EEndMenuKeyGuideType.generated.h"

UENUM(BlueprintType)
enum class EEndMenuKeyGuideType : uint8 {
    Field,
    GBike,
    MiniGameBuggy,
    ChocoboRace,
    ChocoboRaceTutorial,
    SelectByCamera,
    FieldChainAbility,
    FieldShortcutAbility,
    GuideNone,
};

