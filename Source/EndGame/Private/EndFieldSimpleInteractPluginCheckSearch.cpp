#include "EndFieldSimpleInteractPluginCheckSearch.h"

UEndFieldSimpleInteractPluginCheckSearch::UEndFieldSimpleInteractPluginCheckSearch() {
    this->MoveTargetType = ESimpleInteractTarget::ESITarget_World;
    this->CheckInDistance = -1.00f;
    this->CheckInPlaneDistance = -1.00f;
    this->CheckSelfForwardToTargetDegrees = -1.00f;
    this->CheckSelfForwardToTargetForwardDegrees = -1.00f;
    this->CheckTargetForwardToSelfDegrees = -1.00f;
    this->bDisalbePlayedAnimationNameMatching = false;
}


