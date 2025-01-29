#pragma once
#include "CoreMinimal.h"
#include "EEndChapterQuestResetType.generated.h"

UENUM(BlueprintType)
enum class EEndChapterQuestResetType : uint8 {
    None,
    ResetQuest,
    KeepQuest,
    NoneResetQuest,
};

