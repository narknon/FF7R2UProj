#pragma once
#include "CoreMinimal.h"
#include "EndCoordinateAnimationComponentBase.h"
#include "EndNormalizedCoordinateAnimationDefaultOnlyMaterialSettings.h"
#include "EndManualNormalizedCoordinateAnimationComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndManualNormalizedCoordinateAnimationComponent : public UEndCoordinateAnimationComponentBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndNormalizedCoordinateAnimationDefaultOnlyMaterialSettings MaterialSettings;
    
    UEndManualNormalizedCoordinateAnimationComponent(const FObjectInitializer& ObjectInitializer);

};

