#pragma once
#include "CoreMinimal.h"
#include "EEndDebugFlag.generated.h"

UENUM(BlueprintType)
enum class EEndDebugFlag : uint8 {
    IgnoreLocationDataTable,
    EntryLocationFieldTest,
    EntryLocationBattleTest,
    EntryLocationBegining,
    EncountLogOutput,
    BeginEntryLocationUnInitSaveData,
    SingleLocationUmap,
    EntryLocationAthleticLevel,
    IgnoreFieldEncount_FastTravelDebug,
};

