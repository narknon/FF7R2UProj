#include "EndListBox.h"

UEndListBox::UEndListBox() {
    this->bIsVariable = false;
    this->Orientation = Orient_Vertical;
    this->ContentClass = NULL;
    this->CursorClass = NULL;
    this->ItemCount = 0;
    this->DesiredCount = 0;
    this->CursorWidget = NULL;
    this->CachedCursor = NULL;
}

void UEndListBox::SetSelectedIndexWithCause(int32 UserIndex, int32 SlotIndex, EFocusCause FocusCause) {
}

void UEndListBox::SetSelectedIndex(int32 UserIndex, int32 SlotIndex) {
}

void UEndListBox::SetPadding(FMargin InPadding) {
}

void UEndListBox::SetItemCount(int32 InItemCount) {
}

void UEndListBox::SetForceHovered(bool bInHovered) {
}

void UEndListBox::SetDesiredCount(int32 InDesiredCount) {
}

void UEndListBox::SetCursorBoundsExtension(FMargin InCursorBoundsExtension) {
}

void UEndListBox::RefreshItems() {
}

void UEndListBox::RefreshItem(int32 Index) {
}

int32 UEndListBox::GetSelectedIndex(int32 UserIndex) const {
    return 0;
}

bool UEndListBox::GetIsForceHovered() const {
    return false;
}

UWidget* UEndListBox::GetCursorWidget() const {
    return NULL;
}

UWidget* UEndListBox::GetChildAt(int32 Index) const {
    return NULL;
}


