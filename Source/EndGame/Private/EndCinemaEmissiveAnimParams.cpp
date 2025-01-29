#include "EndCinemaEmissiveAnimParams.h"

FEndCinemaEmissiveAnimParams::FEndCinemaEmissiveAnimParams() {
    this->bPreviewOnly = false;
    this->StoryFlagCondition = false;
    this->Modifier = EEndAnimationModifierType::Overlay;
    this->Curve = EEndAnimationCurveType::ZeroLoop;
    this->CurveAsset = NULL;
    this->Duration = 0.00f;
    this->BlendInTime = 0.00f;
    this->BlendOutTime = 0.00f;
    this->bCallStopOnEnd = false;
}

