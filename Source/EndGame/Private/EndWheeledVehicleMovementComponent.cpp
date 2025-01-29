#include "EndWheeledVehicleMovementComponent.h"

UEndWheeledVehicleMovementComponent::UEndWheeledVehicleMovementComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bComponentShouldUpdatePhysicsVolume = false;
    this->WheelSetups.AddDefaulted(8);
    this->bOverrideCOM = false;
    this->ForwardMaxSpeedKph = 100.00f;
    this->BackwardMaxSpeedKph = 40.00f;
    this->MaxAngulerVelocity = 1000.00f;
    this->MaxDepenetrationVelocity = 500.00f;
    this->MaxWheelRotationSpeed = 3000.00f;
}

void UEndWheeledVehicleMovementComponent::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
}


