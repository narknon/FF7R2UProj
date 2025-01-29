#pragma once
#include "CoreMinimal.h"
#include "EndFieldNiblCrawlMoveSetting.h"
#include "EndFieldNiblCrawlStandupSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldNiblCrawlStandupSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndFieldNiblCrawlMoveSetting> AnimationUnits;
    
    ENDGAME_API FEndFieldNiblCrawlStandupSetting();
};

