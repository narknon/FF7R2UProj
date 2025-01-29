#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndLightAnimationDefaultOnlyComponentSettings.h"
#include "EndLightAnimationPreset.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndLightAnimationPreset : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndLightAnimationDefaultOnlyComponentSettings ComponentSettings;
    
    UEndLightAnimationPreset();

};

