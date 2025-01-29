#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "Input/Events.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/UserWidget.h"
#include "EndUserWidget.generated.h"

class UWidget;
class UWidgetAnimation;

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndUserWidget : public UUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bPauseable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bAnimationDuplication;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bSupportsPromotionVideo;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TMap<FName, UWidgetAnimation*> ChachedAnimations;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TMap<FName, UWidgetAnimation*> SharedAnimations;
    
public:
    UEndUserWidget();

    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    void StopAnimationEx(const UWidgetAnimation* InAnimation);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    void StopAnimationByName(FName InAnimationName);
    
    UFUNCTION(BlueprintCallable)
    void StopAllAnimationsEx();
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    void SetZOrderInViewport(int32 InZOrder);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    void SetRotationInScene(FRotator InRotation);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    void SetPlaybackSpeedEx(const UWidgetAnimation* InAnimation, float PlaybackSpeed);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    void SetPlaybackSpeedByName(FName InAnimationName, float PlaybackSpeed);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    void SetNumLoopsToPlayEx(const UWidgetAnimation* InAnimation, int32 NumLoopsToPlay);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    void SetNumLoopsToPlayByName(FName InAnimationName, int32 NumLoopsToPlay);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    void SetLocationInScene(FVector InLocation);
    
    UFUNCTION(BlueprintCallable)
    bool SetFocusToChild(UWidget* InWidget, EFocusCause InFocusCause);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    void ReverseAnimationEx(const UWidgetAnimation* InAnimation);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    void ReverseAnimationByName(FName InAnimationName);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    void RemoveFromViewportEx();
    
    UFUNCTION(BlueprintCallable)
    void PushToFocusStack();
    
    UFUNCTION(BlueprintCallable)
    void PopFromFocusStack();
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    void PlayAnimationToEx(UWidgetAnimation* InAnimation, float StartAtTime, float EndAtTime, int32 NumLoopsToPlay, TEnumAsByte<EUMGSequencePlayMode::Type> PlayMode, float PlaybackSpeed);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    bool PlayAnimationToByName(FName InAnimationName, float StartAtTime, float EndAtTime, int32 NumLoopsToPlay, TEnumAsByte<EUMGSequencePlayMode::Type> PlayMode, float PlaybackSpeed);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    void PlayAnimationExAutoReverse(UWidgetAnimation* InAnimation, float StartAtTime, int32 NumLoopsToPlay, TEnumAsByte<EUMGSequencePlayMode::Type> PlayMode, float PlaybackSpeed, float ReverseSpeed);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    void PlayAnimationEx(UWidgetAnimation* InAnimation, float StartAtTime, int32 NumLoopsToPlay, TEnumAsByte<EUMGSequencePlayMode::Type> PlayMode, float PlaybackSpeed);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    bool PlayAnimationByName(FName InAnimationName, float StartAtTime, int32 NumLoopsToPlay, TEnumAsByte<EUMGSequencePlayMode::Type> PlayMode, float PlaybackSpeed);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    float PauseAnimationEx(const UWidgetAnimation* InAnimation);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    float PauseAnimationByName(FName InAnimationName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsPlayingAnimationIgnoreStopped() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsPlayingAnimationEx() const;
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic, BlueprintPure)
    bool IsInViewportEx() const;
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic, BlueprintPure)
    bool IsAnyAnimationPlayingEx() const;
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    bool IsAnimationPlayingForwardEx(const UWidgetAnimation* InAnimation);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    bool IsAnimationPlayingForwardByName(FName InAnimationName);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic, BlueprintPure)
    bool IsAnimationPlayingEx(const UWidgetAnimation* InAnimation) const;
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic, BlueprintPure)
    bool IsAnimationPlayingByName(FName InAnimationName) const;
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic, BlueprintPure)
    int32 GetZOrderInViewport() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FRotator GetRotationInScene() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FVector GetLocationInScene() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    UWidget* GetFocusedChildWidget() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetAnimationStartTimeByName(FName InAnimationName) const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetAnimationEndTimeByName(FName InAnimationName) const;
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic, BlueprintPure)
    float GetAnimationCurrentTimeEx(const UWidgetAnimation* InAnimation) const;
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic, BlueprintPure)
    float GetAnimationCurrentTimeByName(FName InAnimationName) const;
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    void AddToViewportEx(int32 ZOrder);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    void AddToScene(const FVector& InLocation, const FRotator& InRotation);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    bool AddToPlayerScreenEx(int32 ZOrder);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    void AddToOffscreen(int32 ZOrder);
    
};

