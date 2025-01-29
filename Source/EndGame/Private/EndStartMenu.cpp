#include "EndStartMenu.h"

UEndStartMenu::UEndStartMenu() {
    this->LoadMenuWidgetClass = NULL;
    this->OptionsMenuWidgetClass = NULL;
    this->ButtonAnimationStartTime = 0.77f;
    this->ButtonAnimationDelay = 0.20f;
    this->TrialPlayModeDetailWidgetClass = NULL;
    this->Throbber = NULL;
    this->CachedLoadMenu = NULL;
    this->MainMenu = NULL;
    this->OptionsMenu = NULL;
}

void UEndStartMenu::OnSaveDataSetupItem(UWidget* ItemWidget, int32 ItemIndex) {
}

void UEndStartMenu::OnSaveDataSelectedIndexChanged(int32 ItemIndex) {
}

void UEndStartMenu::OnSaveDataPressedItem(int32 ItemIndex) {
}

void UEndStartMenu::OnSaveDataClicked(UUserWidget* Cell) {
}

void UEndStartMenu::OnSaveDataCancelled() {
}

void UEndStartMenu::OnQuitGame() {
}

void UEndStartMenu::OnOptions() {
}

void UEndStartMenu::OnNewGame() {
}

void UEndStartMenu::OnLoadLatest() {
}

void UEndStartMenu::OnLoadGame() {
}

void UEndStartMenu::OnListMenuSetupItem(UWidget* ItemWidget, int32 ItemIndex) {
}

void UEndStartMenu::OnListMenuSelectedIndexChanged(int32 ItemIndex) {
}

void UEndStartMenu::OnListMenuPressedItem(int32 ItemIndex) {
}

void UEndStartMenu::OnCharaFaceSetupItem(UWidget* ItemWidget, int32 ItemIndex) {
}


