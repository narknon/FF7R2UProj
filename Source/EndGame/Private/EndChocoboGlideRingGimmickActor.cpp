#include "EndChocoboGlideRingGimmickActor.h"

AEndChocoboGlideRingGimmickActor::AEndChocoboGlideRingGimmickActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RingPartsClass = NULL;
    this->bMoveAtRingCenter = false;
    this->RingActor = NULL;
    this->RingPartsActor = NULL;
}


