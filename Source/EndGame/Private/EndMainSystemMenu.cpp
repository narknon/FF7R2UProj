#include "EndMainSystemMenu.h"

UEndMainSystemMenu::UEndMainSystemMenu() {
    this->OptionsMenuWidgetClass = NULL;
    this->ChapterSelectWidgetClass = NULL;
    this->PlaylogList = NULL;
    this->OptionsMenu = NULL;
}

void UEndMainSystemMenu::OnLeftMenuSetupItem(UWidget* ItemWidget, int32 ItemIndex) {
}

void UEndMainSystemMenu::OnLeftMenuPressedItem(int32 ItemIndex) {
}


