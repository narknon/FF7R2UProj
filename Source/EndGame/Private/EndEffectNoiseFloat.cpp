#include "EndEffectNoiseFloat.h"

UEndEffectNoiseFloat::UEndEffectNoiseFloat() {
    this->bCanBeBaked = false;
    this->m_InterpolateKind = EEndEffectInterpolateKind::EaseInOut;
    this->m_RandomSeed = 0;
}


