#include "EndMobPrefabAllowContactExecuteCommand.h"

UEndMobPrefabAllowContactExecuteCommand::UEndMobPrefabAllowContactExecuteCommand() {
    this->bAllowedDuringPlayMotion = true;
    this->ContactMotionBlendTime = 0.10f;
    this->PropagateMotionBlendTime = 0.50f;
    this->OutBlendTime = 0.00f;
}


