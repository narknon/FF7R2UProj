#include "EndCinemaWidgetControlComponent.h"

UEndCinemaWidgetControlComponent::UEndCinemaWidgetControlComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->WidgetAsset = NULL;
    this->LogicalOperator = EEndCutLogicalOperator::AND;
    this->AnimName = TEXT("In");
    this->AnimPosition = 0.00f;
    this->WidgetVisibility = ESlateVisibility::Hidden;
}


