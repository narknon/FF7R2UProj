#include "EndCardGame3DCardHand.h"

AEndCardGame3DCardHand::AEndCardGame3DCardHand(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->CardIndex = 0;
    this->MPC_CardHandFront = 0;
    this->MPC_CardHandBack = 0;
    this->ScreenAngle = 0.00f;
    this->ScreenScale = 1.00f;
    this->ScreenDistance = 1000.00f;
    this->ScreenDistanceOffset = 0.00f;
    this->bChooseableVisible = false;
    this->bCursorVisible = false;
}


