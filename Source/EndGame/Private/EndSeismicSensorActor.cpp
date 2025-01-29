#include "EndSeismicSensorActor.h"

AEndSeismicSensorActor::AEndSeismicSensorActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->_ConcurrencyAsset = NULL;
    this->PositiveSE = NULL;
    this->NegativeSE = NULL;
    this->BeepSE = NULL;
}


