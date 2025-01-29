#include "EndAIRecognitionVolume.h"
#include "Components/SceneComponent.h"
#include "EndAIRecognitionBoxComponent.h"

AEndAIRecognitionVolume::AEndAIRecognitionVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    this->VolumeType = EEndAIRecognitionVolumeType::SafeArea;
    this->GroupId = 0;
    this->RecognitionBoxComponent = CreateDefaultSubobject<UEndAIRecognitionBoxComponent>(TEXT("EndAIRecognitionBoxComponent"));
    this->RecognitionBoxComponent->SetupAttachment(RootComponent);
}


