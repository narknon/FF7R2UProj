#include "EndMainStatusMenu.h"

UEndMainStatusMenu::UEndMainStatusMenu() {
}

void UEndMainStatusMenu::UpdateStatusPanel(EPlayerType PlayerType) {
}

void UEndMainStatusMenu::UpdatePlayerStatusInfo(int32 CellIndex, EPlayerType PlayerType) {
}

void UEndMainStatusMenu::UpdateEquipmentInfo(int32 CellIndex, EPlayerType PlayerType) {
}

void UEndMainStatusMenu::UpdateDescription(EPlayerType PlayerType) {
}

void UEndMainStatusMenu::SetupDescriptionTitle() {
}

void UEndMainStatusMenu::OnSetupSummonItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndMainStatusMenu::OnSetupStatusItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndMainStatusMenu::OnSetupMagicItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndMainStatusMenu::OnSetupLimitItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndMainStatusMenu::OnSetupAbilityItem(UWidget* ItemWidget, int32 CellIndex) {
}

FVector2D UEndMainStatusMenu::OnMeasureSummonItem(int32 CellIndex) {
    return FVector2D{};
}

FVector2D UEndMainStatusMenu::OnMeasureStatusItem(int32 ItemIndex) {
    return FVector2D{};
}

FVector2D UEndMainStatusMenu::OnMeasureMagicItem(int32 CellIndex) {
    return FVector2D{};
}

FVector2D UEndMainStatusMenu::OnMeasureLimitItem(int32 CellIndex) {
    return FVector2D{};
}

FVector2D UEndMainStatusMenu::OnMeasureAbilityItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndMainStatusMenu::OnLeftMenuSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndMainStatusMenu::OnLeftMenuSelectedIndexChanged(int32 CellIndex) {
}


