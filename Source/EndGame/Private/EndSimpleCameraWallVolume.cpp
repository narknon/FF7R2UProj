#include "EndSimpleCameraWallVolume.h"

AEndSimpleCameraWallVolume::AEndSimpleCameraWallVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->CollisionProfileType = ESimpleCameraCollisionProfileType::GameCameraWall;
}


