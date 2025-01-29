#pragma once
#include "CoreMinimal.h"
#include "EGameMode.generated.h"

UENUM(BlueprintType)
enum class EGameMode : uint8 {
    EGameMode_PLAY_GAME,
    EGameMode_FILED_TEST,
    EGameMode_MOTION_TEST,
    EGameMode_BATTLE_TEST,
    EGameMode_SOUND_TEST,
    EGameMode_EVENT_TEST,
    EGameMode_PLAYABLE,
    EGameMode_TRIAL,
    EGameMode_MediaDemo,
    EGameMode_PreviewEvent,
    EGameMode_Expansion2,
    EGameMode_Expansion3,
};

