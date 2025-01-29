#include "EndAIFrogGuysPoint.h"

AEndAIFrogGuysPoint::AEndAIFrogGuysPoint(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->Type = EEndAIFrogGuysType::Disk;
    this->Range = 100.00f;
    this->BottomOffset = 0.00f;
}


