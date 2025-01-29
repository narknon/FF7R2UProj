#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndMovementSettingsBodyCollision.h"
#include "EndMovementSettingsGravity.h"
#include "EndMovementSettings.generated.h"

UCLASS(Blueprintable, DefaultConfig, Config=Game)
class ENDGAME_API UEndMovementSettings : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndMovementSettingsGravity Gravity;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndMovementSettingsBodyCollision BodyCollisionSetting;
    
    UEndMovementSettings();

};

