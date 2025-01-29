#include "EndFieldActionGatherableLifeActor.h"

AEndFieldActionGatherableLifeActor::AEndFieldActionGatherableLifeActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->m_ReturnVFXAsset = NULL;
    this->m_ReturnDistance = -1.00f;
    this->m_ReturnVelocity = -1.00f;
}


