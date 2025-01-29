#include "EndCameraRig_Rail.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "EndPlayerOverlapSplineComponent.h"

AEndCameraRig_Rail::AEndCameraRig_Rail(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
    this->OverlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapVolumeComponent"));
    this->PlayerRailComponent = CreateDefaultSubobject<UEndPlayerOverlapSplineComponent>(TEXT("PlayerRailComponent"));
    this->CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("RailCamera"));
    this->ReturnCameraComponent = NULL;
    this->FalloffStartDistance = 200.00f;
    this->DisengageDistance = 400.00f;
    this->FalloffExtraHeight = 100.00f;
    this->bCanLaunchSelf = true;
    this->bIsInPursuit = false;
    this->MaxSplineWalkSpeed = 700.00f;
    this->CameraFollowSpeed = 700.00f;
    this->bUseAccurateSplineProgress = false;
    this->CameraComponent->SetupAttachment(RailCameraMount);
    this->OverlapComponent->SetupAttachment(RootComponent);
    this->PlayerRailComponent->SetupAttachment(RootComponent);
}

void AEndCameraRig_Rail::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
}

void AEndCameraRig_Rail::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
}


