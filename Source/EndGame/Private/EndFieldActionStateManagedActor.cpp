#include "EndFieldActionStateManagedActor.h"

AEndFieldActionStateManagedActor::AEndFieldActionStateManagedActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->OnceOnlyReact = false;
    this->bDefaultEndStateTriggerIncludeInputCancelNotify = false;
    this->bAllowRailCameraSetup = false;
    this->bUseRailCamera = false;
    this->bUseAccurateSplineProgress = false;
    this->RailCameraComponent = NULL;
    this->ReturnRailCameraComponent = NULL;
}


