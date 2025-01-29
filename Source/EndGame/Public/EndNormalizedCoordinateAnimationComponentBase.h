#pragma once
#include "CoreMinimal.h"
#include "EndCoordinateAnimationComponentBase.h"
#include "EndNormalizedCoordinateAnimationComponentBase.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndNormalizedCoordinateAnimationComponentBase : public UEndCoordinateAnimationComponentBase {
    GENERATED_BODY()
public:
    UEndNormalizedCoordinateAnimationComponentBase(const FObjectInitializer& ObjectInitializer);

};

