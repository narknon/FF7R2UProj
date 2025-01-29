#include "EndItemWindow.h"

UEndItemWindow::UEndItemWindow() {
    this->EndCanvasPanel_0 = NULL;
    this->Billboard_Item = NULL;
    this->EquipInfo = NULL;
    this->CategoryTitle = NULL;
    this->ItemList = NULL;
    this->EquipInfoDetail_Ability = NULL;
    this->EquipInfoDetail_Core = NULL;
    this->EquipInfoDetail_Accessory = NULL;
    this->EquipInfoDetail_Materia = NULL;
    this->Recover_List = NULL;
    this->Sort = NULL;
    this->CategoryList = NULL;
    this->CraftAreaInfo = NULL;
}

void UEndItemWindow::OnRecoverListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndItemWindow::OnRecoverListSelectedIndexChanged(int32 CellIndex) {
}

void UEndItemWindow::OnRecoverListPressedItem(int32 CellIndex) {
}

FVector2D UEndItemWindow::OnRecoverListMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndItemWindow::OnItemTabListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndItemWindow::OnItemTabListSelectedIndexChanged(int32 CellIndex) {
}

FVector2D UEndItemWindow::OnItemTabListMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndItemWindow::OnItemListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndItemWindow::OnItemListSelectedIndexChanged(int32 CellIndex) {
}

void UEndItemWindow::OnItemListPressedItem(int32 CellIndex) {
}

FVector2D UEndItemWindow::OnItemListMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndItemWindow::OnItemCategoryListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndItemWindow::OnItemCategoryListSelectedIndexChanged(int32 CellIndex) {
}

void UEndItemWindow::OnItemCategoryListPressedItem(int32 CellIndex) {
}

FVector2D UEndItemWindow::OnItemCategoryListMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

bool UEndItemWindow::OnItemButtonUnhover() {
    return false;
}

bool UEndItemWindow::OnItemButtonHover() {
    return false;
}


