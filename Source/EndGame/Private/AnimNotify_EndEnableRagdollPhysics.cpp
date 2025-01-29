#include "AnimNotify_EndEnableRagdollPhysics.h"

UAnimNotify_EndEnableRagdollPhysics::UAnimNotify_EndEnableRagdollPhysics() {
    this->bAddImpulse = false;
    this->Type = EEndPhysicsImpulseType::Default;
    this->bApplyKillAttackDirection = false;
    this->bApplyImpulseToAllBones = false;
    this->bAddToCurrentVelocity = true;
    this->Radius = 0.00f;
    this->Strength = 0.00f;
    this->Falloff = RIF_Constant;
    this->bHitPawn = false;
}


