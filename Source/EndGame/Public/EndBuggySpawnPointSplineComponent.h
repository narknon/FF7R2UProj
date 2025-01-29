#pragma once
#include "CoreMinimal.h"
#include "EndSingleSidedSplineComponent.h"
#include "EndBuggySpawnPointSplineComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndBuggySpawnPointSplineComponent : public UEndSingleSidedSplineComponent {
    GENERATED_BODY()
public:
    UEndBuggySpawnPointSplineComponent(const FObjectInitializer& ObjectInitializer);

};

