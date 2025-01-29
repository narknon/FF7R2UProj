#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndNiblCrawlCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndNiblCrawlCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndNiblCrawlCameraModule();
};

