#include "EndWheeledVehicle.h"
#include "EndWheeledVehicleMovementComponent.h"
#include "EndWheeledVehiclePlayerController.h"
#include "EndWheeledVehicleSkeletalMeshComponent.h"

AEndWheeledVehicle::AEndWheeledVehicle(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UEndWheeledVehicleSkeletalMeshComponent>(TEXT("SkeletalMeshComponent0"))) {
    const FProperty* p_SkeletalMeshComponent = GetClass()->FindPropertyByName("SkeletalMeshComponent");
    (*p_SkeletalMeshComponent->ContainerPtrToValuePtr<USkeletalMeshComponent*>(this)) = (USkeletalMeshComponent*)RootComponent;
    this->VehicleMovement = CreateDefaultSubobject<UEndWheeledVehicleMovementComponent>(TEXT("MovementComp"));
    this->PlayerControllerClass = AEndWheeledVehiclePlayerController::StaticClass();
    this->ActionParams = NULL;
    this->InteriorPhysicalMaterial = NULL;
    this->VehicleController = NULL;
}

void AEndWheeledVehicle::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
}


