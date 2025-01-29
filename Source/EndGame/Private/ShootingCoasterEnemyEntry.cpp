#include "ShootingCoasterEnemyEntry.h"

FShootingCoasterEnemyEntry::FShootingCoasterEnemyEntry() {
    this->bIsTypeA = false;
    this->bIsTypeB = false;
    this->bIsTypeC = false;
    this->bIsTypeD = false;
    this->bIsTypeE = false;
    this->EnemyTypeID = 0;
    this->AttachSpline = NULL;
    this->SpawnDistance = 0.00f;
    this->Arrow = NULL;
    this->ShootStartDistance = 0.00f;
    this->ShootEndDistance = 0.00f;
    this->StopAtDistance = 0.00f;
    this->AttachSplinePhase2 = NULL;
}

