#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndRedChainDoorActionCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndRedChainDoorActionCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndRedChainDoorActionCameraModule();
};

