#include "EndAIMoveDefinitionAround.h"

UEndAIMoveDefinitionAround::UEndAIMoveDefinitionAround() {
    this->bEnableOverridePathFindInterval = false;
    this->OverridePathFindInterval = 0.05f;
    this->TimeOut = 0.00f;
    this->DistanceMed = 0.00f;
    this->bUseActionDefParam = false;
    this->bDisablePathFind = false;
    this->bAroundDircSwitch = false;
    this->bSelfRotationAroundDirc = false;
    this->bTargetEscapeAroundDirc = false;
    this->OverrideEQSRingRadius = -1.00f;
    this->RotationRateAccelerator = -1.00f;
}


