#include "SQEX_KineDriverTargetScale.h"

FSQEX_KineDriverTargetScale::FSQEX_KineDriverTargetScale() {
    this->ScaleX = 0.00f;
    this->ScaleY = 0.00f;
    this->ScaleZ = 0.00f;
    this->ClampZero = false;
    this->BaseSpace_DEPLECATED = 0;
    this->SegmentScaleCompensate = false;
    this->InputAsLogarithm = false;
}

