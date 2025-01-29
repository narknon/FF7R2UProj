#include "EndPlayerCameraManager.h"

AEndPlayerCameraManager::AEndPlayerCameraManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->DefaultModifiers.AddDefaulted(1);
    this->GrassCollisionComponent = NULL;
    this->CompositeCollisionComponent = NULL;
    this->MainCameraActor = NULL;
}


