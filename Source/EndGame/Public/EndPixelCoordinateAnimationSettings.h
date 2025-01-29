#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndPixelCoordinateAnimationMaterial.h"
#include "EndPixelCoordinateAnimationSettings.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndPixelCoordinateAnimationSettings : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndPixelCoordinateAnimationMaterial> MaterialSettings;
    
    UEndPixelCoordinateAnimationSettings();

};

