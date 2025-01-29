#pragma once
#include "CoreMinimal.h"
#include "EndSkeletalMeshActorAnimInstance.h"
#include "EndWeaponAnimInstance.generated.h"

UCLASS(Blueprintable, NonTransient)
class UEndWeaponAnimInstance : public UEndSkeletalMeshActorAnimInstance {
    GENERATED_BODY()
public:
    UEndWeaponAnimInstance();

};

