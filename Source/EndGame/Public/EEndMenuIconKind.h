#pragma once
#include "CoreMinimal.h"
#include "EEndMenuIconKind.generated.h"

UENUM(BlueprintType)
enum class EEndMenuIconKind : uint8 {
    None,
    Item,
    KeyItem,
    WeaponCloud,
    WeaponBarret,
    WeaponTifa,
    WeaponAerith,
    Bangle,
    Accessory,
    Materia,
    Resource,
    KnockOut,
    Defeat,
    LevelUpMateria,
    UpgradeWeaponCloud,
    UpgradeWeaponBarret,
    UpgradeWeaponTifa,
    UpgradeWeaponAerith,
    BattleReport,
    WishList,
    WeaponRedXIII,
    WeaponYuffie,
    WeaponCaitsith,
    UpgradeWeaponRedXIII,
    UpgradeWeaponYuffie,
    UpgradeWeaponCaitsith,
    Collection,
    CraftMaterial,
    CraftMaterialGrass,
    CraftMaterialWood,
    CraftMaterialStones,
    CraftMaterialPouch,
    CraftMaterialEnemy,
    CraftMaterialOthers,
    ChocoboAccessory,
};

