#include "EndFieldGridActor.h"
#include "Components/ArrowComponent.h"

AEndFieldGridActor::AEndFieldGridActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->SaveFlow = true;
    this->SaveNormal = false;
    this->UnitLength = 100.00f;
    this->RawGridNumX = 100;
    this->RawGridNumY = 100;
    this->RawGridNumZ = 50;
    this->MergeNum = 1;
    this->GridNumX = 100;
    this->GridNumY = 100;
    this->GridNumZ = 20;
    this->FlowSpeed = 500.00f;
    this->SurfaceRange = 500.00f;
    this->StepNum = 3;
    this->ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
    this->ArrowComponent->SetupAttachment(RootComponent);
}


