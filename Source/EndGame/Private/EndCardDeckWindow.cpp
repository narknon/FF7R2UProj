#include "EndCardDeckWindow.h"

UEndCardDeckWindow::UEndCardDeckWindow() {
    this->Pnl_Menu_Card = NULL;
    this->Pnl_Bg = NULL;
    this->Billboard_Bg = NULL;
    this->DeckList = NULL;
    this->CardList_Player = NULL;
    this->EnemyInformation = NULL;
    this->Card_View = NULL;
    this->Card_EditList = NULL;
    this->GameInformation = NULL;
}

void UEndCardDeckWindow::OnCradDeckListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndCardDeckWindow::OnCradDeckListSelectedIndexChanged(int32 CellIndex) {
}

void UEndCardDeckWindow::OnCradDeckListPressedItem(int32 CellIndex) {
}

FVector2D UEndCardDeckWindow::OnCradDeckListMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndCardDeckWindow::OnCradDeckEditSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndCardDeckWindow::OnCradDeckEditSelectedIndexChanged(int32 CellIndex) {
}

void UEndCardDeckWindow::OnCradDeckEditPressedItem(int32 CellIndex) {
}

FVector2D UEndCardDeckWindow::OnCradDeckEditMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndCardDeckWindow::OnCradDeckEditContentsSetupItem(int32 VerticalIndex, UWidget* ItemWidget, int32 CellIndex) {
}

void UEndCardDeckWindow::OnCradDeckEditContentsSelectedIndexChanged(int32 VerticalIndex, int32 CellIndex) {
}

void UEndCardDeckWindow::OnCradDeckEditContentsPressedItem(int32 VerticalIndex, int32 CellIndex) {
}

void UEndCardDeckWindow::OnCradDeckContentsSelectedIndexChanged(int32 CellIndex) {
}

void UEndCardDeckWindow::OnCradDeckContentsPressedItem(int32 CellIndex) {
}

FVector2D UEndCardDeckWindow::OnCradDeckContentsMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndCardDeckWindow::OnCradDeckContentsListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}


