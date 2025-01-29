#include "EndAnimNotifyStateAttachCollision.h"

UEndAnimNotifyStateAttachCollision::UEndAnimNotifyStateAttachCollision() {
    this->ShapeType = EEndCollision::SPHERE;
    this->CollisionType = EEndAnimNotifyAttachCollisionType::DamageHit;
    this->bAttachToParent = false;
    this->LocationRule = EAttachmentRule::KeepRelative;
    this->RotationRule = EAttachmentRule::KeepRelative;
    this->ScaleRule = EAttachmentRule::KeepRelative;
    this->TMRule = EEndAnimNotifyAttachCollisionTMRule::ComponentTM;
    this->bDisableOtherPushCollision = false;
}


