#pragma once
#include "CoreMinimal.h"
#include "EndMovementSettingsGravity.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndMovementSettingsGravity {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AutoFitUpVectorRotationSpeed;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AutoFitUpVectorWalkableFloorAngle;
    
    FEndMovementSettingsGravity();
};

