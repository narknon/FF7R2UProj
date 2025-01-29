#include "EndCanvasPanelSlot.h"

UEndCanvasPanelSlot::UEndCanvasPanelSlot() {
    this->bAutoSize = false;
    this->bDelayedBuild = false;
    this->ZOrder = 0;
    this->XAngle = 0.00f;
    this->YAngle = 0.00f;
}

void UEndCanvasPanelSlot::SetZOrder(int32 InZOrder) {
}

void UEndCanvasPanelSlot::SetYAngle(float InYAngle) {
}

void UEndCanvasPanelSlot::SetXAngle(float InYAngle) {
}

void UEndCanvasPanelSlot::SetSize(FVector2D InSize) {
}

void UEndCanvasPanelSlot::SetPosition(FVector2D InPosition) {
}

void UEndCanvasPanelSlot::SetOffsets(FMargin InOffset) {
}

void UEndCanvasPanelSlot::SetMinimum(FVector2D InMinimumAnchors) {
}

void UEndCanvasPanelSlot::SetMaximum(FVector2D InMaximumAnchors) {
}

void UEndCanvasPanelSlot::SetLayout(const FAnchorData& InLayoutData) {
}

void UEndCanvasPanelSlot::SetAutoSize(bool InbAutoSize) {
}

void UEndCanvasPanelSlot::SetAnchors(FAnchors InAnchors) {
}

void UEndCanvasPanelSlot::SetAlignment(FVector2D InAlignment) {
}

int32 UEndCanvasPanelSlot::GetZOrder() const {
    return 0;
}

float UEndCanvasPanelSlot::GetYAngle() const {
    return 0.0f;
}

float UEndCanvasPanelSlot::GetXAngle() const {
    return 0.0f;
}

FVector2D UEndCanvasPanelSlot::GetSize() const {
    return FVector2D{};
}

FVector2D UEndCanvasPanelSlot::GetPosition() const {
    return FVector2D{};
}

FMargin UEndCanvasPanelSlot::GetOffsets() const {
    return FMargin{};
}

FAnchorData UEndCanvasPanelSlot::GetLayout() const {
    return FAnchorData{};
}

bool UEndCanvasPanelSlot::GetAutoSize() const {
    return false;
}

FAnchors UEndCanvasPanelSlot::GetAnchors() const {
    return FAnchors{};
}

FVector2D UEndCanvasPanelSlot::GetAlignment() const {
    return FVector2D{};
}


