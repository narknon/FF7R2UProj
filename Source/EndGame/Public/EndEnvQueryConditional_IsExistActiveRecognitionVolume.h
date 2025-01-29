#pragma once
#include "CoreMinimal.h"
#include "EnvQueryConditional.h"
#include "EEndAIRecognitionVolumeType.h"
#include "EndEnvQueryConditional_IsExistActiveRecognitionVolume.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryConditional_IsExistActiveRecognitionVolume : public UEnvQueryConditional {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIRecognitionVolumeType Type;
    
    UEndEnvQueryConditional_IsExistActiveRecognitionVolume();

};

