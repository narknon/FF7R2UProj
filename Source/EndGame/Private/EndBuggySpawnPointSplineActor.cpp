#include "EndBuggySpawnPointSplineActor.h"
#include "EndBuggySpawnPointSplineComponent.h"

AEndBuggySpawnPointSplineActor::AEndBuggySpawnPointSplineActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UEndBuggySpawnPointSplineComponent>(TEXT("EndBuggySpawnPointSplineComponent"));
    this->SplineComponent = (UEndBuggySpawnPointSplineComponent*)RootComponent;
}


