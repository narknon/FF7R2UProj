#pragma once
#include "CoreMinimal.h"
#include "EndMovementSettingsBodyCollision.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndMovementSettingsBodyCollision {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableBodySubCollision;
    
    FEndMovementSettingsBodyCollision();
};

