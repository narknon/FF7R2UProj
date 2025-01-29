#include "EndRopeActor.h"

AEndRopeActor::AEndRopeActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bEnabledPhysicsCollision = true;
}

void AEndRopeActor::RemoveRopeContactIgnoreActor(AActor* Actor) {
}

void AEndRopeActor::DetachRopeRoot() {
}

void AEndRopeActor::DetachRopeEndPoint() {
}

void AEndRopeActor::AttachRopeRootToTransform(const FTransform& Transform) {
}

void AEndRopeActor::AttachRopeRootToSkeletamMesh(USkeletalMeshComponent* Mesh, FName SocketName) {
}

void AEndRopeActor::AttachRopeRootToActor(AActor* Actor, FName SocketName) {
}

void AEndRopeActor::AttachRopeEndPointToSkeletalMesh(USkeletalMeshComponent* Mesh, FName SocketName) {
}

void AEndRopeActor::AttachRopeEndPointToLocation(const FVector& Location) {
}

void AEndRopeActor::AttachRopeEndPointToActor(AActor* Actor, FName SocketName) {
}

void AEndRopeActor::AddRopeContactIgnoreActor(AActor* Actor) {
}


