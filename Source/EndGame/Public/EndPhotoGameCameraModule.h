#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndPhotoGameCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndPhotoGameCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndPhotoGameCameraModule();
};

