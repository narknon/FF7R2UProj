#include "EndFieldActionNiblCrawlMoveActor.h"
#include "Components/SplineComponent.h"

AEndFieldActionNiblCrawlMoveActor::AEndFieldActionNiblCrawlMoveActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->MovingPath = CreateDefaultSubobject<USplineComponent>(TEXT("MovingPathComponent"));
    this->StartCrawlAttachInterpTime = 0.00f;
    this->StartCrawlCameraInterpTime = 0.00f;
    this->bFinishIsPreStand = false;
    this->StepCount = 4;
    this->bStartIsLeftHandFront = false;
    this->bDebugForceActiveArea = false;
    this->MoveInputSuccessTime = 1.00f;
    this->StandUpInputSuccessTime = 1.00f;
    this->StandUpInputAnimationPlayRate = 0.20f;
    this->bUseOverrideCameraOffset = false;
    this->bUseOverrideCamera_Distance = false;
    this->OverrideCamera_Distance = 0.00f;
    this->bUseOverrideCamera_LimitAngle = false;
    this->OverrideCamera_LimitAngle = 20.00f;
    this->bUseOverrideCamera_FOV = false;
    this->OverrideCamera_FOV = 50.00f;
    this->bUseOverrideCamera_PitchLimit = false;
    this->OverrideCamera_PitchLimitMax = 20.00f;
    this->OverrideCamera_PitchLimitMin = -20.00f;
    this->MovingPath->SetupAttachment(RootComponent);
}


