#pragma once
#include "CoreMinimal.h"
#include "EAutoMagicTargetConditionType.generated.h"

UENUM(BlueprintType)
enum class EAutoMagicTargetConditionType : uint8 {
    HpRateLower,
    HpRateHigher,
    StatusResist,
    MpRateForTargetRank,
    IsDead,
    CurableStatusChange,
    NoResist,
    ErasableBuff,
    NeedBarrier,
    NeedBrave,
    NeedProtect,
    NeedDebrave,
    NeedDeprotect,
    WeakPoint,
    UseMagic,
    PlayerOnly,
    RateResist,
    HighPopulation,
    MpRateForGroupRank,
    NoUCPCTarget,
    IsBurst,
    UCPCTarget,
};

