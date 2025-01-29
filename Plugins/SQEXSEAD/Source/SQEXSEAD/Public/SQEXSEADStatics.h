#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "ESQEXSEADCategoryVolumeLayers.h"
#include "ESQEXSEADRealTimeVoiceEffectTypes.h"
#include "ESQEXSEADSoundOutputPorts.h"
#include "SQEXSEAD_BGMOptions.h"
#include "SQEXSEADStatics.generated.h"

class USQEXSEADAudioComponent;
class USQEXSEADBGMSlotController;
class USceneComponent;
class USoundAttenuation;
class USoundBase;
class USoundConcurrency;

UCLASS(Blueprintable)
class SQEXSEAD_API USQEXSEADStatics : public UObject {
    GENERATED_BODY()
public:
    USQEXSEADStatics();

    UFUNCTION(BlueprintCallable)
    static void SuspendBGM_OptionalFade(float FadeTime);
    
    UFUNCTION(BlueprintCallable)
    static void SuspendBGM();
    
    UFUNCTION(BlueprintCallable)
    static void StopAllCategorySounds(float FadeTime);
    
    UFUNCTION(BlueprintCallable)
    static void StopAllBGM_OptionalFade(float FadeTime);
    
    UFUNCTION(BlueprintCallable)
    static void StopAllBGM();
    
    UFUNCTION(BlueprintCallable)
    static USQEXSEADAudioComponent* SpawnSoundAttachedByName(USoundBase* Sound, USceneComponent* AttachToComponent, FName SoundName, float SwitchValue, int32 ZeroOneSlot, float ZeroOneValue, int32 ExternalID, FName AttachPointName, FVector Location, FRotator Rotation, TEnumAsByte<EAttachLocation::Type> LocationType, bool bStopWhenAttachedToDestroyed, bool bVirtualizePlay, bool bUISound, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy, bool bRecycle, float VibrationVolumeMultiplier, ESQEXSEADSoundOutputPorts OutputPort, ESQEXSEADRealTimeVoiceEffectTypes VoiceEffectType);
    
