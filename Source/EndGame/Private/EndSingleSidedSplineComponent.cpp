#include "EndSingleSidedSplineComponent.h"

UEndSingleSidedSplineComponent::UEndSingleSidedSplineComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    const FProperty* p_bClosedLoop = GetClass()->FindPropertyByName("bClosedLoop");
    (*p_bClosedLoop->ContainerPtrToValuePtr<bool>(this)) = true;
    this->bValidRightSide = true;
}


