#include "EndPieImage.h"

UEndPieImage::UEndPieImage() {
    this->BlendMode = BLEND_Translucent;
    this->StartAngle = 0.00f;
    this->EndAngle = 360.00f;
}

void UEndPieImage::SetStartAngle(float InAngle) {
}

void UEndPieImage::SetOpacity(float InOpacity) {
}

void UEndPieImage::SetEndAngle(float InAngle) {
}

void UEndPieImage::SetColorAndOpacity(FLinearColor InColorAndOpacity) {
}

void UEndPieImage::SetBrushFromTextureDynamic(UTexture2DDynamic* Texture, bool bMatchSize) {
}

void UEndPieImage::SetBrushFromTexture(UTexture2D* Texture, bool bMatchSize) {
}

void UEndPieImage::SetBrushFromMaterial(UMaterialInterface* Material) {
}

void UEndPieImage::SetBrushFromAsset(USlateBrushAsset* Asset) {
}

void UEndPieImage::SetBrush(const FSlateBrush& InBrush) {
}

void UEndPieImage::SetBlendMode(TEnumAsByte<EBlendMode> InBlendMode) {
}

UMaterialInstanceDynamic* UEndPieImage::GetDynamicMaterial() {
    return NULL;
}


