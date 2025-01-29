#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndNormalizedCoordinateAnimationDefaultOnlyMaterialSettings.h"
#include "EndNormalizedCoordinateAnimationPreset.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndNormalizedCoordinateAnimationPreset : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndNormalizedCoordinateAnimationDefaultOnlyMaterialSettings MaterialSettings;
    
    UEndNormalizedCoordinateAnimationPreset();

};

