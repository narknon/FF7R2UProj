#include "EndActionTorokkoPlayerController.h"

AEndActionTorokkoPlayerController::AEndActionTorokkoPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->_currentPlayerController = NULL;
    this->_reticleWidget = NULL;
    this->_yuffieReticleWidget = NULL;
    this->_resultScreenWidget = NULL;
    this->ResultScreenWidget = NULL;
    this->ResultScreenWidgetClass = NULL;
    this->_rideActor = NULL;
    this->_currentTargetActor = NULL;
    this->_currentAutoTrackingActor = NULL;
    this->_currentYuffieBoxTarget = NULL;
    this->_cachedYuffieReticleTarget = NULL;
    this->_barretReference = NULL;
    this->_yuffieReference = NULL;
    this->_tifaReference = NULL;
    this->_currentYuffieTriggerBox = NULL;
    this->YuffieTargetWidget = NULL;
    this->BarretTargetWidget = NULL;
    this->YuffieTargetWidgetClass = NULL;
    this->BarretTargetWidgetClass = NULL;
}

void AEndActionTorokkoPlayerController::OnBoxDestroyedCallback(AEndEnvironmentPhysicsStaticMeshActor* BrokenBox) {
}


