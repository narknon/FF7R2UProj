#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EndAIIntentionInterestActionControl.h"
#include "EndAIIntentionManualControl.h"
#include "EndAIModelTemplateData.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndAIModelTemplateData : public UDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAIIntentionManualControl ManualControl;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAIIntentionInterestActionControl InterestActionControl;
    
    UEndAIModelTemplateData();

};

