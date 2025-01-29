#pragma once
#include "CoreMinimal.h"
#include "EndCoordinateAnimationComponentBase.h"
#include "EndPixelCoordinateAnimationDefaultOnlyMaterialSettings.h"
#include "EndManualPixelCoordinateAnimationComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndManualPixelCoordinateAnimationComponent : public UEndCoordinateAnimationComponentBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndPixelCoordinateAnimationDefaultOnlyMaterialSettings MaterialSettings;
    
    UEndManualPixelCoordinateAnimationComponent(const FObjectInitializer& ObjectInitializer);

};

