#pragma once
#include "CoreMinimal.h"
#include "EndCollisionDefaultSettings.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndCollisionDefaultSettings {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float EnvironmentMeshDefaultNearFadeDistance;
    
    FEndCollisionDefaultSettings();
};

