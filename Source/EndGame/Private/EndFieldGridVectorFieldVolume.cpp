#include "EndFieldGridVectorFieldVolume.h"
#include "Components/VectorFieldComponent.h"

AEndFieldGridVectorFieldVolume::AEndFieldGridVectorFieldVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->VectorFieldComponent = CreateDefaultSubobject<UVectorFieldComponent>(TEXT("VectorFieldComponent0"));
    this->m_UnitLength = 150.00f;
}


