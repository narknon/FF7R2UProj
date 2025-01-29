#pragma once
#include "CoreMinimal.h"
#include "EndLightAnimationComponentBase.h"
#include "EndLightAnimationDefaultOnlyComponentSettings.h"
#include "EndManualLightAnimationComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndManualLightAnimationComponent : public UEndLightAnimationComponentBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndLightAnimationDefaultOnlyComponentSettings ComponentSettings;
    
    UEndManualLightAnimationComponent(const FObjectInitializer& ObjectInitializer);

};

