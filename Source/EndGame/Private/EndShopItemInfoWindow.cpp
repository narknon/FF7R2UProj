#include "EndShopItemInfoWindow.h"

UEndShopItemInfoWindow::UEndShopItemInfoWindow() {
    this->_InfoTextWrapSize = 0.00f;
}

FVector2D UEndShopItemInfoWindow::OnMeasureInfoListSize(int32 CellIndex) {
    return FVector2D{};
}

void UEndShopItemInfoWindow::OnMateriaInfoListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndShopItemInfoWindow::OnListCompareItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndShopItemInfoWindow::OnListCompare1Item(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndShopItemInfoWindow::OnCoreListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}


