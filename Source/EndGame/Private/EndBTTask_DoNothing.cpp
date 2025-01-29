#include "EndBTTask_DoNothing.h"

UEndBTTask_DoNothing::UEndBTTask_DoNothing() {
    this->NodeName = TEXT("[End]DoNothing");
    this->m_SelectionType = EBTNodeResult::InProgress;
}


