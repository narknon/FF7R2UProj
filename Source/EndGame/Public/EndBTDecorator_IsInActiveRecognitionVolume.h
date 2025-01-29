#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EEndAIRecognitionVolumeType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_IsInActiveRecognitionVolume.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_IsInActiveRecognitionVolume : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIRecognitionVolumeType Type;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector BlackboardKey;
    
    UEndBTDecorator_IsInActiveRecognitionVolume();

};

