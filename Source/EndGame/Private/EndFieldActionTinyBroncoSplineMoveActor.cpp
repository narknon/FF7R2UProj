#include "EndFieldActionTinyBroncoSplineMoveActor.h"
#include "EndFieldActionSplineComponent.h"

AEndFieldActionTinyBroncoSplineMoveActor::AEndFieldActionTinyBroncoSplineMoveActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->SplineComponent = CreateDefaultSubobject<UEndFieldActionSplineComponent>(TEXT("CrackComponent"));
    this->bSetInitPos = true;
    this->InitSpeed = 0.00f;
    this->MaxSpeed = 60.00f;
    this->Acceleration = 30.00f;
    this->bOverrideSpeedInCutScene = false;
    this->MaxSpeedInCutScene = 30.00f;
    this->ConstantArrivalTime = 1.00f;
    this->SidewayMaxOffset = 1000.00f;
    this->RollMaxAngle = 10.00f;
    this->MaxSplineDeltaYawForMaxRoll = 5.00f;
    this->ForwardCheckTime = 2.00f;
    this->BackToNoOffsetSplinePositionTime = 3.00f;
    this->InvalidOffsetDistanceFromEnd = 10000.00f;
    this->SpeedWeightOnInvalidOffset = 0.50f;
    this->SplineComponent->SetupAttachment(RootComponent);
}


