#include "EndFieldActionRedPullMoveActor.h"
#include "Components/SplineComponent.h"

AEndFieldActionRedPullMoveActor::AEndFieldActionRedPullMoveActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->PlayerMovingPath = CreateDefaultSubobject<USplineComponent>(TEXT("PlayerMovingPathComponent"));
    this->EnemyLeftTurnAngle_Strong_Strong = 10.00f;
    this->EnemyLeftTurnAngle_Strong_Normal = -10.00f;
    this->EnemyLeftTurnAngle_Normal_Strong = 40.00f;
    this->EnemyRightTurnAngle_Strong_Strong = -10.00f;
    this->EnemyRightTurnAngle_Strong_Normal = -40.00f;
    this->EnemyRightTurnAngle_Normal_Strong = 10.00f;
    this->EnemyStrongPullAddDistance = 200.00f;
    this->StartChallengeWaitTime = 1.00f;
    this->FinishChallengeDistance = 100000.00f;
    this->RopeObjectClass = NULL;
    this->bDebugWakeUp = false;
    this->PlayerMovingPath->SetupAttachment(RootComponent);
}


