#include "EndNaviMapStateRenderTarget.h"

UEndNaviMapStateRenderTarget::UEndNaviMapStateRenderTarget() {
    this->Filter = TF_Nearest;
    this->AddressX = TA_Clamp;
    this->AddressY = TA_Clamp;
}

void UEndNaviMapStateRenderTarget::SetVisited(int32 X, int32 Y, bool bSyncTexture) {
}

void UEndNaviMapStateRenderTarget::SetPixel(int32 X, int32 Y, FColor Color) {
}

bool UEndNaviMapStateRenderTarget::IsVisited(int32 X, int32 Y) {
    return false;
}

FColor UEndNaviMapStateRenderTarget::GetPixel(int32 X, int32 Y) {
    return FColor{};
}


