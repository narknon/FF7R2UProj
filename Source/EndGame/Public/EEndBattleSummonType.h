#pragma once
#include "CoreMinimal.h"
#include "EEndBattleSummonType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleSummonType : uint8 {
    Ifrit,
    Chocobo,
    Shiva,
    DebuChocobo,
    Leviathan,
    Bahamut,
    Titan,
    Odin,
    Kjata,
    Alexander,
    Phoenix,
    NeoBahamut,
    Carbuncle,
    Cactuar,
    Hinachocobo,
    Ramuh,
    Gilgamesh,
    Magicpot,
    End2Hinachocobo,
    DLCMoogle,
    Bottom,
    None = 31,
};

