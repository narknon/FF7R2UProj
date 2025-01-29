#pragma once
#include "CoreMinimal.h"
#include "EndLightAnimationComponentBase.h"
#include "EndLightAnimationComponent.generated.h"

class UEndLightAnimationSettings;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndLightAnimationComponent : public UEndLightAnimationComponentBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndLightAnimationSettings* LightAnimationSettings;
    
    UEndLightAnimationComponent(const FObjectInitializer& ObjectInitializer);

};

