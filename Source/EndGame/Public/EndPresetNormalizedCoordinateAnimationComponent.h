#pragma once
#include "CoreMinimal.h"
#include "EndCoordinateAnimationComponentBase.h"
#include "EndPresetNormalizedCoordinateAnimationComponent.generated.h"

class UEndNormalizedCoordinateAnimationPreset;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndPresetNormalizedCoordinateAnimationComponent : public UEndCoordinateAnimationComponentBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndNormalizedCoordinateAnimationPreset* NormalizedCoordinateAnimationPreset;
    
    UEndPresetNormalizedCoordinateAnimationComponent(const FObjectInitializer& ObjectInitializer);

};

