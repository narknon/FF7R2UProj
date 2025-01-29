#include "BodyDriver_DebugImpulseTuningSet.h"

UBodyDriver_DebugImpulseTuningSet::UBodyDriver_DebugImpulseTuningSet() {
    this->ForceSwitchToAnimTime = -1.00f;
    this->EnableRandomImpulses = false;
    this->TreatAsMelee = false;
    this->TreatAsExplosion = false;
    this->TreatAsShake = false;
    this->ImpulseType = kMessageImpulseTypeDefault;
    this->Frequency = 0.00f;
    this->OnlyApplyOncePerActivation = false;
    this->ApplyWhenInactive = false;
    this->ApplyWhenUnbalanced = false;
    this->WaitToApplyAfterBalancing = 0.00f;
    this->ChanceOfWeakRandomImpulse = 0.00f;
    this->ChanceOfStrongRandomImpulse = 0.00f;
    this->ChanceOfMeleeMediumRandomImpulse = 0.00f;
    this->PartOverride = kPartPelvis;
    this->UseOverrideImpulseDirection = false;
    this->UseLastAppliedImpulse = false;
    this->EnableClickImpulses = false;
    this->ChanceOfWeakClickImpulse = 0.00f;
    this->ChanceOfStrongClickImpulse = 0.00f;
    this->EnableFBIKTestMode = false;
}


