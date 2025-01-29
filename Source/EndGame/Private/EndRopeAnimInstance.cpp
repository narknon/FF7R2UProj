#include "EndRopeAnimInstance.h"

UEndRopeAnimInstance::UEndRopeAnimInstance() {
}

bool UEndRopeAnimInstance::UnregisterAttachPoint(int32 AttachPointHandle) {
    return false;
}

void UEndRopeAnimInstance::SetRopeDistanceBias(float InDistanceBias) {
}

void UEndRopeAnimInstance::SetOverrideRopeLength(float InRopeLength) {
}

void UEndRopeAnimInstance::SetFixedRoot(bool bFixed) {
}

void UEndRopeAnimInstance::SetAttachPointLocation(int32 AttachPointHandle, FVector Location) {
}

void UEndRopeAnimInstance::RemoveRopeContactIgnoreActor(AActor* Actor) {
}

int32 UEndRopeAnimInstance::RegisterAttachPoint(float Distance) {
    return 0;
}

bool UEndRopeAnimInstance::IsAppearedRope() const {
    return false;
}

float UEndRopeAnimInstance::GetTotalParticleLength() const {
    return 0.0f;
}

FVector UEndRopeAnimInstance::GetRootPullVector2D() const {
    return FVector{};
}

FVector UEndRopeAnimInstance::GetRootPullVector() const {
    return FVector{};
}

FVector UEndRopeAnimInstance::GetRootPullLocation() const {
    return FVector{};
}

float UEndRopeAnimInstance::GetRootPullLimitLength2D() const {
    return 0.0f;
}

float UEndRopeAnimInstance::GetRootPullLimitLength() const {
    return 0.0f;
}

FVector UEndRopeAnimInstance::GetRootLocation() const {
    return FVector{};
}

FVector UEndRopeAnimInstance::GetEndPullVector2D() const {
    return FVector{};
}

FVector UEndRopeAnimInstance::GetEndPullVector() const {
    return FVector{};
}

FVector UEndRopeAnimInstance::GetEndPullLocation() const {
    return FVector{};
}

float UEndRopeAnimInstance::GetEndPullLimitLength2D() const {
    return 0.0f;
}

float UEndRopeAnimInstance::GetEndPullLimitLength() const {
    return 0.0f;
}

FVector UEndRopeAnimInstance::GetEndLocation() const {
    return FVector{};
}

void UEndRopeAnimInstance::DetachEndPoint() {
}

void UEndRopeAnimInstance::AttachEndPoint(FVector EndPointLocation, const FVector& EndPointVector) {
}

void UEndRopeAnimInstance::AddRopeContactIgnoreActor(AActor* Actor) {
}


