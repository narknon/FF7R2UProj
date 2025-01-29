#include "EndStreamingSwitchVolume.h"

AEndStreamingSwitchVolume::AEndStreamingSwitchVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->SwitchType = EEndStreamingSwitchType::Seamless;
}

void AEndStreamingSwitchVolume::SwitchStreamingVolume(FName InSwitchLabel, EEndStreamingSwitchType InSwitchType, bool NoErrMsg) {
}


