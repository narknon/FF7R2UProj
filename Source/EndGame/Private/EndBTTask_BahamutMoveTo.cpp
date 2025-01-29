#include "EndBTTask_BahamutMoveTo.h"

UEndBTTask_BahamutMoveTo::UEndBTTask_BahamutMoveTo() {
    this->NodeName = TEXT("[End]Bahamut Move To");
    this->NavQueryFilterType = EEndQueryFilterType::Battle;
    this->ArrivalRadius = 300.00f;
    this->StopMoveWhenFinished = true;
    this->MoveRequestBlackBoardName = TEXT("MoveRequest");
    this->HeightTolerance = 30.00f;
    this->HeightAdjustTolerance = 100.00f;
    this->FilterClass = NULL;
    this->StuckTimeLimit = 0.50f;
    this->MoveTimeLimit = 5.00f;
}


