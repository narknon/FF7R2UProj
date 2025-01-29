#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndLightAnimationComponentSettings.h"
#include "EndLightAnimationSettings.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndLightAnimationSettings : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndLightAnimationComponentSettings> ComponentSettings;
    
    UEndLightAnimationSettings();

};

