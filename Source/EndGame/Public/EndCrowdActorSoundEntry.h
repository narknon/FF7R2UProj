#pragma once
#include "CoreMinimal.h"
#include "EndCrowdActorSoundEntry.generated.h"

class USoundBase;

USTRUCT(BlueprintType)
struct FEndCrowdActorSoundEntry {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundBase* Sound;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SoundName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FadeOutTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bFollow;
    
    ENDGAME_API FEndCrowdActorSoundEntry();
};

