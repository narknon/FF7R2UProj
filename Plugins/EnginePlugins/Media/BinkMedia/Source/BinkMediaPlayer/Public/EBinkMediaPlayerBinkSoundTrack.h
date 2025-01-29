#pragma once
#include "CoreMinimal.h"
#include "EBinkMediaPlayerBinkSoundTrack.generated.h"

UENUM(BlueprintType)
enum EBinkMediaPlayerBinkSoundTrack {
    BMASM_Bink_Sound_None,
    BMASM_Bink_Sound_Simple,
    BMASM_Bink_Sound_LanguageOverride,
    BMASM_Bink_Sound_51,
    BMASM_Bink_Sound_51LanguageOverride,
    BMASM_Bink_Sound_71,
    BMASM_Bink_Sound_71LanguageOverride,
};

