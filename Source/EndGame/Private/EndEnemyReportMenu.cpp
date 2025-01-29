#include "EndEnemyReportMenu.h"

UEndEnemyReportMenu::UEndEnemyReportMenu() {
    this->_DetailFlavorTipsDescriptionScrollBox = NULL;
    this->_DetailScrollTextBlock = NULL;
    this->DetailFadeInOutLenght = 0.20f;
    this->CharacterDitherFadeInLenght = 0.20f;
    this->RotationYMin = -20.00f;
    this->RotationYMax = 5.00f;
    this->RotationYDefault = 0.00f;
    this->RotationXSpeed = 80.00f;
    this->RotationYSpeed = 80.00f;
}

void UEndEnemyReportMenu::OnStealListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndEnemyReportMenu::OnResistanceListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndEnemyReportMenu::OnResistanceIconListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndEnemyReportMenu::OnRareDropItemListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndEnemyReportMenu::OnEnemyListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndEnemyReportMenu::OnEnemyListSelectedIndexChanged(int32 CellIndex) {
}

void UEndEnemyReportMenu::OnEnemyListPressedItem(int32 CellIndex) {
}

FVector2D UEndEnemyReportMenu::OnEnemyListMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndEnemyReportMenu::OnDropItemListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndEnemyReportMenu::OnDetailBattleLogListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndEnemyReportMenu::OnDetailAreaListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndEnemyReportMenu::OnDebuffIconSetup(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndEnemyReportMenu::OnBuffIconSetup(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndEnemyReportMenu::OnBattleLogListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndEnemyReportMenu::OnAreaListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndEnemyReportMenu::OnActionTypeListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndEnemyReportMenu::OnAbilityListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}