    UFUNCTION(BlueprintCallable)
    static USQEXSEADAudioComponent* SpawnSoundAttached(USoundBase* Sound, USceneComponent* AttachToComponent, int32 SoundIndex, float SwitchValue, int32 ZeroOneSlot, float ZeroOneValue, int32 ExternalID, FName AttachPointName, FVector Location, FRotator Rotation, TEnumAsByte<EAttachLocation::Type> LocationType, bool bStopWhenAttachedToDestroyed, bool bVirtualizePlay, bool bUISound, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy, bool bRecycle, float VibrationVolumeMultiplier, ESQEXSEADSoundOutputPorts OutputPort, ESQEXSEADRealTimeVoiceEffectTypes VoiceEffectType);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static USQEXSEADAudioComponent* SpawnSoundAtLocationByName(const UObject* WorldContextObject, USoundBase* Sound, FVector Location, FName SoundName, float SwitchValue, int32 ZeroOneSlot, float ZeroOneValue, int32 ExternalID, FRotator Rotation, bool bVirtualizePlay, bool bUISound, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy, bool bRecycle, float VibrationVolumeMultiplier, ESQEXSEADSoundOutputPorts OutputPort, ESQEXSEADRealTimeVoiceEffectTypes VoiceEffectType);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static USQEXSEADAudioComponent* SpawnSoundAtLocation(const UObject* WorldContextObject, USoundBase* Sound, FVector Location, int32 SoundIndex, float SwitchValue, int32 ZeroOneSlot, float ZeroOneValue, int32 ExternalID, FRotator Rotation, bool bVirtualizePlay, bool bUISound, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy, bool bRecycle, float VibrationVolumeMultiplier, ESQEXSEADSoundOutputPorts OutputPort, ESQEXSEADRealTimeVoiceEffectTypes VoiceEffectType);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta=(WorldContext="WorldContextObject"))
    static USQEXSEADAudioComponent* SpawnSound2DByName(const UObject* WorldContextObject, USoundBase* Sound, FName SoundName, float SwitchValue, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundConcurrency* ConcurrencySettings, bool bPersistAcrossLevelTransition, bool bAutoDestroy, bool bRecycle, float VibrationVolumeMultiplier, ESQEXSEADSoundOutputPorts OutputPort, ESQEXSEADRealTimeVoiceEffectTypes VoiceEffectType);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta=(WorldContext="WorldContextObject"))
    static USQEXSEADAudioComponent* SpawnSound2D(const UObject* WorldContextObject, USoundBase* Sound, int32 SoundIndex, float SwitchValue, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundConcurrency* ConcurrencySettings, bool bPersistAcrossLevelTransition, bool bAutoDestroy, bool bRecycle, float VibrationVolumeMultiplier, ESQEXSEADSoundOutputPorts OutputPort, ESQEXSEADRealTimeVoiceEffectTypes VoiceEffectType);
    
    UFUNCTION(BlueprintCallable)
    static bool SetRenderSpeedRate(float Rate);
    
    UFUNCTION(BlueprintCallable)
    static bool SetRenderGrainSlope(float Slope);
    
    UFUNCTION(BlueprintCallable)
    static bool SetRenderGrainSize(float Size);
    
    UFUNCTION(BlueprintCallable)
    static void SetPadVibrationEnable(bool bEnable);
    
    UFUNCTION(BlueprintCallable)
    static void SetPadSpeakerMasterVolume(float Volume);
    
    UFUNCTION(BlueprintCallable)
    static void SetPadSpeakerEnable(bool bEnable);
    
    UFUNCTION(BlueprintCallable)
    static void SetListenerDynamicAudibleRangeMagnification(float mag);
    
    UFUNCTION(BlueprintCallable)
    static void SetExternalParameter(FName ParamName, float Value);
    
    UFUNCTION(BlueprintCallable)
    static void SetEnableBGMAutoResume(bool bIsEnabled);
    
    UFUNCTION(BlueprintCallable)
    static void SetEnableAudioVolumeUpdate(bool bEnable);
    
    UFUNCTION(BlueprintCallable)
    static void SetEffectPreset(FName presetName, float FadeTime);
    
    UFUNCTION(BlueprintCallable)
    static void ResumeBGM_OptionalFade(float FadeTime);
    
    UFUNCTION(BlueprintCallable)
    static void ResumeBGM();
    
    UFUNCTION(BlueprintCallable)
    static void ResetEffectPreset(float resetFadeTime);
    
    UFUNCTION(BlueprintCallable)
    static void ResetAllCategoryTemporarySettings(float resetFadeTime);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta=(WorldContext="WorldContextObject"))
    static FName PlaySound3DByName(const UObject* WorldContextObject, USoundBase* Sound, FName SoundName, FVector Location, float SwitchValue, int32 ZeroOneSlot, float ZeroOneValue, int32 ExternalID, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bVirtualizePlay, bool bUISound, float VibrationVolumeMultiplier, ESQEXSEADSoundOutputPorts OutputPort, ESQEXSEADRealTimeVoiceEffectTypes VoiceEffectType);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta=(WorldContext="WorldContextObject"))
    static void PlaySound3D(const UObject* WorldContextObject, USoundBase* Sound, FVector Location, int32 SoundIndex, float SwitchValue, int32 ZeroOneSlot, float ZeroOneValue, int32 ExternalID, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bVirtualizePlay, bool bUISound, float VibrationVolumeMultiplier, ESQEXSEADSoundOutputPorts OutputPort, ESQEXSEADRealTimeVoiceEffectTypes VoiceEffectType);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta=(WorldContext="WorldContextObject"))
    static FName PlaySound2DByName(const UObject* WorldContextObject, USoundBase* Sound, FName SoundName, float SwitchValue, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundConcurrency* ConcurrencySettings, float VibrationVolumeMultiplier, ESQEXSEADSoundOutputPorts OutputPort, ESQEXSEADRealTimeVoiceEffectTypes VoiceEffectType);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta=(WorldContext="WorldContextObject"))
    static void PlaySound2D(const UObject* WorldContextObject, USoundBase* Sound, int32 SoundIndex, float SwitchValue, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundConcurrency* ConcurrencySettings, float VibrationVolumeMultiplier, ESQEXSEADSoundOutputPorts OutputPort, ESQEXSEADRealTimeVoiceEffectTypes VoiceEffectType);
    
    UFUNCTION(BlueprintCallable)
    static bool IsPlayingBGM(USoundBase* Sound);
    
    UFUNCTION(BlueprintCallable)
    static bool IsExistSoundInBank(USoundBase* Sound, FName SoundName);
    
    UFUNCTION(BlueprintCallable)
    static bool IsExistSectionBGM(USoundBase* Sound, FName SectionName);
    
    UFUNCTION(BlueprintCallable)
    static bool IsExistModeBGM(USoundBase* Sound, FName ModeName);
    
    UFUNCTION(BlueprintCallable)
    static bool IsEnableAudioVolumeUpdate();
    
    UFUNCTION(BlueprintCallable)
    static float GetSoundDuration(USoundBase* Sound, FName SoundName);
    
    UFUNCTION(BlueprintCallable)
    static float GetRenderSpeedRate();
    
    UFUNCTION(BlueprintCallable)
    static float GetRenderGrainSlope();
    
    UFUNCTION(BlueprintCallable)
    static float GetRenderGrainSize();
    
    UFUNCTION(BlueprintCallable)
    static bool GetPadVibrationEnable();
    
    UFUNCTION(BlueprintCallable)
    static bool GetPadSpeakerEnable();
    
    UFUNCTION(BlueprintCallable)
    static USQEXSEADBGMSlotController* GetBGMSlotController(FName Name);
    
    UFUNCTION(BlueprintCallable)
    static void ExecAudioVolumeEvent(FName ActorName, FName AudioVolumeEventName);
    
    UFUNCTION(BlueprintCallable)
    static USQEXSEADBGMSlotController* CreateBGMSlot(FName Name, FSQEXSEAD_BGMOptions Options);
    
    UFUNCTION(BlueprintCallable)
    static void CategoryCtrl_ToggleDebugMute(FName CategoryName, float FadeTime);
    
    UFUNCTION(BlueprintCallable)
    static void CategoryCtrl_Suspend(FName CategoryName, float FadeOutTime);
    
    UFUNCTION(BlueprintCallable)
    static void CategoryCtrl_Stop(FName CategoryName, float FadeOutTime);
    
    UFUNCTION(BlueprintCallable)
    static void CategoryCtrl_SetVolume(FName CategoryName, float Volume, float FadeTime, TEnumAsByte<ESQEXSEADCategoryVolumeLayers::Type> targerlayer);
    
    UFUNCTION(BlueprintCallable)
    static void CategoryCtrl_SetPitch(FName CategoryName, float Pitch, float FadeTime);
    
    UFUNCTION(BlueprintCallable)
    static void CategoryCtrl_Resume(FName CategoryName, float FadeInTime);
    
    UFUNCTION(BlueprintCallable)
    static float CategoryCtrl_GetVolume(FName CategoryName, TEnumAsByte<ESQEXSEADCategoryVolumeLayers::Type> targerlayer);
    
    UFUNCTION(BlueprintCallable)
    static void CategoryCtrl_DebugMute(FName CategoryName, bool bToBeMuted, float FadeTime);
    
    UFUNCTION(BlueprintCallable)
    static void CallEvent(FName EventName);
    
    UFUNCTION(BlueprintCallable)
    static void AutoSeCtrl_SetEnable(bool Enable);
    
};

