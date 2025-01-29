#pragma once
#include "CoreMinimal.h"
#include "EEndWeaponUpgradeEffectsKind.generated.h"

UENUM(BlueprintType)
enum class EEndWeaponUpgradeEffectsKind : uint8 {
    None,
    BeginMenu,
    FadeInFadeOut,
    SpawnCore,
    ActivationSkill,
    Root,
    StartMenu,
    EndMenu,
    Cursor,
    Max,
};

