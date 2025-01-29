#include "EndCondorFortATBGauge.h"

UEndCondorFortATBGauge::UEndCondorFortATBGauge() {
    this->ATB_Gauge_ScaleMark_Width_Default = 2.00f;
}

FVector2D UEndCondorFortATBGauge::OnMeasureItem_GaugeDivisions(int32 ItemIndex) {
    return FVector2D{};
}


