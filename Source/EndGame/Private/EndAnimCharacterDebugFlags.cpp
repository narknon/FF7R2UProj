#include "EndAnimCharacterDebugFlags.h"

FEndAnimCharacterDebugFlags::FEndAnimCharacterDebugFlags() {
    this->bOutputDetailLogs = false;
    this->bVisualizeMovement = false;
    this->bVisualizeLookAt = false;
    this->bVisualizeSaccade = false;
    this->bVisualizeAim = false;
    this->bVisualizeSwordExpression = false;
    this->bEvaluateLookAtRequestedPose = false;
    this->bEvaluateLookAtPrimaryPose = false;
    this->bEvaluateLookAtSecondaryPose = false;
    this->bDumpLookAtRevaluation = false;
    this->bDisableBlink = false;
    this->bDisableEmotion = false;
    this->bDisableAutoSaccade = false;
    this->bDisableLookAtBlend = false;
    this->bDisableCharacterMovementExpression = false;
    this->bDisableFootIK = false;
    this->bVisualizeFootIK = false;
    this->bDisableHandIK = false;
    this->bVisualizeHandIK = false;
    this->bVisualizeJump = false;
}

