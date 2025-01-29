#include "EndAreaMapMenu.h"

UEndAreaMapMenu::UEndAreaMapMenu() {
    this->AreaEffectWidgetClass = NULL;
    this->WorldMapWidgetClass = NULL;
    this->NaviMap = NULL;
    this->NaviCursor = NULL;
    this->TargetIcon = NULL;
    this->TargetButton = NULL;
    this->CircleCanvas = NULL;
    this->InfoWindow = NULL;
    this->BlockFrame = NULL;
    this->BlockCaption = NULL;
    this->PlayerPosIndicator = NULL;
    this->TargetPosIndicator = NULL;
    this->CurrentAnimation = NULL;
    this->Throbber = NULL;
}

void UEndAreaMapMenu::OnStoryListBoxSetupItem(UWidget* ItemWidget, int32 ItemIndex) {
}

void UEndAreaMapMenu::OnReportListSetupItem(UWidget* ItemWidget, int32 ItemIndex) {
}

void UEndAreaMapMenu::OnLeftMenuSetupItem(UWidget* ItemWidget, int32 ItemIndex) {
}

void UEndAreaMapMenu::OnLeftMenuSelectedIndexChanged(int32 ItemIndex) {
}


