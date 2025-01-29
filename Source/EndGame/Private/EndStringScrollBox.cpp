#include "EndStringScrollBox.h"
#include "Layout/Clipping.h"

UEndStringScrollBox::UEndStringScrollBox() {
    this->bIsVariable = false;
    this->Clipping = EWidgetClipping::ClipToBounds;
    this->ScrollBarVisibility = ESlateVisibility::Visible;
    this->AlwaysShowScrollbar = false;
    this->ScrollBarPosition = EEndMenuScrollBarPosition::RightOrBottom;
    this->WrapTextAt = 0.00f;
    this->Font = NULL;
    this->Outline = true;
    this->DesiredCount = 0;
}

void UEndStringScrollBox::SetWrapTextAt(float InWrapTextAt) {
}

void UEndStringScrollBox::SetText(const FString& InText) {
}

void UEndStringScrollBox::SetShadowOffset(FVector2D InShadowOffset) {
}

void UEndStringScrollBox::SetShadowColorAndOpacity(FLinearColor InShadowColorAndOpacity) {
}

void UEndStringScrollBox::SetScrollOffset(float NewScrollOffset) {
}

void UEndStringScrollBox::SetScrollBarPosition(EEndMenuScrollBarPosition InScrollBarPosition) {
}

void UEndStringScrollBox::SetPadding(FMargin InPadding) {
}

void UEndStringScrollBox::SetOutlineColorAndOpacity(FLinearColor InOutlineColorAndOpacity) {
}

void UEndStringScrollBox::SetOutline(bool bInOutline) {
}

void UEndStringScrollBox::SetFont(UEndFont* InFont) {
}

void UEndStringScrollBox::SetDesiredCount(int32 InDesiredCount) {
}

void UEndStringScrollBox::SetCullingBoundsExtension(FMargin InCullingBoundsExtension) {
}

void UEndStringScrollBox::SetColorAndOpacity(FSlateColor InColorAndOpacity) {
}

void UEndStringScrollBox::ScrollToStart() {
}

void UEndStringScrollBox::ScrollToEnd() {
}

void UEndStringScrollBox::RefreshItems() {
}

FString UEndStringScrollBox::GetText() const {
    return TEXT("");
}

float UEndStringScrollBox::GetScrollOffset() const {
    return 0.0f;
}

ESlateVisibility UEndStringScrollBox::GetScrollBarVisibility() const {
    return ESlateVisibility::Visible;
}

float UEndStringScrollBox::GetMaxScrollOffset(float InScrollHeight) const {
    return 0.0f;
}

int32 UEndStringScrollBox::GetLineCount() const {
    return 0;
}


