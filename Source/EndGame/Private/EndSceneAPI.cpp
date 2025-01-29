#include "EndSceneAPI.h"

UEndSceneAPI::UEndSceneAPI() {
}

bool UEndSceneAPI::ValidateSimpleCameraWall(FName TargetActorName) {
    return false;
}

bool UEndSceneAPI::TeleportActor(FName LevelName, FName ActorName, AActor* TargetActor, bool bApplyDestRotation) {
    return false;
}

bool UEndSceneAPI::IsDrawPause(AActor* Actor) {
    return false;
}

bool UEndSceneAPI::InvalidateSimpleCameraWall(FName TargetActorName) {
    return false;
}

FTransform UEndSceneAPI::GetNavTransformFromLevel(FName Level, FName Name) {
    return FTransform{};
}

FTransform UEndSceneAPI::GetNavTransform(FName Name) {
    return FTransform{};
}

FRotator UEndSceneAPI::GetNavRotationFromLevel(FName Level, FName Name) {
    return FRotator{};
}

FRotator UEndSceneAPI::GetNavRotation(FName Name) {
    return FRotator{};
}

FVector UEndSceneAPI::GetNavLocationFromLevel(FName Level, FName Name) {
    return FVector{};
}

FVector UEndSceneAPI::GetNavLocation(FName Name) {
    return FVector{};
}

AEndNavModifierVolume* UEndSceneAPI::GetNavFromNameAndLevel(FName Level, FName Name) {
    return NULL;
}

bool UEndSceneAPI::FindMediaPlayer(const UMaterialInterface* MovieMaterial, UMediaPlayer*& OutMediaPlayer, UMediaTexture*& OutMediaTexture) {
    return false;
}

UMaterialInterface* UEndSceneAPI::FindMaterialByName(AActor* Actor, FName MaterialName) {
    return NULL;
}

AActor* UEndSceneAPI::FindActorFromAccessorBP(FName InAccessId, FName InLevelName, FName InAccsessorActorName) {
    return NULL;
}

void UEndSceneAPI::DetachWeapon(AActor* CharacterActor, EWeaponSlot Slot) {
}

int32 UEndSceneAPI::DestroyActorBP(FName Name) {
    return 0;
}

int32 UEndSceneAPI::CreateActorBP(FName Name, FName CharaSpec, FVector Location, FRotator Rotation) {
    return 0;
}

void UEndSceneAPI::AttachWeapon(AActor* CharacterActor, AActor* WeaponActor, EWeaponSlot Slot) {
}


