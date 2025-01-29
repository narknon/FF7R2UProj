#include "EndNaviMap.h"
#include "Layout/Clipping.h"

UEndNaviMap::UEndNaviMap() {
    this->bIsVariable = false;
    this->Clipping = EWidgetClipping::ClipToBounds;
    this->PixelPerCm = 0.08f;
    this->PrototypeDataV2 = NULL;
    this->MaskTexture = NULL;
}

void UEndNaviMap::SetPosition3D(const FVector& InPos) {
}

FVector2D UEndNaviMap::ConvertToPosition2D(const FVector& InPos) {
    return FVector2D{};
}


