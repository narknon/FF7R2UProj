#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndNormalizedCoordinateAnimationMaterial.h"
#include "EndNormalizedCoordinateAnimationSettings.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndNormalizedCoordinateAnimationSettings : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndNormalizedCoordinateAnimationMaterial> MaterialSettings;
    
    UEndNormalizedCoordinateAnimationSettings();

};

