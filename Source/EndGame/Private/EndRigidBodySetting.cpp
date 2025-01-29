#include "EndRigidBodySetting.h"

UEndRigidBodySetting::UEndRigidBodySetting() {
    this->bEnableAdditiveDamage = false;
    this->AdditiveDamageBlendRateMax = 0.25f;
    this->AdditiveDamageDuration = 0.20f;
    this->AdditiveDamageBlendInTime = 0.20f;
    this->AdditiveDamageBlendOutTime = 0.40f;
    this->AdditiveDamageFirstForce = 10000.00f;
    this->AdditiveDamageAdditiveForce = 5000.00f;
    this->AdditiveDamageHipInfluenceBone = TEXT("C_Head_a");
    this->AdditiveDamageHipMoveRate = 0.00f;
    this->AdditiveDamageHipFallRate = 0.00f;
    this->bEnableRagdoll = false;
    this->RagdollBlendRateMax = 0.50f;
    this->RagdollBlendInTime = 0.00f;
    this->RagdollBlendOutTime = 0.10f;
    this->RagdollHipOrientBone = TEXT("C_Spine_a");
    this->RagdollHipOrientRate = 0.00f;
}


