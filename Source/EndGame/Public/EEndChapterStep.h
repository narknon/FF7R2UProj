#pragma once
#include "CoreMinimal.h"
#include "EEndChapterStep.generated.h"

UENUM(BlueprintType)
enum class EEndChapterStep : uint8 {
    None,
    ChangeChapterStart,
    ChangeChapterLoop,
    ChangeChapterEnd,
    QuestSetupLoop,
    QuestSetupEnd,
    PostStateManagerEntryObjectStart,
    PostStateManagerEntryObjectLoop,
    PostStateManagerEntryObjectEnd,
    Max,
};

