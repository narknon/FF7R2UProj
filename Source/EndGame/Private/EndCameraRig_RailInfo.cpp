#include "EndCameraRig_RailInfo.h"

FEndCameraRig_RailInfo::FEndCameraRig_RailInfo() {
    this->Sequence = NULL;
    this->SequencePlayer = NULL;
    this->ParentComponent = NULL;
    this->MoveSpline = NULL;
    this->CameraSpline = NULL;
    this->RailCameraMount = NULL;
    this->bUseReturnRail = false;
    this->bIsUsingReturnRail = false;
    this->ReturnCameraSpline = NULL;
    this->ReturnRailCameraMount = NULL;
    this->ReturnTransform = NULL;
    this->SplineProgress = 0.00f;
    this->DegreesOfCameraFreedom = 0.00f;
    this->CameraInputRotationSpeed = 0.00f;
    this->CameraComponent = NULL;
    this->ReturnCameraComponent = NULL;
    this->bLockOrientationToRail = false;
    this->LockOrientationAlpha = 0.00f;
    this->bLockOrientationToRailOnReturn = false;
    this->bUseRailCameraMountRotationOnLockOrientation = false;
    this->bIsToFreezeControlRotation = false;
    this->bCanUseDistanceBlend = false;
    this->bUseFixedBlendInTime = false;
    this->bUseFixedBlendOutTime = false;
    this->BlendInTime = 0.00f;
    this->BlendInOption = EAlphaBlendOption::Linear;
    this->BlendOutTime = 0.00f;
    this->BlendOutOption = EAlphaBlendOption::Linear;
    this->bShowRailVisualization = false;
    this->MassiveEnvironmentFrustrumScaleForMainPass = 0.00f;
}

