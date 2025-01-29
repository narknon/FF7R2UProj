#include "EndStreamingTriggerBox.h"
#include "Components/BoxComponent.h"
#include "EEndStreamLevelCollisionType.h"

AEndStreamingTriggerBox::AEndStreamingTriggerBox(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
    this->CollisionType = EEndStreamLevelCollisionType::Box;
    const FProperty* p_CollisionComponent = GetClass()->FindPropertyByName("CollisionComponent");
    (*p_CollisionComponent->ContainerPtrToValuePtr<UShapeComponent*>(this)) = (UShapeComponent*)RootComponent;
}


