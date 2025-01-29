#include "SQEXSEADAutoSeDetectorSettingMisc.h"

FSQEXSEADAutoSeDetectorSettingMisc::FSQEXSEADAutoSeDetectorSettingMisc() {
    this->bEnableTurnDetection = false;
    this->bOverrideTurnSettings = false;
    this->TurnRotVelocityRateThreshold = 0.00f;
    this->TurnVolumeMinRotVelRate = 0.00f;
    this->TurnVolumeMaxRotVelRate = 0.00f;
    this->bEnableHeadRotDetection = false;
    this->bOverrideHeadRotSettings = false;
    this->HeadRotRVelThreshold = 0.00f;
    this->HeadRotVolumeMinRVel = 0.00f;
    this->HeadRotVolumeMaxRVel = 0.00f;
    this->bEnableBowDetection = false;
    this->bOverrideBowSettings = false;
    this->AssumeWaistLessMoveVelocity = 0.00f;
    this->ShoulderRVelThreshold = 0.00f;
    this->bUseShouldersRVelAverage = false;
    this->BowVolumeMinRVel = 0.00f;
    this->BowVolumeMaxRVel = 0.00f;
    this->bEnableRagdollDetection = false;
    this->bOverrideRagdollSettings = false;
    this->RagdollBounceEnoughVel = 0.00f;
    this->RagdollBounceVolumeMinVel = 0.00f;
    this->RagdollBounceVolumeMaxVel = 0.00f;
    this->RagdollFricativeVelThreshold = 0.00f;
    this->RagdollFricativeVolumeMinVel = 0.00f;
    this->RagdollFricativeVolumeMaxVel = 0.00f;
}

