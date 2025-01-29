#include "EndBTDecorator_CheckTargetAttributeBuffResist.h"

UEndBTDecorator_CheckTargetAttributeBuffResist::UEndBTDecorator_CheckTargetAttributeBuffResist() {
    this->NodeName = TEXT("[End][AIPC]CheckTargetAttributeBuffResist");
    this->Operator = EEndAiMathCmp::Equal;
    this->ResistType = EEndBattleAttributeResistType::None;
}


