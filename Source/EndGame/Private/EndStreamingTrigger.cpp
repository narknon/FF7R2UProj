#include "EndStreamingTrigger.h"

AEndStreamingTrigger::AEndStreamingTrigger(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->CollisionType = EEndStreamLevelCollisionType::Invalid;
    this->CollisionComponent = NULL;
}


