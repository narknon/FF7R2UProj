#include "EndColorPickerBar.h"

UEndColorPickerBar::UEndColorPickerBar() {
    this->BlendMode = BLEND_Translucent;
    this->NumBlocks = 32;
    this->Channel = EEndMenuSlateColorPickerChannels::Hue;
    this->Hue = 0.00f;
    this->Saturation = 1.00f;
}

void UEndColorPickerBar::SetSaturation(float InSaturation) {
}

void UEndColorPickerBar::SetOpacity(float InOpacity) {
}

void UEndColorPickerBar::SetNumBlocks(int32 InNumBlocks) {
}

void UEndColorPickerBar::SetHue(float InHue) {
}

void UEndColorPickerBar::SetColorAndOpacity(FLinearColor InColorAndOpacity) {
}

void UEndColorPickerBar::SetChannel(EEndMenuSlateColorPickerChannels InChannel) {
}

void UEndColorPickerBar::SetBlendMode(TEnumAsByte<EBlendMode> InBlendMode) {
}


