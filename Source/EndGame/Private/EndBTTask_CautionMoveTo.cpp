#include "EndBTTask_CautionMoveTo.h"

UEndBTTask_CautionMoveTo::UEndBTTask_CautionMoveTo() {
    this->CautionMoveKind = ECautionMoveKind::ApproachOrLeave;
    this->bFixLocationInRequestedMoveTo = false;
}


