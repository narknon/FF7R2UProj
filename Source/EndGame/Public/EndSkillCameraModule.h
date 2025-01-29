#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndSkillCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndSkillCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndSkillCameraModule();
};

