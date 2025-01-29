#include "EndMagicWindow.h"

UEndMagicWindow::UEndMagicWindow() {
    this->EndCanvasPanel_0 = NULL;
    this->CategoryTitle = NULL;
    this->MemberList = NULL;
    this->EquipInfo = NULL;
    this->Magic_SelectList = NULL;
    this->Recover_List = NULL;
    this->Txt_TitleValue_Mp = NULL;
}

void UEndMagicWindow::OnRecoverListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndMagicWindow::OnRecoverListSelectedIndexChanged(int32 CellIndex) {
}

void UEndMagicWindow::OnRecoverListPressedItem(int32 CellIndex) {
}

FVector2D UEndMagicWindow::OnRecoverListMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndMagicWindow::OnMemberListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndMagicWindow::OnMemberListSelectedIndexChanged(int32 CellIndex) {
}

void UEndMagicWindow::OnMemberListPressedItem(int32 CellIndex) {
}

FVector2D UEndMagicWindow::OnMemberListMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndMagicWindow::OnMagicListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndMagicWindow::OnMagicListSelectedIndexChanged(int32 CellIndex) {
}

void UEndMagicWindow::OnMagicListPressedItem(int32 CellIndex) {
}

FVector2D UEndMagicWindow::OnMagicListMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

bool UEndMagicWindow::OnMagicButtonUnhover() {
    return false;
}

bool UEndMagicWindow::OnMagicButtonHover() {
    return false;
}


