#include "EndDynamicBodyCollisionPrimitive.h"

UEndDynamicBodyCollisionPrimitive::UEndDynamicBodyCollisionPrimitive(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bIgnoreBumpNotify = true;
    this->bIgnoreAttackTarget = true;
    this->bEnablePhysicsBlock = false;
    this->CameraResponse = ECR_Ignore;
    this->PushSpeed = -1.00f;
}


