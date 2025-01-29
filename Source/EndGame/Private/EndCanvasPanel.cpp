#include "EndCanvasPanel.h"
#include "Components/SlateWrapperTypes.h"

UEndCanvasPanel::UEndCanvasPanel() {
    this->bIsVariable = false;
    this->Visibility = ESlateVisibility::SelfHitTestInvisible;
    this->bExplicitChildZOrder = false;
    this->ProjectionMode = ECameraProjectionMode::Orthographic;
    this->FieldOfView = 90.00f;
}

void UEndCanvasPanel::SetProjectionMode(TEnumAsByte<ECameraProjectionMode::Type> InProjectionMode) {
}

void UEndCanvasPanel::SetFieldOfView(float InFieldOfView) {
}

void UEndCanvasPanel::SetExplicitChildZOrder(bool bInExplicitChildZOrder) {
}

void UEndCanvasPanel::SetContentColorAndOpacity(FLinearColor InContentColorAndOpacity) {
}

UEndCanvasPanelSlot* UEndCanvasPanel::AddChildToCanvas(UWidget* Content) {
    return NULL;
}


