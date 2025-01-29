#pragma once
#include "CoreMinimal.h"
#include "EBinkMediaPlayerBinkBufferModes.generated.h"

UENUM(BlueprintType)
enum EBinkMediaPlayerBinkBufferModes {
    BMASM_Bink_Stream,
    BMASM_Bink_PreloadAll,
    BMASM_Bink_StreamUntilResident,
};

