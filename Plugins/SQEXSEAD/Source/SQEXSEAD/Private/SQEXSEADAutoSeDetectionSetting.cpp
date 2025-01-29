#include "SQEXSEADAutoSeDetectionSetting.h"

USQEXSEADAutoSeDetectionSetting::USQEXSEADAutoSeDetectionSetting() {
    this->bUseAnalyzerSettingForMotionOnlyMode = false;
    this->bDistanceClippingEnable = true;
    this->ClippingDistance = 40.00f;
    this->bFollowMeshVisibility = true;
    this->bForceDetectListenerTeleportRuntime = true;
}


