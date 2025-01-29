#include "EndButton.h"

UEndButton::UEndButton() {
    this->ClickMethod = EButtonClickMethod::DownAndUp;
    this->TouchMethod = EButtonTouchMethod::DownAndUp;
    this->PressMethod = EButtonPressMethod::DownAndUp;
    this->IsFocusable = true;
    this->IsForceHovered = false;
    this->CanPress = true;
    this->IgnoreKeyRepeat = false;
    this->FakeDisabled = false;
}

void UEndButton::SetTouchMethod(TEnumAsByte<EButtonTouchMethod::Type> InTouchMethod) {
}

void UEndButton::SetStyle(const FButtonStyle& InStyle) {
}

void UEndButton::SetPressMethod(TEnumAsByte<EButtonPressMethod::Type> InPressMethod) {
}

void UEndButton::SetIsFocusable(bool bInIsFocusable) {
}

void UEndButton::SetIgnoreKeyRepeat(bool bInIgnoreKeyRepeat) {
}

void UEndButton::SetHelpText(const FString& InText) {
}

void UEndButton::SetGuideText(const FString& InText) {
}

void UEndButton::SetForceHovered(bool bInHovered) {
}

void UEndButton::SetFakeDisabled(bool bInFakeDisabled) {
}

void UEndButton::SetColorAndOpacity(FLinearColor InColorAndOpacity) {
}

void UEndButton::SetClickMethod(TEnumAsByte<EButtonClickMethod::Type> InClickMethod) {
}

void UEndButton::SetCanPress(bool bInCanPress) {
}

void UEndButton::SetBackgroundColor(FLinearColor InBackgroundColor) {
}

void UEndButton::Release() {
}

void UEndButton::Press() {
}

bool UEndButton::IsPressed() const {
    return false;
}

bool UEndButton::IsFakeDisabled() const {
    return false;
}

bool UEndButton::GetIsForceHovered() const {
    return false;
}

bool UEndButton::GetIsFocusable() const {
    return false;
}

bool UEndButton::GetIgnoreKeyRepeat() const {
    return false;
}

bool UEndButton::GetCanPress() const {
    return false;
}


