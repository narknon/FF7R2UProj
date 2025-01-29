#pragma once
#include "CoreMinimal.h"
#include "EGameStatus.generated.h"

UENUM(BlueprintType)
enum class EGameStatus : uint8 {
    EGameStatus_INIT_RESIDENT_RESOURCE,
    EGameStatus_INIT_EDITOR_GAME_PALY,
    EGameStatus_INIT_EDITOR_LOCATION,
    EGameStatus_INIT_EDITOR_CUT_SCENE,
    EGameStatus_EMPTY_EDITOR_LOCATION,
    EGameStatus_TO_TITLE,
    EGameStatus_LOAD_SAVEDATA,
    EGameStatus_LOAD_BACKUPDATA,
    EGameStatus_LOAD_SNAPDATA,
    EGameStatus_LOAD_SNAPDATA_2ND,
    EGameStatus_INIT_EDITOR_QUICK_GAME_PALY,
    EGameStatus_JUMP_LOCATION,
    EGameStatus_INIT_EDITOR_PREVIEW_LAUNCHER,
    EGameStatus_TEST_CUT_SCENE,
    EGameStatus_TO_BOOT,
};

