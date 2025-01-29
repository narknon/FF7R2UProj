#pragma once
#include "CoreMinimal.h"
#include "EndSplineActorBase.h"
#include "EndFieldSplineActor.generated.h"

UCLASS(Blueprintable)
class AEndFieldSplineActor : public AEndSplineActorBase {
    GENERATED_BODY()
public:
    AEndFieldSplineActor(const FObjectInitializer& ObjectInitializer);

};

