#include "EndStreamingTriggerCapsule.h"
#include "Components/CapsuleComponent.h"
#include "EEndStreamLevelCollisionType.h"

AEndStreamingTriggerCapsule::AEndStreamingTriggerCapsule(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComp"));
    this->CollisionType = EEndStreamLevelCollisionType::Capsule;
    const FProperty* p_CollisionComponent = GetClass()->FindPropertyByName("CollisionComponent");
    (*p_CollisionComponent->ContainerPtrToValuePtr<UShapeComponent*>(this)) = (UShapeComponent*)RootComponent;
}


