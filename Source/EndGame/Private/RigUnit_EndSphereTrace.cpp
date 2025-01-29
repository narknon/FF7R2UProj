#include "RigUnit_EndSphereTrace.h"

FRigUnit_EndSphereTrace::FRigUnit_EndSphereTrace() {
    this->Radius = 0.00f;
    this->bUseSimpleCollision = false;
    this->bAsyncTrace = false;
    this->bDebugDraw = false;
    this->bHit = false;
}

