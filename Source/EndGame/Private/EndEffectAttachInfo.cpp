#include "EndEffectAttachInfo.h"

FEndEffectAttachInfo::FEndEffectAttachInfo() {
    this->m_LocationRule = EAttachmentRule::KeepRelative;
    this->m_RotationRule = EAttachmentRule::KeepRelative;
    this->m_ScaleRule = EAttachmentRule::KeepRelative;
    this->m_bInWeldSimulatedBodies = false;
}

