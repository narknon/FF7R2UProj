#pragma once
#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "EndMobRouteSplineNonLoopArrowComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndMobRouteSplineNonLoopArrowComponent : public UArrowComponent {
    GENERATED_BODY()
public:
    UEndMobRouteSplineNonLoopArrowComponent(const FObjectInitializer& ObjectInitializer);

};

