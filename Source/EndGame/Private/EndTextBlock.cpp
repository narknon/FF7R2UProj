#include "EndTextBlock.h"

UEndTextBlock::UEndTextBlock() {
    this->bIsVariable = false;
    this->Justification = ETextJustify::Left;
    this->AutoWrapText = false;
    this->AutoShrinkText = true;
    this->WrapTextAt = 0.00f;
    this->LineHeightPercentage = 1.00f;
    this->Gradient = false;
    this->Font = NULL;
    this->MinDesiredWidth = 0.00f;
    this->BlendMode = BLEND_Translucent;
    this->Outline = true;
    this->AllowMacro = true;
    this->LeftAlignedCenter = false;
    this->AutoUpdateButtons = true;
    this->ColoredButtons = false;
    this->ButtonLayoutMode = EEndMenuTextButtonLayoutMode::Middle;
}

void UEndTextBlock::SetWrapTextAt(float InWrapTextAt) {
}

void UEndTextBlock::SetText(const FString& InText) {
}

void UEndTextBlock::SetShadowOffset(FVector2D InShadowOffset) {
}

void UEndTextBlock::SetShadowColorAndOpacity(FLinearColor InShadowColorAndOpacity) {
}

void UEndTextBlock::SetOutlineColorAndOpacity(FLinearColor InOutlineColorAndOpacity) {
}

void UEndTextBlock::SetOutline(bool bInOutline) {
}

void UEndTextBlock::SetOpacity(float InOpacity) {
}

void UEndTextBlock::SetMinDesiredWidth(float InMinDesiredWidth) {
}

void UEndTextBlock::SetLeftAlignedCenter(bool bInLeftAlignedCenter) {
}

void UEndTextBlock::SetJustification(TEnumAsByte<ETextJustify::Type> InJustification) {
}

void UEndTextBlock::SetFont(UEndFont* InFont) {
}

void UEndTextBlock::SetColoredButtons(bool bInColoredButtons) {
}

void UEndTextBlock::SetColorAndOpacity(FSlateColor InColorAndOpacity) {
}

void UEndTextBlock::SetButtonLayoutMode(EEndMenuTextButtonLayoutMode InButtonLayoutMode) {
}

void UEndTextBlock::SetBottomOpacity(float InOpacity) {
}

void UEndTextBlock::SetBottomColorAndOpacity(FSlateColor InColorAndOpacity) {
}

void UEndTextBlock::SetBlendMode(TEnumAsByte<EBlendMode> InBlendMode) {
}

void UEndTextBlock::SetAutoWrapText(bool bInAutoWrapText) {
}

void UEndTextBlock::SetAutoUpdateButtons(bool bInAutoUpdateButtons) {
}

void UEndTextBlock::SetAutoShrinkText(bool bInAutoShrinkText) {
}

void UEndTextBlock::SetAllowMacro(bool bInAllowMacro) {
}

FString UEndTextBlock::GetText() const {
    return TEXT("");
}


