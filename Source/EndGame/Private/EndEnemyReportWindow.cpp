#include "EndEnemyReportWindow.h"

UEndEnemyReportWindow::UEndEnemyReportWindow() {
    this->MenuFadeInOutLenght = 0.00f;
    this->CharacterDitherFadeInLenght = 0.00f;
    this->RotationYMin = 0.00f;
    this->RotationYMax = 0.00f;
    this->RotationYDefault = 0.00f;
    this->RotationXSpeed = 0.00f;
    this->RotationYSpeed = 0.00f;
    this->EndCanvasPanel_0 = NULL;
    this->CategoryTitle = NULL;
    this->LeftMenuScrollBox = NULL;
    this->Detail = NULL;
    this->NewSenseDetail = NULL;
}

void UEndEnemyReportWindow::OnEnemyBookListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndEnemyReportWindow::OnEnemyBookListSelectedIndexChanged(int32 CellIndex) {
}

void UEndEnemyReportWindow::OnEnemyBookListPressedItem(int32 CellIndex) {
}

FVector2D UEndEnemyReportWindow::OnEnemyBookListMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndEnemyReportWindow::OnBattleLogListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndEnemyReportWindow::OnAreaListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndEnemyReportWindow::OnActionTypeListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}


