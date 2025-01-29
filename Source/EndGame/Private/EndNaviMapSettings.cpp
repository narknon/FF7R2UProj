#include "EndNaviMapSettings.h"

UEndNaviMapSettings::UEndNaviMapSettings() {
    this->PixelPerCm = 0.14f;
    this->TextureSize = 4096;
    this->SplitNum = EEndNaviMapSplitNum::Split_None;
    this->GenerateMode = EEndNaviMapGenerateMode::SceneCapture;
    this->bHideSkyLight = false;
    this->bMergeVolumePolys = false;
    this->bSkipUpdateTexture = false;
    this->OutlineDistance = 0.00f;
    this->bBackgroundDebug = false;
    this->BackgroundMode = EEndNaviMapBackgroundMode::None;
    this->RenderMode = EEndNaviMapRenderMode::LitNoShadow;
    this->bSilhouetteGenerate = false;
    this->bSilhouetteRemoveHole = false;
    this->SilhouetteLineWidth = 0.00f;
    this->bGridVolume = false;
    this->GridOpenDistance = 4000.00f;
    this->SceneLayer = EDataBaseSceneLayerType::DEFAULT;
}


