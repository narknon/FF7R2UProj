#include "EndDialoguePostProcessControlActor.h"

AEndDialoguePostProcessControlActor::AEndDialoguePostProcessControlActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->Weight = 1.00f;
    this->bEnabledDepthOfField = false;
    this->FocalDistance = 100.00f;
    this->Fstop = 5.60f;
    this->DepthOfFieldWeight = 1.00f;
    this->bEnableLensExposure = false;
    this->ExposureBias = 0.00f;
    this->LensExposureWeight = 1.00f;
    this->bEnableEstimateExposure = false;
    this->Variance = 0.00f;
    this->EstimateExposureWeight = 1.00f;
    this->bEnableLightModifierEnvironmentLight = false;
    this->EnvironmentLightModifier = 0.00f;
    this->LightModifierEnvironmentLightWeight = 1.00f;
    this->bEnableLightModifierEnvironmentLight_Default = false;
    this->EnvironmentLightModifier_Default = 0.70f;
    this->LightModifierEnvironmentLightWeight_Default = 1.00f;
    this->bEnableDirectionalLightOverride = false;
    this->CascadeDistance0 = 500.00f;
    this->CascadeDistance1 = 5000.00f;
    this->DirectionalLightOverrideWeight = 1.00f;
    this->bEnableDirectionalLightOverride_Default = false;
    this->CascadeDistance0_Default = 500.00f;
    this->CascadeDistance1_Default = 5000.00f;
    this->DirectionalLightOverrideWeight_Default = 1.00f;
    this->bEnableSpotLightOverride = false;
    this->SpotLightShadowBias = 0.00f;
    this->SpotLightOverrideWeight = 1.00f;
    this->bEnableSpotLightOverride_Default = false;
    this->SpotLightShadowBias_Default = 0.00f;
    this->SpotLightOverrideWeight_Default = 1.00f;
}


