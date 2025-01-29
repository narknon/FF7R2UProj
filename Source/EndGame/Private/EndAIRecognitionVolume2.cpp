#include "EndAIRecognitionVolume2.h"

AEndAIRecognitionVolume2::AEndAIRecognitionVolume2(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->VolumeType = EEndAIRecognitionVolumeType::SafeArea;
    this->GroupId = 0;
    this->ShapeType = EEndAIRecognitionVolumeShapeType::Cube;
}


