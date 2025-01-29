#include "EndFrogGuysSeesawGimmickActor.h"

AEndFrogGuysSeesawGimmickActor::AEndFrogGuysSeesawGimmickActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->MaximumExtraAngleDiff = 22.50f;
    this->ReturnAngularSpeed = 5.00f;
    this->AngularSpeedPerDistance = 0.50f;
}

void AEndFrogGuysSeesawGimmickActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
}

void AEndFrogGuysSeesawGimmickActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
}


