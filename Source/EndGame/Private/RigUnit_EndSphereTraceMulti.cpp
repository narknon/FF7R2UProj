#include "RigUnit_EndSphereTraceMulti.h"

FRigUnit_EndSphereTraceMulti::FRigUnit_EndSphereTraceMulti() {
    this->Radius = 0.00f;
    this->bUseSimpleCollision = false;
    this->bAsyncTrace = false;
    this->bDebugDraw = false;
    this->bHit = false;
}

