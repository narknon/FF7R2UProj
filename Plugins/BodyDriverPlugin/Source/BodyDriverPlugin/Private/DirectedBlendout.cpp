#include "DirectedBlendout.h"

FDirectedBlendout::FDirectedBlendout() {
    this->Enabled = false;
    this->BlendOutTimeStartMin = 0.00f;
    this->BlendOutDuration = 0.00f;
    this->ConstraintReturnLinVel = 0.00f;
    this->ConstraintReturnAngVel = 0.00f;
}

