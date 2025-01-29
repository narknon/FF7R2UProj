#include "EndObjectBase.h"

FEndObjectBase::FEndObjectBase() {
    this->UniqueIndex = 0;
    this->Priority = 0;
    this->IgnoreCheck = false;
    this->UseOnOff_StateChange = false;
    this->UseBeginOverlapTrigger_StateChange = false;
    this->UseEffect_StateChange = false;
    this->UsePlannerLevelSet_StateChange = false;
    this->UseAI_StateChange = false;
    this->UseTargetIcon_StateChange = false;
    this->UseGeneral_StateChange = false;
    this->UseEnvironmentAnimation_StateChange = false;
    this->UseEndOverlapTrigger_StateChange = false;
    this->UseResponseAreaAction_StateChange = false;
    this->UseMotionState_StateChange = false;
    this->UseAttachActor0_StateChange = false;
    this->UseAttachActor1_StateChange = false;
    this->UseAttachActor2_StateChange = false;
    this->UseSideDestination_StateChange = false;
    this->UseDisableLookAt_StateChange = false;
}

