#include "EndAnimationSettings.h"

UEndAnimationSettings::UEndAnimationSettings() {
    this->PlannerEventInCameraList.AddDefaulted(2);
    this->ReinsSettings.AddDefaulted(2);
    this->BlendTimeMinWhenWaitMode = 0.05f;
    this->TreasureBoxDistance = 75.00f;
    this->TreasureBoxDistanceLR = 110.00f;
    this->TreasureBoxPickUpDistance = 60.00f;
    this->TreasureBoxLocationSmoothingSpeed = 200.00f;
    this->TreasureBoxRotationSmoothingSpeed = 180.00f;
    this->TreasureBoxTurnTolerance = 22.50f;
    this->TreasureBoxWalkRunEndWaitTime = 0.80f;
    this->PushButtonLocationSmoothingSpeed = 200.00f;
    this->PushButtonRotationSmoothingSpeed = 180.00f;
    this->PushButtonTurnTolerance = 22.50f;
    this->PushButtonWalkRunEndWaitTime = 0.80f;
    this->FaceGuardLoopTimeMin = 0.50f;
}


