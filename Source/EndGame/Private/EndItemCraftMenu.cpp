#include "EndItemCraftMenu.h"

UEndItemCraftMenu::UEndItemCraftMenu() {
    this->EndCanvasPanel_0 = NULL;
    this->LeftMenu = NULL;
    this->Pnl_CraftSelect = NULL;
    this->EquipCell_Top = NULL;
    this->Billboard_Craft = NULL;
    this->AccessoryInfo = NULL;
    this->CategoryBtn = NULL;
    this->Craft_Window = NULL;
    this->Craft_Level = NULL;
    this->Popup = NULL;
}

void UEndItemCraftMenu::OnStatusListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndItemCraftMenu::OnLeftMenuSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndItemCraftMenu::OnLeftMenuSelectedIndexChanged(int32 CellIndex) {
}

void UEndItemCraftMenu::OnLeftMenuPressedItem(int32 CellIndex) {
}

FVector2D UEndItemCraftMenu::OnLeftMenuMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndItemCraftMenu::OnCraftRecipeMenuSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndItemCraftMenu::OnCraftRecipeMenuSelectedIndexChanged(int32 CellIndex) {
}

void UEndItemCraftMenu::OnCategorySwitch2SetupItem(UWidget* ItemWidget, int32 CellIndex) {
}


