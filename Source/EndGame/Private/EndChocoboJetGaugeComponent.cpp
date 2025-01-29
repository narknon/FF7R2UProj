#include "EndChocoboJetGaugeComponent.h"

UEndChocoboJetGaugeComponent::UEndChocoboJetGaugeComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->SubclassJetGauge = NULL;
    this->SubclassJetGaugeCircle = NULL;
    this->JetGaugeWidget = NULL;
    this->JetGaugeElement = NULL;
    this->JetGaugeCircleElement = NULL;
    this->bIsGaugeTypeCircle = false;
    this->JetGaugeHeight = 200.00f;
}


