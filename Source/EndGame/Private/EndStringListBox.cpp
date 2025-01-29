#include "EndStringListBox.h"
#include "Layout/Clipping.h"

UEndStringListBox::UEndStringListBox() {
    this->bIsVariable = false;
    this->Clipping = EWidgetClipping::ClipToBounds;
    this->Orientation = Orient_Vertical;
    this->ContentClass = NULL;
    this->DesiredCount = 0;
}

void UEndStringListBox::SetItems(const TArray<FString>& InItems) {
}

void UEndStringListBox::SetDesiredCount(int32 InDesiredCount) {
}

int32 UEndStringListBox::GetSelectedIndex(int32 UserIndex) const {
    return 0;
}


