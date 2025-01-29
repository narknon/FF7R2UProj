#include "EndSyncPoseSkeletalMeshActor.h"
#include "EndSyncPoseSkeletalMeshComponent.h"

AEndSyncPoseSkeletalMeshActor::AEndSyncPoseSkeletalMeshActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UEndSyncPoseSkeletalMeshComponent>(TEXT("SkeletalMeshComponent0"))) {
    const FProperty* p_SkeletalMeshComponent = GetClass()->FindPropertyByName("SkeletalMeshComponent");
    (*p_SkeletalMeshComponent->ContainerPtrToValuePtr<USkeletalMeshComponent*>(this)) = (USkeletalMeshComponent*)RootComponent;
}


