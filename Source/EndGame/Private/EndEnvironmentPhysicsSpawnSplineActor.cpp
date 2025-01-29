#include "EndEnvironmentPhysicsSpawnSplineActor.h"
#include "EndEnvironmentPhysicsSpawnSplineComponent.h"

AEndEnvironmentPhysicsSpawnSplineActor::AEndEnvironmentPhysicsSpawnSplineActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UEndEnvironmentPhysicsSpawnSplineComponent>(TEXT("EndEnvironmentPhysicsSpawnSplineComponent"));
    this->ConditionType = EEndEnvironmentPhysicsSpawnSplineConditionType::Default;
    this->AutoDestroyTime = 5.00f;
    this->bHighPriorityWaterBuoyancyCheck = false;
    this->RotationRandomRange = 0.00f;
    this->MaxLimitDistance = 60000.00f;
    this->SplineComponent = (UEndEnvironmentPhysicsSpawnSplineComponent*)RootComponent;
}


