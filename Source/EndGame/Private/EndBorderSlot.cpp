#include "EndBorderSlot.h"

UEndBorderSlot::UEndBorderSlot() {
    this->HorizontalAlignment = HAlign_Fill;
    this->VerticalAlignment = VAlign_Fill;
}

void UEndBorderSlot::SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment) {
}

void UEndBorderSlot::SetPadding(FMargin InPadding) {
}

void UEndBorderSlot::SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment) {
}


