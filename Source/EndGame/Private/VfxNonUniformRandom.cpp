#include "VfxNonUniformRandom.h"

FVfxNonUniformRandom::FVfxNonUniformRandom() {
    this->m_Kind = EVfxNonUniformKind::None;
    this->m_Param = 0.00f;
    this->m_bReverse = false;
}

