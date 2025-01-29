#include "EndFieldTerritoryDisableEscapeVolume.h"

AEndFieldTerritoryDisableEscapeVolume::AEndFieldTerritoryDisableEscapeVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bColored = true;
    this->bEnablePhysicsBodyBlock = false;
    this->IsCubeBoxWallVolume = false;
}


