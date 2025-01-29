#include "EndCableCartSkeletalMeshActor.h"
#include "Components/CapsuleComponent.h"
#include "EndFieldMovementComponent.h"

AEndCableCartSkeletalMeshActor::AEndCableCartSkeletalMeshActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCapsuleComponent>(TEXT("MovementCapsuleComponent"))) {
    this->bUseIcon2 = false;
    this->bCharaSpaceCheckIsDriverSameCollision = false;
    this->MovementComponent = CreateDefaultSubobject<UEndFieldMovementComponent>(TEXT("MovementComponent"));
    this->MovementCapsuleComponent = (UCapsuleComponent*)RootComponent;
    this->CartMoveSpeedMax = 300.00f;
    this->DashCartMoveSpeedRate = 1.50f;
    this->CartMoveSpeedInterpTime = 3.00f;
    this->CartRotSpeedMax = 600.00f;
    this->DashCartRotSpeedRate = 1.50f;
    this->CartRotSpeedInterpTime = 1.00f;
    this->bCanOnlyCartAction = false;
    this->CartSoundBank = NULL;
    this->ZeroOne_HasDriverValue = 0.10f;
    this->ZeroOne_FadeTime = 0.20f;
}


