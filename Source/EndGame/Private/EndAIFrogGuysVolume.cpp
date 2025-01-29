#include "EndAIFrogGuysVolume.h"
#include "Components/SceneComponent.h"
#include "EndAIRecognitionBoxComponent.h"

AEndAIFrogGuysVolume::AEndAIFrogGuysVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    this->ShapeType = EEndAIRecognitionVolumeShapeType::Cube;
    this->RecognitionBoxComponent = CreateDefaultSubobject<UEndAIRecognitionBoxComponent>(TEXT("BoxComponent"));
    this->ActiveTimeLength = 0.00f;
    this->ID = 0;
    this->GroupId = 0;
    this->RollType = EEndAIFrogGuysVolumeRollType::CW;
    this->RecognitionBoxComponent->SetupAttachment(RootComponent);
}

void AEndAIFrogGuysVolume::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
}

void AEndAIFrogGuysVolume::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
}


