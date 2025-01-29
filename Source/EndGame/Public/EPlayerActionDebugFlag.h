#pragma once
#include "CoreMinimal.h"
#include "EPlayerActionDebugFlag.generated.h"

UENUM(BlueprintType)
namespace EPlayerActionDebugFlag {
    enum Type {
        CharaBaseSameLeaderActionTest,
        UseCalculatedParkour,
        ForceUseRuntimeParkour,
        NoRuntimeParkourCache,
        NoAddtiveAroundParkourEdge,
        ForceInMemoArea,
        ForceInSercretEnemy,
        DisableOnlyNaviMove,
        ForceWallRunning,
        ForceWallRunningInVolume,
        DisableNPCToMove,
        LadderNoAlwaysAttachMode,
        DisableDualQuatAttach,
        AllPartySameFAction,
        DisableParkour,
        WalkwayReverseAIWithinFollow,
        ForceFAMoveLimitLeft,
        ForceFAMoveLimitRight,
        ForceFAMoveLimitUp,
        ForceFAMoveLimitDown,
        __WallRunInputTestDiable,
        __WallRunInputTestView,
        __TEST_NO_SYNC_SHOOTING,
        UseNewEdgeSearch,
        UseOldEdgeSearch,
        ForceNewFlyMode,
        Max,
    };
}

