#include "EndBattleCameraActor.h"

AEndBattleCameraActor::AEndBattleCameraActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->AimTarget0_to1_Rate = 0.00f;
    this->AimTarget0_Type = EEndBattleCameraTargetType::None;
    this->bAimTarget0_Fix = false;
    this->AimTarget1_Type = EEndBattleCameraTargetType::None;
    this->bAimTarget1_Fix = false;
    this->AimTarget_RelativeLocation_RotateType = EEndBattleCameraRelativeLocationRotateType::AlwaysRotate;
    this->EyeTargetType = EEndBattleCameraTargetType::None;
    this->EyeTargetRelativeLocationSLerpType = EEndBattleCameraSLerpType::None;
    this->bEyeTarget_Fix = false;
    this->EyeToAimTargetRotateType = EEndBattleCameraEyeToAimTargetRotateType::AlwaysRotate;
    this->bEyeToAimTargetRotateIncludePitch = false;
    this->bEyePointFix = false;
    this->AimLeapTime = 0.00f;
    this->EyeLeapTime = 0.00f;
    this->bStabilizer = false;
    this->Roll = 0.00f;
    this->OthersGameSpeed = 1.00f;
    this->bIncludeOwnerGameSpeed = false;
    this->NoOthersGameSpeed = 1.00f;
    this->InputOffsetType = EndBattleCameraInputOffsetType::None;
    this->bMoveUpEyeWhenHitWall = false;
    this->bPerformCollisionCheck = true;
    this->OwnerActor = NULL;
    this->TargetActor = NULL;
    this->SequenceActor = NULL;
    this->AimTarget0_Actor = NULL;
    this->AimTarget1_Actor = NULL;
    this->EyeTargetActor = NULL;
}

void AEndBattleCameraActor::BindTargetActor(AActor* NewOwnerActor, AActor* NewTargetActor) {
}


