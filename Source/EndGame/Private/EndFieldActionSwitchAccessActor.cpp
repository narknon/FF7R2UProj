#include "EndFieldActionSwitchAccessActor.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionSwitchAccessActor::AEndFieldActionSwitchAccessActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->TikableVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("TikableVolume"));
    this->IconInputSuccessTime = 0.00f;
    this->bUsePlayerAnimInputButton = true;
    this->bAccessSpaceBlockCollisionIsNgIcon = false;
    this->bReverseAddPlayerTransformOffsetWhenUseOnlyBackupAnim = false;
    this->bPlayerHandAttachPoint = false;
    this->bUseRightHandIK = false;
    this->bRightHandIKCorrectDir = false;
    this->bAttachToGround = false;
    this->bCanReveseSwitch = false;
    this->bEnablePlayerAttachInterp = true;
    this->bDefaultIsReverse = false;
    this->bAttachIsRotHalfOffset = false;
    this->bAttachIsKeepTargetDir = false;
    this->AttachPointToPlayerAdditiveDistance = 0.00f;
    this->AttachPointToPlayerAdditiveDistanceForIK = 0.00f;
    this->bEnableReverseMotionByWakeDir = false;
    this->MoveRailToRailCartSpeed = 1600.00f;
    this->bCanForceAttachAction = false;
    this->bUseGroundCorrectHandIK_Right = false;
    this->bUseGroundCorrectHandIK_Left = false;
    this->bNoCapsuleSizeModify = false;
    this->TikableVolume->SetupAttachment(RootComponent);
}


