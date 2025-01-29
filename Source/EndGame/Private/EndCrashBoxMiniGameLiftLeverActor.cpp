#include "EndCrashBoxMiniGameLiftLeverActor.h"

AEndCrashBoxMiniGameLiftLeverActor::AEndCrashBoxMiniGameLiftLeverActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bCanBeInCluster = false;
    this->m_GroupIndex = 0;
    this->m_StaticMeshComponent = NULL;
}

void AEndCrashBoxMiniGameLiftLeverActor::SetLiftRootActor(AEndCrashBoxMiniGameLiftRootActor* LiftRootActor) {
}


