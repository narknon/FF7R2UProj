#include "EndCatchableRopeSkeletalMeshActor.h"

AEndCatchableRopeSkeletalMeshActor::AEndCatchableRopeSkeletalMeshActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RopeLength = 300.00f;
    this->PullActorPtr = NULL;
}


