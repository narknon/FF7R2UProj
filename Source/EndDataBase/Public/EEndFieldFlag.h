#pragma once
#include "CoreMinimal.h"
#include "EEndFieldFlag.generated.h"

UENUM(BlueprintType)
enum class EEndFieldFlag : uint8 {
    MainMenuChapterSelect,
    ActionStartChapter,
    StartUninitParsistant,
    LocationJumpBlack,
    LocationJumpEndFadeOut,
    LocationJumpSaveData,
    LocationJumpSaveData_Snap2nd,
    SkipZack,
    CardGameBgImageSkinNone,
    CardGameBgImageSkinCosta,
    LocationJump,
    FinishGameJumpActor,
    FinishFieldManager,
    LocationJumpTitle,
    MainMenuChapterSelect_FinishOnSelectChapter,
    SimpleMethodPlayBGM,
    ActionLocationJump,
    LocationJumpSaved,
};

