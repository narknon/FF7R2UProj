#pragma once
#include "CoreMinimal.h"
#include "EndCoordinateAnimationComponentBase.h"
#include "EndCoordinateAnimationComponent.generated.h"

class UEndNormalizedCoordinateAnimationSettings;
class UEndPixelCoordinateAnimationSettings;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndCoordinateAnimationComponent : public UEndCoordinateAnimationComponentBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndNormalizedCoordinateAnimationSettings* NormalizedCoordinateAnimationSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndPixelCoordinateAnimationSettings* PixelCoordinateAnimationSettings;
    
    UEndCoordinateAnimationComponent(const FObjectInitializer& ObjectInitializer);

};

