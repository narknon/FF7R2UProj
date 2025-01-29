#include "EndNaviMapSettingsAreaMap.h"
#include "EEndNaviMapBackgroundMode.h"
#include "EEndNaviMapGenerateMode.h"
#include "EEndNaviMapRenderMode.h"
#include "EEndNaviMapSplitNum.h"

UEndNaviMapSettingsAreaMap::UEndNaviMapSettingsAreaMap() {
    this->SplitNum = EEndNaviMapSplitNum::Split_MaxCsv;
    this->GenerateMode = EEndNaviMapGenerateMode::SceneCaptureWaterMask;
    this->bMergeVolumePolys = true;
    this->BackgroundMode = EEndNaviMapBackgroundMode::SceneCaptureWaterMask;
    this->RenderMode = EEndNaviMapRenderMode::Lit;
    this->bGridVolume = true;
}


