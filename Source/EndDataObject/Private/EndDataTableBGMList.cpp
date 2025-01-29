#include "EndDataTableBGMList.h"

FEndDataTableBGMList::FEndDataTableBGMList() {
    this->UniqueIndex = 0;
    this->PauseRestart = 0;
    this->IsHighPriorityLoad = 0;
    this->FadeInTime = 0.00f;
    this->FadeOutTime = 0.00f;
    this->OverrideFadeOutTime = 0.00f;
    this->CrossFade = 0;
    this->OneShot = 0;
    this->OneShotPlayTime = 0.00f;
    this->IgnoreVehicleRequest = 0;
    this->EnablePrevFinishSection = 0;
}

