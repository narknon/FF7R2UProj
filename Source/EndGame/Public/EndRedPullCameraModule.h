#pragma once
#include "CoreMinimal.h"
#include "EndNiblCrawlCameraModule.h"
#include "EndRedPullCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndRedPullCameraModule : public FEndNiblCrawlCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndRedPullCameraModule();
};

