#include "EndMainItemMenu.h"

UEndMainItemMenu::UEndMainItemMenu() {
    this->LeftMenu = NULL;
    this->ItemList = NULL;
    this->SelectMemberList = NULL;
    this->Detail = NULL;
    this->EquipCell_Top = NULL;
    this->Billboard_Item = NULL;
    this->Billboard_Materia = NULL;
    this->LightBg00 = NULL;
}

void UEndMainItemMenu::OnMemberMenuSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndMainItemMenu::OnMemberMenuPressedItem(int32 CellIndex) {
}

void UEndMainItemMenu::OnLeftMenuSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndMainItemMenu::OnLeftMenuPressedItem(int32 CellIndex) {
}

void UEndMainItemMenu::OnLeftMenuIndexChanged(int32 CellIndex) {
}

void UEndMainItemMenu::OnItemMenuSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndMainItemMenu::OnItemMenuPressedItem(int32 CellIndex) {
}

FVector2D UEndMainItemMenu::OnItemMenuMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndMainItemMenu::OnItemMenuIndexChanged(int32 CellIndex) {
}


