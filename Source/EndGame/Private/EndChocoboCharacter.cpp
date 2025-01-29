#include "EndChocoboCharacter.h"
#include "EndChocoboPartsSkeletalMeshComponent.h"
#include "EndSkeletalMeshComponent.h"

AEndChocoboCharacter::AEndChocoboCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bForceUpdateKinematicBonesUpdateToPhysics = true;
    this->PartsMeshComp_Head = CreateDefaultSubobject<UEndChocoboPartsSkeletalMeshComponent>(TEXT("PartsMeshComp_Head"));
    USkeletalMeshComponent* p_Mesh_Parent = GetMesh();
    this->PartsMeshComp_Body = CreateDefaultSubobject<UEndChocoboPartsSkeletalMeshComponent>(TEXT("PartsMeshComp_Body"));
    this->PartsMeshComp_Legs = CreateDefaultSubobject<UEndChocoboPartsSkeletalMeshComponent>(TEXT("PartsMeshComp_Legs"));
    this->PartsMeshComp_EquipHead = CreateDefaultSubobject<UEndChocoboPartsSkeletalMeshComponent>(TEXT("PartsMeshComp_EquipHead"));
    this->PartsMeshComp_EquipBody = CreateDefaultSubobject<UEndChocoboPartsSkeletalMeshComponent>(TEXT("PartsMeshComp_EquipBody"));
    this->PartsMeshComp_EquipLegs = CreateDefaultSubobject<UEndChocoboPartsSkeletalMeshComponent>(TEXT("PartsMeshComp_EquipLegs"));
    this->CommonActionParameter = NULL;
    this->AirGlideActionParameter = NULL;
    this->WaterJetActionParameter = NULL;
    this->ClimbActionParameter = NULL;
    this->DefaultPartsIndex = 0;
    this->PartsMeshComp_Body->SetupAttachment(p_Mesh_Parent);
    this->PartsMeshComp_EquipBody->SetupAttachment(p_Mesh_Parent);
    this->PartsMeshComp_EquipHead->SetupAttachment(p_Mesh_Parent);
    this->PartsMeshComp_EquipLegs->SetupAttachment(p_Mesh_Parent);
    this->PartsMeshComp_Head->SetupAttachment(p_Mesh_Parent);
    this->PartsMeshComp_Legs->SetupAttachment(p_Mesh_Parent);
}


