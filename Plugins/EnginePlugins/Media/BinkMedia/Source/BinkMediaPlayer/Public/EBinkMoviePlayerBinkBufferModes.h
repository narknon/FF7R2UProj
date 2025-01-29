#pragma once
#include "CoreMinimal.h"
#include "EBinkMoviePlayerBinkBufferModes.generated.h"

UENUM(BlueprintType)
enum EBinkMoviePlayerBinkBufferModes {
    MP_Bink_Stream,
    MP_Bink_PreloadAll,
    MP_Bink_StreamUntilResident,
};

