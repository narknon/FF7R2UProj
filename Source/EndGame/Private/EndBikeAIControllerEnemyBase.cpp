#include "EndBikeAIControllerEnemyBase.h"

AEndBikeAIControllerEnemyBase::AEndBikeAIControllerEnemyBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->StopToRemoveTime = 3.00f;
    this->FadeOutDuration = 0.00f;
    this->bDiedHitBackground = false;
    this->bNotMoveAlongSplineAfterDeath = false;
    this->bCanAttackSameLine = true;
    this->bAttackPlayerLine = false;
    this->bWithdrawalOneByOne = false;
    this->LineEffectDuration = 3.00f;
    this->LineEffectFadeInLength = 1.00f;
    this->LineEffectFadeOutLength = 1.00f;
    this->LineEffectArcHeight = 1000.00f;
    this->LockOnMarker_InitDistance = 0.00f;
    this->LockOnMarker_InitKeepTime = 0.75f;
    this->LockOnMarker_InterpSpeed = 1.00f;
    this->LockOnMarker_FixedTime = 6.00f;
}


