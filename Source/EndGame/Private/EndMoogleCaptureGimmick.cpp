#include "EndMoogleCaptureGimmick.h"

AEndMoogleCaptureGimmick::AEndMoogleCaptureGimmick(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->m_EffectTarget = EMoogleGimmickTargetType::All;
    this->m_RemoveTarget = EMoogleGimmickTargetType::None;
    this->m_EffectRadius = 100.00f;
    this->m_BreakRadius = 100.00f;
    this->m_Interval = 3.00f;
    this->m_RecoverSec = -1.00f;
    this->m_ValidSec = -1.00f;
    this->m_StartingSec = -1.00f;
    this->m_FinishingSec = -1.00f;
    this->m_EffectVFX = NULL;
    this->m_StandardLoopVFX = NULL;
    this->m_bAttract = false;
    this->m_bDisableStart = false;
    this->m_bBreakOnEffect = false;
    this->m_bNotifyPlayer = false;
    this->m_bEnableNotifyCtrl = false;
    this->m_bFixedGoal = false;
    this->m_bUseBonamikWind = true;
}

void AEndMoogleCaptureGimmick::SetRestartBlock(bool bBlock) {
}


