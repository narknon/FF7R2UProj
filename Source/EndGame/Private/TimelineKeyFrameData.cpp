#include "TimelineKeyFrameData.h"

FTimelineKeyFrameData::FTimelineKeyFrameData() {
    this->DistanceBetweenThisAndNextPoint = 0.00f;
    this->Time = 0.00f;
    this->CurveType = ETimelineMovementType::Straight;
}

