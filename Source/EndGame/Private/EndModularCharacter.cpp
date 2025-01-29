#include "EndModularCharacter.h"
#include "EndSkeletalMeshComponent.h"
#include "EndSyncPoseSkeletalMeshComponent.h"

AEndModularCharacter::AEndModularCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    auto p_Mesh_Parent = GetMesh();
	this->TopsMesh = CreateDefaultSubobject<UEndSyncPoseSkeletalMeshComponent>(TEXT("Tops"));
    this->BottomsMesh = CreateDefaultSubobject<UEndSyncPoseSkeletalMeshComponent>(TEXT("Bottoms"));
    this->HairMesh = CreateDefaultSubobject<UEndSyncPoseSkeletalMeshComponent>(TEXT("Hair"));
    this->HaircovMesh = CreateDefaultSubobject<UEndSyncPoseSkeletalMeshComponent>(TEXT("Haircov"));
    this->OptionalSyncPoseMesh0 = CreateDefaultSubobject<UEndSyncPoseSkeletalMeshComponent>(TEXT("OptionalSyncPose0"));
    this->OptionalAttachMesh0 = CreateDefaultSubobject<UEndSkeletalMeshComponent>(TEXT("OptionalAttach0"));
    this->OptionalAttachMesh1 = CreateDefaultSubobject<UEndSkeletalMeshComponent>(TEXT("OptionalAttach1"));
    this->BottomsMesh->SetupAttachment(p_Mesh_Parent);
    this->HairMesh->SetupAttachment(p_Mesh_Parent);
    this->HaircovMesh->SetupAttachment(p_Mesh_Parent);
    this->OptionalAttachMesh0->SetupAttachment(p_Mesh_Parent);
    this->OptionalAttachMesh1->SetupAttachment(p_Mesh_Parent);
    this->OptionalSyncPoseMesh0->SetupAttachment(p_Mesh_Parent);
    this->TopsMesh->SetupAttachment(p_Mesh_Parent);
}


