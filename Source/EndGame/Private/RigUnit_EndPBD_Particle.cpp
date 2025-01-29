#include "RigUnit_EndPBD_Particle.h"

FRigUnit_EndPBD_Particle::FRigUnit_EndPBD_Particle() {
    this->bFixed = false;
    this->bDetectCollision = false;
    this->Mass = 0.00f;
    this->Radius = 0.00f;
    this->GravityScale = 0.00f;
    this->bUseVelocity = false;
    this->bAutoSetDistanceConstraint = false;
    this->DistanceConstraintParentInvMass = 0.00f;
}

