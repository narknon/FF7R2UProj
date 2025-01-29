#include "SQEX_AnimNotifyState_Bonamik_TemporaryCollision.h"

USQEX_AnimNotifyState_Bonamik_TemporaryCollision::USQEX_AnimNotifyState_Bonamik_TemporaryCollision() {
    this->ShapeType = ESQEX_AnimNotifyState_Bonamik_TemporaryCollision_CollisionType::Box;
    this->Radius = 50.00f;
    this->CapsuleHalfHeight = 100.00f;
    this->bAttachToSocket = false;
    this->bDebugVisibility = false;
    this->DebugLineThickness = 0.50f;
}


