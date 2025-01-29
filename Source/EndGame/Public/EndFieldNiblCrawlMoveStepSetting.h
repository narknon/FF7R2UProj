#pragma once
#include "CoreMinimal.h"
#include "EndFieldNiblCrawlMoveSetting.h"
#include "EndFieldNiblCrawlMoveStepSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldNiblCrawlMoveStepSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndFieldNiblCrawlMoveSetting IdleSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndFieldNiblCrawlMoveSetting MoveSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndFieldNiblCrawlMoveSetting CancelSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName StepSuccessTrigger;
    
    ENDGAME_API FEndFieldNiblCrawlMoveStepSetting();
};

