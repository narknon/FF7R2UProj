#include "EndMenuViewport.h"
#include "Templates/SubclassOf.h"

UEndMenuViewport::UEndMenuViewport() {
}

AActor* UEndMenuViewport::Spawn(TSubclassOf<AActor> ActorClass) {
    return NULL;
}

void UEndMenuViewport::SetViewRotation(FRotator Rotation) {
}

void UEndMenuViewport::SetViewLocation(FVector Location) {
}

FRotator UEndMenuViewport::GetViewRotation() const {
    return FRotator{};
}

UWorld* UEndMenuViewport::GetViewportWorld() const {
    return NULL;
}

FVector UEndMenuViewport::GetViewLocation() const {
    return FVector{};
}


