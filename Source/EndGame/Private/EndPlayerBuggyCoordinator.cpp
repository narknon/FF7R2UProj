#include "EndPlayerBuggyCoordinator.h"

UEndPlayerBuggyCoordinator::UEndPlayerBuggyCoordinator() {
    this->VehicleChara = NULL;
    this->MainRiderChara = NULL;
    this->BattleEscapeSplineActor = NULL;
}

AActor* UEndPlayerBuggyCoordinator::GetVehicleCharacter() const {
    return NULL;
}

AEndCharacterBase* UEndPlayerBuggyCoordinator::GetRiderCharacter(int32 Index) const {
    return NULL;
}


