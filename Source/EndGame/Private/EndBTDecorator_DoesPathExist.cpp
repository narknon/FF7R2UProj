#include "EndBTDecorator_DoesPathExist.h"

UEndBTDecorator_DoesPathExist::UEndBTDecorator_DoesPathExist() {
    this->NodeName = TEXT("[End]DoesPathExist");
    this->bUseCharacterFloorLocation = true;
    this->bProjectionFromPoint = false;
    this->bProjectionToPoint = false;
    this->FilterType = EEndQueryFilterType::Default;
    this->bUseNormalProperties = true;
}


