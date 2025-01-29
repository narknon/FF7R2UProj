#include "SQEX_BonamikWind_Desc.h"

FSQEX_BonamikWind_Desc::FSQEX_BonamikWind_Desc() {
    this->mEnable = false;
    this->mWindConstantSpeed = 0.00f;
    this->mSceneScale = 0.00f;
    this->mConeAngle = 0.00f;
    this->mConeAngleCosine = 0.00f;
    this->mType = ESQEX_BonamikWind_DirectionalSource;
    this->mDistanceModulationNear = 0.00f;
    this->mDistanceModulationFar = 0.00f;
    this->mTimeModulationStart = 0.00f;
    this->mTimeModulationEnd = 0.00f;
    this->mPulseHorizontalVariation = 0.00f;
    this->mPulseVerticalVariation = 0.00f;
    this->mWindSpeed = 0.00f;
    this->mPulseFrequency = 0.00f;
    this->mPulseLength = 0.00f;
    this->mNoiseStrength = 0.00f;
    this->mNoiseSpatial = 0.00f;
    this->mNoiseTemporal = 0.00f;
    this->mNoiseSeed = 0;
}

