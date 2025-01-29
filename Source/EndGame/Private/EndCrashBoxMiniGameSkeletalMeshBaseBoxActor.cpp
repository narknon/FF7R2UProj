#include "EndCrashBoxMiniGameSkeletalMeshBaseBoxActor.h"
#include "Components/PoseableMeshComponent.h"
#include "Net/UnrealNetwork.h"

AEndCrashBoxMiniGameSkeletalMeshBaseBoxActor::AEndCrashBoxMiniGameSkeletalMeshBaseBoxActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("PoseableMeshComponent0"));
    this->bShouldDoAnimNotifies = true;
    this->bWakeOnLevelStart = false;
    this->PoseableMeshComponent = (UPoseableMeshComponent*)RootComponent;
    this->ReplicatedMesh = NULL;
    this->ReplicatedPhysAsset = NULL;
    this->ReplicatedMaterial0 = NULL;
    this->ReplicatedMaterial1 = NULL;
}

void AEndCrashBoxMiniGameSkeletalMeshBaseBoxActor::OnRep_ReplicatedPhysAsset() {
}

void AEndCrashBoxMiniGameSkeletalMeshBaseBoxActor::OnRep_ReplicatedMesh() {
}

void AEndCrashBoxMiniGameSkeletalMeshBaseBoxActor::OnRep_ReplicatedMaterial1() {
}

void AEndCrashBoxMiniGameSkeletalMeshBaseBoxActor::OnRep_ReplicatedMaterial0() {
}

void AEndCrashBoxMiniGameSkeletalMeshBaseBoxActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(AEndCrashBoxMiniGameSkeletalMeshBaseBoxActor, ReplicatedMesh);
    DOREPLIFETIME(AEndCrashBoxMiniGameSkeletalMeshBaseBoxActor, ReplicatedPhysAsset);
    DOREPLIFETIME(AEndCrashBoxMiniGameSkeletalMeshBaseBoxActor, ReplicatedMaterial0);
    DOREPLIFETIME(AEndCrashBoxMiniGameSkeletalMeshBaseBoxActor, ReplicatedMaterial1);
}


