#pragma once
#include "CoreMinimal.h"
#include "EndSingleSidedSplineComponent.h"
#include "EndTinyBroncoDolphinAreaSplineComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndTinyBroncoDolphinAreaSplineComponent : public UEndSingleSidedSplineComponent {
    GENERATED_BODY()
public:
    UEndTinyBroncoDolphinAreaSplineComponent(const FObjectInitializer& ObjectInitializer);

};

