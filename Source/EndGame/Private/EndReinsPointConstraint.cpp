#include "EndReinsPointConstraint.h"

FEndReinsPointConstraint::FEndReinsPointConstraint() {
    this->ChainIndex = 0;
    this->Distance = 0.00f;
    this->bEnableConstraint = false;
    this->ConstraintDistance = 0.00f;
    this->ConstraintStiffness = 0.00f;
    this->bSolveOnResetFrameOnly = false;
}

