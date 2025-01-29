#include "EndNavWorldGeneralJumpActor.h"

AEndNavWorldGeneralJumpActor::AEndNavWorldGeneralJumpActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->bSmartLinkIsRelevant = false;
    this->bNextBuildSave = false;
}


