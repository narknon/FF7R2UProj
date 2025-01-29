#pragma once
#include "CoreMinimal.h"
#include "EMoogleShopNotifyType.generated.h"

UENUM(BlueprintType)
enum class EMoogleShopNotifyType : uint8 {
    MSN_AddPenalty,
    MSN_GimmickStart,
    MSN_GimmickStop,
    Num,
};

