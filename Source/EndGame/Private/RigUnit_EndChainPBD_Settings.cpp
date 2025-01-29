#include "RigUnit_EndChainPBD_Settings.h"

FRigUnit_EndChainPBD_Settings::FRigUnit_EndChainPBD_Settings() {
    this->ParticleReserveCount = 0;
    this->PositionIterationCount = 0;
    this->VelocityIterationCount = 0;
    this->bEnabledXPBD = false;
    this->bEnabledSubStep = false;
    this->bEnabledHighFpsEvaluation = false;
    this->bStopSimulationOnWorldShift = false;
    this->ConstantVelocityDumping = 0.00f;
    this->InterpRate = 0.00f;
    this->RollBias = 0.00f;
    this->StraightLineRemapRate = 0.00f;
    this->SleepTimer = 0.00f;
}

