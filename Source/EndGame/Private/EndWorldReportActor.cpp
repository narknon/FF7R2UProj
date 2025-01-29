#include "EndWorldReportActor.h"
#include "EndSyncPoseSkeletalMeshComponent.h"

AEndWorldReportActor::AEndWorldReportActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->DisplayMaterialIndex = 0;
    this->CoordinateAnimationDuration = 1.00f;
    this->DisplayMeshComponent = CreateDefaultSubobject<UEndSyncPoseSkeletalMeshComponent>(TEXT("DisplayMesh"));
    this->MovieMeshComponent = CreateDefaultSubobject<UEndSyncPoseSkeletalMeshComponent>(TEXT("MovieMesh"));
    this->Monitor_Change_SE = NULL;
    this->DisplayMeshComponent->SetupAttachment(RootComponent);
    this->MovieMeshComponent->SetupAttachment(RootComponent);
}

void AEndWorldReportActor::OnMediaOpened(const FString& OpenedUrl) {
}

void AEndWorldReportActor::OnMediaEndReached() {
}


