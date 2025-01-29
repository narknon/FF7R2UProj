#include "EndWheeledVehicleStuckCheckParam.h"

FEndWheeledVehicleStuckCheckParam::FEndWheeledVehicleStuckCheckParam() {
    this->ForceForStuckWithTireInAir = 0.00f;
    this->ExtraAccelScale = 0.00f;
    this->BeginStuckSpeedKph = 0.00f;
    this->EndStuckSpeedKph = 0.00f;
    this->WheelDummyBeginSpeedOnStuck = 0.00f;
    this->WheelDummySpeedForwardOnStuck = 0.00f;
    this->WheelDummySpeedBackwardOnStuck = 0.00f;
    this->ClimbingSlideDownMaxUpVectorDeltaAngle = 0.00f;
    this->ClimbingSlideDownTimer = 0.00f;
    this->ClimbingSlideDownTireFliction = 0.00f;
}

