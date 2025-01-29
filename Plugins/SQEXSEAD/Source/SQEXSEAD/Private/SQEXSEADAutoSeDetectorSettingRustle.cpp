#include "SQEXSEADAutoSeDetectorSettingRustle.h"

FSQEXSEADAutoSeDetectorSettingRustle::FSQEXSEADAutoSeDetectorSettingRustle() {
    this->bEnableArmRustleElbow = false;
    this->bOverrideArmRustleElbowVolumeRanges = false;
    this->ArmRustleElbowRVelThreshold = 0.00f;
    this->ArmRustleElbowRelativeVelocityVolumeRangeMin = 0.00f;
    this->ArmRustleElbowRelativeVelocityVolumeRangeMax = 0.00f;
    this->bEnableArmRustleHandWave = false;
    this->bOverrideArmRustleHandWaveParameters = false;
    this->ArmRustleHandWaveRVelThreshold = 0.00f;
    this->ArmRustleHandWaveVolumeRangeMin = 0.00f;
    this->ArmRustleHandWaveVolumeRangeMax = 0.00f;
    this->bEnableFootRustleCrotch = false;
    this->bOverrideFootRustleCrotchParameters = false;
    this->FootRustleCrotchFTRelVelThresholdWalk = 0.00f;
    this->FootRustleCrotchFTRelVelThresholdRun = 0.00f;
    this->FootRustleCrotchVolumeRangeMin = 0.00f;
    this->FootRustleCrotchVolumeRangeMax = 0.00f;
    this->bEnableFootRustle = false;
    this->bOverrideFootRustleParameters = false;
    this->FootRustleRVelThresholdWalk = 0.00f;
    this->FootRustleRVelThresholdRun = 0.00f;
    this->FootRustleVolumeRangeMin = 0.00f;
    this->FootRustleVolumeRangeMax = 0.00f;
    this->bEnableFootRustleBend = false;
    this->bOverrideFootRustleBendParameters = false;
    this->FootRustleBendBendThreshold = 0.00f;
    this->FootRustleBendStretchThreshold = 0.00f;
    this->FootRustleBendVolumeRangeMin = 0.00f;
    this->FootRustleBendVolumeRangeMax = 0.00f;
    this->DetectionSuppressTimeDefault = 0.00f;
    this->DetectionSuppressTimeForFast = 0.00f;
}

