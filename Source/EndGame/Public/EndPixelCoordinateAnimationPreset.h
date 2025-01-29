#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndPixelCoordinateAnimationDefaultOnlyMaterialSettings.h"
#include "EndPixelCoordinateAnimationPreset.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndPixelCoordinateAnimationPreset : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndPixelCoordinateAnimationDefaultOnlyMaterialSettings MaterialSettings;
    
    UEndPixelCoordinateAnimationPreset();

};

