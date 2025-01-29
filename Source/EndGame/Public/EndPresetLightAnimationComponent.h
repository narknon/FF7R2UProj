#pragma once
#include "CoreMinimal.h"
#include "EndLightAnimationComponentBase.h"
#include "EndPresetLightAnimationComponent.generated.h"

class UEndLightAnimationPreset;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndPresetLightAnimationComponent : public UEndLightAnimationComponentBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndLightAnimationPreset* LightAnimationPreset;
    
    UEndPresetLightAnimationComponent(const FObjectInitializer& ObjectInitializer);

};

