#include "EndMemberChangeWindow.h"

UEndMemberChangeWindow::UEndMemberChangeWindow() {
    this->EndCanvasPanel_0 = NULL;
    this->List_1 = NULL;
    this->List_2 = NULL;
    this->Pnl_Arrow = NULL;
    this->PartySet_Switch = NULL;
    this->Detail = NULL;
}

void UEndMemberChangeWindow::OnReserveMemberSelectedIndexChanged(int32 CellIndex) {
}

void UEndMemberChangeWindow::OnReserveMemberPressedItem(int32 CellIndex) {
}

FVector2D UEndMemberChangeWindow::OnReserveMemberMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndMemberChangeWindow::OnReserveMemberListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndMemberChangeWindow::OnBattleMemberSelectedIndexChanged(int32 CellIndex) {
}

void UEndMemberChangeWindow::OnBattleMemberPressedItem(int32 CellIndex) {
}

FVector2D UEndMemberChangeWindow::OnBattleMemberMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndMemberChangeWindow::OnBattleMemberListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}


