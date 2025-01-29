#include "RigUnit_EndPBD_Settings.h"

FRigUnit_EndPBD_Settings::FRigUnit_EndPBD_Settings() {
    this->PositionIterationCount = 0;
    this->VelocityIterationCount = 0;
    this->bEnabledXPBD = false;
    this->bEnabledSubStep = false;
    this->bEnabledHighFpsEvaluation = false;
    this->bStopSimulationOnWorldShift = false;
    this->ConstantVelocityDumping = 0.00f;
    this->InterpRate = 0.00f;
    this->RollBias = 0.00f;
}

