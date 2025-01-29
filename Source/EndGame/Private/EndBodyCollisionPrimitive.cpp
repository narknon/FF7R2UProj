#include "EndBodyCollisionPrimitive.h"

UEndBodyCollisionPrimitive::UEndBodyCollisionPrimitive(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bIgnoreDodgeRoll = false;
    this->bIgnoreBumpNotify = false;
    this->bIgnoreAttackTarget = false;
    this->bIgnoreCharaPush = false;
    this->bEnableAttackTargetBySweep = true;
    this->bEnablePhysicsBlock = true;
    this->CameraResponse = ECR_Overlap;
}


