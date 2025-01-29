#include "EndRedHoldDeliveryStaticMeshActor.h"

AEndRedHoldDeliveryStaticMeshActor::AEndRedHoldDeliveryStaticMeshActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bHoldObjectMode = false;
    this->RedCatchBlendRate = 1.00f;
    this->HoldSound_Drop = NULL;
    this->HoldSound_Hold = NULL;
}


