#include "EndEffectComponent.h"

UEndEffectComponent::UEndEffectComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->m_Category = EEndEffectCategory::None;
    this->m_Luminance = 1.00f;
    this->m_Opacity = 1.00f;
}


