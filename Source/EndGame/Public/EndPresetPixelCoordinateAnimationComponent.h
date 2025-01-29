#pragma once
#include "CoreMinimal.h"
#include "EndCoordinateAnimationComponentBase.h"
#include "EndPresetPixelCoordinateAnimationComponent.generated.h"

class UEndPixelCoordinateAnimationPreset;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndPresetPixelCoordinateAnimationComponent : public UEndCoordinateAnimationComponentBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndPixelCoordinateAnimationPreset* PixelCoordinateAnimationPreset;
    
    UEndPresetPixelCoordinateAnimationComponent(const FObjectInitializer& ObjectInitializer);

};

