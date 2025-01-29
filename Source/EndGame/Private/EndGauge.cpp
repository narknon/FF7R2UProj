#include "EndGauge.h"

UEndGauge::UEndGauge() {
    this->Value = 0.00f;
    this->PreviewValue = 0.00f;
    this->MaxValue = 0.00f;
    this->BarFillType = EProgressBarFillType::LeftToRight;
}

void UEndGauge::SetValue(float InValue) {
}

void UEndGauge::SetPreviewValue(float InPreviewValue) {
}

void UEndGauge::SetPreviewColorAndOpacity(FLinearColor InColor) {
}

void UEndGauge::SetMaxValue(float InMaxValue) {
}

void UEndGauge::SetFillEndColorAndOpacity(FLinearColor InColor) {
}

void UEndGauge::SetFillColorAndOpacity(FLinearColor InColor) {
}


