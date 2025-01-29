#include "EndTurnBackBox.h"

AEndTurnBackBox::AEndTurnBackBox(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->m_pTurnBackTriggerBox = NULL;
    this->m_pFollowDiscardTriggerBox = NULL;
    this->m_pBlockWall = NULL;
    this->EnableBlockWall = true;
    this->bOverwriteResetPitch = false;
    this->OverwriteResetPitch = -20.00f;
}


