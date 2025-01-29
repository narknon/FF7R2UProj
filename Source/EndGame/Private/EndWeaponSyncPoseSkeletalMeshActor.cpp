#include "EndWeaponSyncPoseSkeletalMeshActor.h"
#include "EndWeaponSyncPoseSkeletalMeshComponent.h"

AEndWeaponSyncPoseSkeletalMeshActor::AEndWeaponSyncPoseSkeletalMeshActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UEndWeaponSyncPoseSkeletalMeshComponent>(TEXT("SkeletalMeshComponent0"))) {
    const FProperty* p_SkeletalMeshComponent = GetClass()->FindPropertyByName("SkeletalMeshComponent");
    (*p_SkeletalMeshComponent->ContainerPtrToValuePtr<USkeletalMeshComponent*>(this)) = (USkeletalMeshComponent*)RootComponent;
}


