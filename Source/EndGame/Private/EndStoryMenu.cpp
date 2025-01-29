#include "EndStoryMenu.h"

UEndStoryMenu::UEndStoryMenu() {
    this->CurrentAnimation = NULL;
}

void UEndStoryMenu::OnLeftMenuSetupItem(UWidget* ItemWidget, int32 ItemIndex) {
}

void UEndStoryMenu::OnLeftMenuSelectedIndexChanged(int32 ItemIndex) {
}

void UEndStoryMenu::OnLeftMenuPressedItem(int32 ItemIndex) {
}

bool UEndStoryMenu::OnLeftMenuCanFocus(int32 ItemIndex) {
    return false;
}

void UEndStoryMenu::OnChapterChangeBtnSetupItem(UWidget* ItemWidget, int32 ItemIndex) {
}


