#include "EndModularEnemyCharacter.h"
#include "EndSkeletalMeshComponent.h"
#include "EndSyncPoseSkeletalMeshComponent.h"

AEndModularEnemyCharacter::AEndModularEnemyCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->BodyMesh = CreateDefaultSubobject<UEndSyncPoseSkeletalMeshComponent>(TEXT("Body"));
    this->BodyMesh->SetupAttachment(GetMesh());
}


