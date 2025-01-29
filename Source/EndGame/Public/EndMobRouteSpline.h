#pragma once
#include "CoreMinimal.h"
#include "EndSplineActorBase.h"
#include "EndMobRouteSpline.generated.h"

UCLASS(Blueprintable)
class AEndMobRouteSpline : public AEndSplineActorBase {
    GENERATED_BODY()
public:
    AEndMobRouteSpline(const FObjectInitializer& ObjectInitializer);

};

