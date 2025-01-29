#pragma once
#include "CoreMinimal.h"
#include "ChocoboCraftQuestWave.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FChocoboCraftQuestWave {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SineTimer;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SineAmplitude;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SineFrequency;
    
    FChocoboCraftQuestWave();
};

