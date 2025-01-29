#include "EndBTTask_MoveTo.h"

UEndBTTask_MoveTo::UEndBTTask_MoveTo() {
    this->NodeName = TEXT("[End]MoveTo");
    this->bUseBlackboardMoveType = false;
    this->MoveType = EEndAiMoveType::RUN;
    this->NavQueryFilterType = EEndQueryFilterType::Battle;
    this->ArrivalRadius = 50.00f;
    this->PathFindInterval = 0.50f;
    this->IsStrafe = false;
    this->IsFixMove = false;
    this->IsFixMoveFull = false;
    this->IsPathFind = true;
    this->IsPathCorrection = false;
    this->IsForceGroundPath = false;
    this->IsUseGroundPathWhenExist = false;
    this->BlendTime = 0.00f;
    this->bSelectNavPropertyByList = false;
    this->UseNormalProperties = false;
    this->AIMoveNavPropertyType = EEndAIMoveNavPropertyType::Character;
    this->StopMoveWhenFinished = true;
    this->AdjustLocationHeightOnFloorNavmesh = false;
    this->DistanceSwitchWalkMode = -1.00f;
    this->MoveRequestBlackBoardName = TEXT("MoveRequest");
}


