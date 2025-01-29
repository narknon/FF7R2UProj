#include "EndPartySetSwitch.h"

UEndPartySetSwitch::UEndPartySetSwitch() {
    this->EndCanvasPanel_0 = NULL;
    this->EndTextBlock = NULL;
    this->PartySetList = NULL;
}

void UEndPartySetSwitch::OnPartySetSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndPartySetSwitch::OnPartySetSelectedIndexChanged(int32 CellIndex) {
}

FVector2D UEndPartySetSwitch::OnPartySetMeasureItem(int32 CellIndex) {
    return FVector2D{};
}


