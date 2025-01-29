#include "EndNaviMapOctagon.h"
#include "Layout/Clipping.h"

UEndNaviMapOctagon::UEndNaviMapOctagon() {
    this->bIsVariable = false;
    this->Clipping = EWidgetClipping::ClipToBounds;
    this->PixelPerCm = 0.08f;
    this->PrototypeDataV2 = NULL;
    this->RenderTexture = NULL;
    this->MaskTexture = NULL;
}

void UEndNaviMapOctagon::SetPosition3D(const FVector& InPos) {
}

FVector2D UEndNaviMapOctagon::ConvertToPosition2D(const FVector& InPos) {
    return FVector2D{};
}


