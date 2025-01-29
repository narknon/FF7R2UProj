#pragma once
#include "CoreMinimal.h"
#include "EEndAIRecognitionVolumeType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_IsExistActiveRecognitionVolume.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_IsExistActiveRecognitionVolume : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIRecognitionVolumeType Type;
    
    UEndBTDecorator_IsExistActiveRecognitionVolume();

};

