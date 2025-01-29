#include "SQEX_KineDriverTargetBendRoll.h"

FSQEX_KineDriverTargetBendRoll::FSQEX_KineDriverTargetBendRoll() {
    this->SourceQuat = 0;
    this->QuatWeight = 0.00f;
    this->AsQuatAngle = false;
    this->Roll = 0.00f;
    this->SegmentScaleCompensate = false;
    this->ReverseOrder = false;
}

