#include "EndMidgarMenu.h"

UEndMidgarMenu::UEndMidgarMenu() {
    this->ZoomMinDistance = 430.00f;
    this->ZoomMaxDistance = 900.00f;
    this->ZoomDistanceUpperLayerDefault = 600.00f;
    this->ZoomDistanceLowerLayerDefault = 480.00f;
    this->DefaultCurrentLocationAngleOffset = 30.00f;
    this->ResetAnimationLength = 0.50f;
    this->MidgarSectorsAnimationLength = 0.30f;
    this->FadeInOutLenght = 0.20f;
    this->RotationYMin = -40.00f;
    this->RotationYMax = -10.00f;
    this->RotationYDefault = -20.00f;
    this->RotationXDefault = 0.00f;
    this->OutAnimationSpeedUp = 3.00f;
    this->RotationXSpeed = 80.00f;
    this->RotationYSpeed = 80.00f;
    this->ZoomSpeed = 200.00f;
}

void UEndMidgarMenu::ShowLegend(bool Show) {
}


