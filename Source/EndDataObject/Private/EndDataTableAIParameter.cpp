#include "EndDataTableAIParameter.h"

FEndDataTableAIParameter::FEndDataTableAIParameter() {
    this->Movable = 0;
    this->HitWall = 0;
    this->HitObject = 0;
    this->HitSelfReaction = 0;
    this->HitOthersReaction = 0;
    this->FitFloor = 0;
    this->MaxWeight = 0;
    this->DisableTickPause = 0;
    this->EnableSafeTransform = 0;
    this->ForceTurn = 0;
    this->InterpolationMove = 0;
    this->WalkRange = 0;
    this->GoalRadius = 0;
    this->FollowUpDashDistance = 0.00f;
    this->ForceWalk = 0;
    this->FlightMaxSpeed = 0.00f;
    this->FlightAcceleration = 0.00f;
    this->NoOverTaking = 0;
    this->NoOverTakingDistance = 0.00f;
    this->StopDistance = 0.00f;
    this->LeadTurn = 0;
    this->RangeRadius = 0.00f;
    this->StayTimeMIn = 0;
    this->StayTimeRand = 0;
    this->TurnBackDistance = 0.00f;
    this->MoveStartDistance = 0.00f;
}

