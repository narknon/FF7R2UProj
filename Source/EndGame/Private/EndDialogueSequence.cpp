#include "EndDialogueSequence.h"

UEndDialogueSequence::UEndDialogueSequence() {
    this->Version = EEndDialogueSequenceVersion::None;
    this->bFullGenerateOnly = false;
    this->bSeamlessIn = false;
    this->bIgnoreReferenceCharacterSetting = false;
    this->bEnableEnvironmentLightModulation = false;
    this->ExtraFloorTraceDistance = 0.00f;
    this->MassiveEnvironmentFrustumScale = 1.00f;
    this->ViewSlaveLocationFarClippingPlane = 0.00f;
    this->StreamedShadowFarClippingPlane = 0.00f;
}


