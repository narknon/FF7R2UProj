#include "EndBikeCharacterComponent.h"

UEndBikeCharacterComponent::UEndBikeCharacterComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->BikeMovementSetting = NULL;
    this->CurrentBikeController = NULL;
    this->BikePlayerControllerClass = NULL;
    this->BikeAIController = NULL;
}


