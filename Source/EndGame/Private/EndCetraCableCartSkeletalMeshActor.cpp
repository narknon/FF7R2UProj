#include "EndCetraCableCartSkeletalMeshActor.h"

AEndCetraCableCartSkeletalMeshActor::AEndCetraCableCartSkeletalMeshActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->m_SphereRound = 175.00f;
    this->PlayerReleseAnim = NULL;
    this->m_InterpDurationRate = 0.80f;
}


