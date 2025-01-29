#include "EndWeaponSkeletalMeshActor.h"

AEndWeaponSkeletalMeshActor::AEndWeaponSkeletalMeshActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bEndAnimationLooping = true;
    this->MateriaMaterialIndex = -1;
}


