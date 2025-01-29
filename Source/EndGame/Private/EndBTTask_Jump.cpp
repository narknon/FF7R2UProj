#include "EndBTTask_Jump.h"

UEndBTTask_Jump::UEndBTTask_Jump() {
    this->bUseBlackboardAngle = false;
    this->Angle = 45.00f;
    this->bUseBlackboardRotationInterpSpeed = false;
    this->RotationInterpSpeed = 5.00f;
    this->bUseBlackboardGravityScale = false;
    this->GravityScale = 5.00f;
    this->bLandingWithTimer = true;
    this->bForceJump = false;
}


