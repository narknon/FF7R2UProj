#include "EndUserWidget.h"

UEndUserWidget::UEndUserWidget() : UUserWidget(FObjectInitializer::Get()) {
    this->bPauseable = false;
    this->bAnimationDuplication = false;
    this->bSupportsPromotionVideo = true;
}

void UEndUserWidget::StopAnimationEx(const UWidgetAnimation* InAnimation) {
}

void UEndUserWidget::StopAnimationByName(FName InAnimationName) {
}

void UEndUserWidget::StopAllAnimationsEx() {
}

void UEndUserWidget::SetZOrderInViewport(int32 InZOrder) {
}

void UEndUserWidget::SetRotationInScene(FRotator InRotation) {
}

void UEndUserWidget::SetPlaybackSpeedEx(const UWidgetAnimation* InAnimation, float PlaybackSpeed) {
}

void UEndUserWidget::SetPlaybackSpeedByName(FName InAnimationName, float PlaybackSpeed) {
}

void UEndUserWidget::SetNumLoopsToPlayEx(const UWidgetAnimation* InAnimation, int32 NumLoopsToPlay) {
}

void UEndUserWidget::SetNumLoopsToPlayByName(FName InAnimationName, int32 NumLoopsToPlay) {
}

void UEndUserWidget::SetLocationInScene(FVector InLocation) {
}

bool UEndUserWidget::SetFocusToChild(UWidget* InWidget, EFocusCause InFocusCause) {
    return false;
}

void UEndUserWidget::ReverseAnimationEx(const UWidgetAnimation* InAnimation) {
}

void UEndUserWidget::ReverseAnimationByName(FName InAnimationName) {
}

void UEndUserWidget::RemoveFromViewportEx() {
}

void UEndUserWidget::PushToFocusStack() {
}

void UEndUserWidget::PopFromFocusStack() {
}

void UEndUserWidget::PlayAnimationToEx(UWidgetAnimation* InAnimation, float StartAtTime, float EndAtTime, int32 NumLoopsToPlay, TEnumAsByte<EUMGSequencePlayMode::Type> PlayMode, float PlaybackSpeed) {
}

bool UEndUserWidget::PlayAnimationToByName(FName InAnimationName, float StartAtTime, float EndAtTime, int32 NumLoopsToPlay, TEnumAsByte<EUMGSequencePlayMode::Type> PlayMode, float PlaybackSpeed) {
    return false;
}

void UEndUserWidget::PlayAnimationExAutoReverse(UWidgetAnimation* InAnimation, float StartAtTime, int32 NumLoopsToPlay, TEnumAsByte<EUMGSequencePlayMode::Type> PlayMode, float PlaybackSpeed, float ReverseSpeed) {
}

void UEndUserWidget::PlayAnimationEx(UWidgetAnimation* InAnimation, float StartAtTime, int32 NumLoopsToPlay, TEnumAsByte<EUMGSequencePlayMode::Type> PlayMode, float PlaybackSpeed) {
}

bool UEndUserWidget::PlayAnimationByName(FName InAnimationName, float StartAtTime, int32 NumLoopsToPlay, TEnumAsByte<EUMGSequencePlayMode::Type> PlayMode, float PlaybackSpeed) {
    return false;
}

float UEndUserWidget::PauseAnimationEx(const UWidgetAnimation* InAnimation) {
    return 0.0f;
}

float UEndUserWidget::PauseAnimationByName(FName InAnimationName) {
    return 0.0f;
}

bool UEndUserWidget::IsPlayingAnimationIgnoreStopped() const {
    return false;
}

bool UEndUserWidget::IsPlayingAnimationEx() const {
    return false;
}

bool UEndUserWidget::IsInViewportEx() const {
    return false;
}

bool UEndUserWidget::IsAnyAnimationPlayingEx() const {
    return false;
}

bool UEndUserWidget::IsAnimationPlayingForwardEx(const UWidgetAnimation* InAnimation) {
    return false;
}

bool UEndUserWidget::IsAnimationPlayingForwardByName(FName InAnimationName) {
    return false;
}

bool UEndUserWidget::IsAnimationPlayingEx(const UWidgetAnimation* InAnimation) const {
    return false;
}

bool UEndUserWidget::IsAnimationPlayingByName(FName InAnimationName) const {
    return false;
}

int32 UEndUserWidget::GetZOrderInViewport() const {
    return 0;
}

FRotator UEndUserWidget::GetRotationInScene() const {
    return FRotator{};
}

FVector UEndUserWidget::GetLocationInScene() const {
    return FVector{};
}

UWidget* UEndUserWidget::GetFocusedChildWidget() const {
    return NULL;
}

float UEndUserWidget::GetAnimationStartTimeByName(FName InAnimationName) const {
    return 0.0f;
}

float UEndUserWidget::GetAnimationEndTimeByName(FName InAnimationName) const {
    return 0.0f;
}

float UEndUserWidget::GetAnimationCurrentTimeEx(const UWidgetAnimation* InAnimation) const {
    return 0.0f;
}

float UEndUserWidget::GetAnimationCurrentTimeByName(FName InAnimationName) const {
    return 0.0f;
}

void UEndUserWidget::AddToViewportEx(int32 ZOrder) {
}

void UEndUserWidget::AddToScene(const FVector& InLocation, const FRotator& InRotation) {
}

bool UEndUserWidget::AddToPlayerScreenEx(int32 ZOrder) {
    return false;
}

void UEndUserWidget::AddToOffscreen(int32 ZOrder) {
}


