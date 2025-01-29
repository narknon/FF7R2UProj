#include "EndDataTableResponseArea.h"

FEndDataTableResponseArea::FEndDataTableResponseArea() {
    this->ReactionRangeSquare = 0.00f;
    this->SugessionRange = 0.00f;
    this->SugessionRangeSquare = 0.00f;
    this->ReactionAngle = 0.00f;
    this->SugessionAngle = 0.00f;
    this->NeedRaycast = 0;
    this->NeedScreenSpace = 0;
    this->NeedNaviCheck = 0;
    this->ReactionScreenRatioX = 0.00f;
    this->ReactionScreenRatioY = 0.00f;
    this->SugessionScreenRatioX = 0.00f;
    this->SugessionScreenRatioY = 0.00f;
    this->NeedZAngleCheck = 0;
    this->MaxZDistance = 0.00f;
    this->ReactionInEllipse = 0;
}

