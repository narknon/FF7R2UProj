#include "EndNaviMapCircle.h"
#include "Layout/Clipping.h"

UEndNaviMapCircle::UEndNaviMapCircle() {
    this->bIsVariable = false;
    this->Clipping = EWidgetClipping::ClipToBounds;
    this->PixelPerCm = 0.08f;
    this->NumSides = 32;
    this->PrototypeDataV2 = NULL;
    this->RenderTexture = NULL;
    this->MaskTexture = NULL;
}

void UEndNaviMapCircle::SetPosition3D(const FVector& InPos) {
}

FVector2D UEndNaviMapCircle::ConvertToPosition2D(const FVector& InPos) {
    return FVector2D{};
}


