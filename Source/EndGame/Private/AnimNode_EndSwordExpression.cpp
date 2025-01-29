#include "AnimNode_EndSwordExpression.h"

FAnimNode_EndSwordExpression::FAnimNode_EndSwordExpression() {
    this->EndPointDistance = 0.00f;
    this->bEnabledEndPointGravity = false;
    this->AnimatedPositionStiffness = 0.00f;
    this->VelocityFriction = 0.00f;
    this->ConstraintAngle = 0.00f;
    this->ConstraintAngleStiffness = 0.00f;
    this->ContactPadding = 0.00f;
    this->ContactPaddingWalkScale = 0.00f;
    this->ContactPaddingRunScale = 0.00f;
    this->ContactPaddingDashScale = 0.00f;
    this->ContactPositionStiffness = 0.00f;
    this->ContactVelocityStiffness = 0.00f;
    this->PositionIterationCount = 0;
    this->VelocityIterationCount = 0;
    this->WeightSmoothRate = 0.00f;
    this->ActiveDuringTime = 0.00f;
    this->DeltaRotationInterpSpeedWalk = 0.00f;
    this->DeltaRotationInterpSpeedRun = 0.00f;
    this->DeltaRotationInterpSpeedDash = 0.00f;
}

