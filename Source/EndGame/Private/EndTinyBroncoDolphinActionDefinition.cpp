#include "EndTinyBroncoDolphinActionDefinition.h"

FEndTinyBroncoDolphinActionDefinition::FEndTinyBroncoDolphinActionDefinition() {
    this->ActionType = EEndTinyBroncoDolphinActionType::SimpleJump;
    this->BaseLifeTime = 0.00f;
    this->AddLifeTimeRandom = 0.00f;
}

