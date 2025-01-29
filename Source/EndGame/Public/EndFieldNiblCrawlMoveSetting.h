#pragma once
#include "CoreMinimal.h"
#include "EndFieldNiblCrawlMoveAnimUnit.h"
#include "EndFieldNiblCrawlMoveSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldNiblCrawlMoveSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndFieldNiblCrawlMoveAnimUnit> AnimationUnits;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLastAnimIsLoop;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLastAnimIsKeep;
    
    ENDGAME_API FEndFieldNiblCrawlMoveSetting();
};

