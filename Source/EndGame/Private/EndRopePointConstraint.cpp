#include "EndRopePointConstraint.h"

FEndRopePointConstraint::FEndRopePointConstraint() {
    this->Distance = 0.00f;
    this->bEnableConstraint = false;
    this->ConstraintDistance = 0.00f;
    this->ConstraintStiffness = 0.00f;
    this->bSolveOnResetFrameOnly = false;
}

