#include "EndAIMoveComponent.h"

UEndAIMoveComponent::UEndAIMoveComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bUseSteering = true;
    this->CanParkourMove = false;
    this->UseMoveOnlyNavMeshInAerial = false;
    this->bCanFixMove = true;
    this->MinMoveType = EEndAiMoveType::WALK;
    this->bImpossibleAutoIgnorePushActor = false;
    this->bInvalidAerialPathSearch = false;
    this->bForceInvalidAerialNavPushBack = false;
}


