#pragma once
#include "CoreMinimal.h"
#include "EndSingleSidedSplineComponent.h"
#include "EndBuggyUnsafeAreaSplineComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndBuggyUnsafeAreaSplineComponent : public UEndSingleSidedSplineComponent {
    GENERATED_BODY()
public:
    UEndBuggyUnsafeAreaSplineComponent(const FObjectInitializer& ObjectInitializer);

};

