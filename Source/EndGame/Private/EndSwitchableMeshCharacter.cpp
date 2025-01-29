#include "EndSwitchableMeshCharacter.h"
#include "EndSwitchableBodySkeletalMeshComponent.h"

AEndSwitchableMeshCharacter::AEndSwitchableMeshCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UEndSwitchableBodySkeletalMeshComponent>(TEXT("CharacterMesh0"))) {
    const FProperty* p_Mesh = GetClass()->FindPropertyByName("Mesh");
    (*p_Mesh->ContainerPtrToValuePtr<USkeletalMeshComponent*>(this))->SetupAttachment(RootComponent);
}


