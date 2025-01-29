#include "EndSelectTargetPoint.h"

AEndSelectTargetPoint::AEndSelectTargetPoint(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->m_DecideSecond = 1.00f;
    this->m_SyncAnimDuration = 10.00f;
    this->m_bWaitDeform = true;
    this->m_bOverrideSlavePoint = false;
    this->m_keepDecideCount = 0;
    this->m_bContinueNext = false;
    this->m_bIgnoreFinishMotion = false;
    this->bInitizliedDeforms = false;
}


