#include "EndMainMagicMenu.h"

UEndMainMagicMenu::UEndMainMagicMenu() {
    this->Txt_Category_Title = NULL;
    this->Billboard_CategoryImg = NULL;
    this->LeftMenu = NULL;
    this->ItemList = NULL;
    this->SelectMemberList = NULL;
    this->Detail = NULL;
    this->EquipCell_Top = NULL;
    this->Billboard_CharaImg = NULL;
}

void UEndMainMagicMenu::OnMagicMenuSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndMainMagicMenu::OnMagicMenuPressedItem(int32 CellIndex) {
}

void UEndMainMagicMenu::OnMagicMenuIndexChanged(int32 CellIndex) {
}

void UEndMainMagicMenu::OnLeftMenuSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndMainMagicMenu::OnLeftMenuPressedItem(int32 CellIndex) {
}

void UEndMainMagicMenu::OnLeftMenuIndexChanged(int32 CellIndex) {
}


