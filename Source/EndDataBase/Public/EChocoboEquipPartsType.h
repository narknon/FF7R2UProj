#pragma once
#include "CoreMinimal.h"
#include "EChocoboEquipPartsType.generated.h"

UENUM(BlueprintType)
enum class EChocoboEquipPartsType : uint8 {
    EChocoboEquipPartsType_Head,
    EChocoboEquipPartsType_Body,
    EChocoboEquipPartsType_Leg,
    EChocoboEquipPartsType_Max UMETA(Hidden),
    EChocoboEquipPartsType_None = EChocoboEquipPartsType_Max,
};

