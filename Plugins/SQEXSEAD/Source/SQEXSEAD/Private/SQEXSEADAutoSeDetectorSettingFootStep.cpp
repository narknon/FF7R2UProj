#include "SQEXSEADAutoSeDetectorSettingFootStep.h"

FSQEXSEADAutoSeDetectorSettingFootStep::FSQEXSEADAutoSeDetectorSettingFootStep() {
    this->bEnableFootStepWalkRun = false;
    this->bOverrideFootStepParameters = false;
    this->FootStepWalkVolumeRangeMin = 0.00f;
    this->FootStepWalkVolumeRangeMax = 0.00f;
    this->FootStepRunVolumeRangeMin = 0.00f;
    this->FootStepRunVolumeRangeMax = 0.00f;
    this->FootStepKEnergyVolumeRangeMin = 0.00f;
    this->FootStepKEnergyVolumeRangeMax = 0.00f;
    this->bEnableFootShuffle = false;
    this->bOverrideFootShuffleParameters = false;
    this->bEnableFootShuffleLessMove = false;
    this->FootShuffleAssumeBodyStopVelocityThreshold = 0.00f;
    this->FootShuffleDetectFootVelocityThreshold = 0.00f;
    this->FootShuffleVolumeRangeMin = 0.00f;
    this->FootShuffleVolumeRangeMax = 0.00f;
    this->bEnableFootShuffleInMotion = false;
    this->FootShuffleInMotionFootAccelThreshold = 0.00f;
    this->FootShuffleInMotionVolumeRangeMin = 0.00f;
    this->FootShuffleInMotionVolumeRangeMax = 0.00f;
    this->bEnableFootShuffleTurn = false;
    this->FootShuffleTurnMoveDirRotVelocityRateThreshold = 0.00f;
    this->FootShuffleTurnFootVelocityThreshold = 0.00f;
    this->FootShuffleTurnVolumeRangeMin = 0.00f;
    this->FootShuffleTurnVolumeRangeMax = 0.00f;
    this->bOverrideLandNormalParameters = false;
    this->bEnableLandAlgoCheckOnlyCharaGrounded = false;
    this->LandNormalAssumeFlyTime = 0.00f;
    this->LandNormalEnoughVelocity = 0.00f;
    this->LandNormalVolumeRangeMin = 0.00f;
    this->LandNormalVolumeRangeMax = 0.00f;
    this->bEnableLandHard = false;
    this->bOverrideLandHardParameters = false;
    this->LandHardAssumeFlyTime = 0.00f;
    this->LandHardEnoughVelocity = 0.00f;
    this->LandHardVolumeRangeMin = 0.00f;
    this->LandHardVolumeRangeMax = 0.00f;
}

