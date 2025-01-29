#include "EndMateriaSetAllWindow.h"

UEndMateriaSetAllWindow::UEndMateriaSetAllWindow() {
    this->EndCanvasPanel_0 = NULL;
    this->MateriaSet_SelectList = NULL;
    this->MateriaSet_InfoList = NULL;
}

void UEndMateriaSetAllWindow::OnMateriaSetSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndMateriaSetAllWindow::OnMateriaSetSelectedIndexChanged(int32 CellIndex) {
}

void UEndMateriaSetAllWindow::OnMateriaSetPressedItem(int32 CellIndex) {
}

FVector2D UEndMateriaSetAllWindow::OnMateriaSetMeasureItem(int32 CellIndex) {
    return FVector2D{};
}


