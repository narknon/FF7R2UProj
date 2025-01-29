#include "EndMergedSimpleCollisionActor.h"
#include "EndMergedSimpleCollisionComponent.h"

AEndMergedSimpleCollisionActor::AEndMergedSimpleCollisionActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bCanBeInCluster = true;
    this->RootComponent = CreateDefaultSubobject<UEndMergedSimpleCollisionComponent>(TEXT("MergedSimpleCollisionComponent"));
    this->MergedSimpleCollisionComponent = (UEndMergedSimpleCollisionComponent*)RootComponent;
}


