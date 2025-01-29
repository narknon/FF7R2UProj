#include "EndBTDecorator_SensingCharacter.h"

UEndBTDecorator_SensingCharacter::UEndBTDecorator_SensingCharacter() {
    this->m_SensingCharacterType = EEndAISensingCharacterType::Party;
    this->m_bUseSourceToTarget = false;
    this->m_Distance = 100.00f;
    this->m_ArithmeticOperation_Distance = EEndAiMathCmp::LessEqual;
    this->m_bUseBodyRadius = true;
    this->m_Angle = 180.00f;
    this->m_ArithmeticOperation_Angle = EEndAiMathCmp::LessEqual;
    this->m_bAbs_Angle = true;
    this->m_bCheckHeight = false;
    this->m_Height = 200.00f;
    this->m_bIgnorePartyLeader = true;
    this->m_bPartyLeaderOnly = false;
    this->m_bIgnoreFollowLeader = true;
    this->m_bFollowLeaderOnly = false;
    this->m_bIgnoreFieldActionWaitMoving = false;
}


