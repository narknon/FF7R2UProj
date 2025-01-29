#include "EndChocoboClimbActionParam.h"

UEndChocoboClimbActionParam::UEndChocoboClimbActionParam() {
    this->StartClimbAngle = 30.00f;
    this->ClimbStartMotionAnticipationTime = 0.00f;
    this->ClimbStartRootMotionTranslationScale = 1.00f;
    this->AdditionalMaxStepHeight = 50.00f;
    this->WalkTranslationScale = 0.50f;
    this->WalkPlayRate = 1.00f;
    this->FastWalkTranslationScale = 1.20f;
    this->FastWalkPlayRate = 1.20f;
    this->VirtualSpeedMax = 15.00f;
    this->RaycastCheckOffset = 40.00f;
    this->OnClimbSucceedForwardSpeed = 3.00f;
    this->FallingAccelUpward = 20.00f;
    this->FallingAccelDownward = 20.00f;
    this->FallingMaxSpeedMin = 10.00f;
    this->FallingMaxSpeedMax = 20.00f;
    this->ClimbDownStartTerminalVelocity = 50.00f;
    this->ClimbDownAdditionalForwardSpeed = 3.00f;
    this->ClimbDownStartRotationTime = 1.00f;
    this->ClimbDownStartRootMotionTranslationScale = 1.00f;
    this->ClimbDownMovableAngle = 30.00f;
    this->ClimbDownMaxSpeed = 30.00f;
    this->ClimbDownAdditionalMaxSpeed = 10.00f;
    this->ClimbDownAccel = 15.00f;
}


