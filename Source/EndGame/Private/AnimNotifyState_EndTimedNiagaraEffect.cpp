#include "AnimNotifyState_EndTimedNiagaraEffect.h"

UAnimNotifyState_EndTimedNiagaraEffect::UAnimNotifyState_EndTimedNiagaraEffect() {
    this->m_bDestroyAtEnd = false;
    this->m_bIgnoreWhenFinished = false;
    this->m_bDetachWhenFinished = false;
    this->m_bDisableVibrationVolumeSE = false;
    this->m_bBranchConditionInverse = false;
    this->m_bUseWildcardExpression = false;
    this->m_bEnableSynchroParentActor = true;
    this->m_bEnableSynchroParentActorVisible = false;
    this->m_bSkipCreateParentActorDrawPause = false;
    this->m_bDestroyAtEndIfBoundToCutScene = false;
    this->m_bEnableCreateEffectDelay = false;
    this->m_BranchConditionType = EEndAnimNotifyBranchConditionType::None;
    this->m_AttachType = EEndAnimNotifyAttachType::None;
}


