#include "EndCoordinateAnimationPreviewSettings.h"

FEndCoordinateAnimationPreviewSettings::FEndCoordinateAnimationPreviewSettings() {
    this->CurveType = EEndAnimationCurveType::ZeroLoop;
    this->bLoop = false;
    this->TimelineScale = 0.00f;
}

