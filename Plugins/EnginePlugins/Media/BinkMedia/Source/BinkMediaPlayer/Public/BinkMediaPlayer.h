#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "MediaPlayerInterface.h"
#include "EBinkMediaPlayerBinkBufferModes.h"
#include "EBinkMediaPlayerBinkDrawStyle.h"
#include "EBinkMediaPlayerBinkSoundTrack.h"
#include "BinkMediaPlayer.generated.h"

class UMediaPlaylist;
class UTexture;

UCLASS(Blueprintable)
class BINKMEDIAPLAYER_API UBinkMediaPlayer : public UObject, public IMediaPlayerInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 Looping: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 StartImmediately: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 DelayedOpen: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector2D BinkDestinationUpperLeft;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector2D BinkDestinationLowerRight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString URL;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<EBinkMediaPlayerBinkBufferModes> BinkBufferMode;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<EBinkMediaPlayerBinkSoundTrack> BinkSoundTrack;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 BinkSoundTrackStart;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<EBinkMediaPlayerBinkDrawStyle> BinkDrawStyle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 BinkLayerDepth;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    UMediaPlaylist* Playlist;
    
    UBinkMediaPlayer();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool SupportsSeeking() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool SupportsScrubbing() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool SupportsRate(float Rate, bool Unthinned) const;
    
    UFUNCTION(BlueprintCallable)
    void Stop();
    
    UFUNCTION(BlueprintCallable)
    void SetVolume(float Rate);
    
    UFUNCTION(BlueprintCallable)
    bool SetRate(float Rate);
    
    UFUNCTION(BlueprintCallable)
    bool SetLooping(bool InLooping);
    
    UFUNCTION(BlueprintCallable)
    bool Seek(const FTimespan& InTime);
    
    UFUNCTION(BlueprintCallable)
    bool Rewind();
    
    UFUNCTION(BlueprintCallable)
    bool Play();
    
    UFUNCTION(BlueprintCallable)
    bool Pause();
    
    UFUNCTION(BlueprintCallable)
    bool OpenUrl(const FString& NewUrl);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsStopped() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsPlaying() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsPaused() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsLooping() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsInitialized() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FString GetUrl() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FTimespan GetTime() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetRate() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FTimespan GetDuration() const;
    
    UFUNCTION(BlueprintCallable)
    void Draw(UTexture* Texture, bool tonemap, int32 out_nits, float Alpha, bool srgb_decode, bool hdr);
    
    UFUNCTION(BlueprintCallable)
    void CloseUrl();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool CanPlay() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool CanPause() const;
    

    // Fix for true pure virtual functions not being implemented
};

