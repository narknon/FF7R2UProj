#include "RigUnit_EndPBD_ChainParticle.h"

FRigUnit_EndPBD_ChainParticle::FRigUnit_EndPBD_ChainParticle() {
    this->bDetectCollision = false;
    this->Mass = 0.00f;
    this->Radius = 0.00f;
    this->GravityScale = 0.00f;
    this->bFixedRootItem = false;
    this->bFixedEndItem = false;
}

