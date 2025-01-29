#include "EndMainTopMenu.h"

UEndMainTopMenu::UEndMainTopMenu() {
    this->PartyLevel = NULL;
    this->Throbber = NULL;
}

bool UEndMainTopMenu::SetupPartySlot(int32 SlotIndex) {
    return false;
}


void UEndMainTopMenu::OnLeftMenuSetupItem(UWidget* ItemWidget, int32 ItemIndex) {
}

void UEndMainTopMenu::OnLeftMenuSelectedIndexChanged(int32 ItemIndex) {
}

void UEndMainTopMenu::OnLeftMenuPressedItem(int32 ItemIndex) {
}


