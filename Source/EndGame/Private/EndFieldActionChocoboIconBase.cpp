#include "EndFieldActionChocoboIconBase.h"

AEndFieldActionChocoboIconBase::AEndFieldActionChocoboIconBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->MarkerTypeEnter = EEndFieldActionChocoboMarkerType::None;
    this->MarkerTypeExit = EEndFieldActionChocoboMarkerType::None;
    this->SpawnChocoboDistanceFromIcon = 1000.00f;
}


