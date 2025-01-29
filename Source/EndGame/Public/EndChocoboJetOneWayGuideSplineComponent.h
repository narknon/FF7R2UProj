#pragma once
#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "EndChocoboJetOneWayGuideSplineComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndChocoboJetOneWayGuideSplineComponent : public USplineComponent {
    GENERATED_BODY()
public:
    UEndChocoboJetOneWayGuideSplineComponent(const FObjectInitializer& ObjectInitializer);

};

