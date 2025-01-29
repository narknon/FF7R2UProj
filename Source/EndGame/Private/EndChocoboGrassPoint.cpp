#include "EndChocoboGrassPoint.h"
#include "Components/CapsuleComponent.h"

AEndChocoboGrassPoint::AEndChocoboGrassPoint(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
    this->ChocoboGrassID = 0;
    this->GrassActor = NULL;
    this->CollisionComponent->SetupAttachment(RootComponent);
}


