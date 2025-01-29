#include "RigUnit_EndAim_Effector.h"

FRigUnit_EndAim_Effector::FRigUnit_EndAim_Effector() {
    this->bComponentSpaceForwardAim = false;
    this->TranslationActiveDistance = 0.00f;
    this->bForceSkipSolvedTarget = false;
    this->AdditiveContinuationTargetScore = 0;
}

