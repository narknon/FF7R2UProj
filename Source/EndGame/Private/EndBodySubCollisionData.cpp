#include "EndBodySubCollisionData.h"

FEndBodySubCollisionData::FEndBodySubCollisionData() {
    this->ShapeType = EEndCollision::SPHERE;
    this->bAttatchToMesh = false;
    this->bEnableSlopeCheck = false;
    this->bConnectFromRoot = false;
    this->bDisableMoveOnlyXY = false;
    this->bAllowForcePushBack = false;
}

