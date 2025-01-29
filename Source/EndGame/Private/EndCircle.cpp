#include "EndCircle.h"

UEndCircle::UEndCircle() {
    this->BlendMode = BLEND_Translucent;
    this->Radius = 50.00f;
    this->NumSides = 32;
    this->StartAngle = 0.00f;
    this->EndAngle = 360.00f;
}

void UEndCircle::SetStartAngle(float InAngle) {
}

void UEndCircle::SetRadius(float InRadius) {
}

void UEndCircle::SetOpacity(float InOpacity) {
}

void UEndCircle::SetNumSides(int32 InNumSides) {
}

void UEndCircle::SetEndAngle(float InAngle) {
}

void UEndCircle::SetColorAndOpacity(FLinearColor InColorAndOpacity) {
}

void UEndCircle::SetBrushFromTextureDynamic(UTexture2DDynamic* Texture, bool bMatchSize) {
}

void UEndCircle::SetBrushFromTexture(UTexture2D* Texture, bool bMatchSize) {
}

void UEndCircle::SetBrushFromMaterial(UMaterialInterface* Material) {
}

void UEndCircle::SetBrushFromAsset(USlateBrushAsset* Asset) {
}

void UEndCircle::SetBrush(const FSlateBrush& InBrush) {
}

void UEndCircle::SetBlendMode(TEnumAsByte<EBlendMode> InBlendMode) {
}

UMaterialInstanceDynamic* UEndCircle::GetDynamicMaterial() {
    return NULL;
}


