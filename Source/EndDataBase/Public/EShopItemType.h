#pragma once
#include "CoreMinimal.h"
#include "EShopItemType.generated.h"

UENUM(BlueprintType)
enum class EShopItemType : uint8 {
    EShopItemType_Item,
    EShopItemType_Equipment,
    EShopItemType_Weapon = EShopItemType_Equipment,
    EShopItemType_Materia,
    EShopItemType_Armor,
    EShopItemType_Accessory,
    EShopItemType_JukeBox,
    EShopItemType_Card,
    EShopItemType_Material,
    EShopItemType_MAX UMETA(Hidden),
    EShopItemType_None,
};

