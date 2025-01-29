#include "EndStatusWindow.h"

UEndStatusWindow::UEndStatusWindow() {
    this->EndCanvasPanel_0 = NULL;
    this->CategoryTitle = NULL;
    this->MemberList = NULL;
    this->EquipInfo_01 = NULL;
    this->EquipInfo_02 = NULL;
    this->EquipInfo_03 = NULL;
    this->StatusList_IconList_01 = NULL;
    this->Title_Atk_Attribution = NULL;
    this->Title_Def_Attribution = NULL;
    this->StatusList = NULL;
    this->StatusList_IconList_02 = NULL;
    this->StatusList_IconList_03 = NULL;
    this->StatusList_IconList_04 = NULL;
    this->StatusList_IconList_05 = NULL;
    this->StatusAbilityList = NULL;
}

void UEndStatusWindow::OnWeaponCoreSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

FVector2D UEndStatusWindow::OnWeaponCoreMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndStatusWindow::OnSummonSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

FVector2D UEndStatusWindow::OnSummonMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndStatusWindow::OnPassiveListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

FVector2D UEndStatusWindow::OnPassiveListMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndStatusWindow::OnMemberListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndStatusWindow::OnMemberListSelectedIndexChanged(int32 CellIndex) {
}

void UEndStatusWindow::OnMemberListPressedItem(int32 CellIndex) {
}

FVector2D UEndStatusWindow::OnMemberListMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndStatusWindow::OnMagicSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

FVector2D UEndStatusWindow::OnMagicMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndStatusWindow::OnLimitSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

FVector2D UEndStatusWindow::OnLimitMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndStatusWindow::OnChainActionSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

FVector2D UEndStatusWindow::OnChainActionMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndStatusWindow::OnChainAbilitySetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

FVector2D UEndStatusWindow::OnChainAbilityMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndStatusWindow::OnAbilitySetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

FVector2D UEndStatusWindow::OnAbilityMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndStatusWindow::OnAbilityListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

FVector2D UEndStatusWindow::OnAbilityListMeasureItem(int32 CellIndex) {
    return FVector2D{};
}


