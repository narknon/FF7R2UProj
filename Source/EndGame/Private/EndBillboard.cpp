#include "EndBillboard.h"

UEndBillboard::UEndBillboard() {
    this->DrawAs = ESlateBrushDrawType::Image;
    this->Tiling = ESlateBrushTileType::NoTile;
    this->BlendMode = BLEND_Translucent;
    this->bAutoLoad = false;
    this->Throbber = NULL;
    this->MovieMaterial = NULL;
}

void UEndBillboard::SetOpacity(float InOpacity) {
}

void UEndBillboard::SetImagePath(FSoftObjectPath InImagePath, bool bInRewind, bool bInLoop) {
}

void UEndBillboard::SetImageAssetNameString(const FString& InAssetName, bool bInRewind, bool bInLoop) {
}

void UEndBillboard::SetImageAssetName(FName InAssetName, bool bInRewind, bool bInLoop) {
}

void UEndBillboard::SetColorAndOpacity(FLinearColor InColorAndOpacity) {
}

void UEndBillboard::SetBlendMode(TEnumAsByte<EBlendMode> InBlendMode) {
}

FSoftObjectPath UEndBillboard::MakeImagePathFromAssetNameString(const FString& InAssetName) {
    return FSoftObjectPath{};
}

FSoftObjectPath UEndBillboard::MakeImagePathFromAssetName(FName InAssetName) {
    return FSoftObjectPath{};
}


