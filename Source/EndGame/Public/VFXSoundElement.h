#pragma once
#include "CoreMinimal.h"
#include "EndSoundHandle.h"
#include "VFXSoundElement.generated.h"

USTRUCT(BlueprintType)
struct FVFXSoundElement {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    FEndSoundHandle m_SoundHandles[3];
    
    ENDGAME_API FVFXSoundElement();
};

