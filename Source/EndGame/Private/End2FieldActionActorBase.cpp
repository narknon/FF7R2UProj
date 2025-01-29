#include "End2FieldActionActorBase.h"

AEnd2FieldActionActorBase::AEnd2FieldActionActorBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bNpcEndMotionIsForceFastMove = false;
    this->bDisableDeactiveByHidden = false;
    this->FieldActionActorHashVersion = 0;
    this->FieldActionActorHash32 = 0;
    this->FieldActionActorHash64 = 0;
}

void AEnd2FieldActionActorBase::TestTargetIconAction() {
}


