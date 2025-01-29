#include "EndBTTask_FindGroundLocation.h"

UEndBTTask_FindGroundLocation::UEndBTTask_FindGroundLocation() {
    this->NodeName = TEXT("[End]FindGroundLocation");
    this->GroundLocationBlackBoardName = TEXT("MoveToLocation");
    this->TraceDistanceToGround = 3000.00f;
}


