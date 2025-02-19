#pragma once
#include "CoreMinimal.h"
#include "EEndGameModeSequence.generated.h"

UENUM(BlueprintType)
enum class EEndGameModeSequence : uint8 {
    None,
    Begin,
    Boot,
    Boot_OnlineSubsystem,
    Boot_CommonSaveData_PreCheck,
    Boot_LoadWait,
    Boot_Resident,
    Boot_Resident_Wait,
    Boot_CommonSaveData,
    Boot_CommonSaveData_CheckWait,
    Boot_CommonSaveData_Make,
    Boot_CommonSaveData_MakeWait,
    Boot_CommonSaveData_Load,
    Boot_CommonSaveData_LoadWait,
    Boot_Font_Load,
    Boot_Font_LoadWait,
    Boot_AppContent,
    Boot_AppContent_CheckWait,
    Boot_AppContent_Message,
    Boot_AppContent_MessageWait,
    Boot_AppContent_Update,
    Boot_AppContent_UpdateWait,
    Boot_SendTrigger,
    Boot_GameIntentWait,
    DebugMenu,
    DebugMenu_LoadWait,
    DebugMenu_NormalWait,
    DebugMenu_NormalUnload,
    DebugMenu_TestPlay,
    DebugMenu_TestPlayLoop,
    DebugMenu_TestPlayLoadWait,
    Title_Shader_CompileWait,
    Title,
    Title_Wait,
    LocationJump,
    LocationJump_JumpWait,
    LocationJump_GameWait,
    LocationJump_BootWait,
    Editor,
    Editor_UnloadWait,
    Editor_GameJumpWait,
    Editor_Finish,
};

