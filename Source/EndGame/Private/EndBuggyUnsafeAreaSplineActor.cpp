#include "EndBuggyUnsafeAreaSplineActor.h"
#include "EndBuggyUnsafeAreaSplineComponent.h"

AEndBuggyUnsafeAreaSplineActor::AEndBuggyUnsafeAreaSplineActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UEndBuggyUnsafeAreaSplineComponent>(TEXT("EndBuggyUnsafeAreaSplineComponent"));
    this->SplineComponent = (UEndBuggyUnsafeAreaSplineComponent*)RootComponent;
    this->bHideBuggyAfterGetOff = false;
    this->bEnableHeightLimit = true;
}


