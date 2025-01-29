#include "EndNumberLabel.h"

UEndNumberLabel::UEndNumberLabel() {
    this->BlendMode = BLEND_Translucent;
    this->Value = 0;
    this->Justification = ETextJustify::Left;
    this->MinDigits = 0;
    this->FontIndex = 0;
    this->Spacing = 0;
    this->bZeroFilled = false;
}

void UEndNumberLabel::SetZeroFilled(bool bInZeroFilled) {
}

void UEndNumberLabel::SetValue(int32 InValue) {
}

void UEndNumberLabel::SetSpacing(int32 InSpacing) {
}

void UEndNumberLabel::SetOpacity(float InOpacity) {
}

void UEndNumberLabel::SetMinDigits(int32 InMinDigits) {
}

void UEndNumberLabel::SetJustification(TEnumAsByte<ETextJustify::Type> InJustification) {
}

void UEndNumberLabel::SetFontIndex(int32 InFontIndex) {
}

void UEndNumberLabel::SetColorAndOpacity(FLinearColor InColorAndOpacity) {
}

void UEndNumberLabel::SetBlendMode(TEnumAsByte<EBlendMode> InBlendMode) {
}


