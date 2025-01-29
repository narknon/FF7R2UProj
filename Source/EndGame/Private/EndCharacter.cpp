#include "EndCharacter.h"

AEndCharacter::AEndCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bCanFieldAttack = false;
    this->bCreatePhysicsBlockPrimitive = true;
    this->bOverrideBodyDriverTuningSets = true;
    this->BodyDriverBaseData = NULL;
    this->BodyDriverBipedFall = NULL;
    this->BodyDriverBalanceRecovery = NULL;
    this->BodyDriverStaggerfall = NULL;
    this->BodyDriverShakeData = NULL;
    this->BodyDriverKnockbackBalance = NULL;
    this->BodyDriverBipedIK = NULL;
    this->BodyDriverDebugImpulses = NULL;
    this->BodyDriverIdleAnim = NULL;
    this->BodyDriverArchtypeData = NULL;
    this->BodyDriverArchtypeSkeletalMesh = NULL;
    this->BodyDriverArchtypeBaseData = NULL;
    this->BodyDriverArchtypeBipedFall = NULL;
    this->BodyDriverArchtypeBalanceRecovery = NULL;
    this->BodyDriverArchtypeStaggerfall = NULL;
    this->BodyDriverArchtypeShakeData = NULL;
    this->BodyDriverArchtypeDebugImpulses = NULL;
    this->BodyDriverArchtypeIdleAnim = NULL;
    this->BattleTalkCharacterComponent = NULL;
}


