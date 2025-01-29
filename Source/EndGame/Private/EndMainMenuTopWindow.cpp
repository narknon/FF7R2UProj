#include "EndMainMenuTopWindow.h"

UEndMainMenuTopWindow::UEndMainMenuTopWindow() {
    this->PartyLevel = NULL;
    this->TopContent2 = NULL;
    this->Throbber = NULL;
}

bool UEndMainMenuTopWindow::SetupPartySlot(int32 SlotIndex) {
    return false;
}


void UEndMainMenuTopWindow::OnLeftMenuSetupItem(UWidget* ItemWidget, int32 ItemIndex) {
}

void UEndMainMenuTopWindow::OnLeftMenuSelectedIndexChanged(int32 ItemIndex) {
}

void UEndMainMenuTopWindow::OnLeftMenuPressedItem(int32 ItemIndex) {
}


