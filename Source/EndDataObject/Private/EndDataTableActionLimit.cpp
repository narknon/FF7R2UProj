#include "EndDataTableActionLimit.h"

FEndDataTableActionLimit::FEndDataTableActionLimit() {
    this->CameraLookAt_Use = 0;
    this->CameraLookAt_IsTurnRequested = 0;
    this->CameraLookAt_CanSkip = 0;
    this->CameraLookAt_IsPreserveLastDir = 0;
    this->CameraLookAt_StopControl = 0;
    this->CameraLookAt_DisablePitchLimit = 0;
    this->CameraOperator = 0;
    this->InterestPointBind_Use = 0;
    this->InterestPointBind_InterestRadius = 0.00f;
    this->InterestPointBind_Type = 0;
    this->PlayerMoveType_Use = 0;
    this->PlayerMoveType_type = 0;
    this->PlayerMoveType_useDashMode = 0;
    this->StrictMoveType = 0;
    this->autoWalkType_Use = 0;
    this->autoWalkType_specialType = 0;
    this->autoWalkType_beginTurnBackDistance = 0.00f;
    this->autoWalkType_turnBackDistance = 0.00f;
    this->autoWalkType_EnableTrunBack = 0;
    this->autoWalkType_turnBackTiming = 0;
    this->autoWalkType_bPathFindOnce_old = 0;
    this->autoWalkType_turnBackWarningType = 0;
    this->autoWalkType_SpecificLifeTimeSeconds = 0.00f;
    this->autoWalkType_DeactivatePitchIndex = 0;
    this->autoWalkType_useStoryIndex = 0;
    this->autoWalkType_TurnBack_ForceWalk = 0;
    this->autoWalkType_TurnBack_MaxWeight = 0;
    this->StrictMoveType_2 = 0;
}

