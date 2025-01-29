#pragma once
#include "CoreMinimal.h"
#include "EEndBattleDamageSourcePositionBaseType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleDamageSourcePositionBaseType : uint8 {
    Owner,
    OwnerWeapon1,
    OwnerWeapon2,
    OwnerWeapon3,
    OwnerWeapon4,
    OwnerWeapon5,
    OwnerWeapon6,
    OwnerWeapon7,
    OwnerWeapon8,
    OwnerWeapon9,
    Target,
    TargetWeapon1,
    TargetWeapon2,
    TargetWeapon3,
    TargetWeapon4,
    TargetWeapon5,
    TargetWeapon6,
    TargetWeapon7,
    TargetWeapon8,
    TargetWeapon9,
    ParentDamageSource,
    HitPosition,
    SpecifiedLocation = 23,
    LayoutItemLocation,
    EnvironmentActor,
    OwnerAerithAssist,
    TargetTop,
    OwnerAttributeAssist,
    OwnerCombinationPartner1,
    OwnerComponent,
    OwnerIceReflect,
    TargetDamageSource,
    OwnerCombinationAttachCharacter,
    OwnerMaster,
    ParentDamageSourceTarget,
    TargetPriorityFatMoogle,
};

