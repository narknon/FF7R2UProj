#include "EndNavAPI.h"

UEndNavAPI::UEndNavAPI() {
}

bool UEndNavAPI::ValidateNavModifierVolume(const FName ActorName) {
    return false;
}

bool UEndNavAPI::ValidateFieldActionModifierVolume(const FName ActorName) {
    return false;
}

bool UEndNavAPI::ValidateBlockingModifierVolume(const FName LevelName, const FName ActorName) {
    return false;
}

bool UEndNavAPI::ValidateAerialIgnoreVolume(const FName ActorName) {
    return false;
}

bool UEndNavAPI::InvalidateNavModifierVolume(const FName ActorName) {
    return false;
}

bool UEndNavAPI::InvalidateFieldActionModifierVolume(const FName ActorName) {
    return false;
}

bool UEndNavAPI::InvalidateBlockingModifierVolume(const FName LevelName, const FName ActorName) {
    return false;
}

bool UEndNavAPI::InvalidateAerialIgnoreVolume(const FName ActorName) {
    return false;
}

FTransform UEndNavAPI::GetNavModifierTransform(const FName Name) {
    return FTransform{};
}

AEndNavModifierVolume* UEndNavAPI::GetNavFromName(const FName Name) {
    return NULL;
}

FNavAgentProperties UEndNavAPI::GetAgentPropety(EEndNavLayerType InLayerType) {
    return FNavAgentProperties{};
}

bool UEndNavAPI::FindNearestNavMeshPointAgent(FVector TargetLocation, FVector& OutLocation, FName InModifierName, FNavAgentProperties InAgentProperty, FVector SearchRange, EEndQueryFilterType FilterType) {
    return false;
}

bool UEndNavAPI::FindNearestNavMeshPoint(FVector TargetLocation, FVector& OutLocation, FName InModifierName, FVector SearchRange, EEndQueryFilterType FilterType) {
    return false;
}

void UEndNavAPI::DisableNavStreaming(bool Disabled) {
}


