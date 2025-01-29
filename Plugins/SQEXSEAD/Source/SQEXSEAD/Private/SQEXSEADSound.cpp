#include "SQEXSEADSound.h"
#include "Sound/SoundBase.h"

USQEXSEADSound::USQEXSEADSound() {
    this->bBypassVolumeScaleForPriority = true;
    this->VirtualizationMode = EVirtualizationMode::PlayWhenSilent;
    this->FrequenciesToAnalyze.AddDefaulted(4);
    this->bForcedIgnore = false;
    this->bUseKohrogiAttenuation = false;
    this->ReferenceBank = NULL;
    this->SoundIndex = 0;
    this->bOverrideStopFadeTime = false;
    this->StopFadeTime = 0.50f;
    this->bIsUISound = false;
    this->PauseFadeTime = 0.00f;
    this->bIgnoreListenerDynamicAudibleRangeMagnification = false;
    this->bNoSEAD3DForcePlayOnLoopSound = false;
    this->bIgnoreAudioVolumeAttenuation = false;
    this->bEnableSEADTracingOcclusion = false;
    this->SEADOcclusionTraceChannel = ECC_Visibility;
    this->SoundNameAliasSetting = NULL;
    this->bStreamingAsset_PlatformPS5 = false;
    this->bStreamingAsset_PlatformXSX = false;
    this->EndCustomType = ESQEXSEADENDCustomSoundTypes::Default;
}


